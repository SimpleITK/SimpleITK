#ifndef __sitkDetail_h
#define __sitkDetail_h

#include "sitkMemberFunctionFactoryBase.h"
#include "FunctionTraits.h"

namespace itk {
namespace simple {

// this namespace is internal classes not part of the external simple ITK interface
namespace detail {


template < class TMemberFunctionPointer >
struct MemberFunctionAddressor
{
  typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

  template< typename TImageType >
  TMemberFunctionPointer operator() ( void ) const
    {
      return &ObjectType::template ExecuteInternal< TImageType >;
    }
};

template < class TMemberFunctionPointer >
struct DualExecuteInternalAddressor
{
  typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

  template< typename TImageType1, typename TImageType2 >
  TMemberFunctionPointer operator() ( void ) const
    {
      return &ObjectType::template DualExecuteInternal< TImageType1, TImageType2 >;
    }
};


template < class TMemberFunctionPointer >
struct AllocateMemberFunctionAddressor
{
  typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

  template< typename TImageType >
  TMemberFunctionPointer operator() ( void ) const
    {
      return &ObjectType::template AllocateInternal< TImageType >;
    }
};


}
}
}
#endif
