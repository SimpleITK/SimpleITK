#ifndef __sitkMacro_h
#define __sitkMacro_h


// Ideally, take the types from the C99 standard.  However,
// VS 8 does not have stdint.h, but they are defined anyway.
#ifndef _MSC_VER
#include <stdint.h>
#endif

#include "sitkConfigure.h"

#include "sitkPixelIDTypeLists.h"
#include "sitkPixelIDValues.h"
#include "sitkExceptionObject.h"

namespace itk {
namespace simple {

#define printStdVector(vec, os)\
  {\
  os << "[";\
  for(unsigned int cntr = 0; cntr < vec.size()-1; ++cntr)\
    {\
    os << vec[cntr] << ",";\
    }\
  os << vec[vec.size()-1] << "]";\
  }

#define sitkExceptionMacro(x)                                           \
  {                                                                     \
      std::ostringstream message;                                       \
      message << "sitk::ERROR: " x;                                     \
      ::itk::simple::GenericException e_(__FILE__, __LINE__, message.str().c_str(), ITK_LOCATION); \
      throw e_; /* Explicit naming to work around Intel compiler bug.  */ \
    }


template <typename T>
void Unused( const T &) {};

#ifdef SITK_SUPPORTS_STATIC_ASSERT
// utilize the c++0x static_assert if available
#define sitkStaticAssert( expr, str) static_assert( expr, str )
#else

template<bool> struct StaticAssertFailure;
template<> struct StaticAssertFailure<true>{ enum { Value = 1 }; };

#define BOOST_JOIN( X, Y ) BOOST_DO_JOIN( X, Y )
#define BOOST_DO_JOIN( X, Y ) BOOST_DO_JOIN2(X,Y)
#define BOOST_DO_JOIN2( X, Y ) X##Y

#define sitkStaticAssert( expr, str ) enum { BOOST_JOIN( static_assert_typedef, __LINE__) = sizeof( itk::simple::StaticAssertFailure<((expr) == 0 ? false : true )> ) };


#endif

}
}


#endif
