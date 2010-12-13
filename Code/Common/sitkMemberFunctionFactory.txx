#ifndef __sitkMemberFunctionFactory_txx
#define __sitkMemberFunctionFactory_h

#include "sitkMemberFunctionFactory.h"
#include "sitkDetail.h"

namespace itk
{
namespace simple
{
// this namespace is internal classes not part of the external simple ITK interface
namespace detail {


// a privately declared predicate for use with the typelist::ForEach
// algorithm
//
// This predicate calls the member function factories AddressorType on
// each valid ImageType defined from the pixel type id, and the
// provided dimension,
template < typename TMemberFunctionFactory, unsigned int ImageDimension >
struct MemberFunctionInstantiater
{
  MemberFunctionInstantiater( TMemberFunctionFactory &factory )
    : m_Factory( factory )
    {}

  template <class TPixelIDType>
  void operator()( TPixelIDType )
    {
      typedef TPixelIDType                                      PixelIDType;
      typedef typename TMemberFunctionFactory::ObjectType       ObjectType;
      typedef typename TMemberFunctionFactory::AddressorType    AddressorType;

      // this maps the pixel type to an array id
      int id = PixelIDToPixelIDValue< PixelIDType >::Result;

      AddressorType addressor;
      if ( id > 0 &&  id < typelist::Length< InstantiatedPixelIDTypeList >::Result )
        {
        typedef typename PixelIDToImageType<TPixelIDType, ImageDimension>::ImageType ImageType;
        m_Factory.Register(addressor.operator()<ImageType>(), (ImageType*)(NULL));
        }
    }

private:

  TMemberFunctionFactory &m_Factory;
};

template <typename TMemberFunctionPointer,
          typename TMemberFunctionAddressor>
MemberFunctionFactory<TMemberFunctionPointer, TMemberFunctionAddressor>
::MemberFunctionFactory( typename MemberFunctionFactory::ObjectType *pObject )
  : m_ObjectPointer( pObject )
{
  assert( pObject );
}

template <typename TMemberFunctionPointer,
          typename TMemberFunctionAddressor>
template<typename TImageType >
void MemberFunctionFactory<TMemberFunctionPointer, TMemberFunctionAddressor>
::Register( typename MemberFunctionFactory::MemberFunctionType pfunc,  TImageType*  )
{
  PixelIDValueType pixelID = ImageTypeToPixelIDValue<TImageType>::Result;

  // this shouldn't occour, just may be useful for debugging
  assert( pixelID > 0 && pixelID < typelist::Length< InstantiatedPixelIDTypeList >::Result );

  sitkStaticAssert( TImageType::ImageDimension == 2 || TImageType::ImageDimension == 3,
                    "Image Dimension out of range" );
  sitkStaticAssert( ImageTypeToPixelIDValue<TImageType>::Result != (int)sitkUnknown,
                    "invalid pixel type");

  if ( pixelID > 0 && pixelID < typelist::Length< InstantiatedPixelIDTypeList >::Result )
    {
    switch( TImageType::ImageDimension )
      {
      case 3:
        Superclass::m_PFunction3[ pixelID ] = Superclass::BindObject( pfunc, m_ObjectPointer );
        break;
      case 2:
        Superclass::m_PFunction2[ pixelID ] = Superclass::BindObject( pfunc, m_ObjectPointer );
        break;
      default:
        break;
      }
    }
}

template <typename TMemberFunctionPointer,
          typename TMemberFunctionAddressor>
template <typename TPixelIDTypeList,
          unsigned int ImageDimension >
void MemberFunctionFactory<TMemberFunctionPointer, TMemberFunctionAddressor>
::RegisterMemberFunctions( void )
{
  typedef MemberFunctionInstantiater< MemberFunctionFactory, ImageDimension > InstantiaterType;

  // initialize function array with pointer
  typelist::ForEach<TPixelIDTypeList> forEachTypeInList;
  forEachTypeInList( InstantiaterType( *this ) );
}


template <typename TMemberFunctionPointer,
          typename TMemberFunctionAddressor>
typename MemberFunctionFactory<TMemberFunctionPointer, TMemberFunctionAddressor>::FunctionObjectType
MemberFunctionFactory<TMemberFunctionPointer, TMemberFunctionAddressor>
::GetMemberFunction( PixelIDValueType pixelID, unsigned int imageDimension  )
{
  if ( pixelID >= typelist::Length< InstantiatedPixelIDTypeList >::Result || pixelID < 0 )
    {
    sitkExceptionMacro ( << "unexpected error pixelID is out of range" );
    }

  switch ( imageDimension )
    {
    case 3:
      // check if tr1::function has been set
      if ( Superclass::m_PFunction3[ pixelID ] )
        {
        return Superclass::m_PFunction3[ pixelID ];
        }

        sitkExceptionMacro ( << "Pixel type: " << pixelID << " is not supported in 3D" );

      break;
    case 2:
      // check if tr1::function has been set
      if ( Superclass::m_PFunction2[ pixelID ] )
        {
        return Superclass::m_PFunction2[ pixelID ];
        }

        sitkExceptionMacro ( << "Pixel type: " << pixelID << " is not supported in 2D" );

      break;
    default:
      sitkExceptionMacro ( << "Image dimension " << imageDimension << " is not supported" );
      throw;
    }
}


} // end namespace detail
} // end namespace simple
} // end namespace itk


#endif //  __sitkMemberFunctionFactory_h
