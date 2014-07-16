#include "sitkImageRegistrationMethod.h"

#include "sitkCreateInterpolator.hxx"
#include "itkImage.h"
#include "itkImageRegistrationMethodv4.h"

#include "itkRegistrationParameterScalesFromJacobian.h"
#include "itkRegistrationParameterScalesFromIndexShift.h"
#include "itkRegistrationParameterScalesFromPhysicalShift.h"

#include "itkCorrelationImageToImageMetricv4.h"
#include "itkDemonsImageToImageMetricv4.h"
#include "itkJointHistogramMutualInformationImageToImageMetricv4.h"
#include "itkMeanSquaresImageToImageMetricv4.h"
#include "itkMattesMutualInformationImageToImageMetricv4.h"


template< typename TValue, typename TType>
itk::Array<TValue> sitkSTLVectorToITKArray( const std::vector< TType > & in )
{
  itk::Array<TValue> out(in.size());
  std::copy(in.begin(), in.end(), out.begin());
  return out;
}

namespace itk
{
namespace simple
{

ImageRegistrationMethod::ImageRegistrationMethod()
  : m_Interpolator(sitkLinear),
    m_OptimizerScalesType(Manual),
    m_MetricSamplingPercentage(1,1.0),
    m_MetricSamplingStrategy(NONE),
    m_ShrinkFactorsPerLevel(1, 1),
    m_SmoothingSigmasPerLevel(1,0.0),
    m_SmoothingSigmasAreSpecifiedInPhysicalUnits(true),
    m_ActiveOptimizer(NULL)
{
  m_MemberFactory.reset( new  detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  // m_MemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, 3 > ();
  // m_MemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, 2 > ();

  m_MemberFactory->RegisterMemberFunctions< RealPixelIDTypeList, 3 > ();
  m_MemberFactory->RegisterMemberFunctions< RealPixelIDTypeList, 2 > ();

  this->SetMetricAsMattesMutualInformation();

}


ImageRegistrationMethod::~ImageRegistrationMethod()
{
}

std::string  ImageRegistrationMethod::ToString() const
{
  std::ostringstream out;
  out << "itk::simple" << this->GetName() << std::endl;

  out << Superclass::ToString();

  if ( this->m_ActiveOptimizer )
    {
    out << "ActiveOptimizer:";
    this->m_ActiveOptimizer->Print(out, 1);
    }

  out << "  Interpolator: ";
  this->ToStringHelper(out, this->m_Interpolator);
  out << std::endl;

  out << "  Transform: ";
  this->ToStringHelper(out, this->m_Transform.ToString());
  out << std::endl;

  return out.str();
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricAsCorrelation( )
{
  m_MetricType = Correlation;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricAsDemons( double intensityDifferenceThreshold )
{
  m_MetricType = Demons;
  m_MetricIntensityDifferenceThreshold = intensityDifferenceThreshold;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricAsJointHistogramMutualInformation( unsigned int numberOfHistogramBins,
                                                                     double varianceForJointPDFSmoothing )
{
  m_MetricType = JointHistogramMutualInformation;
  m_MetricNumberOfHistogramBins = numberOfHistogramBins;
  m_MetricVarianceForJointPDFSmoothing = varianceForJointPDFSmoothing;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricAsMeanSquares( )
{
  m_MetricType = MeanSquares;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricAsMattesMutualInformation( unsigned int numberOfHistogramBins )
{
  m_MetricType = MattesMutualInformation;
  m_MetricNumberOfHistogramBins = numberOfHistogramBins;
  return *this;
}

template <class TImageType>
itk::ImageToImageMetricv4<TImageType,
                          TImageType,
                          TImageType,
                          double,
                          DefaultImageToImageMetricTraitsv4< TImageType, TImageType, TImageType, double >
                          >*
ImageRegistrationMethod::CreateMetric( )
{
  typedef TImageType     FixedImageType;
  typedef TImageType     MovingImageType;


  switch (m_MetricType)
    {
    case Correlation:
    {
      typedef itk::CorrelationImageToImageMetricv4< FixedImageType, MovingImageType > _MetricType;

      typename _MetricType::Pointer metric = _MetricType::New();
      metric->Register();
      return metric.GetPointer();
    }
    case Demons:
    {
      typedef itk::DemonsImageToImageMetricv4< FixedImageType, MovingImageType > _MetricType;
      typename _MetricType::Pointer metric = _MetricType::New();
      metric->SetIntensityDifferenceThreshold(m_MetricIntensityDifferenceThreshold);
      metric->Register();
      return metric.GetPointer();
    }
    case JointHistogramMutualInformation:
    {
      typedef itk::JointHistogramMutualInformationImageToImageMetricv4< FixedImageType, MovingImageType > _MetricType;
      typename _MetricType::Pointer metric = _MetricType::New();
      metric->SetNumberOfHistogramBins(m_MetricNumberOfHistogramBins);
      metric->SetVarianceForJointPDFSmoothing(m_MetricVarianceForJointPDFSmoothing);
      metric->Register();
      return metric.GetPointer();
    }
    case MeanSquares:
    {
      typedef itk::MeanSquaresImageToImageMetricv4< FixedImageType, MovingImageType > _MetricType;
      typename _MetricType::Pointer metric = _MetricType::New();
      metric->Register();
      return metric.GetPointer();
    }
    case MattesMutualInformation:
    {
      typedef itk::MattesMutualInformationImageToImageMetricv4< FixedImageType, MovingImageType > _MetricType;
      typename _MetricType::Pointer metric = _MetricType::New();
      metric->SetNumberOfHistogramBins(m_MetricNumberOfHistogramBins);
      metric->Register();
      return metric.GetPointer();
    }
    default:
      break; // fall through to exception
    }
  sitkExceptionMacro("LogicError: Unexpected case!");

}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerAsConjugateGradientLineSearch( double learningRate,
                                                                    unsigned int numberOfIterations,
                                                                    double convergenceMinimumValue,
                                                                    unsigned int convergenceWindowSize,
                                                                    double lineSearchLowerLimit,
                                                                    double lineSearchUpperLimit,
                                                                    double lineSearchEpsilon,
                                                                    unsigned int lineSearchMaximumIterations,
                                                                    EstimateLearningRateType estimateLearningRate,
                                                                    double maximumStepSizeInPhysicalUnits )
{
  m_OptimizerType = ConjugateGradientLineSearch;
  m_OptimizerLearningRate = learningRate;
  m_OptimizerNumberOfIterations = numberOfIterations;
  m_OptimizerConvergenceMinimumValue = convergenceMinimumValue;
  m_OptimizerConvergenceWindowSize = convergenceWindowSize;
  m_OptimizerLineSearchLowerLimit = lineSearchLowerLimit;
  m_OptimizerLineSearchUpperLimit = lineSearchUpperLimit;
  m_OptimizerLineSearchEpsilon = lineSearchEpsilon;
  m_OptimizerLineSearchMaximumIterations = lineSearchMaximumIterations;
  m_OptimizerEstimateLearningRate = estimateLearningRate;
  m_OptimizerMaximumStepSizeInPhysicalUnits = maximumStepSizeInPhysicalUnits;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerAsRegularStepGradientDescent( double learningRate,
                                                                   double minStep,
                                                                   unsigned int numberOfIteratons,
                                                                   double relaxationFactor,
                                                                   double gradientMagnitudeTolerance,
                                                                   EstimateLearningRateType estimateLearningRate,
                                                                   double maximumStepSizeInPhysicalUnits )
{
  m_OptimizerType = RegularStepGradientDescent;
  m_OptimizerLearningRate = learningRate;
  m_OptimizerMinimumStepLength = minStep;
  m_OptimizerNumberOfIterations = numberOfIteratons;
  m_OptimizerRelaxationFactor = relaxationFactor;
  m_OptimizerGradientMagnitudeTolerance = gradientMagnitudeTolerance;
  m_OptimizerEstimateLearningRate = estimateLearningRate;
  m_OptimizerMaximumStepSizeInPhysicalUnits = maximumStepSizeInPhysicalUnits;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerAsGradientDescent( double learningRate,
                                                        unsigned int numberOfIteratons,
                                                        double convergenceMinimumValue,
                                                        unsigned int convergenceWindowSize,
                                                        EstimateLearningRateType estimateLearningRate,
                                                        double maximumStepSizeInPhysicalUnits )
{
  m_OptimizerType = GradientDescent;
  m_OptimizerLearningRate = learningRate;
  m_OptimizerNumberOfIterations = numberOfIteratons;
  m_OptimizerConvergenceMinimumValue = convergenceMinimumValue;
  m_OptimizerConvergenceWindowSize = convergenceWindowSize;
  m_OptimizerEstimateLearningRate = estimateLearningRate;
  m_OptimizerMaximumStepSizeInPhysicalUnits = maximumStepSizeInPhysicalUnits;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerAsGradientDescentLineSearch( double learningRate,
                                                                  unsigned int numberOfIterations,
                                                                  double convergenceMinimumValue,
                                                                  unsigned int convergenceWindowSize,
                                                                  double lineSearchLowerLimit,
                                                                  double lineSearchUpperLimit,
                                                                  double lineSearchEpsilon,
                                                                  unsigned int lineSearchMaximumIterations,
                                                                  EstimateLearningRateType estimateLearningRate,
                                                                  double maximumStepSizeInPhysicalUnits )
{
  m_OptimizerType = GradientDescentLineSearch;
  m_OptimizerLearningRate = learningRate;
  m_OptimizerNumberOfIterations = numberOfIterations;
  m_OptimizerConvergenceMinimumValue = convergenceMinimumValue;
  m_OptimizerConvergenceWindowSize = convergenceWindowSize;
  m_OptimizerLineSearchLowerLimit = lineSearchLowerLimit;
  m_OptimizerLineSearchUpperLimit = lineSearchUpperLimit;
  m_OptimizerLineSearchEpsilon = lineSearchEpsilon;
  m_OptimizerLineSearchMaximumIterations = lineSearchMaximumIterations;
  m_OptimizerEstimateLearningRate = estimateLearningRate;
  m_OptimizerMaximumStepSizeInPhysicalUnits = maximumStepSizeInPhysicalUnits;
  return *this;
}


ImageRegistrationMethod::Self&
  ImageRegistrationMethod::SetOptimizerAsLBFGSB( double gradientConvergenceTolerance,
                                                 unsigned int maximumNumberOfIterations,
                                                 unsigned int maximumNumberOfCorrections,
                                                 unsigned int maximumNumberOfFunctionEvaluations,
                                                 double costFunctionConvergenceFactor,
                                                 double lowerBound,
                                                 double upperBound)
{
  m_OptimizerType = LBFGSB;
  m_OptimizerGradientConvergenceTolerance = gradientConvergenceTolerance;
  m_OptimizerNumberOfIterations = maximumNumberOfIterations;
  m_OptimizerMaximumNumberOfCorrections = maximumNumberOfCorrections;
  m_OptimizerMaximumNumberOfFunctionEvaluations = maximumNumberOfFunctionEvaluations;
  m_OptimizerCostFunctionConvergenceFactor = costFunctionConvergenceFactor;
  m_OptimizerLowerBound = lowerBound;
  m_OptimizerUpperBound = upperBound;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerScales( const std::vector<double> &scales)
{
  this->m_OptimizerScalesType = Manual;
  this->m_OptimizerScales = scales;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerScalesFromJacobian( unsigned int centralRegionRadius )
{
  this->m_OptimizerScalesType = Jacobian;
  this->m_OptimizerScalesCentralRegionRadius = centralRegionRadius;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerScalesFromIndexShift( unsigned int centralRegionRadius,
                                                           double smallParameterVariation )
{
  this->m_OptimizerScalesType = IndexShift;
  this->m_OptimizerScalesCentralRegionRadius = centralRegionRadius;
  this->m_OptimizerScalesSmallParameterVariation = smallParameterVariation;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerScalesFromPhysicalShift( unsigned int centralRegionRadius,
                                                              double smallParameterVariation )
{
  this->m_OptimizerScalesType = PhysicalShift;
  this->m_OptimizerScalesCentralRegionRadius = centralRegionRadius;
  this->m_OptimizerScalesSmallParameterVariation = smallParameterVariation;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricSamplingPercentage(double percentage)
{
  m_MetricSamplingPercentage.resize(1);
  m_MetricSamplingPercentage[0] = percentage;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricSamplingPercentagePerLevel(const std::vector<double> &percentage)
{
  m_MetricSamplingPercentage = percentage;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricSamplingStrategy( MetricSamplingStrategyType strategy)
{
  m_MetricSamplingStrategy = strategy;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetShrinkFactorsPerLevel( const std::vector<unsigned int> &shrinkFactors )
{
  this->m_ShrinkFactorsPerLevel = shrinkFactors;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetSmoothingSigmasPerLevel( const std::vector<double> &smoothingSigmas )
{
  this->m_SmoothingSigmasPerLevel = smoothingSigmas;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetSmoothingSigmasAreSpecifiedInPhysicalUnits(bool arg)
{
  m_SmoothingSigmasAreSpecifiedInPhysicalUnits = arg;
  return *this;
}

const std::string &ImageRegistrationMethod::GetOptimizerStopConditionDescription() const
{
  return this->m_StopConditionDescription;
}

unsigned int ImageRegistrationMethod::GetOptimizerIteration() const
{
  if (bool(this->m_pfGetOptimizerIteration))
    {
    return this->m_pfGetOptimizerIteration();
    }
  return this->m_Iteration;
}


std::vector<double> ImageRegistrationMethod::GetOptimizerPosition() const
{
  if(bool(this->m_pfGetOptimizerPosition))
    {
    return this->m_pfGetOptimizerPosition();
    }
  return std::vector<double>();
}

double ImageRegistrationMethod::GetMetricValue() const
{
  if(bool(this->m_pfGetMetricValue))
    {
    return this->m_pfGetMetricValue();
    }
  return m_MetricValue;
}

template <typename TMetric>
 itk::RegistrationParameterScalesEstimator< TMetric >*
ImageRegistrationMethod::CreateScalesEstimator()
{
  switch(m_OptimizerScalesType)
    {
    case Jacobian:
    {
      typedef RegistrationParameterScalesFromJacobian<TMetric> ScalesEstimatorType;
      typename ScalesEstimatorType::Pointer scalesEstimator = ScalesEstimatorType::New();
      scalesEstimator->SetCentralRegionRadius(this->m_OptimizerScalesCentralRegionRadius);
      scalesEstimator->Register();
      return scalesEstimator;
    }
    case IndexShift:
    {
      typedef RegistrationParameterScalesFromIndexShift<TMetric> ScalesEstimatorType;
      typename ScalesEstimatorType::Pointer scalesEstimator = ScalesEstimatorType::New();
      scalesEstimator->SetCentralRegionRadius(this->m_OptimizerScalesCentralRegionRadius);
      scalesEstimator->SetSmallParameterVariation(this->m_OptimizerScalesSmallParameterVariation);
      scalesEstimator->Register();
      return scalesEstimator;
    }
    case PhysicalShift:
    {
      typedef RegistrationParameterScalesFromPhysicalShift<TMetric> ScalesEstimatorType;
      typename ScalesEstimatorType::Pointer scalesEstimator = ScalesEstimatorType::New();
      scalesEstimator->SetCentralRegionRadius(this->m_OptimizerScalesCentralRegionRadius);
      scalesEstimator->SetSmallParameterVariation(this->m_OptimizerScalesSmallParameterVariation);
      scalesEstimator->Register();
      return scalesEstimator;
    }
    case Manual:
      return NULL;
    default:
      break; // fall through to exception
    }
  sitkExceptionMacro("LogicError: Unexpected case!");

}

Transform ImageRegistrationMethod::Execute ( const Image &fixed, const Image & moving )
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

template<class TImageType>
Transform ImageRegistrationMethod::ExecuteInternal ( const Image &inFixed, const Image &inMoving )
{
  typedef TImageType     FixedImageType;
  typedef TImageType     MovingImageType;


  typedef itk::ImageRegistrationMethodv4<FixedImageType, MovingImageType>  RegistrationType;
  typename RegistrationType::Pointer   registration  = RegistrationType::New();

    typename RegistrationType::InitialTransformType *itkTx;
  if ( !(itkTx = dynamic_cast<typename RegistrationType::InitialTransformType *>(this->m_Transform.GetITKBase())) )
    {
    sitkExceptionMacro( "Unexpected error converting transform! Possible miss matching dimensions!" );
    }

  registration->SetInitialTransform( itkTx );
  registration->InPlaceOn();

  // Get the pointer to the ITK image contained in image1
  typename FixedImageType::ConstPointer fixed = this->CastImageToITK<FixedImageType>( inFixed );
  typename MovingImageType::ConstPointer moving = this->CastImageToITK<MovingImageType>( inMoving );

  typedef itk::ImageToImageMetricv4<FixedImageType, MovingImageType> _MetricType;
  typename _MetricType::Pointer metric = this->CreateMetric<FixedImageType>();
  registration->SetMetric( metric );
  metric->UnRegister();

  metric->SetMaximumNumberOfThreads(this->GetNumberOfThreads());

  metric->SetUseMovingImageGradientFilter(true);
  metric->SetUseFixedImageGradientFilter(true);

  typedef itk::InterpolateImageFunction< FixedImageType, double > FixedInterpolatorType;
  typename FixedInterpolatorType::Pointer   fixedInterpolator  = CreateInterpolator(fixed.GetPointer(), m_Interpolator);
  metric->SetFixedInterpolator( fixedInterpolator );

  typedef itk::InterpolateImageFunction< MovingImageType, double > MovingInterpolatorType;
  typename MovingInterpolatorType::Pointer   movingInterpolator  = CreateInterpolator(moving.GetPointer(), m_Interpolator);
  metric->SetMovingInterpolator( movingInterpolator );

  registration->SetFixedImage( fixed );
  registration->SetMovingImage( moving );

  // determine number of levels
  const unsigned int numberOfLevels = m_ShrinkFactorsPerLevel.size();
  if (m_ShrinkFactorsPerLevel.size() != m_SmoothingSigmasPerLevel.size())
    {
    sitkExceptionMacro( "Number of per level parameters for shrink factors and smoothing sigmas don't match!");
    }
  registration->SetNumberOfLevels(numberOfLevels);

  // set sampling

  // todo test enum match
  typename RegistrationType::MetricSamplingStrategyType itkSamplingStrategy = static_cast<typename RegistrationType::MetricSamplingStrategyType>(int(m_MetricSamplingStrategy));
  registration->SetMetricSamplingStrategy(itkSamplingStrategy);

  if (m_MetricSamplingPercentage.size()==1)
    {
    registration->SetMetricSamplingPercentage(this->m_MetricSamplingPercentage[0]);
    }
  else
    {
    if (m_ShrinkFactorsPerLevel.size() != m_MetricSamplingPercentage.size())
      {
      sitkExceptionMacro("Number of per level sampling percentage does not match!");
      }
    typename RegistrationType::MetricSamplingPercentageArrayType param(m_MetricSamplingPercentage.size());
    std::copy(m_MetricSamplingPercentage.begin(), m_MetricSamplingPercentage.end(), param.begin());
    registration->SetMetricSamplingPercentagePerLevel(param);
    }

  typename RegistrationType::ShrinkFactorsArrayType shrinkFactorsPerLevel( m_ShrinkFactorsPerLevel.size() );
  std::copy(m_ShrinkFactorsPerLevel.begin(), m_ShrinkFactorsPerLevel.end(), shrinkFactorsPerLevel.begin());
  registration->SetShrinkFactorsPerLevel( shrinkFactorsPerLevel );

  typename RegistrationType::SmoothingSigmasArrayType smoothingSigmasPerLevel( m_SmoothingSigmasPerLevel.size() );
  std::copy(m_SmoothingSigmasPerLevel.begin(), m_SmoothingSigmasPerLevel.end(), smoothingSigmasPerLevel.begin());
  registration->SetSmoothingSigmasPerLevel( smoothingSigmasPerLevel );
  registration->SetSmoothingSigmasAreSpecifiedInPhysicalUnits(m_SmoothingSigmasAreSpecifiedInPhysicalUnits);

  typename  itk::ObjectToObjectOptimizerBaseTemplate<double>::Pointer optimizer = this->CreateOptimizer( itkTx->GetNumberOfParameters() );
  optimizer->UnRegister();

  optimizer->SetNumberOfThreads(this->GetNumberOfThreads());

  registration->SetOptimizer( optimizer );

  typename itk::RegistrationParameterScalesEstimator< _MetricType >::Pointer scalesEstimator = this->CreateScalesEstimator<_MetricType>();
  if (scalesEstimator)
    {
    scalesEstimator->UnRegister();
    scalesEstimator->SetMetric( metric );
    scalesEstimator->SetTransformForward( true );
    optimizer->SetScalesEstimator( scalesEstimator );
    }
  else if ( m_OptimizerScales.size() )
    {
    itk::ObjectToObjectOptimizerBaseTemplate<double>::ScalesType scales(m_OptimizerScales.size());
    std::copy( m_OptimizerScales.begin(), m_OptimizerScales.end(), scales.begin() );
    optimizer->SetScales(scales);
    }

  this->m_ActiveOptimizer = optimizer;
  this->PreUpdate( registration.GetPointer() );

  if (this->GetDebug())
    {
    registration->Print(std::cout);
    registration->GetOptimizer()->Print(std::cout);
    registration->GetMetric()->Print(std::cout);
    }

  registration->Update();


  // update measurements
  this->m_StopConditionDescription = registration->GetOptimizer()->GetStopConditionDescription();

  m_MetricValue = this->GetMetricValue();
  m_Iteration = this->GetOptimizerIteration();

  m_pfGetOptimizerIteration = nsstd::function<unsigned int()>();
  m_pfGetOptimizerPosition =  nsstd::function<std::vector<double>()>();
  m_pfGetMetricValue = nsstd::function<double()>();


  return this->m_Transform;
}


void ImageRegistrationMethod::PreUpdate( itk::ProcessObject *p )
{
  Superclass::PreUpdate(p);
}



unsigned long ImageRegistrationMethod::AddITKObserver(const itk::EventObject &e, itk::Command *c)
{
  assert(this->m_ActiveOptimizer);

  if (e.CheckEvent(&GetITKEventObject(sitkIterationEvent)))
    {
    return this->m_ActiveOptimizer->AddObserver(e,c);
    }
  return Superclass::AddITKObserver(e,c);
}

void ImageRegistrationMethod::RemoveITKObserver( EventCommand &e )
{
  assert(this->m_ActiveOptimizer);

  if (e.m_Event == sitkIterationEvent)
    {
    this->m_ActiveOptimizer->RemoveObserver(e.m_ITKTag);
    return;
    }
  return Superclass::RemoveITKObserver(e);
}

void ImageRegistrationMethod::OnActiveProcessDelete( ) throw()
{
  Superclass::OnActiveProcessDelete( );
  this->m_ActiveOptimizer = NULL;
}


}
}
