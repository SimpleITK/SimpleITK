#ifndef __sitkMemberFunctionFactoryBase_h
#define __sitkMemberFunctionFactoryBase_h



#include <tr1/functional>

#include "sitkPixelTypeLists.h"
#include "sitkMacro.h"

#include "FunctionTraits.h"

namespace itk
{
namespace simple
{

template< typename TMemberFunctionPointer, unsigned int TArity = detail::FunctionTraits<TMemberFunctionPointer>::arity>
class MemberFunctionFactoryBase;


template< typename TMemberFunctionPointer>
class MemberFunctionFactoryBase<TMemberFunctionPointer, 1>
{
protected:
  typedef TMemberFunctionPointer                            MemberFunctionType;
  typedef typename detail::FunctionTraits<MemberFunctionType>::ResultType    MemberFunctionResultType;
  typedef typename detail::FunctionTraits<MemberFunctionType>::Argument0Type MemberFunctionArgumentType;
  typedef typename detail::FunctionTraits<MemberFunctionType>::ClassType     ObjectType;


  MemberFunctionFactoryBase( void ) { }

public:

  typedef std::tr1::function< MemberFunctionResultType ( MemberFunctionArgumentType ) > FunctionObjectType;

  FunctionObjectType GetMemberFunction( ImageDataType imageDataType, unsigned int imageDimension  )
    {
      // assert that it's in the sane range
      assert ( imageDataType < typelist::Length< InstantiatedPixelTypeList >::Result );

      switch ( imageDimension )
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
          std::cerr << "Image dimension of " << imageDimension << "is not supported!";
          throw;
        }
    }


protected:

FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace std::tr1::placeholders;

      // this is really only needed because std::bind1st for not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return std::tr1::bind( pfunc,objectPointer, _1 );
    }

  // array of pointers to member functions
  FunctionObjectType  m_PFunction3[ typelist::Length< InstantiatedPixelTypeList >::Result ];
  FunctionObjectType  m_PFunction2[ typelist::Length< InstantiatedPixelTypeList >::Result ];

private:

  MemberFunctionFactoryBase * operator=(  MemberFunctionFactoryBase & );  // Not Implemented
  MemberFunctionFactoryBase( const  MemberFunctionFactoryBase& );  // Not Implemented
};


template< typename TMemberFunctionPointer>
class MemberFunctionFactoryBase<TMemberFunctionPointer, 2>
{
protected:
  typedef TMemberFunctionPointer                                     MemberFunctionType;
  typedef typename detail::FunctionTraits<MemberFunctionType>::ResultType    MemberFunctionResultType;
  typedef typename detail::FunctionTraits<MemberFunctionType>::Argument0Type MemberFunctionArgument0Type;
  typedef typename detail::FunctionTraits<MemberFunctionType>::Argument1Type MemberFunctionArgument1Type;
  typedef typename detail::FunctionTraits<MemberFunctionType>::ClassType     ObjectType;


  MemberFunctionFactoryBase( void ) { }

public:

  typedef std::tr1::function< MemberFunctionResultType ( MemberFunctionArgument1Type,  MemberFunctionArgument0Type) > FunctionObjectType;

  FunctionObjectType GetMemberFunction( ImageDataType imageDataType, unsigned int imageDimension  )
    {
      // assert that it's in the sane range
      assert ( imageDataType < typelist::Length< InstantiatedPixelTypeList >::Result );

      switch ( imageDimension )
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
          std::cerr << "Image dimension of " << imageDimension << "is not supported!";
          throw;
        }
    }


protected:


  FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace std::tr1::placeholders;

      // this is really only needed because std::bind1st for not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return std::tr1::bind( pfunc, objectPointer, _1, _2 );
    }

  // array of pointers to member functions
  FunctionObjectType  m_PFunction3[ typelist::Length< InstantiatedPixelTypeList >::Result ];
  FunctionObjectType  m_PFunction2[ typelist::Length< InstantiatedPixelTypeList >::Result ];

private:

  MemberFunctionFactoryBase * operator=(  MemberFunctionFactoryBase & );  // Not Implemented
  MemberFunctionFactoryBase( const  MemberFunctionFactoryBase& );  // Not Implemented
};

} // end namespace simple
} // end namespace itk

#endif // __sitkMemberFunctionFactoryBase_h
