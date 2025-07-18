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
#ifndef sitkMemberFunctionFactoryBase_h
#define sitkMemberFunctionFactoryBase_h

#include "sitkConfigure.h"
#include "sitkPixelIDTypeLists.h"

#include "Ancillary/type_list2.h"
#include "Ancillary/FunctionTraits.h"
#include "Ancillary/const_expr_hash.h"

#include <functional>

namespace itk::simple::detail
{

template <typename TKey, typename TValue>
using DefaultHashMap =
  ConstexprHashMap<TKey,
                   TValue,
                   (SITK_MAX_DIMENSION - 1) * typelist2::length<InstantiatedPixelIDTypeList>::value,
                   DimensionPixelHash>;


template <typename TMemberFunctionPointer,
          typename TKey,
          class TContainer = DefaultHashMap<TKey, TMemberFunctionPointer>>
class MemberFunctionFactoryBase
{
protected:
  using MemberFunctionType = TMemberFunctionPointer;
  using ObjectType = typename ::detail::FunctionTraits<MemberFunctionType>::ClassType;
  using MemberFunctionResultType = typename ::detail::FunctionTraits<MemberFunctionType>::ResultType;
  using FunctionMapType = TContainer;


  MemberFunctionFactoryBase() = default;

public:
  /**  the pointer MemberFunctionType redefined as a std::function
   * object */
  using FunctionObjectType = typename ::detail::FunctionTraits<MemberFunctionType>::FunctionObjectType;

  [[nodiscard]] constexpr double
  GetLoadFactor() const noexcept
  {
    return m_PFunction.load_factor();
  }

  [[nodiscard]] constexpr std::size_t
  GetMaximumLoadFactor() const noexcept
  {
    return m_PFunction.max_load_factor();
  }

  [[nodiscard]] constexpr std::size_t
  GetSize() const noexcept
  {
    return m_PFunction.size();
  }

  [[nodiscard]] constexpr std::size_t
  GetMaxSize() const noexcept
  {
    return m_PFunction.max_size();
  }

protected:
  using KeyType = TKey;


  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object
   */
  template <typename... Args>
  static FunctionObjectType
  BindObject(MemberFunctionResultType (ObjectType ::*pfunc)(Args...), ObjectType * objectPointer)
  {
    return [pfunc, objectPointer](Args... args) -> MemberFunctionResultType {
      return std::invoke(pfunc, objectPointer, std::forward<Args>(args)...);
    };
  }


  // maps of Keys to pointers to member functions
  FunctionMapType m_PFunction;
};

} // namespace itk::simple::detail

#endif // sitkMemberFunctionFactoryBase_h
