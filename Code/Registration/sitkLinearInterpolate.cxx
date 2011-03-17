#include "sitkLinearInterpolate.h"
#include "itkImage.h"
#include "itkLinearInterpolateImageFunction.h"
namespace itk
{
namespace simple
{
  LinearInterpolate::LinearInterpolate()
    {
    m_MemberFactory.reset( new  detail::MemberFunctionFactory<MemberFunctionType>( this ) );
    m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 3, GetInterpolatorMemberFunctionAddressor<MemberFunctionType> > ();
    m_MemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, 2, GetInterpolatorMemberFunctionAddressor<MemberFunctionType> > ();
    }

  template<class TImage>
  ::itk::Object::Pointer LinearInterpolate::GetInterpolatorInternal ( Image* image )
  {
    ::itk::Object::Pointer ptr;
    ptr = (::itk::Object*) (::itk::LinearInterpolateImageFunction<TImage,double>::New());
    return ptr;
  }

  ::itk::Object::Pointer LinearInterpolate::GetInterpolator ( Image* image )
  {
    const PixelIDValueType fixedType = image->GetPixelIDValue();
    const unsigned int fixedDim = image->GetDimension();
    if (this->m_MemberFactory->HasMemberFunction( fixedType, fixedDim ) )
      {
      return this->m_MemberFactory->GetMemberFunction( fixedType, fixedDim )( image );
      }
    sitkExceptionMacro( << "Filter does not support fixed image type: " << itk::simple::GetPixelIDValueAsString (fixedType) );
    return NULL;
  }
}
}


