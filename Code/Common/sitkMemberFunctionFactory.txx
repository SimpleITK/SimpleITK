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

template <class TObjectType,
          typename TMemberFunctionPointer,
          typename TMemberFunctionAddressor>
MemberFunctionFactory<TObjectType, TMemberFunctionPointer, TMemberFunctionAddressor>
::MemberFunctionFactory( MemberFunctionFactory::ObjectType *pObject )
  : m_ObjectPointer( pObject )
{
  assert( pObject );
}

template <class TObjectType,
          typename TMemberFunctionPointer,
          typename TMemberFunctionAddressor>
template<typename TImageType >
void MemberFunctionFactory<TObjectType, TMemberFunctionPointer, TMemberFunctionAddressor>
::Register( MemberFunctionFactory::MemberFunctionType pfunc,  TImageType*  )
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

template <class TObjectType,
          typename TMemberFunctionPointer,
          typename TMemberFunctionAddressor>
template <typename TPixelTypeList,
          unsigned int ImageDimension >
void MemberFunctionFactory<TObjectType, TMemberFunctionPointer, TMemberFunctionAddressor>
::RegisterMemberFunctions( void )
{
  typedef detail::MemberFunctionInstantiater< MemberFunctionFactory, ImageDimension > InstantiaterType;

  // initialize function array with pointer
  typelist::ForEach<TPixelTypeList> forEachTypeInList;
  forEachTypeInList( InstantiaterType( *this ) );
}


} // end namespace detail
} // end namespace simple
} // end namespace itk


#endif //  __sitkMemberFunctionFactory_h
