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

// This one header will include all SimpleITK filters and external
// objects.
#include <SimpleITK.h>
#include <iostream>
#include <stdlib.h>

namespace sitk = itk::simple;

int
main(int argc, char * argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << argv[0] << " <input-1> <input-2>" << std::endl;
    return 1;
  }

  // Two vector images of same pixel type and dimension expected
  sitk::Image image1 = sitk::ReadImage(argv[1]);
  sitk::Image image2 = sitk::ReadImage(argv[2]);

  // Join two N-D Vector images to form an (N+1)-D image
  sitk::JoinSeriesImageFilter join;
  sitk::Image                 joinedImage = join.Execute(image1, image2);

  // Extract first three channels of joined image (assuming RGB)
  sitk::VectorIndexSelectionCastImageFilter select;
  select.SetOutputPixelType(sitk::sitkUInt8);

  select.SetIndex(0);
  sitk::Image channel1Image = select.Execute(joinedImage);
  select.SetIndex(1);
  sitk::Image channel2Image = select.Execute(joinedImage);
  select.SetIndex(2);
  sitk::Image channel3Image = select.Execute(joinedImage);

  // Recompose image (should be same as joined_image)
  sitk::ComposeImageFilter compose;
  sitk::Image              composedImage = compose.Execute(channel1Image, channel2Image, channel3Image);

  // Select same subregion using ExtractImageFilter
  sitk::ExtractImageFilter extract;
  extract.SetSize({ 30, 30, 0 });
  extract.SetIndex({ 10, 10, 0 });
  sitk::Image extractedImage = extract.Execute(composedImage);

  // Select same sub-region using CropImageFilter (NOTE: CropImageFilter cannot
  // reduce dimensions unlike ExtractImageFilter, so cropped_image is a three
  // dimensional image with depth of 1)
  sitk::CropImageFilter crop;
  crop.SetLowerBoundaryCropSize({ 10, 10, 0 });
  crop.SetUpperBoundaryCropSize({ composedImage.GetWidth() - 40, composedImage.GetHeight() - 40, 1 });
  sitk::Image croppedImage = crop.Execute(composedImage);

  return 0;
}
