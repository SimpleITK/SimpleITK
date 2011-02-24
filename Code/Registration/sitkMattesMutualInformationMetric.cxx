#include "sitkMattesMutualInformationMetric.h"

namespace itk
{
namespace simple
{
  MattesMutualInformationMetric::MattesMutualInformationMetric() {
    m_DualMemberFactory.reset( new  detail::DualMemberFunctionFactory<MemberFunctionType>( this ) );
    // cast between basic images
    this->Register2DFunctions();
    this->Register3DFunctions();
  }



  template<class TFixedImage, class TMovingImage>
  ::itk::SingleValuedCostFunction::Pointer MattesMutualInformationMetric::GetMetricInternal ( Image* imageA, Image* imageB )
  {
    ::itk::SingleValuedCostFunction::Pointer ptr = (::itk::SingleValuedCostFunction*) ::itk::MattesMutualInformationImageToImageMetric<TFixedImage,TMovingImage>::New();
    return ptr;
  }

  ::itk::SingleValuedCostFunction::Pointer MattesMutualInformationMetric::GetMetric ( Image* imageA, Image* imageB )
  {
  const PixelIDValueType fixedType = imageA->GetPixelIDValue();
  const PixelIDValueType movingType = imageB->GetPixelIDValue();
  const unsigned int fixedDim = imageA->GetDimension();
  const unsigned int movingDim = imageB->GetDimension();
  if ( fixedDim != movingDim )
    {
      sitkExceptionMacro(<<"This metric does not support images with dimensions " << fixedDim << " and " << movingDim);
    }

  if (this->m_DualMemberFactory->HasMemberFunction( fixedType, movingType, fixedDim ) )
    {
      return this->m_DualMemberFactory->GetMemberFunction( fixedType, movingType, fixedDim )( imageA, imageB );
    }

  sitkExceptionMacro( << "Filter does not support fixed image type: " << itk::simple::GetPixelIDValueAsString (fixedType)
                      << " and moving image type: "
                      << itk::simple::GetPixelIDValueAsString (movingType) );
  }
}
}


