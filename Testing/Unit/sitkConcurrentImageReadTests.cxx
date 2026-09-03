/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include <SimpleITKTestHarness.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkGaussianImageSource.h>

#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <vector>

namespace
{
namespace sitk = itk::simple;

// Per-thread progress marker so a hang can be localized to a specific
// thread/iteration/file without needing to attach a debugger.
struct WorkerProgress
{
  std::atomic<unsigned int> iteration{ 0 };
  std::atomic<unsigned int> fileIndex{ 0 };
  std::atomic<bool>         finished{ false };
};

// Generates "n" square Gaussian-blob images of the given pixel type and
// writes each to outputDir/g_<i>.<ext>, returning the list of file names.
std::vector<std::string>
CreateConcurrentReadTestData(const std::string &    outputDir,
                             const std::string &    ext,
                             sitk::PixelIDValueEnum pixelType,
                             unsigned int           n = 64,
                             unsigned int           size = 128)
{
  std::vector<std::string> files;
  files.reserve(n);

  for (unsigned int i = 0; i < n; ++i)
  {
    const double mean = 4.0 * (i + 1);

    sitk::GaussianImageSource gaussian;
    gaussian.SetSize({ size, size });
    gaussian.SetMean({ mean, mean });
    gaussian.SetSigma({ size / 8.0, size / 8.0 });
    gaussian.SetScale(255);
    gaussian.SetOutputPixelType(pixelType);
    const sitk::Image image = gaussian.Execute();

    std::ostringstream fname;
    fname << outputDir << "/g_" << i << "." << ext;
    sitk::WriteImage(image, fname.str());
    files.push_back(fname.str());
  }
  return files;
}

// Stresses concurrent reads of "files" using "nThreads" worker threads, each
// independently looping over the *entire* file list "repeat" times (so the
// same files are hit concurrently by many threads, maximizing contention on
// any shared/global state inside the ImageIO). Every image read is verified
// against an expected pixel buffer computed once, single-threaded, up front.
//
// If the operation does not complete within timeoutSeconds, this dumps the
// per-thread progress table (to localize the hang) and aborts the process so
// a debugger/core file can capture native thread stacks. Returns a
// human-readable failure message, or an empty string on success.
std::string
ConcurrentReadStressTest(const std::vector<std::string> & files,
                         sitk::PixelIDValueEnum           pixelType,
                         unsigned int                     nThreads,
                         unsigned int                     repeat,
                         unsigned int                     timeoutSeconds)
{
  // Compute the expected pixel buffer for each file with a single-threaded reference read.
  std::vector<std::vector<uint8_t>> expectedBytes(files.size());
  for (size_t i = 0; i < files.size(); ++i)
  {
    const sitk::Image img = sitk::ReadImage(files[i]);
    const auto *      buf = static_cast<const uint8_t *>(const_cast<sitk::Image &>(img).GetBufferAsVoid());
    const size_t      bufferSize =
      img.GetNumberOfPixels() * img.GetSizeOfPixelComponent() * img.GetNumberOfComponentsPerPixel();
    expectedBytes[i].assign(buf, buf + bufferSize);
  }

  std::mutex                  errorMutex;
  std::vector<std::string>    errors;
  std::vector<WorkerProgress> progress(nThreads);
  std::atomic<size_t>         successfulReads{ 0 };

  auto worker = [&repeat, &progress, &files, &pixelType, &errorMutex, &errors, &expectedBytes, &successfulReads](
                  unsigned int threadId) {
    for (unsigned int r = 0; r < repeat; ++r)
    {
      progress[threadId].iteration = r;
      for (size_t i = 0; i < files.size(); ++i)
      {
        progress[threadId].fileIndex = static_cast<unsigned int>(i);
        try
        {
          const sitk::Image img = sitk::ReadImage(files[i]);
          const auto *      buf = static_cast<const uint8_t *>(const_cast<sitk::Image &>(img).GetBufferAsVoid());
          const size_t      bufferSize = img.GetNumberOfPixels() * img.GetSizeOfPixelComponent();
          const std::vector<uint8_t> bytes(buf, buf + bufferSize);
          if (bytes != expectedBytes[i])
          {
            std::lock_guard<std::mutex> lock(errorMutex);
            errors.push_back("thread " + std::to_string(threadId) + " iter " + std::to_string(r) + " file " + files[i] +
                             ": pixel buffer mismatch");
          }
          else
          {
            ++successfulReads;
          }
        }
        catch (const std::exception & e)
        {
          std::lock_guard<std::mutex> lock(errorMutex);
          errors.push_back("thread " + std::to_string(threadId) + " iter " + std::to_string(r) + " file " + files[i] +
                           " threw: " + e.what());
        }
      }
    }
    progress[threadId].finished = true;
  };

  std::vector<std::thread> workers;
  workers.reserve(nThreads);
  for (unsigned int t = 0; t < nThreads; ++t)
  {
    workers.emplace_back(worker, t);
  }

  // Joiner thread so the main thread can poll for a timeout without blocking
  // on join() itself.
  std::atomic<bool> allJoined{ false };
  std::thread       joiner([&workers, &allJoined]() {
    for (auto & w : workers)
    {
      w.join();
    }
    allJoined = true;
  });

  const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds);
  while (!allJoined)
  {
    if (std::chrono::steady_clock::now() > deadline)
    {
      std::ostringstream msg;
      msg << "TIMEOUT: concurrent read did not complete within " << timeoutSeconds << "s. Per-thread progress:\n";
      for (unsigned int t = 0; t < nThreads; ++t)
      {
        msg << "  thread " << t << ": iteration=" << progress[t].iteration << " fileIndex=" << progress[t].fileIndex
            << " (" << files[progress[t].fileIndex] << ")"
            << " finished=" << (progress[t].finished ? "true" : "false") << '\n';
      }
      std::cerr << msg.str() << std::flush;
      // Abort (rather than leak the stuck threads and return) so a debugger
      // or core file captures the native thread backtraces at the point of
      // the hang.
      std::abort();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  joiner.join();

  if (errors.empty())
  {
    std::ostringstream msg;
    msg << "SUCCESS: " << successfulReads << " concurrent reads completed";
    return msg.str();
  }
  std::ostringstream msg;
  msg << "FAILED: " << errors.size() << " error(s) after " << successfulReads << " successful reads:\n";
  for (const auto & e : errors)
  {
    msg << "  " << e << '\n';
  }
  return msg.str();
}

void
RunConcurrentImageReadTest(const std::string & ext, sitk::PixelIDValueEnum pixelType)
{
  const std::string  outputDir = dataFinder.GetOutputDirectory();
  const unsigned int numFiles = 16;

  const std::vector<std::string> files = CreateConcurrentReadTestData(outputDir, ext, pixelType, numFiles);

  // Fixed (not scaled off std::thread::hardware_concurrency()) so this runs
  // with consistent, CI-appropriate load regardless of how many cores the
  // build machine has -- enough concurrency to reproduce contention in the
  // ImageIO stack, without spawning an unbounded number of threads on
  // many-core machines.
  const unsigned int nThreads = 16;
  const unsigned int repeat = 4;
  const unsigned int timeoutSeconds = 60;

  const std::string result = ConcurrentReadStressTest(files, pixelType, nThreads, repeat, timeoutSeconds);
  std::cout << result << std::endl;
  EXPECT_TRUE(result.find("SUCCESS") == 0) << result;
}

} // namespace

TEST(ConcurrentImageRead, JPEG) { RunConcurrentImageReadTest("jpg", sitk::sitkUInt8); }

TEST(ConcurrentImageRead, TIFF) { RunConcurrentImageReadTest("tiff", sitk::sitkUInt16); }

TEST(ConcurrentImageRead, PNG) { RunConcurrentImageReadTest("png", sitk::sitkUInt16); }

TEST(ConcurrentImageRead, NIFTI) { RunConcurrentImageReadTest("nii", sitk::sitkUInt32); }

TEST(ConcurrentImageRead, MetaImage) { RunConcurrentImageReadTest("mha", sitk::sitkUInt32); }
