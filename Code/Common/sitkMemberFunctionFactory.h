#ifndef __sitkMemberFunctionFactory_h
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
          typename TMemberFunctionPointer = typename TObjectType::MemberFunctionType,
          typename TMemberFunctionAddressor = detail::MemberFunctionAddressor< TObjectType, TMemberFunctionPointer > >
class MemberFunctionFactory
  : public MemberFunctionFactoryBase<TMemberFunctionPointer>
{

public:
  typedef MemberFunctionFactoryBase<TMemberFunctionPointer> Superclass;
  typedef TObjectType                                ObjectType;
  typedef TMemberFunctionPointer                     MemberFunctionType;
  typedef TMemberFunctionAddressor                   AddressorType;


  typedef Superclass FunctionObjectType;


public:

  MemberFunctionFactory( ObjectType *pObject )
    : m_ObjectPointer( pObject )
  {
    assert( pObject );
  }

  template< typename TImageType >
  void Register( MemberFunctionType pfunc,  TImageType*  )
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

  template < typename TPixelTypeList, unsigned int ImageDimension >
  void RegisterMemberFunctions( void )
  {
    typedef detail::MemberFunctionInstantiater< MemberFunctionFactory, ImageDimension > InstantiaterType;

    // initialize function array with pointer
    typelist::ForEach<TPixelTypeList> forEachTypeInList;
    forEachTypeInList( InstantiaterType( *this ) );
  }


protected:

  ObjectType *m_ObjectPointer;


};

} // end namespace detail
} // end namespace simple
} // end namespace itk


#endif //  __sitkMemberFunctionFactory_h
