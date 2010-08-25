#include "simpleAffineRegistration.h"
#include "itkRegularStepGradientDescentOptimizer.h"
#include "itkImageRegistrationMethod.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkMattesMutualInformationImageToImageMetric.h"
#include "itkAffineTransform.h"

namespace itk {
  namespace simple {

    AffineRegistration::AffineRegistration() {
      this->m_NumberOfIterations = 100;
    }

    std::string AffineRegistration::toString() {
      std::ostringstream out;
      return out.str();
    }

    AffineRegistration& AffineRegistration::setNumberOfIterations ( unsigned int i ) {
      this->m_NumberOfIterations = i;
      return *this;
    }

    unsigned int AffineRegistration::getNumberOfIterations() {
      return this->m_NumberOfIterations;
    }

    Transform AffineRegistration::execute ( Image::Pointer fixed, Image::Pointer moving ) {
      // Would likely want to check to see if the images are null
      Transform t;
      switch ( fixed->getImageDataType() ) {
        sitkImageDataTypeSwitch ( return this->executeInternalOne<DataType>( fixed, moving ) );
      }
      return t;
    }

    template <class TFixed>
    Transform AffineRegistration::executeInternalOne ( Image::Pointer fixed, Image::Pointer moving ) {
      Transform t;
      switch ( moving->getImageDataType() ) {
        sitkImageDataTypeSwitch ( return ( this->executeInternalTwo<TFixed, DataType>( fixed, moving ) ));
      }
      return t;
    }
    
    // This is where the real action starts!
    template <class TFixed, class TMoving> Transform AffineRegistration::executeInternalTwo ( Image::Pointer fixed, Image::Pointer moving ) {
      typedef itk::Image<TFixed,3> FixedImageType;
      typedef itk::Image<TMoving,3> MovingImageType;
      
      int mNumberOfHistogramBins = 30;
      int mNumberOfSpatialSamples = 10000;
      double mTranslationScale = 100.0;

      typedef itk::MattesMutualInformationImageToImageMetric<FixedImageType, MovingImageType>    MetricType;
      typedef itk::RegularStepGradientDescentOptimizer OptimizerType;
      typedef itk::LinearInterpolateImageFunction<MovingImageType, double>  InterpolatorType;
      typedef itk::ImageRegistrationMethod<FixedImageType,MovingImageType>  RegistrationType;
      typedef itk::AffineTransform< double > TransformType;
      typedef OptimizerType::ScalesType OptimizerScalesType;
      typedef itk::LinearInterpolateImageFunction<MovingImageType, double> ResampleInterpolatorType;

      typename OptimizerType::Pointer      optimizer     = OptimizerType::New();
      optimizer->SetNumberOfIterations ( m_NumberOfIterations );
      optimizer->SetMinimumStepLength ( .0005 );
      optimizer->SetMaximumStepLength ( 10.0 );
      optimizer->SetMinimize(true);   

      typename TransformType::Pointer transform = TransformType::New();
      OptimizerScalesType scales ( transform->GetNumberOfParameters() );
      scales.Fill ( 1.0 );
      for( unsigned j = 9; j < 12; j++ )
        {
          scales[j] = 1.0 / vnl_math_sqr(mTranslationScale);
        }
      optimizer->SetScales( scales );

      typename MetricType::Pointer  metric        = MetricType::New();
      metric->SetNumberOfHistogramBins ( mNumberOfHistogramBins );
      metric->SetNumberOfSpatialSamples( mNumberOfSpatialSamples );
      metric->ReinitializeSeed(123);
  
      // Create the interpolator
      typename InterpolatorType::Pointer interpolator = InterpolatorType::New();

      // Set up the registration
      typename RegistrationType::Pointer registration = RegistrationType::New();
      registration->SetTransform ( transform );
      registration->SetInitialTransformParameters ( transform->GetParameters() );
      registration->SetMetric ( metric );
      registration->SetOptimizer ( optimizer );
      registration->SetInterpolator ( interpolator );
      registration->SetFixedImage( dynamic_cast<FixedImageType*> ( fixed->getITKImage().GetPointer() ) );
      registration->SetMovingImage( dynamic_cast<MovingImageType*> ( moving->getITKImage().GetPointer() ) );

      try {
        registration->StartRegistration();
      } catch( itk::ExceptionObject & err ) {
        std::cout << "ExceptionObject caught !" << err.what() << std::endl;
        throw err;
      }


      Transform t;
      transform->SetParameters ( registration->GetLastTransformParameters() );
      t.setITKTransform ( transform.GetPointer() );
      return t;
    }
  }
}
