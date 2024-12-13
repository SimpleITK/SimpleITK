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

#include <sitkImage.h>
#include <sitkComposeImageFilter.h>
#include <sitkPasteImageFilter.h>
#include <sitkVectorIndexSelectionCastImageFilter.h>
#include <sitkMinimumMaximumImageFilter.h>
#include <sitkShow.h>
#include <sitkExtractImageFilter.h>

TEST(Compose2220, X)
{namespace sitk = itk::simple;

  const unsigned int size = 400;
  const unsigned int nchannels = 100;
  std::vector<sitk::Image> images;

  for (unsigned int i = 0; i < nchannels; ++i) {
    sitk::Image d({size, size, size}, sitk::sitkUInt8);
    itk::simple::PasteImageFilter paster;
    paster.SetSourceSize({size, size, 1});
    paster.SetDestinationIndex({0, 0, int(i)});
    d = paster.Execute(d, i%250);
    images.push_back(d);

  }

  sitk::ComposeImageFilter filter;
  filter.SetDebug(true);
  sitk::Image img = filter.Execute(images);
  std::cout << filter.ToString() << std::endl;
  std::cout <<"check\n" << std::endl;

  for (unsigned int i = 0; i < nchannels; ++i) {
    // extract the i-th z-slice form img;
    auto slice = sitk::Extract(img, {size, size, 0},
                               {0, 0, int(i)});

    sitk::Image component = sitk::VectorIndexSelectionCast(slice, i);
    sitk::MinimumMaximumImageFilter minMaxFilter;
    minMaxFilter.Execute(component);
    EXPECT_TRUE(
        (minMaxFilter.GetMinimum() == i%250 || minMaxFilter.GetMaximum() == i%250))
        << "compose filter: problem with component " << i
        << " min: " << minMaxFilter.GetMinimum()
        << " max: " << minMaxFilter.GetMaximum() << std::endl;
  }
}
