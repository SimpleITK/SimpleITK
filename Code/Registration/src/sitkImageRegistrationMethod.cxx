/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#include "sitkImageRegistrationMethod.h"

#include "sitkCreateInterpolator.hxx"
#include "sitkCastImageFilter.h"

#include "itkImageMaskSpatialObject.h"
#include "itkImage.h"
#include "itkImageRegistrationMethodv4.h"

#include "itkRegistrationParameterScalesFromJacobian.h"
#include "itkRegistrationParameterScalesFromIndexShift.h"
#include "itkRegistrationParameterScalesFromPhysicalShift.h"

#include "sitkImageRegistrationMethod_CreateParametersAdaptor.hxx"


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
namespace
{

struct CurrentLevelCustomCast
{
  template<typename TRegistrationType>
  static unsigned int CustomCast(const TRegistrationType *reg)
    {
      itk::SizeValueType ret = reg->GetCurrentLevel();
      if (ret > std::numeric_limits<unsigned int>::max())
        {
        return 0;
        }
      return static_cast<unsigned int>(ret);
    }
};
}

ImageRegistrationMethod::ImageRegistrationMethod()
  : m_Interpolator(sitkLinear),
    m_InitialTransformInPlace(true),
    m_OptimizerScalesType(Manual),
    m_MetricSamplingPercentage(1,1.0),
    m_MetricSamplingStrategy(NONE),
    m_MetricSamplingSeed(0u),
    m_MetricUseFixedImageGradientFilter(true),
    m_MetricUseMovingImageGradientFilter(true),
    m_ShrinkFactorsPerLevel(1, 1),
    m_SmoothingSigmasPerLevel(1,0.0),
    m_SmoothingSigmasAreSpecifiedInPhysicalUnits(true),
    m_ActiveOptimizer(NULL)
{
  m_MemberFactory.reset( new  detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  m_EvaluateMemberFactory.reset( new detail::MemberFunctionFactory<EvaluateMemberFunctionType>(this) );

  // m_MemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, 3 > ();
  // m_MemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, 2 > ();

  m_MemberFactory->RegisterMemberFunctions< RealPixelIDTypeList, 3 > ();
  m_MemberFactory->RegisterMemberFunctions< RealPixelIDTypeList, 2 > ();

  typedef EvaluateMemberFunctionAddressor<EvaluateMemberFunctionType> EvaluateMemberFunctionAddressorType;
  m_EvaluateMemberFactory->RegisterMemberFunctions< RealPixelIDTypeList, 3, EvaluateMemberFunctionAddressorType > ();
  m_EvaluateMemberFactory->RegisterMemberFunctions< RealPixelIDTypeList, 2, EvaluateMemberFunctionAddressorType > ();

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
  this->ToStringHelper(out, this->m_InitialTransform.ToString());
  out << std::endl;

  return out.str();
}


ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetInitialTransform ( const Transform &transform )
{
  this->m_InitialTransform = transform;
  this->m_InitialTransform.MakeUnique();
  this->m_InitialTransformInPlace = true;
  return *this;
    }


ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetInitialTransform ( Transform &transform, bool inPlace )
{
  if (inPlace)
    {
    // The registration framework will modify this transform. We
    // need to make it unique so that it can be written to.
    transform.MakeUnique();
    }


  this->m_InitialTransform = transform;
  this->m_InitialTransformInPlace = inPlace;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetVirtualDomain( const std::vector<uint32_t> &virtualSize,
                            const std::vector<double> &virtualOrigin,
                            const std::vector<double> &virtualSpacing,
                            const std::vector<double> &virtualDirection )
{
  const size_t dim = virtualSize.size();

  if ( virtualOrigin.size() != dim )
    {
    sitkExceptionMacro("Expected virtualOrigin to be of length " << dim << "!" );
    }

  if ( virtualSpacing.size() != dim )
    {
    sitkExceptionMacro("Expected virtualSpacing to be of length " << dim << "!" );
    }

  if ( virtualDirection.size() != dim*dim )
    {
    sitkExceptionMacro("Expected virtualDirection to be of length " << dim*dim << "!" );
    }

  this->m_VirtualDomainSize = virtualSize;
  this->m_VirtualDomainOrigin = virtualOrigin;
  this->m_VirtualDomainSpacing = virtualSpacing;
  this->m_VirtualDomainDirection = virtualDirection;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetVirtualDomainFromImage( const Image &virtualImage )
{
  this->m_VirtualDomainSize = virtualImage.GetSize();
  this->m_VirtualDomainOrigin = virtualImage.GetOrigin();
  this->m_VirtualDomainSpacing = virtualImage.GetSpacing();
  this->m_VirtualDomainDirection = virtualImage.GetDirection();

  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricAsANTSNeighborhoodCorrelation(  unsigned int radius )
{
  m_MetricRadius = radius;
  m_MetricType = ANTSNeighborhoodCorrelation;
  return *this;
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
                                               unsigned int numberOfIterations,
                                               unsigned int maximumNumberOfCorrections,
                                               unsigned int maximumNumberOfFunctionEvaluations,
                                               double costFunctionConvergenceFactor,
                                               double lowerBound,
                                               double upperBound,
                                               bool trace )
{
  m_OptimizerType = LBFGSB;
  m_OptimizerGradientConvergenceTolerance = gradientConvergenceTolerance;
  m_OptimizerNumberOfIterations = numberOfIterations;
  m_OptimizerMaximumNumberOfCorrections = maximumNumberOfCorrections;
  m_OptimizerMaximumNumberOfFunctionEvaluations = maximumNumberOfFunctionEvaluations;
  m_OptimizerCostFunctionConvergenceFactor = costFunctionConvergenceFactor;
  m_OptimizerLowerBound = lowerBound;
  m_OptimizerUpperBound = upperBound;
  m_OptimizerTrace = trace;
  return *this;
}


ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerWeights( const std::vector<double> &weights)
{
  this->m_OptimizerWeights = weights;
  return *this;
}

std::vector<double>
ImageRegistrationMethod::GetOptimizerWeights( ) const
{
  return this->m_OptimizerWeights;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerAsExhaustive(const std::vector<unsigned int> &numberOfSteps,
                                                  double stepLength )
{
  m_OptimizerType = Exhaustive;
  m_OptimizerStepLength = stepLength;
  m_OptimizerNumberOfSteps = numberOfSteps;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerAsAmoeba( double simplexDelta,
                                               unsigned int numberOfIterations,
                                               double parametersConvergenceTolerance,
                                               double functionConvergenceTolerance,
                                               bool withRestarts )
{
  m_OptimizerType = Amoeba;
  m_OptimizerSimplexDelta = simplexDelta;
  m_OptimizerNumberOfIterations = numberOfIterations;
  m_OptimizerParametersConvergenceTolerance = parametersConvergenceTolerance;
  m_OptimizerFunctionConvergenceTolerance = functionConvergenceTolerance;
  m_OptimizerWithRestarts = withRestarts;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerAsPowell(unsigned int numberOfIterations,
                                              unsigned int maximumLineIterations,
                                              double stepLength,
                                              double stepTolerance,
                                              double valueTolerance )
{
  m_OptimizerType = Powell;
  m_OptimizerNumberOfIterations = numberOfIterations;
  m_OptimizerMaximumLineIterations = maximumLineIterations;
  m_OptimizerStepLength = stepLength;
  m_OptimizerStepTolerance = stepTolerance;
  m_OptimizerValueTolerance = valueTolerance;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerAsOnePlusOneEvolutionary(unsigned int numberOfIterations,
                                                              double epsilon,
                                                              double initialRadius,
                                                              double growthFactor,
                                                              double shrinkFactor,
                                                              unsigned int seed)
{
  m_OptimizerType = OnePlusOneEvolutionary;
  m_OptimizerNumberOfIterations = numberOfIterations;
  m_OptimizerEpsilon = epsilon;
  m_OptimizerInitialRadius = initialRadius;
  m_OptimizerGrowthFactor = growthFactor;
  m_OptimizerShrinkFactor = shrinkFactor;
  m_OptimizerSeed = seed;

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
ImageRegistrationMethod::SetMetricFixedMask( const Image &binaryMask )
{
  // todo
  m_MetricFixedMaskImage = binaryMask;
  //m_MetricFixedMaskRegion.clear();
  return *this;
 }

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricMovingMask( const Image &binaryMask )
{
  m_MetricMovingMaskImage = binaryMask;
  //m_MetricMovingMaskRegion.clear();
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerScalesFromJacobian( unsigned int centralRegionRadius )
{
  this->m_OptimizerScalesType = Jacobian;
  this->m_OptimizerScalesCentralRegionRadius = centralRegionRadius;
  this->m_OptimizerScales = std::vector<double>();
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerScalesFromIndexShift( unsigned int centralRegionRadius,
                                                           double smallParameterVariation )
{
  this->m_OptimizerScalesType = IndexShift;
  this->m_OptimizerScalesCentralRegionRadius = centralRegionRadius;
  this->m_OptimizerScalesSmallParameterVariation = smallParameterVariation;
  this->m_OptimizerScales = std::vector<double>();
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetOptimizerScalesFromPhysicalShift( unsigned int centralRegionRadius,
                                                              double smallParameterVariation )
{
  this->m_OptimizerScalesType = PhysicalShift;
  this->m_OptimizerScalesCentralRegionRadius = centralRegionRadius;
  this->m_OptimizerScalesSmallParameterVariation = smallParameterVariation;
  this->m_OptimizerScales = std::vector<double>();
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricSamplingPercentage(double percentage, unsigned int seed)
{
  m_MetricSamplingPercentage.resize(1);
  m_MetricSamplingPercentage[0] = percentage;
  m_MetricSamplingSeed = seed;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricSamplingPercentagePerLevel(const std::vector<double> &percentage, unsigned int seed)
{
  m_MetricSamplingPercentage = percentage;
  m_MetricSamplingSeed = seed;
  return *this;
}

ImageRegistrationMethod::Self&
ImageRegistrationMethod::SetMetricSamplingStrategy( MetricSamplingStrategyType strategy)
{
  m_MetricSamplingStrategy = strategy;
  return *this;
}

ImageRegistrationMethod::Self& ImageRegistrationMethod::SetMetricUseFixedImageGradientFilter(bool arg)
{
  m_MetricUseFixedImageGradientFilter = arg;
  return *this;
}

ImageRegistrationMethod::Self& ImageRegistrationMethod::SetMetricUseMovingImageGradientFilter(bool arg)
{
  m_MetricUseMovingImageGradientFilter = arg;
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

std::string ImageRegistrationMethod::GetOptimizerStopConditionDescription() const
{
  if (bool(this->m_pfGetOptimizerStopConditionDescription))
    {
    return this->m_pfGetOptimizerStopConditionDescription();
    }
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


double ImageRegistrationMethod::GetOptimizerLearningRate() const
{
  if(bool(this->m_pfGetOptimizerLearningRate))
    {
    return this->m_pfGetOptimizerLearningRate();
    }
  return 0.0;
}


double ImageRegistrationMethod::GetOptimizerConvergenceValue() const
{
  if(bool(this->m_pfGetOptimizerConvergenceValue))
    {
    return this->m_pfGetOptimizerConvergenceValue();
    }
  return 0.0;
}


double ImageRegistrationMethod::GetMetricValue() const
{
  if(bool(this->m_pfGetMetricValue))
    {
    return this->m_pfGetMetricValue();
    }
  return m_MetricValue;
}

std::vector<double> ImageRegistrationMethod::GetOptimizerScales() const
{
  if(this->m_OptimizerScalesType==Manual)
    {
    return m_OptimizerScales;
    }
  else if(bool(this->m_pfGetOptimizerScales))
    {
    return this->m_pfGetOptimizerScales();
    }
  return std::vector<double>();
}


unsigned int ImageRegistrationMethod::GetCurrentLevel() const
{
  if (bool(this->m_pfGetCurrentLevel))
    {
    return this->m_pfGetCurrentLevel();
    }
  return 0;
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


template<unsigned int VDimension>
itk::SpatialObject<VDimension> *
ImageRegistrationMethod::CreateSpatialObjectMask(const Image &imageMask)
{
  // this should be checked before this function
  assert(imageMask.GetDimension() == VDimension);

  // todo add the image to the spatial object, the spatial object only
  // seems to support unsigned char image types.

  Image mask = imageMask;

  if (mask.GetPixelID() != sitkUInt8)
    {
    mask = Cast(mask, sitkUInt8);
    }

  // ick assuming uint8 == uchar
  typedef itk::Image<unsigned char, VDimension> ITKImageType;
  typename ITKImageType::ConstPointer itkImage = this->CastImageToITK<ITKImageType>(mask);

  typedef itk::ImageMaskSpatialObject<VDimension> SpatialObjectMaskType;
  typename SpatialObjectMaskType::Pointer spatialMask = SpatialObjectMaskType::New();
  spatialMask->SetImage(itkImage);
  spatialMask->Register();
  return spatialMask;
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
  const unsigned int ImageDimension = FixedImageType::ImageDimension;
  //typedef itk::SpatialObject<ImageDimension> SpatialObjectMaskType;


  typedef itk::ImageRegistrationMethodv4<FixedImageType, MovingImageType>  RegistrationType;
  typename RegistrationType::Pointer   registration  = RegistrationType::New();

  // this variable will hold the initial moving then fixed, then the
  // initial to optimize.
  const std::string strIdentityTransform = "IdentityTransform";

  // Set initial moving transform
  if ( strIdentityTransform != this->m_MovingInitialTransform.GetITKBase()->GetNameOfClass())
    {
    typename RegistrationType::InitialTransformType *itkTx;
    if ( !(itkTx = dynamic_cast<typename RegistrationType::InitialTransformType *>(this->m_MovingInitialTransform.GetITKBase())) )
      {
      sitkExceptionMacro( "Unexpected error converting initial moving transform! Possible miss matching dimensions!" );
      }
    registration->SetMovingInitialTransform(itkTx);
    }

  // Set initial fixed transform
  if ( strIdentityTransform != this->m_FixedInitialTransform.GetITKBase()->GetNameOfClass())
    {
    typename RegistrationType::InitialTransformType *itkTx;
    if ( !(itkTx = dynamic_cast<typename RegistrationType::InitialTransformType *>(this->m_FixedInitialTransform.GetITKBase())) )
      {
      sitkExceptionMacro( "Unexpected error converting initial moving transform! Possible miss matching dimensions!" );
      }
    registration->SetFixedInitialTransform(itkTx);
    }

  typename RegistrationType::InitialTransformType *itkTx;
  if ( !(itkTx = dynamic_cast<typename RegistrationType::InitialTransformType *>(this->m_InitialTransform.GetITKBase())) )
    {
    sitkExceptionMacro( "Unexpected error converting initial transform! Possible miss matching dimensions!" );
    }

  registration->SetInitialTransform( itkTx );
  registration->SetInPlace(this->m_InitialTransformInPlace);


  typedef itk::ObjectToObjectOptimizerBaseTemplate<double> _OptimizerType;
  typename  _OptimizerType::Pointer optimizer = this->CreateOptimizer( itkTx->GetNumberOfParameters() );
  optimizer->UnRegister();

  // allocate optimizer early, to register the registration process
  // object's onDelete callback
  this->m_ActiveOptimizer = optimizer;
  const bool stashedDebug = this->GetDebug();
  this->DebugOff();
  this->PreUpdate( registration.GetPointer() );
  this->SetDebug(stashedDebug);


  // Get the pointer to the ITK image contained in image1
  typename FixedImageType::ConstPointer fixed = this->CastImageToITK<FixedImageType>( inFixed );
  typename MovingImageType::ConstPointer moving = this->CastImageToITK<MovingImageType>( inMoving );

  typedef itk::ImageToImageMetricv4<FixedImageType, MovingImageType> _MetricType;
  typename _MetricType::Pointer metric = this->CreateMetric<FixedImageType>();
  metric->UnRegister();
  this->SetupMetric(metric.GetPointer(), fixed.GetPointer(), moving.GetPointer());

  registration->SetMetric( metric );

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

      }
    typename RegistrationType::MetricSamplingPercentageArrayType param(m_MetricSamplingPercentage.size());
    std::copy(m_MetricSamplingPercentage.begin(), m_MetricSamplingPercentage.end(), param.begin());
    registration->SetMetricSamplingPercentagePerLevel(param);
    }

  if ( m_MetricSamplingSeed == sitkWallClock )
    {
    registration->MetricSamplingReinitializeSeed();
    }
  else
    {
    registration->MetricSamplingReinitializeSeed(m_MetricSamplingSeed);
    }

  typename RegistrationType::ShrinkFactorsArrayType shrinkFactorsPerLevel( m_ShrinkFactorsPerLevel.size() );
  std::copy(m_ShrinkFactorsPerLevel.begin(), m_ShrinkFactorsPerLevel.end(), shrinkFactorsPerLevel.begin());
  registration->SetShrinkFactorsPerLevel( shrinkFactorsPerLevel );

  typename RegistrationType::SmoothingSigmasArrayType smoothingSigmasPerLevel( m_SmoothingSigmasPerLevel.size() );
  std::copy(m_SmoothingSigmasPerLevel.begin(), m_SmoothingSigmasPerLevel.end(), smoothingSigmasPerLevel.begin());
  registration->SetSmoothingSigmasPerLevel( smoothingSigmasPerLevel );
  registration->SetSmoothingSigmasAreSpecifiedInPhysicalUnits(m_SmoothingSigmasAreSpecifiedInPhysicalUnits);


  // setup transform parameters adaptor
  std::vector<typename RegistrationType::TransformParametersAdaptorPointer> adaptors =
    this->CreateTransformParametersAdaptor<typename RegistrationType::TransformParametersAdaptorPointer>(registration.GetPointer());
  registration->SetTransformParametersAdaptorsPerLevel(adaptors);

  //
  // Configure Optimizer
  //
  optimizer->SetNumberOfThreads(this->GetNumberOfThreads());

  registration->SetOptimizer( optimizer );

  if ( m_OptimizerWeights.size( ) )
    {
    itk::ObjectToObjectOptimizerBaseTemplate<double>::ScalesType weights(m_OptimizerWeights.size());
    std::copy( m_OptimizerWeights.begin(), m_OptimizerWeights.end(), weights.begin() );
    optimizer->SetWeights(weights);
    }

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

  if (this->GetDebug())
    {
    registration->Print(std::cout);
    registration->GetOptimizer()->Print(std::cout);
    registration->GetMetric()->Print(std::cout);
    }

  m_pfGetOptimizerStopConditionDescription =  nsstd::bind(&_OptimizerType::GetStopConditionDescription, optimizer.GetPointer());

  m_pfGetCurrentLevel = nsstd::bind(&CurrentLevelCustomCast::CustomCast<RegistrationType>,registration.GetPointer());


  try
    {
    registration->Update();
    }
  catch(std::exception &e)
    {
    m_StopConditionDescription = e.what();

    m_MetricValue = this->GetMetricValue();
    m_Iteration = this->GetOptimizerIteration();

    throw;
    }


  // update measurements
  m_StopConditionDescription = registration->GetOptimizer()->GetStopConditionDescription();

  m_MetricValue = this->GetMetricValue();
  m_Iteration = this->GetOptimizerIteration();

  if (this->m_InitialTransformInPlace)
    {
    if (m_pfUpdateWithBestValue)
      {
      m_pfUpdateWithBestValue(this->m_InitialTransform.GetITKBase());
      }

    return this->m_InitialTransform;
    }
  else
    {
    // TOOD: It should not be necessary to return a composite
    // transform the sitk::Transform class is missing a constructor
    // which accepts an arbitrary ITK transform.
    typename RegistrationType::OutputTransformType* itkOutTx = registration->GetModifiableTransform();

    typedef itk::CompositeTransform<double, ImageDimension> CompositeTransformType;

    typename CompositeTransformType::Pointer comp = CompositeTransformType::New();
    comp->ClearTransformQueue();
    comp->AddTransform( itkOutTx );

    if (m_pfUpdateWithBestValue)
      {
      m_pfUpdateWithBestValue(comp);
      }

    return Transform(comp.GetPointer());
    }
}


double ImageRegistrationMethod::MetricEvaluate ( const Image &fixed, const Image & moving )
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
    return this->m_EvaluateMemberFactory->GetMemberFunction( fixedType, fixedDim )( fixed, moving );
    }

  sitkExceptionMacro( << "Filter does not support fixed image type: " << itk::simple::GetPixelIDValueAsString (fixedType) );

}



template<class TImageType>
double ImageRegistrationMethod::EvaluateInternal ( const Image &inFixed, const Image &inMoving )
{
  typedef TImageType     FixedImageType;
  typedef TImageType     MovingImageType;
  const unsigned int ImageDimension = FixedImageType::ImageDimension;
  //typedef itk::SpatialObject<ImageDimension> SpatialObjectMaskType;

 typedef itk::ImageRegistrationMethodv4<FixedImageType, MovingImageType>  RegistrationType;

  // this variable will hold the initial moving then fixed, then the
  // initial to optimize.
  const std::string strIdentityTransform = "IdentityTransform";

  // Get the pointer to the ITK image contained in image1
  typename FixedImageType::ConstPointer fixed = this->CastImageToITK<FixedImageType>( inFixed );
  typename MovingImageType::ConstPointer moving = this->CastImageToITK<MovingImageType>( inMoving );

  typedef itk::ImageToImageMetricv4<FixedImageType, MovingImageType> _MetricType;
  typename _MetricType::Pointer metric = this->CreateMetric<FixedImageType>();
  metric->UnRegister();

  this->SetupMetric(metric.GetPointer(), fixed.GetPointer(), moving.GetPointer());

  metric->SetFixedImage(fixed);
  metric->SetMovingImage(moving);

  typedef itk::CompositeTransform<double, ImageDimension> CompositeTransformType;
  typename CompositeTransformType::Pointer movingInitialCompositeTransform = CompositeTransformType::New();
  // Set initial moving transform
  if ( strIdentityTransform != this->m_MovingInitialTransform.GetITKBase()->GetNameOfClass())
    {
    typename RegistrationType::InitialTransformType *itkTx;
    if ( !(itkTx = dynamic_cast<typename RegistrationType::InitialTransformType *>(this->m_MovingInitialTransform.GetITKBase())) )
      {
      sitkExceptionMacro( "Unexpected error converting initial moving transform! Possible miss matching dimensions!" );
      }
    movingInitialCompositeTransform->AddTransform(itkTx);
    }

  // Set initial fixed transform
  if ( strIdentityTransform != this->m_FixedInitialTransform.GetITKBase()->GetNameOfClass())
    {
    typename RegistrationType::InitialTransformType *itkTx;
    if ( !(itkTx = dynamic_cast<typename RegistrationType::InitialTransformType *>(this->m_FixedInitialTransform.GetITKBase())) )
      {
      sitkExceptionMacro( "Unexpected error converting initial moving transform! Possible miss matching dimensions!" );
      }
    metric->SetFixedTransform(itkTx);
    }

  typename RegistrationType::InitialTransformType *itkTx;
  if ( !(itkTx = dynamic_cast<typename RegistrationType::InitialTransformType *>(this->m_InitialTransform.GetITKBase())) )
    {
    sitkExceptionMacro( "Unexpected error converting initial transform! Possible miss matching dimensions!" );
    }
  movingInitialCompositeTransform->AddTransform(itkTx);
  metric->SetMovingTransform(movingInitialCompositeTransform);

  metric->Initialize();

  return metric->GetValue();
}


template <class TImageType>
void
ImageRegistrationMethod::SetupMetric(
  itk::ImageToImageMetricv4<TImageType,
  TImageType,
  TImageType,
  double,
  itk::DefaultImageToImageMetricTraitsv4< TImageType, TImageType, TImageType, double >
  >*metric, const TImageType *fixed, const TImageType *moving)
{

  typedef TImageType     FixedImageType;
  typedef TImageType     MovingImageType;
  const unsigned int ImageDimension = FixedImageType::ImageDimension;
  typedef itk::SpatialObject<ImageDimension> SpatialObjectMaskType;

  metric->SetMaximumNumberOfThreads(this->GetNumberOfThreads());

  metric->SetUseFixedImageGradientFilter( m_MetricUseFixedImageGradientFilter );
  metric->SetUseMovingImageGradientFilter( m_MetricUseMovingImageGradientFilter );

  if ( this->m_VirtualDomainSize.size() != 0 )
    {
    typename FixedImageType::SpacingType itkSpacing = sitkSTLVectorToITK<typename FixedImageType::SpacingType>(this->m_VirtualDomainSpacing);
    typename FixedImageType::PointType itkOrigin = sitkSTLVectorToITK<typename FixedImageType::PointType>(this->m_VirtualDomainOrigin);
    typename FixedImageType::DirectionType itkDirection = sitkSTLToITKDirection<typename FixedImageType::DirectionType>(this->m_VirtualDomainDirection);

    typename FixedImageType::RegionType itkRegion;
    itkRegion.SetSize( sitkSTLVectorToITK<typename FixedImageType::SizeType>( this->m_VirtualDomainSize ) );

    metric->SetVirtualDomain( itkSpacing, itkOrigin, itkDirection, itkRegion );
    }

  typedef itk::InterpolateImageFunction< FixedImageType, double > FixedInterpolatorType;
  typename FixedInterpolatorType::Pointer   fixedInterpolator  = CreateInterpolator(fixed, m_Interpolator);
  metric->SetFixedInterpolator( fixedInterpolator );

  typedef itk::InterpolateImageFunction< MovingImageType, double > MovingInterpolatorType;
  typename MovingInterpolatorType::Pointer   movingInterpolator  = CreateInterpolator(moving, m_Interpolator);
  metric->SetMovingInterpolator( movingInterpolator );

  // todo implement ImageRegionSpatialObject
  if ( m_MetricFixedMaskImage.GetSize() != std::vector<unsigned int>(m_MetricFixedMaskImage.GetDimension(), 0u) )
    {
    if ( m_MetricFixedMaskImage.GetDimension() != FixedImageType::ImageDimension )
      {
      sitkExceptionMacro("FixedMaskImage does not match dimension of then fixed image!");
      }
    typename SpatialObjectMaskType::ConstPointer fixedMask = this->CreateSpatialObjectMask<ImageDimension>(m_MetricFixedMaskImage);
    fixedMask->UnRegister();
    metric->SetFixedImageMask(fixedMask);
    }

  if ( m_MetricMovingMaskImage.GetSize() != std::vector<unsigned int>(m_MetricMovingMaskImage.GetDimension(), 0u) )
    {
    if ( m_MetricMovingMaskImage.GetDimension() != MovingImageType::ImageDimension )
      {
      sitkExceptionMacro("MovingMaskImage does not match dimension of the moving image!");
      }
    typename SpatialObjectMaskType::ConstPointer movingMask = this->CreateSpatialObjectMask<ImageDimension>(m_MetricMovingMaskImage);
    movingMask->UnRegister();
    metric->SetMovingImageMask(movingMask);
    }
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

  // clean up all pointer functions here
  this->m_pfGetOptimizerIteration = SITK_NULLPTR;
  this->m_pfGetOptimizerPosition = SITK_NULLPTR;
  this->m_pfGetOptimizerLearningRate = SITK_NULLPTR;
  this->m_pfGetOptimizerConvergenceValue = SITK_NULLPTR;
  this->m_pfGetMetricValue = SITK_NULLPTR;
  this->m_pfGetOptimizerScales = SITK_NULLPTR;
  this->m_pfGetOptimizerStopConditionDescription = SITK_NULLPTR;

  this->m_pfUpdateWithBestValue = SITK_NULLPTR;

  this->m_pfGetCurrentLevel = SITK_NULLPTR;

  this->m_ActiveOptimizer = SITK_NULLPTR;
}


}
}
