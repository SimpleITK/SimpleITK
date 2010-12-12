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

#define sitkExceptionMacro(x)                                           \
  {                                                                     \
      std::ostringstream message;                                       \
      message << "sitk::ERROR: " x;                                     \
      ::itk::simple::GenericException e_(__FILE__, __LINE__, message.str().c_str(), ITK_LOCATION); \
      throw e_; /* Explicit naming to work around Intel compiler bug.  */ \
    }

#ifdef SITK_SUPPORTS_STATIC_ASSERT
#define sitkStaticAssert( expr, str) static_assert( expr, str )
#else
// todo actuall make this a static assert, need to add a try compile
// for C++0x static_assert, and then have a fall back. This will work
// in many cases for now.
#define sitkStaticAssert( expr, str )            \
  {                                              \
    if ( !(expr) ) sitkExceptionMacro( <<"StaticAssert failed: " << str ); \
  }
#endif

}
}


#endif
