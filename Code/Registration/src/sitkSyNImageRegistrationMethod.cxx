/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#include "sitkSyNImageRegistrationMethod.hxx"

#include "itkCommand.h"
#include "itkEventObject.h"

#include <typeinfo>

namespace itk::simple
{

namespace
{

// ITK's MultiResolutionIterationEvent derives from IterationEvent, so a
// plain IterationEvent observer would also fire at each level start.
class ExactIterationEventCommand : public itk::Command
{
public:
  using Self = ExactIterationEventCommand;
  using Superclass = itk::Command;
  using Pointer = itk::SmartPointer<Self>;
  itkNewMacro(Self);

  void
  SetCommand(itk::Command * command)
  {
    m_Command = command;
  }

  void
  Execute(itk::Object * caller, const itk::EventObject & event) override
  {
    if (typeid(event) == typeid(itk::IterationEvent))
    {
      m_Command->Execute(caller, event);
    }
  }

  void
  Execute(const itk::Object * caller, const itk::EventObject & event) override
  {
    if (typeid(event) == typeid(itk::IterationEvent))
    {
      m_Command->Execute(caller, event);
    }
  }

private:
  itk::Command::Pointer m_Command;
};

} // namespace


SyNImageRegistrationMethod::SyNImageRegistrationMethod()
  : m_Interpolator(sitkLinear)
  , m_InitialTransformInPlace(true)
  , m_MetricType(ANTSNeighborhoodCorrelation)
  , m_MetricRadius(2)
  , m_MetricIntensityDifferenceThreshold(0.001)
  , m_MetricNumberOfHistogramBins(32)
  , m_MetricVarianceForJointPDFSmoothing(1.5)
  , m_MetricSamplingPercentage(1, 1.0)
  , m_MetricSamplingStrategy(NONE)
  , m_MetricSamplingSeed(0u)
  , m_MetricUseFixedImageGradientFilter(false)
  , m_MetricUseMovingImageGradientFilter(false)
  , m_ShrinkFactorsPerLevel({ 8, 4, 2, 1 })
  , m_SmoothingSigmasPerLevel({ 3.0, 2.0, 1.0, 0.0 })
  , m_SmoothingSigmasAreSpecifiedInPhysicalUnits(false)
  , m_NumberOfIterationsPerLevel({ 100, 70, 50, 20 })
  , m_LearningRate(0.2)
  , m_ConvergenceThreshold(1e-6)
  , m_ConvergenceWindowSize(10)
  , m_GaussianSmoothingVarianceForTheUpdateField(3.0)
  , m_GaussianSmoothingVarianceForTheTotalField(0.0)
  , m_DownsampleImagesForMetricDerivatives(true)
  , m_AverageMidPointGradients(false)
  , m_CurrentLevel(0)
  , m_Iteration(0)
  , m_MetricValue(0.0)
  , m_ConvergenceValue(0.0)
  , m_NumberOfValidPoints(0)
{}


SyNImageRegistrationMethod::~SyNImageRegistrationMethod() = default;


std::string
SyNImageRegistrationMethod::ToString() const
{
  using itk::simple::operator<<;
  std::ostringstream out;
  out << "itk::simple" << this->GetName() << std::endl;

  out << Superclass::ToString();

  out << "  Interpolator: ";
  this->ToStringHelper(out, this->m_Interpolator);
  out << std::endl;

  out << "  InitialTransform: ";
  this->ToStringHelper(out, this->m_InitialTransform.ToString());
  out << std::endl;

  out << "  InitialTransformInPlace: ";
  this->ToStringHelper(out, this->m_InitialTransformInPlace);
  out << std::endl;

  out << "  ShrinkFactorsPerLevel: " << this->m_ShrinkFactorsPerLevel << std::endl;
  out << "  SmoothingSigmasPerLevel: " << this->m_SmoothingSigmasPerLevel << std::endl;
  out << "  SmoothingSigmasAreSpecifiedInPhysicalUnits: ";
  this->ToStringHelper(out, this->m_SmoothingSigmasAreSpecifiedInPhysicalUnits);
  out << std::endl;

  out << "  NumberOfIterationsPerLevel: " << this->m_NumberOfIterationsPerLevel << std::endl;
  out << "  LearningRate: " << this->m_LearningRate << std::endl;
  out << "  ConvergenceThreshold: " << this->m_ConvergenceThreshold << std::endl;
  out << "  ConvergenceWindowSize: " << this->m_ConvergenceWindowSize << std::endl;
  out << "  GaussianSmoothingVarianceForTheUpdateField: " << this->m_GaussianSmoothingVarianceForTheUpdateField
      << std::endl;
  out << "  GaussianSmoothingVarianceForTheTotalField: " << this->m_GaussianSmoothingVarianceForTheTotalField
      << std::endl;
  out << "  DownsampleImagesForMetricDerivatives: ";
  this->ToStringHelper(out, this->m_DownsampleImagesForMetricDerivatives);
  out << std::endl;
  out << "  AverageMidPointGradients: ";
  this->ToStringHelper(out, this->m_AverageMidPointGradients);
  out << std::endl;

  return out.str();
}


void
SyNImageRegistrationMethod::SetInitialTransform(const Transform & transform)
{
  const DisplacementFieldTransform check(transform);

  this->m_InitialTransform = transform;
  this->m_InitialTransform.MakeUnique();
  this->m_InitialTransformInPlace = true;
}


void
SyNImageRegistrationMethod::SetInitialTransform(Transform & transform, bool inPlace)
{
  // Validate the type now so a bad transform fails early.
  const DisplacementFieldTransform check(transform);

  // clear before making unique, in case the same transform is being
  // assigned again.
  this->m_InitialTransform = Transform();

  if (inPlace)
  {
    transform.MakeUnique();
  }

  this->m_InitialTransform = transform;
  this->m_InitialTransformInPlace = inPlace;
}


void
SyNImageRegistrationMethod::SetMetricAsANTSNeighborhoodCorrelation(unsigned int radius)
{
  m_MetricRadius = radius;
  m_MetricType = ANTSNeighborhoodCorrelation;
}


void
SyNImageRegistrationMethod::SetMetricAsCorrelation()
{
  m_MetricType = Correlation;
}


void
SyNImageRegistrationMethod::SetMetricAsDemons(double intensityDifferenceThreshold)
{
  m_MetricType = Demons;
  m_MetricIntensityDifferenceThreshold = intensityDifferenceThreshold;
}


void
SyNImageRegistrationMethod::SetMetricAsJointHistogramMutualInformation(unsigned int numberOfHistogramBins,
                                                                       double       varianceForJointPDFSmoothing)
{
  m_MetricType = JointHistogramMutualInformation;
  m_MetricNumberOfHistogramBins = numberOfHistogramBins;
  m_MetricVarianceForJointPDFSmoothing = varianceForJointPDFSmoothing;
}


void
SyNImageRegistrationMethod::SetMetricAsMeanSquares()
{
  m_MetricType = MeanSquares;
}


void
SyNImageRegistrationMethod::SetMetricAsMattesMutualInformation(unsigned int numberOfHistogramBins)
{
  m_MetricType = MattesMutualInformation;
  m_MetricNumberOfHistogramBins = numberOfHistogramBins;
}


void
SyNImageRegistrationMethod::SetMetricFixedMask(const Image & binaryMask)
{
  m_MetricFixedMaskImage = binaryMask;
}


void
SyNImageRegistrationMethod::SetMetricMovingMask(const Image & binaryMask)
{
  m_MetricMovingMaskImage = binaryMask;
}


void
SyNImageRegistrationMethod::SetMetricSamplingPercentage(double percentage, unsigned int seed)
{
  m_MetricSamplingPercentage.resize(1);
  m_MetricSamplingPercentage[0] = percentage;
  m_MetricSamplingSeed = seed;
}


void
SyNImageRegistrationMethod::SetMetricSamplingPercentagePerLevel(const std::vector<double> & percentage,
                                                                unsigned int                seed)
{
  m_MetricSamplingPercentage = percentage;
  m_MetricSamplingSeed = seed;
}


const std::vector<double> &
SyNImageRegistrationMethod::GetMetricSamplingPercentagePerLevel() const
{
  return m_MetricSamplingPercentage;
}


void
SyNImageRegistrationMethod::SetMetricSamplingStrategy(MetricSamplingStrategyType strategy)
{
  m_MetricSamplingStrategy = strategy;
}


void
SyNImageRegistrationMethod::SetMetricUseFixedImageGradientFilter(bool arg)
{
  m_MetricUseFixedImageGradientFilter = arg;
}


void
SyNImageRegistrationMethod::SetMetricUseMovingImageGradientFilter(bool arg)
{
  m_MetricUseMovingImageGradientFilter = arg;
}


void
SyNImageRegistrationMethod::SetShrinkFactorsPerLevel(const std::vector<unsigned int> & shrinkFactors)
{
  this->m_ShrinkFactorsPerLevel = shrinkFactors;
}


void
SyNImageRegistrationMethod::SetSmoothingSigmasPerLevel(const std::vector<double> & smoothingSigmas)
{
  this->m_SmoothingSigmasPerLevel = smoothingSigmas;
}


void
SyNImageRegistrationMethod::SetSmoothingSigmasAreSpecifiedInPhysicalUnits(bool arg)
{
  m_SmoothingSigmasAreSpecifiedInPhysicalUnits = arg;
}


void
SyNImageRegistrationMethod::SetNumberOfIterationsPerLevel(const std::vector<unsigned int> & iterations)
{
  this->m_NumberOfIterationsPerLevel = iterations;
}


void
SyNImageRegistrationMethod::SetLearningRate(double learningRate)
{
  this->m_LearningRate = learningRate;
}


void
SyNImageRegistrationMethod::SetConvergenceThreshold(double threshold)
{
  this->m_ConvergenceThreshold = threshold;
}


void
SyNImageRegistrationMethod::SetConvergenceWindowSize(unsigned int windowSize)
{
  this->m_ConvergenceWindowSize = windowSize;
}


void
SyNImageRegistrationMethod::SetGaussianSmoothingVarianceForTheUpdateField(double variance)
{
  this->m_GaussianSmoothingVarianceForTheUpdateField = variance;
}


void
SyNImageRegistrationMethod::SetGaussianSmoothingVarianceForTheTotalField(double variance)
{
  this->m_GaussianSmoothingVarianceForTheTotalField = variance;
}


void
SyNImageRegistrationMethod::SetDownsampleImagesForMetricDerivatives(bool arg)
{
  this->m_DownsampleImagesForMetricDerivatives = arg;
}


void
SyNImageRegistrationMethod::SetAverageMidPointGradients(bool arg)
{
  this->m_AverageMidPointGradients = arg;
}


unsigned int
SyNImageRegistrationMethod::GetCurrentLevel() const
{
  if (bool(this->m_pfGetCurrentLevel))
  {
    return this->m_pfGetCurrentLevel();
  }
  return this->m_CurrentLevel;
}


unsigned int
SyNImageRegistrationMethod::GetCurrentIteration() const
{
  if (bool(this->m_pfGetCurrentIteration))
  {
    return this->m_pfGetCurrentIteration();
  }
  return this->m_Iteration;
}


double
SyNImageRegistrationMethod::GetMetricValue() const
{
  if (bool(this->m_pfGetMetricValue))
  {
    return this->m_pfGetMetricValue();
  }
  return this->m_MetricValue;
}


double
SyNImageRegistrationMethod::GetConvergenceValue() const
{
  if (bool(this->m_pfGetConvergenceValue))
  {
    return this->m_pfGetConvergenceValue();
  }
  return this->m_ConvergenceValue;
}


uint64_t
SyNImageRegistrationMethod::GetMetricNumberOfValidPoints() const
{
  if (bool(this->m_pfGetMetricNumberOfValidPoints))
  {
    return this->m_pfGetMetricNumberOfValidPoints();
  }
  return this->m_NumberOfValidPoints;
}


std::string
SyNImageRegistrationMethod::GetStopConditionDescription() const
{
  return this->m_StopConditionDescription;
}


DisplacementFieldTransform
SyNImageRegistrationMethod::Execute(const Image & fixed, const Image & moving)
{
  const PixelIDValueType fixedType = fixed.GetPixelIDValue();
  const unsigned int     fixedDim = fixed.GetDimension();
  if (fixed.GetPixelIDValue() != moving.GetPixelIDValue())
  {
    sitkExceptionMacro(<< "Fixed and moving images must be the same datatype! Got " << fixed.GetPixelIDTypeAsString()
                       << " and " << moving.GetPixelIDTypeAsString());
  }

  if (fixed.GetDimension() != moving.GetDimension())
  {
    sitkExceptionMacro(<< "Fixed and moving images must be the same dimensionality! Got " << fixed.GetDimension()
                       << " and " << moving.GetDimension());
  }

  static const auto memberFactory = []() {
    detail::MemberFunctionFactory<MemberFunctionType> factory;
    factory.RegisterMemberFunctions<RealPixelIDTypeList, 3>();
    factory.RegisterMemberFunctions<RealPixelIDTypeList, 2>();
    return factory;
  }();

  if (memberFactory.HasMemberFunction(fixedType, fixedDim))
  {
    return memberFactory.GetMemberFunction(fixedType, fixedDim, this)(fixed, moving);
  }

  sitkExceptionMacro(<< "Filter does not support fixed image type: "
                     << itk::simple::GetPixelIDValueAsString(fixedType));
}


unsigned long
SyNImageRegistrationMethod::AddITKObserver(const itk::EventObject & e, itk::Command * c)
{
  if (typeid(e) == typeid(itk::IterationEvent))
  {
    ExactIterationEventCommand::Pointer filter = ExactIterationEventCommand::New();
    filter->SetCommand(c);
    return Superclass::AddITKObserver(e, filter);
  }
  return Superclass::AddITKObserver(e, c);
}


void
SyNImageRegistrationMethod::OnActiveProcessDelete() noexcept
{
  Superclass::OnActiveProcessDelete();

  this->m_pfGetCurrentLevel = nullptr;
  this->m_pfGetCurrentIteration = nullptr;
  this->m_pfGetMetricValue = nullptr;
  this->m_pfGetConvergenceValue = nullptr;
  this->m_pfGetMetricNumberOfValidPoints = nullptr;
}

} // namespace itk::simple
