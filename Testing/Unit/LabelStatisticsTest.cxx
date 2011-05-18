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
        //By using the same image, the label variance values should equal to Zero.
        ASSERT_EQ(lsFilter.GetVariance(testLabelValue) , 0.0      );
        }
    }
}
