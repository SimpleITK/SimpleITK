#include <SimpleITKTestHarness.h>
#include <SimpleITK.h>

TEST(Registration,CreateMattes) {
  itk::simple::Image image2d( 32, 32, itk::simple::sitkUInt8 );
  itk::simple::Image image3d( 32, 32, 32, itk::simple::sitkUInt8 );

  itk::simple::MattesMutualInformationMetric metric;

  ASSERT_TRUE ( metric.GetMetric ( image2d ).IsNotNull() );
  ASSERT_TRUE ( metric.GetMetric ( image3d ).IsNotNull() );
  // Can't make a 2d to 3d registration yet...
  // ASSERT_THROW ( metric.GetMetric ( image2d.get(), image3d.get() ) );
}

TEST(Registration,Components) {
  itk::simple::ImageFileReader reader;

  itk::simple::Image fixed = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0001_MR1_mpr-1_anon.nrrd" ) ).Execute();
  itk::simple::Image moving = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0002_MR1_mpr-1_anon.nrrd" ) ).Execute();

  itk::simple::AffineTransform transform;
  itk::simple::MattesMutualInformationMetric metric;
  itk::simple::LinearInterpolate interpolate;
  itk::simple::RegularStepGradientDescentOptimizer optimizer;

  metric.SetNumberOfHistogramBins ( 32 );

  itk::simple::Registration registration;
  registration.SetTransform ( &transform );
  registration.SetMetric ( &metric );
  registration.SetInterpolate ( &interpolate );
  registration.SetOptimizer ( &optimizer );
  registration.SetUseCenteredInitializationOff();
  std::vector<double> params;
  try {
    params = registration.Execute ( fixed, moving );
  } catch ( itk::ExceptionObject e ) {
    std::cout << "Registration failed: " << e.what() << std::endl;
  }
  ASSERT_NO_THROW ( params = registration.Execute ( fixed, moving ) );
  ASSERT_NE ( params.size(), 0 );
}

TEST(Registration,Defaults) {
  itk::simple::ImageFileReader reader;

  itk::simple::Image fixed = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0001_MR1_mpr-1_anon.nrrd" ) ).Execute();
  itk::simple::Image moving = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0002_MR1_mpr-1_anon.nrrd" ) ).Execute();

  itk::simple::Registration registration;
  registration.SetUseCenteredInitializationOff();
  std::vector<double> params;
  ASSERT_NO_THROW ( params = registration.Execute ( fixed, moving ) );
  ASSERT_NE ( params.size(), 0 );
}

TEST(Registration,Resample) {
  itk::simple::ImageFileReader reader;

  itk::simple::Image fixed = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0001_MR1_mpr-1_anon.nrrd" ) ).Execute();
  itk::simple::Image moving = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0002_MR1_mpr-1_anon.nrrd" ) ).Execute();

  itk::simple::ResampleImageFilter resample;
  resample.SetResampleParametersFromImage ( fixed );
  itk::simple::Image resampled = resample.Execute ( moving );
  itk::simple::ImageFileWriter writer;

  IMAGECOMPAREWITHTOLERANCE ( resampled, "Resample", 0.1 );
}
