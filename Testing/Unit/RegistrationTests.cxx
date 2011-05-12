#include <SimpleITKTestHarness.h>

#include <SimpleITK.h>

TEST(Registration,CreateMattes) {
  itk::simple::Image image2d( 32, 32, itk::simple::sitkUInt8 );
  itk::simple::Image image3d( 32, 32, 32, itk::simple::sitkUInt8 );

  itk::simple::MattesMutualInformationMetric metric;

  ASSERT_TRUE ( metric.GetMetric ( image2d ).IsNotNull() );
  ASSERT_TRUE ( metric.GetMetric ( image3d ).IsNotNull() );
}

static float ExpectedParameters[] = {1.0007, -0.00291716, -0.00417716,
                                     0.00237245, 0.998502, -0.00246285,
                                     -0.000911028, 0.000150096, 0.996861,
                                     -0.0263989, -0.113908, -0.0758585 };

TEST(Registration,Components) {
  itk::simple::ImageFileReader reader;

  itk::simple::Image fixed = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0001_MR1_mpr-1_anon.nrrd" ) ).Execute();
  itk::simple::Image moving = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0002_MR1_mpr-1_anon.nrrd" ) ).Execute();

  itk::simple::Registration registration;
  registration.SetOptimizer ( new itk::simple::RegularStepGradientDescentOptimizer() );
  itk::simple::Transform *transform = NULL;
  transform = new itk::simple::AffineTransform();
  std::vector<double> params;

  // Create a transform
  params.push_back ( 1 );
  params.push_back ( 0 );
  params.push_back ( 0 );

  params.push_back ( 0 );
  params.push_back ( 1 );
  params.push_back ( 0 );

  params.push_back ( 0 );
  params.push_back ( 0 );
  params.push_back ( 1 );

  params.push_back ( 0 );
  params.push_back ( 0 );
  params.push_back ( 0 );
  transform->SetParameters ( params );

  registration.SetTransform ( transform );
  registration.SetMetric ( new itk::simple::MattesMutualInformationMetric() );
  registration.SetInterpolate ( new itk::simple::LinearInterpolate() );
  registration.SetUseCenteredInitializationOff();
  try {
    transform = registration.Execute ( fixed, moving );
  } catch ( itk::simple::GenericException e ) {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  ASSERT_NO_THROW ( transform = registration.Execute ( fixed, moving ) );
  params = transform->GetParameters();
  ASSERT_EQ ( params.size(), 12u );
  for ( size_t idx = 0; idx < 9; idx++ ) {
    ASSERT_NEAR ( params[idx], ExpectedParameters[idx], 0.01 ) << "idx = " << idx;
  }
  ASSERT_NEAR ( params[9], ExpectedParameters[9], 0.2 ) << "idx = 9";
  ASSERT_NEAR ( params[10], ExpectedParameters[10], 0.2 ) << "idx = 10";
  ASSERT_NEAR ( params[11], ExpectedParameters[11], 0.2 ) << "idx = 11";
}


TEST(Registration,Defaults) {
  itk::simple::ImageFileReader reader;

  itk::simple::Image fixed = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0001_MR1_mpr-1_anon.nrrd" ) ).Execute();
  itk::simple::Image moving = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0002_MR1_mpr-1_anon.nrrd" ) ).Execute();

  itk::simple::Registration registration;
  registration.SetUseCenteredInitializationOff();
  std::vector<double> params;
  itk::simple::Transform *transform = NULL;
  ASSERT_NO_THROW ( transform = registration.Execute ( fixed, moving ) );
  params = transform->GetParameters();
  ASSERT_EQ ( params.size(), 12u );
  for ( size_t idx = 0; idx < params.size(); idx++ ) {
    ASSERT_NEAR ( params[idx], ExpectedParameters[idx], 0.01 );
  }

}

TEST(Registration,Resample) {
  itk::simple::ImageFileReader reader;

  itk::simple::Image fixed = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0001_MR1_mpr-1_anon.nrrd" ) ).Execute();
  itk::simple::Image moving = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0002_MR1_mpr-1_anon.nrrd" ) ).Execute();

  itk::simple::Registration registration;
  registration.SetUseCenteredInitializationOff();
  itk::simple::Transform *transform = NULL;
  ASSERT_NO_THROW ( transform = registration.Execute ( fixed, moving ) );

  itk::simple::ResampleImageFilter resample;
  resample.SetResampleParametersFromImage ( fixed );
  resample.SetTransform ( transform );
  itk::simple::Image resampled = resample.Execute ( moving );
  itk::simple::ImageFileWriter writer;

  IMAGECOMPAREWITHTOLERANCE ( resampled, "Resample", 0.1 );
}
