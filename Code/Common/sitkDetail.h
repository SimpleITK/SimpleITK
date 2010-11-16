#ifndef __sitkDetails_h
#define __sitkDetails_h

#include "sitkMemberFunctionFactoryBase.h"
#include "itkImage.h"
#include "sitkImage.h"

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


}
}
}
#endif
