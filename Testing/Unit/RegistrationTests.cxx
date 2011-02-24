#include <SimpleITKTestHarness.h>

#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>
#include <sitkMattesMutualInformationMetric.h>

#include "itkImage.h"
#include "itkVectorImage.h"

#include <stdint.h>

TEST(Registration,CreateMattes) {
  auto_ptr<itk::simple::Image> image2d ( new itk::simple::Image ( 32, 32, itk::simple::sitkUInt8 ) );
  auto_ptr<itk::simple::Image> image3d ( new itk::simple::Image ( 32, 32, 32, itk::simple::sitkUInt8 ) );

  itk::simple::MattesMutualInformationMetric metric();

  ASSERT_TRUE ( metric.GetMetric ( image2d, image2d ).IsNotNULL() );
  ASSERT_TRUE ( metric.GetMetric ( image3d, image3d ).IsNotNULL() );
  // Can't make a 2d to 3d registration yet...
  ASSERT_THROWS ( metric.GetMetric ( image2d, image3d ) );
}
