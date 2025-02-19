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
#include <sitkDICOMOrientImageFilter.h>


TEST(BasicFilters, DICOMOrientImageFilter_Direction)
{
  namespace sitk = itk::simple;

  auto directionLPS = v9(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
  auto directionRAS = v9(-1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0);

  EXPECT_EQ(directionLPS, sitk::DICOMOrientImageFilter::GetDirectionCosinesFromOrientation("LPS"));
  EXPECT_EQ("LPS", sitk::DICOMOrientImageFilter::GetOrientationFromDirectionCosines(directionLPS));

  EXPECT_EQ(v9(-1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0),
            sitk::DICOMOrientImageFilter::GetDirectionCosinesFromOrientation("RAS"));
  EXPECT_EQ("RAS", sitk::DICOMOrientImageFilter::GetOrientationFromDirectionCosines(directionRAS));
}
