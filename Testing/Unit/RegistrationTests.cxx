#include <SimpleITKTestHarness.h>

#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>
#include <sitkMattesMutualInformationMetric.h>
#include <sitkRegistration.h>
#include <sitkExceptionObject.h>

#include "itkImage.h"
#include "itkVectorImage.h"

#include <stdint.h>
#include <memory>

TEST(Registration,CreateMattes) {
  std::auto_ptr<itk::simple::Image> image2d ( new itk::simple::Image ( 32, 32, itk::simple::sitkUInt8 ) );
  std::auto_ptr<itk::simple::Image> image3d ( new itk::simple::Image ( 32, 32, 32, itk::simple::sitkUInt8 ) );

  itk::simple::MattesMutualInformationMetric metric;

  ASSERT_TRUE ( metric.GetMetric ( image2d.get() ).IsNotNull() );
  ASSERT_TRUE ( metric.GetMetric ( image3d.get() ).IsNotNull() );
  // Can't make a 2d to 3d registration yet...
  // ASSERT_THROW ( metric.GetMetric ( image2d.get(), image3d.get() ) );
}

TEST(Registration,Simple) {
  itk::simple::ImageFileReader reader;
  itk::simple::Image* fixed;
  itk::simple::Image* moving;
  fixed = reader.SetFileName ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ) ).Execute();
  moving = reader.SetFileName ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ) ).Execute();

  itk::simple::Registration registration;
  std::vector<double> params;
  try {
    params = registration.Execute ( fixed, moving );
  } catch ( itk::ExceptionObject e ) {
    std::cout << "Registration failed: " << e.what() << std::endl;
  }
  ASSERT_NO_THROW ( params = registration.Execute ( fixed, moving ) );
  ASSERT_NE ( params.size(), 0 );
}
