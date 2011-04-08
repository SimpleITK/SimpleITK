#include "sitkMattesMutualInformationMetric.h"

namespace itk
{
namespace simple
{
  MattesMutualInformationMetric::MattesMutualInformationMetric() {
    m_MemberFactory.reset( new  detail::MemberFunctionFactory<MemberFunctionType>( this ) );
    this->m_HistogramBins = 128;
    this->m_SpatialSamples = 20000;
    // cast between basic images
    m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 3, GetMetricMemberFunctionAddressor<MemberFunctionType> > ();
    m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 2, GetMetricMemberFunctionAddressor<MemberFunctionType> > ();
  }


  MattesMutualInformationMetric& MattesMutualInformationMetric::SetNumberOfHistogramBins ( uint32_t bins )
  {
    this->m_HistogramBins = bins;
    return *this;
  }
  uint32_t MattesMutualInformationMetric::GetNumberOfHistogramBins()
  {
    return this->m_HistogramBins;
  }
  MattesMutualInformationMetric& MattesMutualInformationMetric::SetNumberOfSpatialSamples ( uint32_t samples )
  {
    this->m_SpatialSamples = samples;
    return *this;
  }
  uint32_t MattesMutualInformationMetric::GetNumberOfSpatialSamples()
  {
    return this->m_SpatialSamples;
  }

  template<class TImage>
  ::itk::SingleValuedCostFunction::Pointer MattesMutualInformationMetric::GetMetricInternal ( const Image &image )
  {
    typename ::itk::MattesMutualInformationImageToImageMetric<TImage,TImage>::Pointer metric = ::itk::MattesMutualInformationImageToImageMetric<TImage,TImage>::New();
    metric->SetNumberOfHistogramBins ( m_HistogramBins );
    metric->SetNumberOfSpatialSamples( m_SpatialSamples );
    return metric.GetPointer();
  }

  ::itk::SingleValuedCostFunction::Pointer MattesMutualInformationMetric::GetMetric ( const Image &image )
  {
  const PixelIDValueType fixedType = image.GetPixelIDValue();
  const unsigned int fixedDim = image.GetDimension();
  if (this->m_MemberFactory->HasMemberFunction( fixedType, fixedDim ) )
    {
      return this->m_MemberFactory->GetMemberFunction( fixedType, fixedDim )( image );
    }

  sitkExceptionMacro( << "Filter does not support fixed image type: " << itk::simple::GetPixelIDValueAsString (fixedType) );
  }
}
}


