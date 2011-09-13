#include "sitkRegistration.h"
#include "itkImageRegistrationMethod.h"

#include "itkMattesMutualInformationImageToImageMetric.h"
#include "itkRegularStepGradientDescentOptimizer.h"

#include <memory>

namespace itk
{
namespace simple
{

namespace {

template< typename TOptimizer >
class CommandIterationUpdate
  : public itk::Command
{
public:
  typedef  CommandIterationUpdate   Self;
  typedef  itk::Command             Superclass;
  typedef itk::SmartPointer<Self>   Pointer;

  itkNewMacro( Self );
protected:
  CommandIterationUpdate() {};


public:

  typedef TOptimizer   OptimizerType;
  typedef const OptimizerType *                          OptimizerPointer;

  void Execute(itk::Object *caller, const itk::EventObject & event)
  {
    Execute( (const itk::Object *)caller, event);
  }

  void Execute(const itk::Object * object, const itk::EventObject & event)
  {

    OptimizerPointer optimizer =
      dynamic_cast< OptimizerPointer >( object );

    if( ! itk::IterationEvent().CheckEvent( &event ) )
      {
      return;
      }

    std::cout << optimizer->GetCurrentIteration() << " = ";
    std::cout << '\t' << "    CurrentStep: " << optimizer->GetCurrentStepLength() << std::endl;
    std::cout << '\t' << "          Value: " << optimizer->GetValue() << std::endl;
    std::cout << '\t' << "       Gradient: " << optimizer->GetGradient() << std::endl;
    std::cout << '\t' << "CurrentPosition: " << optimizer->GetCurrentPosition() << std::endl;
  }
};

} // end local namespace




  Transform Register ( const Image &fixed, const Image & moving, const Transform &transform, InterpolateFunctionEnum interpolator, Metric *metric, SOptimizer *optimizer )
  {
  Registration registration;
  registration.SetTransform ( transform );
  registration.SetInterpolator ( interpolator );
  //registration.SetMetric ( metric );
  //registration.SetOptimizer ( optimizer );
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
  //m_UseCenteredInitialization = true;
  //m_Transform = Transform(); default contructed to identity transfrom
  m_Interpolator = sitkLinearInterpolate;
  //m_Metric.reset ( new MattesMutualInformationMetric() );.
  //m_Optimizer.reset ( new RegularStepGradientDescentOptimizer() );
  }

  std::string Registration::ToString () const
  {
    // Print with 2d defaults
    itk::simple::Image image(1,1,itk::simple::sitkUInt8);
    ::itk::TransformBase::ConstPointer transformBase = m_Transform.GetITKBase (  );
    //::itk::Object::Pointer interpolatorBase = m_Interpolate->GetInterpolator ( image ).GetPointer();
    //::itk::SingleValuedCostFunction::Pointer metricBase = m_Metric->GetMetric ( image ).GetPointer();
    //::itk::Optimizer::Pointer optimizerBase = m_Optimizer->GetOptimizer().GetPointer();

    // Check for valid types
    std::ostringstream out;
    out << "\n\nTransform:\n";
    transformBase->Print ( out );
    out << "\n\nInterpolator:\n";
    out << m_Interpolator << std::endl;
    //interpolatorBase->Print ( out );
    out << "\n\nMetric:\n";
    //metricBase->Print ( out );
    out << "\n\nOptimizer:\n";
    //optimizerBase->Print ( out );
    return out.str();
  }

template<class TImage>
Transform Registration::ExecuteInternal (const Image &fixed, const Image& moving )
{
  typedef TImage TInputImage;
  typedef itk::ImageRegistrationMethod<TImage,TImage>  RegistrationType;
  typename RegistrationType::Pointer registration = RegistrationType::New();

  // convert transform to itk Transform type
  typename RegistrationType::TransformType* itkTransform =
    dynamic_cast<typename RegistrationType::TransformType*> ( m_Transform.GetITKBase ( ) );
  if ( !itkTransform )
    {
    sitkExceptionMacro(<<"Transform is not a valid type");
    }

  // Create Interpolator
  typename itk::InterpolateImageFunction<TImage, double>::Pointer itkInterpolator = detail::CreateInterpolator<TImage>( m_Interpolator );

  // Create Optimizer
  ::itk::RegularStepGradientDescentOptimizer::Pointer opt = ::itk::RegularStepGradientDescentOptimizer::New();
  opt->SetNumberOfIterations( 2000 );
  opt->SetMinimumStepLength( .00005 );
  opt->SetMaximumStepLength( 0.1 );
  opt->MaximizeOff();

   typename RegistrationType::OptimizerType::Pointer itkOptimizer = opt.GetPointer();
   typedef CommandIterationUpdate< ::itk::RegularStepGradientDescentOptimizer > IterationUpdateType;
   typename IterationUpdateType::Pointer observer = IterationUpdateType::New();
   itkOptimizer->AddObserver( itk::IterationEvent(), observer );


  // Create Metric
   typename ::itk::MattesMutualInformationImageToImageMetric<TImage, TImage>::Pointer metric = ::itk::MattesMutualInformationImageToImageMetric<TImage, TImage>::New();
   metric->SetNumberOfHistogramBins( 128 );
   metric->SetNumberOfSpatialSamples( 20000 );
  typename RegistrationType::MetricType::Pointer itkMetric
    = metric.GetPointer();

  // Set 'em up
  registration->SetTransform ( itkTransform );
  registration->SetInterpolator ( itkInterpolator );
  registration->SetOptimizer ( itkOptimizer );
  registration->SetMetric ( itkMetric );

  registration->SetFixedImage( dynamic_cast<const typename RegistrationType::FixedImageType*> (fixed.GetITKBase()));
  registration->SetFixedImageRegion( registration->GetFixedImage()->GetLargestPossibleRegion() );
  registration->SetMovingImage( dynamic_cast<const typename RegistrationType::MovingImageType*> (moving.GetITKBase()));


  typename RegistrationType::TransformType::ParametersType params = registration->GetTransform()->GetParameters();
  registration->SetInitialTransformParameters ( params );

  // HACK FIXME TODO
  // The scales need to be brough back
  typename RegistrationType::OptimizerType::ScalesType scales ( params.size() );
  scales.Fill ( 1.0 );
  for ( unsigned int idx = 0; idx < scales.Size(); idx++ )
    {
    scales[idx] = .0001;
    }
  registration->GetOptimizer()->SetScales ( scales );

  registration->Update();

  typedef typename RegistrationType::ParametersType ParametersType;
  const ParametersType &finalParameters = registration->GetLastTransformParameters();
  std::vector<double> parameters( finalParameters.begin(), finalParameters.end() );

  // copy then set the parameters
  Transform out = m_Transform;
  out.SetParameters( parameters );
  return out;
  }

  Transform Registration::Execute ( const Image &fixed, const Image & moving )
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

Registration& Registration::SetTransform ( const Transform &transform )
{
  this->m_Transform = transform;
  return *this;
}
const Transform & Registration::GetTransform( void ) const
{
  return m_Transform;
}

Registration& Registration::SetInterpolator ( InterpolateFunctionEnum interp )
{
  this->m_Interpolator = interp;
  return *this;
}
InterpolateFunctionEnum Registration::GetInterpolator( void ) const
{
  return this->m_Interpolator;
}


// Registration& Registration::SetMetric ( Metric *metric )
// {
//   m_Metric.reset ( metric->Clone() );
//   return *this;
// }
// Registration& Registration::SetOptimizer ( SOptimizer *optimizer )
// {
//   m_Optimizer.reset ( optimizer->Clone() );
//   return *this;
// }

}
}


