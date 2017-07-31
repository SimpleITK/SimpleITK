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
#ifndef sitkMacro_h
#define sitkMacro_h

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


#if __cplusplus >= 201103L
// In c++11 the override keyword allows you to explicity define that a function
// is intended to override the base-class version.  This makes the code more
// managable and fixes a set of common hard-to-find bugs.
#define SITK_OVERRIDE override
// In C++11 the throw-list specification has been deprecated,
// replaced with the noexcept specifier. Using this function
// specification adds the run-time check that the method does not
// throw. If it does throw then std::terminate will be called.
// Use cautiously.
#define SITK_NOEXCEPT noexcept
#else
#define SITK_OVERRIDE
#define SITK_NOEXCEPT throw()
#endif

#if defined(SITK_HAS_TEMPLATE_DISAMBIGUATOR_DEPENDENT_NAME)
#define CLANG_TEMPLATE template
#else
#define CLANG_TEMPLATE
#endif



#if  !defined(SITK_RETURN_SELF_TYPE_HEADER)
#define SITK_RETURN_SELF_TYPE_HEADER Self &
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


#define sitkMacroJoin( X, Y ) sitkDoMacroJoin( X, Y )
#define sitkDoMacroJoin( X, Y ) sitkDoMacroJoin2(X,Y)
#define sitkDoMacroJoin2( X, Y ) X##Y

#ifdef SITK_HAS_CXX11_STATIC_ASSERT
// utilize the c++11 static_assert if available
#define sitkStaticAssert( expr, str) static_assert( expr, str )
#else

template<bool> struct StaticAssertFailure;
template<> struct StaticAssertFailure<true>{ enum { Value = 1 }; };

#define sitkStaticAssert( expr, str ) enum { sitkMacroJoin( static_assert_typedef, __LINE__) = sizeof( itk::simple::StaticAssertFailure<((expr) == 0 ? false : true )> ) };


#endif
}
}

#define sitkPragma(x) _Pragma (#x)

#if defined(__clang__) && defined(__has_warning)
#define sitkClangDiagnosticPush()       sitkPragma( clang diagnostic push )
#define sitkClangDiagnosticPop()        sitkPragma( clang diagnostic pop )
#define sitkClangWarningIgnore_0(x)
#define sitkClangWarningIgnore_1(x)  sitkPragma( clang diagnostic ignored x)
#define sitkClangWarningIgnore(x)    sitkMacroJoin( sitkClangWarningIgnore_, __has_warning(x) )(x)
#else
#define sitkClangDiagnosticPush()
#define sitkClangDiagnosticPop()
#define sitkClangWarningIgnore(x)
#endif


#endif
