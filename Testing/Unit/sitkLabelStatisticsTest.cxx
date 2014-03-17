/*=========================================================================
*
*  Copyright Insight Software Consortium
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
#include <SimpleITK.h>
#include "itkImage.h"
#include "itkVectorImage.h"

#include <stdint.h>
#include <memory>

TEST(LabelStatistics,Simple) {
  itk::simple::ImageFileReader reader;

  //By using the same image, the label min/max values should equal the label itself.
  itk::simple::Image intensityImage = reader.SetFileName ( dataFinder.GetFile ( "Input/2th_cthead1.png" ) ).Execute();
  itk::simple::Image labelImage     = reader.SetFileName ( dataFinder.GetFile ( "Input/2th_cthead1.png" ) ).Execute();

  itk::simple::LabelStatisticsImageFilter lsFilter;

  EXPECT_TRUE(lsFilter.GetUseHistograms());
  lsFilter.UseHistogramsOff();
  EXPECT_FALSE(lsFilter.GetUseHistograms());
  lsFilter.UseHistogramsOn();
  EXPECT_TRUE(lsFilter.GetUseHistograms());
  lsFilter.SetUseHistograms(false);
  EXPECT_FALSE(lsFilter.GetUseHistograms());
  lsFilter.SetUseHistograms(true);
  EXPECT_TRUE(lsFilter.GetUseHistograms());

  try {
    lsFilter.Execute ( intensityImage, labelImage );
  } catch ( itk::ExceptionObject e ) {
    std::cout << "LabelStatistics failed: " << e.what() << std::endl;
  }

  for(uint64_t testLabelValue=0; testLabelValue < 256; testLabelValue++) {
      if( lsFilter.HasLabel(testLabelValue) )
        {
        //By using the same image, the label min/max/mean values should equal the label itself.
        ASSERT_EQ(lsFilter.GetMinimum (testLabelValue) , testLabelValue);
        ASSERT_EQ(lsFilter.GetMaximum (testLabelValue) , testLabelValue);
        ASSERT_EQ(lsFilter.GetMean    (testLabelValue) , testLabelValue);
        ASSERT_EQ(lsFilter.GetMedian  (testLabelValue) , testLabelValue);
        //By using the same image, the label variance values should equal to Zero.
        ASSERT_EQ(lsFilter.GetSigma   (testLabelValue) , 0.0      );
        ASSERT_EQ(lsFilter.GetVariance(testLabelValue) , 0.0      );
        }
  }
  ASSERT_EQ(lsFilter.GetSum  (0) , 0     );
  ASSERT_EQ(lsFilter.GetCount(0) , 33390 );
}
