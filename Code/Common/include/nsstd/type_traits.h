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
#ifndef sitk_nsstd_type_traits_h
#define sitk_nsstd_type_traits_h

#include "sitkConfigure.h"

#if !defined SITK_HAS_TR1_TYPE_TRAITS && !defined SITK_HAS_CXX11_TYPE_TRAITS
#error "No system (tr1/c++11) type_traits header available!"
#endif

#if defined SITK_HAS_CXX11_TYPE_TRAITS || !defined SITK_HAS_TR1_SUB_INCLUDE
#include <type_traits>
#else
#include <tr1/type_traits>
#endif


namespace itk
{
namespace simple
{
namespace nsstd
{
#if defined SITK_HAS_TR1_TYPE_TRAITS && !defined SITK_HAS_CXX11_TYPE_TRAITS
using std::tr1::is_same;
using std::tr1::true_type;
using std::tr1::false_type;
using std::tr1::integral_constant;
#else
using std::is_same;
using std::true_type;
using std::false_type;
using std::integral_constant;
#endif
}
}
}

#endif // sitk_nsstd_type_traits_h
