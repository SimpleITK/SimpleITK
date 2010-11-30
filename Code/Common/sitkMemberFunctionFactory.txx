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
// each valid valid ImageType defined as itk::Image<PixelType,
// ImageDimension>.
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
  typedef typename TImageType::PixelType PixelType;
  unsigned int imageDataType = typelist::IndexOf< InstantiatedPixelTypeList, PixelType >::Result;


  if ( imageDataType > 0 && imageDataType < typelist::Length< InstantiatedPixelTypeList >::Result )
    {
    switch( TImageType::ImageDimension )
      {
      case 3:
        Superclass::m_PFunction3[ imageDataType ] = Superclass::BindObject( pfunc, m_ObjectPointer );
        break;
      case 2:
        Superclass::m_PFunction2[ imageDataType ] = Superclass::BindObject( pfunc, m_ObjectPointer );
        break;
      default:
        std::cerr << "Tried to register image with unsupported dimension of " << (unsigned)TImageType::ImageDimension << std::endl;
      }
    }
}

template <typename TMemberFunctionPointer,
          typename TMemberFunctionAddressor>
template <typename TPixelTypeList,
          unsigned int ImageDimension >
void MemberFunctionFactory<TMemberFunctionPointer, TMemberFunctionAddressor>
::RegisterMemberFunctions( void )
{
  typedef MemberFunctionInstantiater< MemberFunctionFactory, ImageDimension > InstantiaterType;

  // initialize function array with pointer
  typelist::ForEach<TPixelTypeList> forEachTypeInList;
  forEachTypeInList( InstantiaterType( *this ) );
}


template <typename TMemberFunctionPointer,
          typename TMemberFunctionAddressor>
typename MemberFunctionFactory<TMemberFunctionPointer, TMemberFunctionAddressor>::FunctionObjectType
MemberFunctionFactory<TMemberFunctionPointer, TMemberFunctionAddressor>
::GetMemberFunction( ImageDataType imageDataType, unsigned int imageDimension  )
{
  // assert that it's in the sane range
  assert ( imageDataType < typelist::Length< InstantiatedPixelTypeList >::Result );

  switch ( imageDimension )
    {
    case 3:
      // check if tr1::function has been set
      if ( Superclass::m_PFunction3[ imageDataType ] )
        {
        return Superclass::m_PFunction3[ imageDataType ];
        }
      else
        {
        std::cerr << "Pixel type is not supported for this commandlet" << std::endl;
        itkGenericExceptionMacro ( << "Pixel type is not supported for this commandlet" );
        }
      break;
    case 2:
      // check if tr1::function has been set
      if ( Superclass::m_PFunction2[ imageDataType ] )
        {
        return Superclass::m_PFunction2[ imageDataType ];
        }
      else
        {
        std::cerr << "Pixel type is not supported for this commandlet" << std::endl;
        // need to thow something better or have some other definded behavior
        throw;
        }
      break;
    default:
      std::cerr << "Image dimension of " << imageDimension << "is not supported!";
      throw;
    }
}


} // end namespace detail
} // end namespace simple
} // end namespace itk


#endif //  __sitkMemberFunctionFactory_h
