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
#ifndef sitkSyNImageRegistrationMethod_hxx
#define sitkSyNImageRegistrationMethod_hxx

#include "sitkSyNImageRegistrationMethod.h"

#include "sitkCreateInterpolator.hxx"
#include "sitkCastImageFilter.h"

#include "itkImage.h"
#include "itkImageMaskSpatialObject.h"
#include "itkDisplacementFieldTransformParametersAdaptor.h"
#include "itkInvertDisplacementFieldImageFilter.h"
#include "itkShrinkImageFilter.h"
#include "itkSyNImageRegistrationMethod.h"

#include "itkANTSNeighborhoodCorrelationImageToImageMetricv4.h"
#include "itkCorrelationImageToImageMetricv4.h"
#include "itkDemonsImageToImageMetricv4.h"
#include "itkJointHistogramMutualInformationImageToImageMetricv4.h"
#include "itkMeanSquaresImageToImageMetricv4.h"
#include "itkMattesMutualInformationImageToImageMetricv4.h"

#include <algorithm>
#include <limits>

namespace itk::simple
{

namespace
{

template <typename TValue>
unsigned int
ClampToUnsignedInt(TValue value)
{
  if (value > std::numeric_limits<unsigned int>::max())
  {
    return std::numeric_limits<unsigned int>::max();
  }
  return static_cast<unsigned int>(value);
}

// The required grid is the shrunken fixed image, which is also the
// virtual domain ITK uses at that level.
template <typename TTransformBase, typename TFixedImageType>
typename TransformParametersAdaptorBase<TTransformBase>::Pointer
CreateSyNDisplacementFieldAdaptor(const FixedArray<unsigned int, TFixedImageType::ImageDimension> & shrinkFactors,
                                  const TFixedImageType *                                           fixedImage)
{
  constexpr unsigned int Dimension = TFixedImageType::ImageDimension;
  using DisplacementFieldTransformType = itk::DisplacementFieldTransform<double, Dimension>;

  auto shrinkFilter = ShrinkImageFilter<TFixedImageType, TFixedImageType>::New();
  shrinkFilter->SetShrinkFactors(shrinkFactors);
  shrinkFilter->SetInput(fixedImage);
  shrinkFilter->UpdateOutputInformation();
  const TFixedImageType * shrunk = shrinkFilter->GetOutput();

  auto adaptor = DisplacementFieldTransformParametersAdaptor<DisplacementFieldTransformType>::New();
  adaptor->SetRequiredSpacing(shrunk->GetSpacing());
  adaptor->SetRequiredSize(shrunk->GetLargestPossibleRegion().GetSize());
  adaptor->SetRequiredDirection(shrunk->GetDirection());
  adaptor->SetRequiredOrigin(shrunk->GetOrigin());
  return adaptor.GetPointer();
}

} // namespace


template <class TImageType>
itk::ImageToImageMetricv4<TImageType,
                          TImageType,
                          TImageType,
                          double,
                          itk::DefaultImageToImageMetricTraitsv4<TImageType, TImageType, TImageType, double>> *
SyNImageRegistrationMethod::CreateMetric()
{
  using FixedImageType = TImageType;
  using MovingImageType = TImageType;

  auto bindNumberOfValidPoints = [this](auto * metric) {
    this->m_pfGetMetricNumberOfValidPoints = [metric] {
      return static_cast<uint64_t>(
        std::min<itk::SizeValueType>(metric->GetNumberOfValidPoints(), std::numeric_limits<uint64_t>::max()));
    };
  };

  switch (m_MetricType)
  {
    case ANTSNeighborhoodCorrelation:
    {
      using _MetricType = itk::ANTSNeighborhoodCorrelationImageToImageMetricv4<FixedImageType, MovingImageType>;
      typename _MetricType::Pointer metric = _MetricType::New();
      bindNumberOfValidPoints(metric.GetPointer());
      typename _MetricType::RadiusType radius;
      radius.Fill(m_MetricRadius);
      metric->SetRadius(radius);
      metric->Register();
      return metric.GetPointer();
    }
    case Correlation:
    {
      using _MetricType = itk::CorrelationImageToImageMetricv4<FixedImageType, MovingImageType>;
      typename _MetricType::Pointer metric = _MetricType::New();
      bindNumberOfValidPoints(metric.GetPointer());
      metric->Register();
      return metric.GetPointer();
    }
    case Demons:
    {
      using _MetricType = itk::DemonsImageToImageMetricv4<FixedImageType, MovingImageType>;
      typename _MetricType::Pointer metric = _MetricType::New();
      bindNumberOfValidPoints(metric.GetPointer());
      metric->SetIntensityDifferenceThreshold(m_MetricIntensityDifferenceThreshold);
      metric->Register();
      return metric.GetPointer();
    }
    case JointHistogramMutualInformation:
    {
      using _MetricType = itk::JointHistogramMutualInformationImageToImageMetricv4<FixedImageType, MovingImageType>;
      typename _MetricType::Pointer metric = _MetricType::New();
      bindNumberOfValidPoints(metric.GetPointer());
      metric->SetNumberOfHistogramBins(m_MetricNumberOfHistogramBins);
      metric->SetVarianceForJointPDFSmoothing(m_MetricVarianceForJointPDFSmoothing);
      metric->Register();
      return metric.GetPointer();
    }
    case MeanSquares:
    {
      using _MetricType = itk::MeanSquaresImageToImageMetricv4<FixedImageType, MovingImageType>;
      typename _MetricType::Pointer metric = _MetricType::New();
      bindNumberOfValidPoints(metric.GetPointer());
      metric->Register();
      return metric.GetPointer();
    }
    case MattesMutualInformation:
    {
      using _MetricType = itk::MattesMutualInformationImageToImageMetricv4<FixedImageType, MovingImageType>;
      typename _MetricType::Pointer metric = _MetricType::New();
      bindNumberOfValidPoints(metric.GetPointer());
      metric->SetNumberOfHistogramBins(m_MetricNumberOfHistogramBins);
      metric->Register();
      return metric.GetPointer();
    }
    default:
      break; // fall through to exception
  }
  sitkExceptionMacro("LogicError: Unexpected case!");
}


template <unsigned int VDimension>
itk::SpatialObject<VDimension> *
SyNImageRegistrationMethod::CreateSpatialObjectMask(const Image & imageMask)
{
  assert(imageMask.GetDimension() == VDimension);

  Image mask = imageMask;
  if (mask.GetPixelID() != sitkUInt8)
  {
    mask = Cast(mask, sitkUInt8);
  }

  // SyN resamples the masks per level and requires an ImageMaskSpatialObject.
  using ITKImageType = itk::Image<unsigned char, VDimension>;
  typename ITKImageType::ConstPointer itkImage = this->CastImageToITK<ITKImageType>(mask);

  using SpatialObjectMaskType = itk::ImageMaskSpatialObject<VDimension>;
  typename SpatialObjectMaskType::Pointer spatialMask = SpatialObjectMaskType::New();
  spatialMask->SetImage(itkImage);
  spatialMask->Register();
  return spatialMask;
}


template <class TImageType>
void
SyNImageRegistrationMethod::SetupMetric(
  itk::ImageToImageMetricv4<TImageType,
                            TImageType,
                            TImageType,
                            double,
                            itk::DefaultImageToImageMetricTraitsv4<TImageType, TImageType, TImageType, double>> *
                     metric,
  const TImageType * fixed,
  const TImageType * moving)
{
  using FixedImageType = TImageType;
  using MovingImageType = TImageType;
  constexpr unsigned int ImageDimension = FixedImageType::ImageDimension;
  using SpatialObjectMaskType = itk::SpatialObject<ImageDimension>;

  if (this->GetNumberOfWorkUnits() > 0)
  {
    metric->SetMaximumNumberOfWorkUnits(this->GetNumberOfWorkUnits());
  }

  metric->SetUseFixedImageGradientFilter(m_MetricUseFixedImageGradientFilter);
  metric->SetUseMovingImageGradientFilter(m_MetricUseMovingImageGradientFilter);

  using FixedInterpolatorType = itk::InterpolateImageFunction<FixedImageType, double>;
  typename FixedInterpolatorType::Pointer fixedInterpolator = CreateInterpolator(fixed, m_Interpolator);
  metric->SetFixedInterpolator(fixedInterpolator);

  using MovingInterpolatorType = itk::InterpolateImageFunction<MovingImageType, double>;
  typename MovingInterpolatorType::Pointer movingInterpolator = CreateInterpolator(moving, m_Interpolator);
  metric->SetMovingInterpolator(movingInterpolator);

  if (m_MetricFixedMaskImage.GetSize() != std::vector<unsigned int>(m_MetricFixedMaskImage.GetDimension(), 0u))
  {
    if (m_MetricFixedMaskImage.GetDimension() != ImageDimension)
    {
      sitkExceptionMacro("FixedMaskImage does not match dimension of the fixed image!");
    }
    typename SpatialObjectMaskType::ConstPointer fixedMask =
      this->CreateSpatialObjectMask<ImageDimension>(m_MetricFixedMaskImage);
    fixedMask->UnRegister();
    metric->SetFixedImageMask(fixedMask);
  }

  if (m_MetricMovingMaskImage.GetSize() != std::vector<unsigned int>(m_MetricMovingMaskImage.GetDimension(), 0u))
  {
    if (m_MetricMovingMaskImage.GetDimension() != ImageDimension)
    {
      sitkExceptionMacro("MovingMaskImage does not match dimension of the moving image!");
    }
    typename SpatialObjectMaskType::ConstPointer movingMask =
      this->CreateSpatialObjectMask<ImageDimension>(m_MetricMovingMaskImage);
    movingMask->UnRegister();
    metric->SetMovingImageMask(movingMask);
  }
}


template <class TImageType>
DisplacementFieldTransform
SyNImageRegistrationMethod::ExecuteInternal(const Image & inFixed, const Image & inMoving)
{
  using FixedImageType = TImageType;
  using MovingImageType = TImageType;
  constexpr unsigned int ImageDimension = FixedImageType::ImageDimension;

  using RegistrationType = itk::SyNImageRegistrationMethod<FixedImageType, MovingImageType>;
  using OutputTransformType = typename RegistrationType::OutputTransformType;
  using DisplacementFieldType = typename OutputTransformType::DisplacementFieldType;
  using InitialTransformType = typename RegistrationType::InitialTransformType;

  typename RegistrationType::Pointer registration = RegistrationType::New();

  const std::string strIdentityTransform = "IdentityTransform";

  if (strIdentityTransform != this->m_MovingInitialTransform.GetITKBase()->GetNameOfClass())
  {
    auto * itkTx = dynamic_cast<InitialTransformType *>(this->m_MovingInitialTransform.GetITKBase());
    if (!itkTx)
    {
      sitkExceptionMacro("Unexpected error converting initial moving transform! Possible miss matching dimensions!");
    }
    registration->SetMovingInitialTransform(itkTx);
  }

  if (strIdentityTransform != this->m_FixedInitialTransform.GetITKBase()->GetNameOfClass())
  {
    auto * itkTx = dynamic_cast<InitialTransformType *>(this->m_FixedInitialTransform.GetITKBase());
    if (!itkTx)
    {
      sitkExceptionMacro("Unexpected error converting initial fixed transform! Possible miss matching dimensions!");
    }
    registration->SetFixedInitialTransform(itkTx);
  }

  typename FixedImageType::ConstPointer  fixed = this->CastImageToITK<FixedImageType>(inFixed);
  typename MovingImageType::ConstPointer moving = this->CastImageToITK<MovingImageType>(inMoving);

  // The output transform is always optimized in place by ITK; a copy
  // is made here instead when the user asked for a non in-place
  // initial transform.
  DisplacementFieldTransform outputTransform = [this, &strIdentityTransform]() {
    if (strIdentityTransform == this->m_InitialTransform.GetITKBase()->GetNameOfClass())
    {
      return DisplacementFieldTransform(FixedImageType::ImageDimension);
    }
    DisplacementFieldTransform tx(this->m_InitialTransform);
    if (!this->m_InitialTransformInPlace)
    {
      auto * itkTx = dynamic_cast<OutputTransformType *>(tx.GetITKBase());
      if (itkTx == nullptr || itkTx->GetDisplacementField() == nullptr)
      {
        return DisplacementFieldTransform(FixedImageType::ImageDimension);
      }
      tx.MakeUnique();
    }
    return tx;
  }();

  auto * itkOutputTransform = dynamic_cast<OutputTransformType *>(outputTransform.GetITKBase());
  if (!itkOutputTransform)
  {
    sitkExceptionMacro("Unexpected error converting initial transform! Possible miss matching dimensions!");
  }

  if (itkOutputTransform->GetDisplacementField() == nullptr)
  {
    auto field = DisplacementFieldType::New();
    field->CopyInformation(fixed);
    field->SetRegions(fixed->GetLargestPossibleRegion());
    field->AllocateInitialized();
    itkOutputTransform->SetDisplacementField(field);
  }
  else
  {
    // SyN starts from its half-way transforms, not the output field, so a
    // supplied deformation seeds the fixed half and the moving half is zero.
    DisplacementFieldType *                 field = itkOutputTransform->GetModifiableDisplacementField();
    typename DisplacementFieldType::Pointer inverseField = itkOutputTransform->GetModifiableInverseDisplacementField();
    if (inverseField == nullptr)
    {
      auto inverter = InvertDisplacementFieldImageFilter<DisplacementFieldType>::New();
      inverter->SetInput(field);
      inverter->SetMaximumNumberOfIterations(20);
      inverter->SetMeanErrorToleranceThreshold(0.001);
      inverter->SetMaxErrorToleranceThreshold(0.1);
      inverter->Update();
      inverseField = inverter->GetOutput();
    }

    auto fixedToMiddle = OutputTransformType::New();
    fixedToMiddle->SetDisplacementField(field);
    fixedToMiddle->SetInverseDisplacementField(inverseField);

    auto zeroField = [field] {
      auto zero = DisplacementFieldType::New();
      zero->CopyInformation(field);
      zero->SetRegions(field->GetLargestPossibleRegion());
      zero->AllocateInitialized();
      return zero;
    };
    auto movingToMiddle = OutputTransformType::New();
    movingToMiddle->SetDisplacementField(zeroField());
    movingToMiddle->SetInverseDisplacementField(zeroField());

    registration->SetFixedToMiddleTransform(fixedToMiddle);
    registration->SetMovingToMiddleTransform(movingToMiddle);
  }

  registration->SetInitialTransform(itkOutputTransform);
  registration->InPlaceOn();

  const bool stashedDebug = this->GetDebug();
  this->DebugOff();
  this->PreUpdate(registration.GetPointer());
  this->SetDebug(stashedDebug);

  using _MetricType = itk::ImageToImageMetricv4<FixedImageType, MovingImageType>;
  typename _MetricType::Pointer metric = this->CreateMetric<FixedImageType>();
  metric->UnRegister();
  this->SetupMetric(metric.GetPointer(), fixed.GetPointer(), moving.GetPointer());

  registration->SetMetric(metric);
  registration->SetFixedImage(fixed);
  registration->SetMovingImage(moving);

  const unsigned int numberOfLevels = m_ShrinkFactorsPerLevel.size();
  if (numberOfLevels == 0)
  {
    sitkExceptionMacro("At least one level is required, but the shrink factors per level are empty!");
  }
  if (m_ShrinkFactorsPerLevel.size() != m_SmoothingSigmasPerLevel.size())
  {
    sitkExceptionMacro("Number of per level parameters for shrink factors and smoothing sigmas don't match!");
  }
  if (m_ShrinkFactorsPerLevel.size() != m_NumberOfIterationsPerLevel.size())
  {
    sitkExceptionMacro("Number of per level parameters for shrink factors and number of iterations don't match!");
  }
  registration->SetNumberOfLevels(numberOfLevels);

  auto itkSamplingStrategy =
    static_cast<typename RegistrationType::MetricSamplingStrategyEnum>(int(m_MetricSamplingStrategy));
  registration->SetMetricSamplingStrategy(itkSamplingStrategy);

  if (m_MetricSamplingPercentage.size() == 1)
  {
    registration->SetMetricSamplingPercentage(this->m_MetricSamplingPercentage[0]);
  }
  else
  {
    if (m_ShrinkFactorsPerLevel.size() != m_MetricSamplingPercentage.size())
    {
      sitkExceptionMacro("Number of per level parameters for shrink factors and sampling percentage don't match!");
    }
    typename RegistrationType::MetricSamplingPercentageArrayType param(m_MetricSamplingPercentage.size());
    std::copy(m_MetricSamplingPercentage.begin(), m_MetricSamplingPercentage.end(), param.begin());
    registration->SetMetricSamplingPercentagePerLevel(param);
  }

  if (m_MetricSamplingSeed == sitkWallClock)
  {
    registration->MetricSamplingReinitializeSeed();
  }
  else
  {
    registration->MetricSamplingReinitializeSeed(m_MetricSamplingSeed);
  }

  typename RegistrationType::ShrinkFactorsArrayType shrinkFactorsPerLevel(m_ShrinkFactorsPerLevel.size());
  std::copy(m_ShrinkFactorsPerLevel.begin(), m_ShrinkFactorsPerLevel.end(), shrinkFactorsPerLevel.begin());
  registration->SetShrinkFactorsPerLevel(shrinkFactorsPerLevel);

  typename RegistrationType::SmoothingSigmasArrayType smoothingSigmasPerLevel(m_SmoothingSigmasPerLevel.size());
  std::copy(m_SmoothingSigmasPerLevel.begin(), m_SmoothingSigmasPerLevel.end(), smoothingSigmasPerLevel.begin());
  registration->SetSmoothingSigmasPerLevel(smoothingSigmasPerLevel);
  registration->SetSmoothingSigmasAreSpecifiedInPhysicalUnits(m_SmoothingSigmasAreSpecifiedInPhysicalUnits);

  typename RegistrationType::NumberOfIterationsArrayType iterationsPerLevel(m_NumberOfIterationsPerLevel.size());
  std::copy(m_NumberOfIterationsPerLevel.begin(), m_NumberOfIterationsPerLevel.end(), iterationsPerLevel.begin());
  registration->SetNumberOfIterationsPerLevel(iterationsPerLevel);

  registration->SetLearningRate(m_LearningRate);
  registration->SetConvergenceThreshold(m_ConvergenceThreshold);
  registration->SetConvergenceWindowSize(m_ConvergenceWindowSize);
  registration->SetGaussianSmoothingVarianceForTheUpdateField(m_GaussianSmoothingVarianceForTheUpdateField);
  registration->SetGaussianSmoothingVarianceForTheTotalField(m_GaussianSmoothingVarianceForTheTotalField);
  registration->SetDownsampleImagesForMetricDerivatives(m_DownsampleImagesForMetricDerivatives);
  registration->SetAverageMidPointGradients(m_AverageMidPointGradients);

  // The half-way transforms are resized at each level by these
  // adaptors; SyN requires one per level (ITK issue 6994).
  std::vector<typename RegistrationType::TransformParametersAdaptorPointer> adaptors;
  for (unsigned int level = 0; level < numberOfLevels; ++level)
  {
    adaptors.push_back(CreateSyNDisplacementFieldAdaptor<InitialTransformType>(
      registration->GetShrinkFactorsPerDimension(level), fixed.GetPointer()));
  }
  registration->SetTransformParametersAdaptorsPerLevel(adaptors);

  sitkDebugMacro(<< *registration << *registration->GetMetric());

  m_pfGetCurrentLevel = [reg = registration.GetPointer()] { return ClampToUnsignedInt(reg->GetCurrentLevel()); };
  m_pfGetCurrentIteration = [reg = registration.GetPointer()] {
    return ClampToUnsignedInt(reg->GetCurrentIteration());
  };
  m_pfGetMetricValue = [reg = registration.GetPointer()] { return reg->GetCurrentMetricValue(); };
  m_pfGetConvergenceValue = [reg = registration.GetPointer()] { return reg->GetCurrentConvergenceValue(); };

  auto storeMeasurements = [this, numberOfLevels] {
    // ITK leaves the level and iteration counters one past the last
    // completed step.
    m_CurrentLevel = std::min(this->GetCurrentLevel(), numberOfLevels - 1);
    m_Iteration = this->GetCurrentIteration();
    if (m_Iteration > 0)
    {
      --m_Iteration;
    }
    m_MetricValue = this->GetMetricValue();
    m_ConvergenceValue = this->GetConvergenceValue();
    m_NumberOfValidPoints = this->GetMetricNumberOfValidPoints();
  };

  try
  {
    registration->Update();
  }
  catch (std::exception & e)
  {
    m_StopConditionDescription = e.what();
    storeMeasurements();
    throw;
  }

  storeMeasurements();

  std::ostringstream description;
  if (registration->GetIsConverged())
  {
    description << "Convergence threshold reached after " << m_Iteration << " iterations at level " << m_CurrentLevel
                << ".";
  }
  else
  {
    description << "Maximum number of iterations (" << m_Iteration << ") exceeded at level " << m_CurrentLevel << ".";
  }
  m_StopConditionDescription = description.str();

  return outputTransform;
}

} // namespace itk::simple

#endif // sitkSyNImageRegistrationMethod_hxx
