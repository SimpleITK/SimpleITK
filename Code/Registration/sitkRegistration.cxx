#include "sitkRegistration.h"
#include "itkImageRegistrationMethod.h"
#include "sitkAffineTransform.h"
#include "sitkLinearInterpolate.h"
#include "sitkMattesMutualInformationMetric.h"
#include "sitkRegularStepGradientDescentOptimizer.h"
#include "itkCenteredTransformInitializer.h"
#include <memory>

namespace itk
{
namespace simple
{

  Transform* Register ( const Image &fixed, const Image & moving, Transform *transform, Interpolate *interpolate, Metric *metric, SOptimizer *optimizer )
  {
  Registration registration;
  registration.SetTransform ( transform );
  registration.SetInterpolate ( interpolate );
  registration.SetMetric ( metric );
  registration.SetOptimizer ( optimizer );
  return registration.Execute ( fixed, moving );
  }


  Registration::~Registration()
  {
  }
  Registration::Registration()
  {
  m_MemberFactory.reset( new  detail::MemberFunctionFactory<MemberFunctionType>( this ) );
  // cast between basic images
  m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 3, RegistrationAddressor<MemberFunctionType> > ();
  m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 2, RegistrationAddressor<MemberFunctionType> > ();

  // Reasonable defaults?
  m_UseCenteredInitialization = true;
  m_Transform.reset ( new AffineTransform() );
  m_Interpolate.reset ( new LinearInterpolate() );
  m_Metric.reset ( new MattesMutualInformationMetric() );
  m_Optimizer.reset ( new RegularStepGradientDescentOptimizer() );
  }

  std::string Registration::ToString () const
  {
    // Print with 2d defaults
    itk::simple::Image image(1,1,itk::simple::sitkUInt8);
    ::itk::TransformBase::Pointer transformBase = m_Transform->GetTransform ( image.GetDimension() ).GetPointer();
    ::itk::Object::Pointer interpolatorBase = m_Interpolate->GetInterpolator ( image ).GetPointer();
    ::itk::SingleValuedCostFunction::Pointer metricBase = m_Metric->GetMetric ( image ).GetPointer();
    ::itk::Optimizer::Pointer optimizerBase = m_Optimizer->GetOptimizer().GetPointer();

    // Check for valid types
    std::ostringstream out;
    out << "\n\nTransform:\n";
    transformBase->Print ( out );
    out << "\n\nInterpolator:\n";
    interpolatorBase->Print ( out );
    out << "\n\nMetric:\n";
    metricBase->Print ( out );
    out << "\n\nOptimizer:\n";
    optimizerBase->Print ( out );
    return out.str();
  }

template<class TImage>
Transform* Registration::ExecuteInternal (const Image &fixed, const Image& moving )
{
  typedef itk::ImageRegistrationMethod<TImage,TImage>  RegistrationType;
  typename RegistrationType::Pointer registration = RegistrationType::New();

  ::itk::TransformBase::Pointer transformBase = m_Transform->GetTransform ( fixed.GetDimension() ).GetPointer();
  ::itk::Object::Pointer interpolatorBase = m_Interpolate->GetInterpolator ( fixed ).GetPointer();
  ::itk::SingleValuedCostFunction::Pointer metricBase = m_Metric->GetMetric ( fixed ).GetPointer();
  ::itk::Optimizer::Pointer optimizerBase = m_Optimizer->GetOptimizer().GetPointer();

  if ( NULL == dynamic_cast<typename RegistrationType::TransformType*> ( transformBase.GetPointer() ) )
    {
    sitkExceptionMacro(<<"Transform is not a valid type");
    }
  if ( NULL == dynamic_cast<typename RegistrationType::InterpolatorType*> ( interpolatorBase.GetPointer() ) )
    {
    sitkExceptionMacro(<<"Interpolator is not a valid type");
    }
  if ( NULL == dynamic_cast<typename RegistrationType::MetricType*> ( metricBase.GetPointer() ) )
    {
    sitkExceptionMacro(<<"Metric is not a valid type");
    }
  if ( NULL == dynamic_cast<typename RegistrationType::OptimizerType*> ( optimizerBase.GetPointer() ) )
    {
    sitkExceptionMacro(<<"Optimizer is not a valid type");
    }
  // Set 'em up
  registration->SetTransform ( dynamic_cast<typename RegistrationType::TransformType*> ( transformBase.GetPointer() ) );
  registration->SetInterpolator ( dynamic_cast<typename RegistrationType::InterpolatorType*> ( interpolatorBase.GetPointer() ) );
  registration->SetMetric ( dynamic_cast<typename RegistrationType::MetricType*> ( metricBase.GetPointer() ) );
  registration->SetOptimizer ( dynamic_cast<typename RegistrationType::OptimizerType*> ( optimizerBase.GetPointer() ) );
  registration->SetFixedImage( dynamic_cast<const typename RegistrationType::FixedImageType*> (fixed.GetImageBase()));
  registration->SetMovingImage( dynamic_cast<const typename RegistrationType::MovingImageType*> (moving.GetImageBase()));

  typedef ::itk::MatrixOffsetTransformBase<double, TImage::ImageDimension, TImage::ImageDimension> OffsetTransformType;
  if ( m_UseCenteredInitialization && dynamic_cast<OffsetTransformType*> ( transformBase.GetPointer() ) )
    {
    typedef typename ::itk::CenteredTransformInitializer<OffsetTransformType,
      typename RegistrationType::FixedImageType,
      typename RegistrationType::MovingImageType> InitializerType;
    typename InitializerType::Pointer initializer = InitializerType::New();
    initializer->SetFixedImage ( registration->GetFixedImage() );
    initializer->SetMovingImage ( registration->GetMovingImage() );
    initializer->SetTransform ( dynamic_cast<OffsetTransformType*> ( transformBase.GetPointer() ) );
    initializer->InitializeTransform();
    }

  typename RegistrationType::TransformType::ParametersType params = registration->GetTransform()->GetParameters();
  registration->SetInitialTransformParameters ( params );

  std::vector<double> tempScales = m_Transform->GetOptimizerScales ( fixed.GetDimension() );
  typename RegistrationType::OptimizerType::ScalesType scales ( tempScales.size() );
  scales.Fill ( 1.0 );
  for ( unsigned int idx = 0; idx < tempScales.size(); idx++ )
    {
    scales[idx] = tempScales[idx];
    }
  registration->GetOptimizer()->SetScales ( scales );


  registration->Update();

  typedef typename RegistrationType::ParametersType ParametersType;
  ParametersType finalParameters = registration->GetLastTransformParameters();
  std::vector<double> parameters;
  for ( unsigned int idx = 0; idx < finalParameters.GetSize(); idx++ )
    {
    parameters.push_back ( finalParameters.GetElement ( idx ) );
    }
  Transform *out = m_Transform.get()->Clone();
  out->SetParameters ( parameters );
  return out;
  }

