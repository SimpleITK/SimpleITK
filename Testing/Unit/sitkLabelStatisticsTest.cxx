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

  std::vector<int64_t> labels = lsFilter.GetLabels();
  for(std::vector<int64_t>::const_iterator i = labels.begin(); i != labels.end(); ++i)
    {
    //By using the same image, the label min/max/mean values should equal the label itself.
    ASSERT_EQ(lsFilter.GetMinimum (*i) , *i);
    ASSERT_EQ(lsFilter.GetMaximum (*i) , *i);
    ASSERT_EQ(lsFilter.GetMean    (*i) , *i);
    ASSERT_EQ(lsFilter.GetMedian  (*i) , *i);
    //By using the same image, the label variance values should equal to Zero.
    ASSERT_EQ(lsFilter.GetSigma   (*i) , 0.0      );
    ASSERT_EQ(lsFilter.GetVariance(*i) , 0.0      );
    }

  ASSERT_EQ(lsFilter.GetSum  (0) , 0     );
  ASSERT_EQ(lsFilter.GetCount(0) , 33390u );
}


TEST(LabelStatistics,Commands) {
  namespace sitk = itk::simple;

  sitk::Image image = sitk::ReadImage ( dataFinder.GetFile ( "Input/cthead1.png" ) );
  sitk::Image labels = sitk::ReadImage ( dataFinder.GetFile ( "Input/2th_cthead1.mha" ) );

  sitk::LabelStatisticsImageFilter stats;


  ProgressUpdate progressCmd(stats);
  stats.AddCommand(sitk::sitkProgressEvent, progressCmd);

  CountCommand abortCmd(stats);
  stats.AddCommand(sitk::sitkAbortEvent, abortCmd);

  CountCommand deleteCmd(stats);
  stats.AddCommand(sitk::sitkDeleteEvent, deleteCmd);

  CountCommand endCmd(stats);
  stats.AddCommand(sitk::sitkEndEvent, endCmd);

  CountCommand iterCmd(stats);
  stats.AddCommand(sitk::sitkIterationEvent, iterCmd);

  CountCommand startCmd(stats);
  stats.AddCommand(sitk::sitkStartEvent, startCmd);

  CountCommand userCmd(stats);
  stats.AddCommand(sitk::sitkUserEvent, userCmd);

  stats.DebugOn();

  stats.Execute ( image, labels );

  EXPECT_EQ( stats.GetName(), "LabelStatisticsImageFilter" );
  EXPECT_NO_THROW( stats.ToString() );
  EXPECT_TRUE ( stats.HasLabel ( 0 ) );
  EXPECT_TRUE ( stats.HasLabel ( 1 ) );
  EXPECT_TRUE ( stats.HasLabel ( 2 ) );
  EXPECT_FALSE ( stats.HasLabel ( 99 ) );
  EXPECT_FALSE ( stats.HasLabel ( 1024 ) );

  EXPECT_NEAR ( stats.GetMinimum ( 0 ), 0, 0.01 );
  EXPECT_NEAR ( stats.GetMaximum ( 0 ), 99, 0.01 );
  EXPECT_NEAR ( stats.GetMean ( 0 ), 13.0911, 0.001 );
  EXPECT_NEAR ( stats.GetSigma ( 0 ),  16.4065, 0.01 );
  EXPECT_NEAR ( stats.GetVariance ( 0 ),  269.173, 0.01 );
  EXPECT_NEAR ( stats.GetCount ( 0 ),  36172, 0.01 );
  EXPECT_NEAR ( stats.GetSum ( 0 ),  473533, 0.01 );
  EXPECT_NEAR ( stats.GetMedian ( 0 ), 12.0, 0.001 );

  ASSERT_EQ( 4u, stats.GetBoundingBox(0).size() );
  EXPECT_EQ( 0, stats.GetBoundingBox(0)[0] );
  EXPECT_EQ( 255, stats.GetBoundingBox(0)[1] );
  EXPECT_EQ( 0, stats.GetBoundingBox(0)[2] );
  EXPECT_EQ( 255, stats.GetBoundingBox(0)[3] );

  EXPECT_EQ ( 1.0f, stats.GetProgress() );
  EXPECT_EQ ( 1.0f, progressCmd.m_Progress );
  EXPECT_EQ ( 0, abortCmd.m_Count );
  EXPECT_EQ ( 1, endCmd.m_Count );
  EXPECT_EQ ( 0, iterCmd.m_Count );
  EXPECT_EQ ( 1, startCmd.m_Count );
  EXPECT_EQ ( 0, userCmd.m_Count );

 // internal filter does not get deleted since there are active measurements
  EXPECT_EQ ( 0, deleteCmd.m_Count );

  const std::vector<int64_t> myLabels = stats.GetLabels();
  EXPECT_EQ ( myLabels.size() , 3u);

  // const sitk::LabelStatisticsImageFilter::LabelStatisticsMap myMap = stats.GetLabelStatisticsMap();
  // EXPECT_EQ( myLabels.size() , myMap.size() );

  // const sitk::MeasurementMap myMeasurementMap = stats.GetMeasurementMap(0);
  // EXPECT_EQ( myMeasurementMap.size(), 8u ); //4 measurements produced

  // const sitk::BasicMeasurementMap myBasicMeasurementMap =
  //   myMeasurementMap.GetBasicMeasurementMap();
  // EXPECT_EQ( myBasicMeasurementMap.size(), 8u ); //4 measurements produced

  // EXPECT_EQ ( myMeasurementMap.ToString(), "Count, Maximum, Mean, Minimum, Sigma, Sum, Variance, approxMedian, \n36172, 99, 13.0911, 0, 16.4065, 473533, 269.173, 12, \n" );
}
