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
#include "sitkPixelIDTypes.h"
#include "sitkPixelIDTypeLists.h"
#include "sitkMacro.h"
#include "sitkNonCopyable.h"

#include "Ancillary/type_list2.h"
#include "Ancillary/FunctionTraits.h"

#include <unordered_map>
#include <functional>
#include <tuple>

namespace itk::simple::detail
{

// make hash function available in current name space to take priority

template <typename T>
struct hash : public std::hash<T>
{};

/** A utility function to chain hashes */
template <typename T>
inline void
hash_combine(std::size_t & seed, const T & val)
{
  // Code from boost
  // Reciprocal of the golden ratio helps spread entropy
  //     and handles duplicates.
  std::hash<T> hasher;
  seed ^= hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename S, typename T>
struct hash<std::pair<S, T>>
{
  inline size_t
  operator()(const std::pair<S, T> & val) const
  {
    size_t seed = 0;
    hash_combine(seed, val.first);
    hash_combine(seed, val.second);
    return seed;
  }
};

template <class... TupleArgs>
struct hash<std::tuple<TupleArgs...>>
{

public:
  size_t
  operator()(std::tuple<TupleArgs...> tupleValue) const
  {
    size_t seed = 0;
    std::apply([&seed](auto... tupleElement) { (hash_combine(seed, tupleElement), ...); }, tupleValue);
    return seed;
  }
};


template <typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase
{
protected:
  using MemberFunctionType = TMemberFunctionPointer;
  using ObjectType = typename ::detail::FunctionTraits<MemberFunctionType>::ClassType;
  using MemberFunctionResultType = typename ::detail::FunctionTraits<MemberFunctionType>::ResultType;


  MemberFunctionFactoryBase()
    : m_PFunction(3 * typelist2::length<InstantiatedPixelIDTypeList>::value)
  {}

public:
  /**  the pointer MemberFunctionType redefined as a std::function
   * object */
  using FunctionObjectType = typename ::detail::FunctionTraits<MemberFunctionType>::FunctionObjectType;

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


  using FunctionMapType = std::unordered_map<TKey, FunctionObjectType, hash<TKey>>;

  // maps of Keys to pointers to member functions
  FunctionMapType m_PFunction;
};

} // namespace itk::simple::detail

#endif // sitkMemberFunctionFactoryBase_h