  Transform* Registration::Execute ( const Image &fixed, const Image & moving )
  {
  const PixelIDValueType fixedType = fixed.GetPixelIDValue();
  const unsigned int fixedDim = fixed.GetDimension();

  if ( fixed.GetPixelIDValue() != moving.GetPixelIDValue() )
    {
    sitkExceptionMacro ( << "Fixed and moving images must be the same datatype! Got "
                         << fixed.GetPixelIDValue() << " and " << moving.GetPixelIDValue() );
    }

  if ( fixed.GetDimension() != moving.GetDimension() )
    {
    sitkExceptionMacro ( << "Fixed and moving images must be the same dimensionality! Got "
                         << fixed.GetDimension() << " and " << moving.GetDimension() );
    }

  if (this->m_MemberFactory->HasMemberFunction( fixedType, fixedDim ) )
    {
    return this->m_MemberFactory->GetMemberFunction( fixedType, fixedDim )( fixed, moving );
    }

  sitkExceptionMacro( << "Filter does not support fixed image type: " << itk::simple::GetPixelIDValueAsString (fixedType) );
  }

Registration& Registration::SetTransform ( Transform *transform )
{
  m_Transform.reset ( transform->Clone() );
  return *this;
}
Registration& Registration::SetInterpolate ( Interpolate *interpolate )
{
  m_Interpolate.reset ( interpolate->Clone() );
  return *this;
}
Registration& Registration::SetMetric ( Metric *metric )
{
  m_Metric.reset ( metric->Clone() );
  return *this;
}
Registration& Registration::SetOptimizer ( SOptimizer *optimizer )
{
  m_Optimizer.reset ( optimizer->Clone() );
  return *this;
}

Registration& Registration::SetUseCenteredInitialization ( bool init )
  {
  this->m_UseCenteredInitialization = init;
  return *this;
  }
bool Registration::GetUseCenteredInitialization()
  {
  return this->m_UseCenteredInitialization;
  }
Registration& Registration::SetUseCenteredInitializationOn()
  {
  return this->SetUseCenteredInitialization ( true );
  }
Registration& Registration::SetUseCenteredInitializationOff()
  {
  return this->SetUseCenteredInitialization ( false );
  }


}
}


