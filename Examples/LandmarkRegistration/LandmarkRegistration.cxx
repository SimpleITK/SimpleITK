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

/// A SimpleITK example demonstrating landmark registration.

#include <SimpleITK.h>
#include <iostream>
#include <vector>

namespace sitk = itk::simple;

int
main(int argc, char * argv[])
{
  using sitk::operator<<;

  // Black image with a small white square in it.
  sitk::Image fixedImage(100, 100, sitk::sitkUInt8);
  // Set pixels in rectangle [11:20, 11:20] to 200
  for (unsigned int x = 11; x < 20; ++x)
  {
    for (unsigned int y = 11; y < 20; ++y)
    {
      fixedImage.SetPixelAsUInt8({ x, y }, 200);
    }
  }

  // Black image with a small grey square at a different location.
  sitk::Image movingImage(100, 100, sitk::sitkUInt8);
  // Set pixels in rectangle [51:60, 51:60] to 69
  for (unsigned int x = 51; x < 60; ++x)
  {
    for (unsigned int y = 51; y < 60; ++y)
    {
      movingImage.SetPixelAsUInt8({ x, y }, 69);
    }
  }

  // Landmarks are 3 corners of the squares.
  // 3 (X, Y) pairs are flattened into 1-d lists.
  std::vector<double> fixedLandmarks = { 10, 10, 20, 10, 20, 20 };
  std::vector<double> movingLandmarks = { 50, 50, 60, 50, 60, 60 };

  // Set up the LandmarkBasedTransformInitializerFilter.
  sitk::LandmarkBasedTransformInitializerFilter landmarkInitializer;

  landmarkInitializer.SetFixedLandmarks(fixedLandmarks);
  landmarkInitializer.SetMovingLandmarks(movingLandmarks);

  sitk::Transform transform = sitk::Euler2DTransform();

  // Compute the transform.
  sitk::Transform outputTransform = landmarkInitializer.Execute(transform);

  std::cout << outputTransform.ToString() << std::endl;

  // Resample the transformed moving image onto the fixed image.
  sitk::Image outputImage = sitk::Resample(movingImage, fixedImage, outputTransform, sitk::sitkLinear, 150);

  // Write the resampled image.
  sitk::WriteImage(outputImage, "landmark_example.png");

  // Write the transform.
  std::string outName;
  if (argc > 1)
  {
    outName = argv[1];
  }
  else
  {
    outName = "landmark_transform.tfm";
  }

  sitk::WriteTransform(outputTransform, outName);

  return 0;
}
