#ifndef __sitkLinearInterpolate_h
#define __sitkLinearInterpolate_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "sitkImage.h"
#include "itkLinearInterpolateImageFunction.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkInterpolate.h"

namespace itk
{
namespace simple
{
class LinearInterpolate : public Interpolate
  {
  public:
    LinearInterpolate();
    ::itk::Object::Pointer GetInterpolator ( Image* image );
  protected:
    template<class TImage>
    ::itk::Object::Pointer GetInterpolatorInternal ( Image* image );
    template < class TMemberFunctionPointer >
    struct GetInterpolatorMemberFunctionAddressor
    {
      typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

      template< typename TImage >
      TMemberFunctionPointer operator() ( void ) const
      {
        return &ObjectType::template GetInterpolatorInternal < TImage >;
      }
    };

    typedef ::itk::Object::Pointer (LinearInterpolate::*MemberFunctionType)( Image* image );
    friend struct GetInterpolatorMemberFunctionAddressor<MemberFunctionType>;
    std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    virtual Interpolate* Clone() { return new LinearInterpolate ( *this ); };
  };
}
}

#endif
