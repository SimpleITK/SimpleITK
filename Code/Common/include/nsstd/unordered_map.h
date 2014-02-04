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
#ifndef __sitk_nsstd_unordered_map_h
#define __sitk_nsstd_unordered_map_h

#include "sitkConfigure.h"


#if defined SITK_HAS_TR1_UNORDERED_MAP || defined SITK_HAS_CXX11_UNORDERED_MAP
#if defined SITK_HAS_TR1_SUB_INCLUDE
#include <tr1/unordered_map>
#elif
#include <unordered_map>
#endif
#else
#error "No system (tr1) unordered_map header available!"
#endif

namespace itk
{
namespace simple
{
namespace nsstd
{
#if defined SITK_HAS_TR1_SUB_INCLUDE
using std::tr1::unordered_map;
#else
using std::unordered_map;
#endif
}
}
}


#endif //__sitk_nsstd_unordered_map_h
