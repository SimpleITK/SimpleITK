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
#include <sitkGaussianImageSource.h>
#include <sitkHashImageFilter.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>

#include <future>
#include <vector>

namespace
{
namespace sitk = itk::simple;

void
RunConcurrentImageReadTest(const std::string & ext, sitk::PixelIDValueEnum pixelType)
{
  std::vector<std::string> files;
  std::vector<std::string> expectedHashes;
  for (unsigned int index = 0; index < 16; ++index)
  {
    const double mean = 4.0 * (index + 1);
    const auto   image = sitk::GaussianSource(pixelType, { 128, 128 }, { 16.0, 16.0 }, { mean, mean });
    const auto   filename = dataFinder.GetOutputDirectory() + "/g_" + std::to_string(index) + "." + ext;
    sitk::WriteImage(image, filename);
    files.push_back(filename);
    expectedHashes.push_back(sitk::Hash(sitk::ReadImage(filename)));
  }

  constexpr unsigned int         numThreads = 16;
  std::vector<std::future<void>> workers;
  for (unsigned int threadIndex = 0; threadIndex < numThreads; ++threadIndex)
  {
    workers.push_back(std::async(std::launch::async, [&]() {
      for (unsigned int iteration = 0; iteration < 4; ++iteration)
      {
        for (size_t index = 0; index < files.size(); ++index)
        {
          EXPECT_EQ(expectedHashes[index], sitk::Hash(sitk::ReadImage(files[index]))) << files[index];
        }
      }
    }));
  }
  for (auto & worker : workers)
  {
    EXPECT_NO_THROW(worker.get());
  }
}

} // namespace

TEST(ConcurrentImageRead, JPEG) { RunConcurrentImageReadTest("jpg", sitk::sitkUInt8); }

TEST(ConcurrentImageRead, TIFF) { RunConcurrentImageReadTest("tiff", sitk::sitkUInt16); }

TEST(ConcurrentImageRead, PNG) { RunConcurrentImageReadTest("png", sitk::sitkUInt16); }

TEST(ConcurrentImageRead, NIFTI) { RunConcurrentImageReadTest("nii", sitk::sitkUInt32); }

TEST(ConcurrentImageRead, MetaImage) { RunConcurrentImageReadTest("mha", sitk::sitkUInt32); }

TEST(ConcurrentImageRead, DICOM) { RunConcurrentImageReadTest("dcm", sitk::sitkUInt32); }
