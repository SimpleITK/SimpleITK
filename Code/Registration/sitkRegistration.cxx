#include "sitkRegistration.h"
#include "itkImageRegistrationMethod.h"
#include "sitkAffineTransform.h"
#include "sitkLinearInterpolate.h"
#include "sitkMattesMutualInformationMetric.h"
#include "sitkRegularStepGradientDescentOptimizer.h"

namespace itk
{
namespace simple
{
  Registration::Registration() {
    m_MemberFactory.reset( new  detail::MemberFunctionFactory<MemberFunctionType>( this ) );
    // cast between basic images
    m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 3, RegistrationAddressor<MemberFunctionType> > ();
    m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 2, RegistrationAddressor<MemberFunctionType> > ();
  }

  template<class TImage>
  std::vector<double> Registration::ExecuteInternal ( Image* fixed, Image* moving )
  {
  // Hard coded variables
  AffineTransform transform;
  LinearInterpolate interpolate;
  MattesMutualInformationMetric metric;
  RegularStepGradientDescentOptimizer optimizer;

  typedef itk::ImageRegistrationMethod<TImage,TImage>  RegistrationType;
  typename RegistrationType::Pointer registration = RegistrationType::New();

  ::itk::TransformBase::Pointer transformBase = transform.GetTransform ( fixed->GetDimension() ).GetPointer();
  ::itk::Object::Pointer interpolatorBase = interpolate.GetInterpolator ( fixed ).GetPointer();
  ::itk::SingleValuedCostFunction::Pointer metricBase = metric.GetMetric ( fixed ).GetPointer();
  ::itk::Optimizer::Pointer optimizerBase = optimizer.GetOptimizer().GetPointer();

  // Check for valid types
  std::ostringstream out;
  transformBase->Print ( out );
  interpolatorBase->Print ( out );
  metricBase->Print ( out );
  optimizerBase->Print ( out );
  std::cout << out.str() << std::endl;
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

  // Why this isn't the default, I'll never know...
  registration->SetInitialTransformParameters ( registration->GetTransform()->GetParameters() );

  std::vector<double> tempScales = transform.GetOptimizerScales ( fixed->GetDimension() );
  typename RegistrationType::OptimizerType::ScalesType scales ( tempScales.size() );
  scales.Fill ( 1.0 );
  for ( unsigned int idx = 0; idx < tempScales.size(); idx++ )
    {
    scales[idx] = tempScales[idx];
    }
  registration->GetOptimizer()->SetScales ( scales );

  registration->SetFixedImage( dynamic_cast<typename RegistrationType::FixedImageType*> (fixed->GetImageBase().GetPointer()));
  registration->SetMovingImage( dynamic_cast<typename RegistrationType::MovingImageType*> (moving->GetImageBase().GetPointer()));

  registration->StartRegistration();

  typedef typename RegistrationType::ParametersType ParametersType;
  ParametersType finalParameters = registration->GetLastTransformParameters();
  std::vector<double> parameters;
  for ( unsigned int idx = 0; idx < finalParameters.GetSize(); idx++ )
    {
    parameters.push_back ( finalParameters.GetElement ( idx ) );
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
}
}


