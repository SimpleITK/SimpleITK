#include "sitkMattesMutualInformationMetric.h"

namespace itk
{
namespace simple
{
  MattesMutualInformationMetric::MattesMutualInformationMetric() {
    m_MemberFactory.reset( new  detail::MemberFunctionFactory<MemberFunctionType>( this ) );
    // cast between basic images
    m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 3, GetMetricMemberFunctionAddressor<MemberFunctionType> > ();
    m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 2, GetMetricMemberFunctionAddressor<MemberFunctionType> > ();
  }



  template<class TImage>
  ::itk::SingleValuedCostFunction::Pointer MattesMutualInformationMetric::GetMetricInternal ( const Image &image )
  {
    Unused( image );
    typename ::itk::MattesMutualInformationImageToImageMetric<TImage,TImage>::Pointer metric = ::itk::MattesMutualInformationImageToImageMetric<TImage,TImage>::New();
    metric->SetNumberOfHistogramBins ( 128 );
    metric->SetNumberOfSpatialSamples( 1000000 );
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


