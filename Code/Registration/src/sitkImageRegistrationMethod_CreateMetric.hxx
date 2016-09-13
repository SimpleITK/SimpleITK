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
#ifndef sitkImageRegistrationMethod_CreateMetric_hxx
#define sitkImageRegistrationMethod_CreateMetric_hxx

#include "sitkImageRegistrationMethod.h"

#include "itkANTSNeighborhoodCorrelationImageToImageMetricv4.h"
#include "itkCorrelationImageToImageMetricv4.h"
#include "itkDemonsImageToImageMetricv4.h"
#include "itkJointHistogramMutualInformationImageToImageMetricv4.h"
#include "itkMeanSquaresImageToImageMetricv4.h"
#include "itkMattesMutualInformationImageToImageMetricv4.h"

namespace itk
{
namespace simple
{

template <class TImageType>
itk::ImageToImageMetricv4<TImageType,
                          TImageType,
                          TImageType,
                          double,
                          itk::DefaultImageToImageMetricTraitsv4< TImageType, TImageType, TImageType, double >
                          >*
ImageRegistrationMethod::CreateMetric( )
{
  typedef TImageType     FixedImageType;
  typedef TImageType     MovingImageType;


  switch (m_MetricType)
    {
    case ANTSNeighborhoodCorrelation:
    {
    typedef itk::ANTSNeighborhoodCorrelationImageToImageMetricv4<FixedImageType, MovingImageType > _MetricType;

      typename _MetricType::Pointer metric = _MetricType::New();
      typename _MetricType::RadiusType radius;
      radius.Fill( m_MetricRadius );
      metric->SetRadius( radius );
      metric->Register();
      return metric.GetPointer();
    }
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

}
}
#endif  // sitkImageRegistrationMethod_CreateMetric_hxx
