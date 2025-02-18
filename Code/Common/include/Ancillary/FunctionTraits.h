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
#include <functional>

namespace detail
{

template <typename FunctionType>
struct SITK_ABI_HIDDEN FunctionTraits;
template <typename Ret, typename C, typename... Args>
struct SITK_ABI_HIDDEN FunctionTraits<Ret (C::*)(Args...)>
{
  static constexpr unsigned int arity = sizeof...(Args);
  using ClassType = C;
  using ResultType = Ret;
  template <std::size_t J>
  using ArgumentType = std::tuple_element_t<J, std::tuple<Args...>>;
  using FunctionObjectType = std::function<Ret(Args...)>;
};

} // namespace detail

#endif
