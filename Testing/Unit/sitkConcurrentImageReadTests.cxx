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

// Native (non-Python) reproduction of the intermittent hang seen in
// Wrapping/Python/tests/ConcurrentImageRead.py, which is labeled UNSTABLE on
// APPLE (see Wrapping/Python/tests/CMakeLists.txt). Because this stresses
// itk::simple::ReadImage from plain std::thread workers, any hang here is in
// the ITK ImageIO stack itself, not in the SWIG/GIL layer. Run this test
// directly under a debugger (e.g. `lldb -- ./SimpleITKUnitTestDriver0
// --gtest_filter='ConcurrentImageRead.*'`) to get native thread backtraces if
// it hangs -- macOS blocks attaching a debugger to an already-running
// process, so launching under the debugger from the start avoids that.

#include <SimpleITKTestHarness.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>

#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
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

// Builds a square image with a synthetic Gaussian-blob pattern centered at
// (meanX, meanY), directly filling the pixel buffer. This avoids pulling in
// any ImageFilter/ImageSource classes so the test only exercises the stable,
// low-level Image and ImageIO API surface.
sitk::Image
CreateGaussianTestImage(unsigned int size, double meanX, double meanY, sitk::PixelIDValueEnum pixelType)
{
  sitk::Image  img(std::vector<unsigned int>{ size, size }, pixelType);
  const double sigma = size / 8.0;

  auto gaussianAt = [&](unsigned int x, unsigned int y) {
    const double dx = static_cast<double>(x) - meanX;
    const double dy = static_cast<double>(y) - meanY;
    return std::exp(-(dx * dx + dy * dy) / (2.0 * sigma * sigma));
  };

  switch (pixelType)
  {
    case sitk::sitkUInt8:
    {
      uint8_t * buf = img.GetBufferAsUInt8();
      for (unsigned int y = 0; y < size; ++y)
      {
        for (unsigned int x = 0; x < size; ++x)
        {
          buf[y * size + x] = static_cast<uint8_t>(gaussianAt(x, y) * 255.0);
        }
      }
      break;
    }
    case sitk::sitkUInt16:
    {
      uint16_t * buf = img.GetBufferAsUInt16();
      for (unsigned int y = 0; y < size; ++y)
      {
        for (unsigned int x = 0; x < size; ++x)
        {
          buf[y * size + x] = static_cast<uint16_t>(gaussianAt(x, y) * 65535.0);
        }
      }
      break;
    }
    case sitk::sitkUInt32:
    {
      uint32_t * buf = img.GetBufferAsUInt32();
      for (unsigned int y = 0; y < size; ++y)
      {
        for (unsigned int x = 0; x < size; ++x)
        {
          buf[y * size + x] = static_cast<uint32_t>(gaussianAt(x, y) * 4294967295.0);
        }
      }
      break;
    }
    default:
      throw std::invalid_argument("CreateGaussianTestImage: unsupported pixel type");
  }
  return img;
}

// Copies out the raw pixel buffer as bytes, for exact equality comparison.
// (HashImageFilter is avoided here: this local build's pixel-type/dimension
// instantiation does not cover 32-bit integer pixels in 2D, so a direct
// buffer comparison is used instead -- it is also a stricter check anyway.)
std::vector<uint8_t>
GetRawBufferBytes(const sitk::Image & img, sitk::PixelIDValueEnum pixelType)
{
  const size_t numPixels = img.GetNumberOfPixels();
  switch (pixelType)
  {
    case sitk::sitkUInt8:
    {
      const auto * buf = const_cast<sitk::Image &>(img).GetBufferAsUInt8();
      return std::vector<uint8_t>(buf, buf + numPixels * sizeof(uint8_t));
    }
    case sitk::sitkUInt16:
    {
      const auto * buf = const_cast<sitk::Image &>(img).GetBufferAsUInt16();
      const auto * begin = reinterpret_cast<const uint8_t *>(buf);
      return std::vector<uint8_t>(begin, begin + numPixels * sizeof(uint16_t));
    }
    case sitk::sitkUInt32:
    {
      const auto * buf = const_cast<sitk::Image &>(img).GetBufferAsUInt32();
      const auto * begin = reinterpret_cast<const uint8_t *>(buf);
      return std::vector<uint8_t>(begin, begin + numPixels * sizeof(uint32_t));
    }
    default:
      throw std::invalid_argument("GetRawBufferBytes: unsupported pixel type");
  }
}

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
    const double      mean = 4.0 * (i + 1);
    const sitk::Image image = CreateGaussianTestImage(size, mean, mean, pixelType);

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
    expectedBytes[i] = GetRawBufferBytes(sitk::ReadImage(files[i]), pixelType);
  }

  std::mutex                  errorMutex;
  std::vector<std::string>    errors;
  std::vector<WorkerProgress> progress(nThreads);

  auto worker = [&](unsigned int threadId) {
    for (unsigned int r = 0; r < repeat; ++r)
    {
      progress[threadId].iteration = r;
      for (size_t i = 0; i < files.size(); ++i)
      {
        progress[threadId].fileIndex = static_cast<unsigned int>(i);
        try
        {
          const std::vector<uint8_t> bytes = GetRawBufferBytes(sitk::ReadImage(files[i]), pixelType);
          if (bytes != expectedBytes[i])
          {
            std::lock_guard<std::mutex> lock(errorMutex);
            errors.push_back("thread " + std::to_string(threadId) + " iter " + std::to_string(r) + " file " + files[i] +
                             ": pixel buffer mismatch");
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
  std::thread       joiner([&]() {
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
    return {};
  }
  std::ostringstream msg;
  msg << errors.size() << " error(s):\n";
  for (const auto & e : errors)
  {
    msg << "  " << e << '\n';
  }
  return msg.str();
}

void
RunConcurrentImageReadTest(const std::string & ext, sitk::PixelIDValueEnum pixelType)
{
  const std::string              outputDir = dataFinder.GetOutputDirectory();
  const std::vector<std::string> files = CreateConcurrentReadTestData(outputDir, ext, pixelType);

  const unsigned int nThreads = std::max(4u, std::thread::hardware_concurrency() * 4);
  const unsigned int repeat = 8;
  const unsigned int timeoutSeconds = 90;

  const std::string result = ConcurrentReadStressTest(files, pixelType, nThreads, repeat, timeoutSeconds);
  EXPECT_TRUE(result.empty()) << result;
}

} // namespace

TEST(ConcurrentImageRead, JPEG) { RunConcurrentImageReadTest("jpg", sitk::sitkUInt8); }

TEST(ConcurrentImageRead, TIFF) { RunConcurrentImageReadTest("tiff", sitk::sitkUInt16); }

TEST(ConcurrentImageRead, PNG) { RunConcurrentImageReadTest("png", sitk::sitkUInt16); }

TEST(ConcurrentImageRead, NIFTI) { RunConcurrentImageReadTest("nii", sitk::sitkUInt32); }

TEST(ConcurrentImageRead, MetaImage) { RunConcurrentImageReadTest("mha", sitk::sitkUInt32); }
