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
  registration.SetTransform ( new itk::simple::AffineTransform() );
  registration.SetMetric ( new itk::simple::MattesMutualInformationMetric() );
  registration.SetInterpolate ( new itk::simple::LinearInterpolate() );
  registration.SetUseCenteredInitializationOff();
  std::vector<double> params;
  itk::simple::Transform *transform;
  ASSERT_NO_THROW ( transform = registration.Execute ( fixed, moving ) );
  params = transform->GetParameters();
  ASSERT_EQ ( params.size(), 12u );
  for ( size_t idx = 0; idx < params.size(); idx++ ) {
    ASSERT_NEAR ( params[idx], ExpectedParameters[idx], 0.01 );
  }
  ASSERT_NO_THROW ( params = registration.Execute ( fixed, moving ) );
  ASSERT_NE ( params.size(), 0u );
}


TEST(Registration,Defaults) {
  itk::simple::ImageFileReader reader;

  itk::simple::Image fixed = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0001_MR1_mpr-1_anon.nrrd" ) ).Execute();
  itk::simple::Image moving = reader.SetFileName ( dataFinder.GetFile ( "Input/OAS1_0002_MR1_mpr-1_anon.nrrd" ) ).Execute();

  itk::simple::Registration registration;
  registration.SetUseCenteredInitializationOff();
  std::vector<double> params;
  itk::simple::Transform *transform;
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

  itk::simple::ResampleImageFilter resample;
  resample.SetResampleParametersFromImage ( fixed );
  itk::simple::Image resampled = resample.Execute ( moving );
  itk::simple::ImageFileWriter writer;

  IMAGECOMPAREWITHTOLERANCE ( resampled, "Resample", 0.1 );
}
