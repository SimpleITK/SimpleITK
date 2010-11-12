#ifndef __sitkDetails_h
#define __sitkDetails_h

#include "sitkMemberFunctionFactoryBase.h"
#include "itkImage.h"
#include "sitkImage.h"

namespace itk {
namespace simple {
// this namespace is internal classes not part of the simple ITK interface
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


}
}
}
#endif
