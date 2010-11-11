#ifndef __sitkDetails_h
#define __sitkDetails_h

#include "sitkMacro.h"
#include "sitkPixelTypeLists.h"

namespace itk {
namespace simple {
// this namespace is internal classes not part of the simple ITK interface
namespace detail {


  // predicate used with typelist::ForEach to initialize arrays for
  // run-time dispatching
  template < typename TObject, 
             typename TMemberFunctionPointer = typename TObject::MemberFunctionType>
  struct PFuncArrayInitializer
  {
    PFuncArrayInitializer( TMemberFunctionPointer *a ) : createFunctions( a ) {}

    template <class TPixelType>
    void operator()( TPixelType t )
    {
      typedef TPixelType                 PixelType;

      // this maps the pixel type to an array index
      int index = typelist::IndexOf< InstantiatedPixelTypeList, PixelType >::Result;

      if ( index > 0 &&  index < typelist::Length< InstantiatedPixelTypeList >::Result )
        {
        createFunctions[index] =   &TObject::template ExecuteInternal<PixelType>;
        }
    }
  private:
    TMemberFunctionPointer *createFunctions;
  };

  template < typename TObject, 
             typename TPixelType1,
             typename TMemberFunctionPointer = typename TObject::MemberFunctionType
             >
  struct PFuncArrayInitializer2
  {
    PFuncArrayInitializer2( TMemberFunctionPointer *a ) : createFunctions( a ) {}

    template <class TPixelType2>
    void operator()( TPixelType2 t )
    {
      typedef TPixelType1                PixelType1;
      typedef TPixelType2                PixelType2;

      // this maps the pixel type to an array index
      int index = typelist::IndexOf< InstantiatedPixelTypeList, PixelType2 >::Result;

      if ( index > 0 &&  index < typelist::Length< InstantiatedPixelTypeList >::Result )
        {
        createFunctions[index] =   &TObject::template ExecuteInternal2<PixelType1, PixelType2>;
        }
    }
  private:
    TMemberFunctionPointer *createFunctions;
  };


template <class TSimpleFilter,
          typename TMemberFunctionPointer = typename TSimpleFilter::MemberFunctionType,
          typename TInitializer = PFuncArrayInitializer< TSimpleFilter, TMemberFunctionPointer> >
  class MemberFunctionFactory
  {
  public:
    typedef TSimpleFilter                            SimpleFilterType;
    typedef TMemberFunctionPointer                   MemberFunctionType;
    typedef typename SimpleFilterType::PixelTypeList PixelTypeList;
    typedef TInitializer                             PFuncArrayInitializerType;

    MemberFunctionFactory( void )
      {

      // initialize array to all zeros
      std::fill_n( m_PFunction, size_t(typelist::Length< InstantiatedPixelTypeList >::Result), MemberFunctionType(0) );

      // initialize function array with pointer
      typelist::ForEach<PixelTypeList> arrayInitializer;
      arrayInitializer( PFuncArrayInitializerType( this->m_PFunction ) );
      }

    MemberFunctionType GetMemberFunction( int imageDataType )
      {
        // assert that it's in the sane range
        assert ( imageDataType > 0 && imageDataType < typelist::Length< InstantiatedPixelTypeList >::Result );

        if ( m_PFunction[ imageDataType ] )
          {
          return m_PFunction[ imageDataType ];
          }
        else
          {
          std::cerr << "Pixel type is not supported for this simple ITK filter" << std::endl;
          // need to thow something better or have some other definded behavior
          throw;
          }

      }

  private:

    // array of pointers to member functions
    MemberFunctionType  m_PFunction[ typelist::Length< InstantiatedPixelTypeList >::Result ];
  };


}
}
}
#endif
