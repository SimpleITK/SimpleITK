#ifndef __sitkDetails_h
#define __sitkDetails_h

#include <tr1/functional>

#include "sitkPixelTypeLists.h"
#include "itkImage.h"

namespace itk {
namespace simple {
// this namespace is internal classes not part of the simple ITK interface
namespace detail {


template < class TClass, class TMemberFunctionPointer >
struct MemberFunctionAddressor
{
  template< typename TImageType >
  TMemberFunctionPointer operator() ( void ) const { return &TClass::template operator< TImageType >ExecuteInternal; }
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



class MemberFunctionFactoryBase
{

public:

  typedef std::tr1::function< void ( void ) > FunctionObjectType;

protected:

  MemberFunctionFactoryBase( void ) { }

public:

  template< typename TImageType >
  FunctionObjectType GetMemberFunction( void  )
  {
    long imageDataType = typelist::IndexOf< InstantiatedPixelTypeList, typename TImageType::PixelType>::Result;

    // assert that it's in the sane range
    assert ( imageDataType > 0 && imageDataType < typelist::Length< AllPixelTypeList >::Result );

    switch ( TImageType::ImageDimension )
      {
      case 3:
        // check if tr1::function has been set
        if ( m_PFunction3[ imageDataType ] )
          {
          return m_PFunction3[ imageDataType ];
          }
        else
          {
          std::cerr << "Pixel type is not supported for this commandlet" << std::endl;
          // need to thow something better or have some other definded behavior
          throw;
          }
        break;
      case 2:
        // check if tr1::function has been set
        if ( m_PFunction2[ imageDataType ] )
          {
          return m_PFunction2[ imageDataType ];
          }
        else
          {
          std::cerr << "Pixel type is not supported for this commandlet" << std::endl;
          // need to thow something better or have some other definded behavior
          throw;
          }
        break;
      default:
        std::cerr << "Image dimension of " << TImageType::ImageDimension << "is not supported!";
        throw;
      }
  }

protected:

  // array of pointers to member functions
  FunctionObjectType  m_PFunction3[ typelist::Length< InstantiatedPixelTypeList >::Result ];
  FunctionObjectType  m_PFunction2[ typelist::Length< InstantiatedPixelTypeList >::Result ];

private:

  MemberFunctionFactoryBase * operator=(  MemberFunctionFactoryBase & );  // Not Implemented
  MemberFunctionFactoryBase( const  MemberFunctionFactoryBase& );  // Not Implemented
};



template <class TObjectType,
          typename TMemberFunctionPointer = typename TObjectType::MemberFunctionType,
          typename TMemberFunctionAddressor = detail::MemberFunctionAddressor< TObjectType, TMemberFunctionPointer > >
class MemberFunctionFactory
  : public MemberFunctionFactoryBase
{

public:
  typedef TObjectType                                ObjectType;
  typedef TMemberFunctionPointer                     MemberFunctionType;
  typedef TMemberFunctionAddressor                   AddressorType;


  typedef MemberFunctionFactoryBase::FunctionObjectType FunctionObjectType;


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
    unsigned int imageDimension = TImageType::ImageDimension;

    if ( imageDataType > 0 && imageDataType < typelist::Length< InstantiatedPixelTypeList >::Result )
      {
      switch( TImageType::ImageDimension )
        {
        case 3:
          m_PFunction3[ imageDataType ] = std::tr1::bind( pfunc, m_ObjectPointer );
          break;
        case 2:
          m_PFunction2[ imageDataType ] = std::tr1::bind( pfunc, m_ObjectPointer );
          break;
        default:
          cltDebugMacro( "Tried to register image with unsupported dimension of " << TImageType::ImageDimension );
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
