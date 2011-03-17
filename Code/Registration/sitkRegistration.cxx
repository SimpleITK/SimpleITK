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

std::vector<double> Register ( Image* fixed, Image* moving, Transform *transform, Interpolate *interpolate, Metric *metric, Optimizer *optimizer )
  {
  Registration registration;
  registration.SetTransform ( transform );
  registration.SetInterpolate ( interpolate );
  registration.SetMetric ( metric );
  registration.SetOptimizer ( optimizer );
  return registration.Execute ( fixed, moving );
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

template<class TImage>
std::vector<double> Registration::ExecuteInternal ( Image* fixed, Image* moving )
{
  typedef itk::ImageRegistrationMethod<TImage,TImage>  RegistrationType;
  typename RegistrationType::Pointer registration = RegistrationType::New();

  ::itk::TransformBase::Pointer transformBase = m_Transform->GetTransform ( fixed->GetDimension() ).GetPointer();
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
  registration->SetFixedImage( dynamic_cast<typename RegistrationType::FixedImageType*> (fixed->GetImageBase().GetPointer()));
  registration->SetMovingImage( dynamic_cast<typename RegistrationType::MovingImageType*> (moving->GetImageBase().GetPointer()));

  // Why this isn't the default, I'll never know...
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

  std::vector<double> tempScales = m_Transform->GetOptimizerScales ( fixed->GetDimension() );
  typename RegistrationType::OptimizerType::ScalesType scales ( tempScales.size() );
  scales.Fill ( 1.0 );
  for ( unsigned int idx = 0; idx < tempScales.size(); idx++ )
    {
    scales[idx] = tempScales[idx];
    }
  registration->GetOptimizer()->SetScales ( scales );


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
  out << "\n\nModified Transform:\n";
  registration->GetTransform()->Print ( out );

  out << "\n\n\nRegistration object:\n";
  registration->Print ( out );
  std::cout << out.str() << std::endl;
  std::cout << "\n\nScales: " << scales << std::endl;

  try
    {
    registration->Update();
    }
  catch( itk::ExceptionObject & err )
    {
    std::cout << "ExceptionObject caught !" << err.what() << std::endl;
    throw err;
    }

  typedef typename RegistrationType::ParametersType ParametersType;
  ParametersType finalParameters = registration->GetLastTransformParameters();
  std::vector<double> parameters;
  std::cout << "Final parameters:\n";
  for ( unsigned int idx = 0; idx < finalParameters.GetSize(); idx++ )
    {
    parameters.push_back ( finalParameters.GetElement ( idx ) );
    std::cout << "\tParameters[" << idx << "] = " << parameters[idx] << "\n";
    }

  return parameters;
  }

  std::vector<double> Registration::Execute ( Image* fixed, Image* moving )
  {
  const PixelIDValueType fixedType = fixed->GetPixelIDValue();
  const unsigned int fixedDim = fixed->GetDimension();
  if ( fixed->GetPixelIDValue() != moving->GetPixelIDValue() )
    {
    sitkExceptionMacro ( << "Fixed and moving images must be the same datatype! Got "
                         << fixed->GetPixelIDValue() << " and " << moving->GetPixelIDValue() );
    }

  if ( fixed->GetDimension() != moving->GetDimension() )
    {
    sitkExceptionMacro ( << "Fixed and moving images must be the same dimensionality! Got "
                         << fixed->GetDimension() << " and " << moving->GetDimension() );
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
Registration& Registration::SetOptimizer ( Optimizer *optimizer )
{
m_Optimizer.reset ( optimizer->Clone() );
return *this;
}
/*
  Transform& Registration::GetTransform()
  {
  // return m_Transform;
  }
  Interpolate& Registration::GetInterpolate()
  {
  // return m_Interpolate;
  }
  Metric& Registration::GetMetric()
  {
  // return m_Metric;
  }
  Optimizer& Registration::GetOptimizer()
  {
  // return m_Optimizer;
  }
*/

Registration& Registration::SetUseCenteredInitialization ( bool init )
  {
  this->m_UseCenteredInitialization = init;
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


