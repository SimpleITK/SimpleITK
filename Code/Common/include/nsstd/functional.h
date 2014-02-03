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
#ifndef __sitk_nsstd_functional_h
#define __sitk_nsstd_functional_h

#include "sitkConfigure.h"


#if defined SITK_HAS_TR1_FUNCTIONAL || defined SITK_HAS_CXX11_FUNCTIONAL
#if defined SITK_HAS_TR1_SUB_INCLUDE
#include <tr1/functional>
#else
#include <functional>
#endif
#else
#error "No system (tr1) functional header available!"
#endif

namespace itk
{
namespace simple
{
namespace nsstd
{
#if defined SITK_HAS_TR1_FUNCTIONAL
using std::tr1::function;
using std::tr1::bind;
namespace placeholders =  std::tr1::placeholders;
#else
using std::function;
using std::bind;
namespace placeholders =  std::placeholders;
#endif
}
}
}

#endif //__sitk_nsstd_functional_h
