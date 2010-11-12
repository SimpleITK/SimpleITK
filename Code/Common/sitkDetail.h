#ifndef __sitkDetails_h
#define __sitkDetails_h

#include "sitkMemberFunctionFactoryBase.h"
#include "itkImage.h"
#include "sitkImage.h"

namespace itk {
namespace simple {

// this namespace is internal classes not part of the external simple ITK interface
namespace detail {


template < class TClass, class TMemberFunctionPointer >
struct MemberFunctionAddressor
{
  template< typename TImageType >
  TMemberFunctionPointer operator() ( void ) const
    {
      return &TClass::template ExecuteInternal< TImageType >;
    }
};


template < typename TMemberFunctionFactory, unsigned int ImageDimension >
struct MemberFunctionInstantiater
{
  MemberFunctionInstantiater( TMemberFunctionFactory &factory )
    : m_Factory( factory )
  {}

  template <class TPixelType>
  void operator()( TPixelType t )
    {
      typedef TPixelType                                        PixelType;
      typedef typename TMemberFunctionFactory::ObjectType       ObjectType;
      typedef typename TMemberFunctionFactory::AddressorType    AddressorType;

      // this maps the pixel type to an array id
      int id = typelist::IndexOf< InstantiatedPixelTypeList, PixelType >::Result;

      AddressorType addressor;
      if ( id > 0 &&  id < typelist::Length< InstantiatedPixelTypeList >::Result )
        {
        typedef itk::Image< PixelType, ImageDimension> ImageType;
        m_Factory.Register(addressor.operator()<ImageType>(), (ImageType*)(NULL));
        }
    }

private:


  TMemberFunctionFactory &m_Factory;
};


}
}
}
#endif
