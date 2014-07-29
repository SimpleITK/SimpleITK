/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#ifndef __sitkMacro_h
#define __sitkMacro_h

#include <stdint.h>
#include <stddef.h>
#include <cassert>
#include <sstream>
#include <limits>

#include "sitkConfigure.h"


// Setup symbol exports
//
#if defined _WIN32 || defined __CYGWIN__
   #ifdef __GNUC__
    #define SITK_ABI_EXPORT __attribute__ ((dllexport))
    #define SITK_ABI_IMPORT __attribute__ ((dllimport))
    #define SITK_ABI_HIDDEN
  #else
    #define SITK_ABI_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #define SITK_ABI_IMPORT __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #define SITK_ABI_HIDDEN
  #endif
#else
  #if __GNUC__ >= 4
    #define SITK_ABI_EXPORT __attribute__ ((visibility ("default")))
    #define SITK_ABI_IMPORT __attribute__ ((visibility ("default")))
    #define SITK_ABI_HIDDEN  __attribute__ ((visibility ("hidden")))
  #else
    #define SITK_ABI_EXPORT
    #define SITK_ABI_IMPORT
    #define SITK_ABI_HIDDEN
  #endif
#endif

namespace itk {

namespace simple {

class GenericException;

#define sitkExceptionMacro(x)                                           \
  {                                                                     \
    std::ostringstream message;                                         \
    message << "sitk::ERROR: " x;                                       \
    throw ::itk::simple::GenericException(__FILE__, __LINE__, message.str().c_str()); \
  }

#if defined(SITK_HAS_CXX11_NULLPTR) && !defined(SITK_HAS_TR1_SUB_INCLUDE)
#define SITK_NULLPTR nullptr
#else
#define SITK_NULLPTR NULL
#endif


#ifdef SITK_HAS_CXX11_STATIC_ASSERT
// utilize the c++11 static_assert if available
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
