#include <SimpleITKTestHarness.h>
#include <SimpleITK.h>
#include "itkImage.h"
#include "itkVectorImage.h"

#include <stdint.h>
#include <memory>

TEST(Registration,CreateMattes) {
  itk::simple::Image image2d( 32, 32, itk::simple::sitkUInt8 );
  itk::simple::Image image3d( 32, 32, 32, itk::simple::sitkUInt8 );

  itk::simple::MattesMutualInformationMetric metric;

  ASSERT_TRUE ( metric.GetMetric ( image2d ).IsNotNull() );
  ASSERT_TRUE ( metric.GetMetric ( image3d ).IsNotNull() );
  // Can't make a 2d to 3d registration yet...
  // ASSERT_THROW ( metric.GetMetric ( image2d.get(), image3d.get() ) );
}

TEST(Registration,Simple) {
  itk::simple::ImageFileReader reader;

  itk::simple::Image fixed = reader.SetFileName ( dataFinder.GetFile ( "Input/Fixed.nrrd" ) ).Execute();
  itk::simple::Image moving = reader.SetFileName ( dataFinder.GetFile ( "Input/Moving.nrrd" ) ).Execute();

  itk::simple::AffineTransform transform;
  itk::simple::MattesMutualInformationMetric metric;
  itk::simple::LinearInterpolate interpolate;
  itk::simple::RegularStepGradientDescentOptimizer optimizer;

  itk::simple::Registration registration;
  registration.SetTransform ( &transform );
  registration.SetMetric ( &metric );
  registration.SetInterpolate ( &interpolate );
  registration.SetOptimizer ( &optimizer );
  std::vector<double> params;
  try {
    params = registration.Execute ( fixed, moving );
  } catch ( itk::ExceptionObject e ) {
    std::cout << "Registration failed: " << e.what() << std::endl;
  }
  ASSERT_NO_THROW ( params = registration.Execute ( fixed, moving ) );
  ASSERT_NE ( params.size(), 0u );
}
