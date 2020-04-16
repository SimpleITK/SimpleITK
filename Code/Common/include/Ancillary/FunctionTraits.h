/*=========================================================================
*
*  Copyright NumFOCUS
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
#ifndef __FunctionTraits_h
#define __FunctionTraits_h

#include "sitkMacro.h"

namespace detail {

template<typename FunctionType> struct SITK_ABI_HIDDEN FunctionTraits;

template<typename R,
         typename C>
struct SITK_ABI_HIDDEN FunctionTraits<R (C::*)(void)> {
  static const unsigned int arity = 0;
  using ClassType = C;
  using ResultType = R;
};


template<typename R,
         typename C,
         typename A0>
struct SITK_ABI_HIDDEN FunctionTraits<R (C::*)(A0)> {
  static const unsigned int arity = 1;
  using ClassType = C;
  using ResultType = R;
  using Argument0Type = A0;
};


template<typename R,
         typename C,
         typename A0,
         typename A1>
struct SITK_ABI_HIDDEN FunctionTraits<R (C::*)(A0, A1)> {
  static const unsigned int arity = 2;
  using ClassType = C;
  using ResultType = R;
  using Argument0Type = A0;
  using Argument1Type = A1;
};


template<typename R,
         typename C,
         typename A0,
         typename A1,
         typename A2>
struct SITK_ABI_HIDDEN FunctionTraits<R (C::*)(A0, A1, A2)> {
  static const unsigned int arity = 3;
  using ClassType = C;
  using ResultType = R;
  using Argument0Type = A0;
  using Argument1Type = A1;
  using Argument2Type = A2;
};

template<typename R,
         typename C,
         typename A0,
         typename A1,
         typename A2,
         typename A3>
struct SITK_ABI_HIDDEN FunctionTraits<R (C::*)(A0, A1, A2, A3)> {
  static const unsigned int arity = 4;
  using ClassType = C;
  using ResultType = R;
  using Argument0Type = A0;
  using Argument1Type = A1;
  using Argument2Type = A2;
  using Argument3Type = A3;
};

template<typename R,
         typename C,
         typename A0,
         typename A1,
         typename A2,
         typename A3,
         typename A4>
struct SITK_ABI_HIDDEN FunctionTraits<R (C::*)(A0, A1, A2, A3, A4)> {
  static const unsigned int arity = 5;
  using ClassType = C;
  using ResultType = R;
  using Argument0Type = A0;
  using Argument1Type = A1;
  using Argument2Type = A2;
  using Argument3Type = A3;
  using Argument4Type = A4;
};

}

#endif
