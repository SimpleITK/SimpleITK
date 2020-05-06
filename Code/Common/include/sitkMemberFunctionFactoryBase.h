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

#include "Ancillary/TypeList.h"
#include "Ancillary/FunctionTraits.h"

#include <unordered_map>
#include <functional>
#include <tuple>

namespace itk
{
namespace simple
{

// this namespace is internal and not part of the external simple ITK interface
namespace detail {

// make hash function available in current name space to take priority

template <typename T> struct hash : public std::hash<T>{};

/** A utility function to chain hashes */
template<typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
  // Code from boost
  // Reciprocal of the golden ratio helps spread entropy
  //     and handles duplicates.
  std::hash<T> hasher;
  seed ^= hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename S, typename T>
struct hash<std::pair<S, T>>
{
  inline size_t operator()(const std::pair<S, T>& val) const
    {
      size_t seed = 0;
      hash_combine(seed, val.first);
      hash_combine(seed, val.second);
      return seed;
    }
};

template<class... TupleArgs>
struct hash<std::tuple<TupleArgs...>>
{
private:
  // recursive hashing of std::tuple from Sarang Baheti's blog
  // https://www.variadic.xyz/2018/01/15/hashing-stdpair-and-stdtuple/
  template<size_t Idx, typename... TupleTypes>
  inline typename std::enable_if<Idx == sizeof...(TupleTypes), void>::type
  hash_combine_tup(size_t&, const std::tuple<TupleTypes...>&) const {}

  template<size_t Idx, typename... TupleTypes>
  inline typename std::enable_if<Idx < sizeof...(TupleTypes), void>::type
  hash_combine_tup(size_t& seed, const std::tuple<TupleTypes...>& tup) const
    {
      hash_combine(seed, std::get<Idx>(tup));

      //  on to next element
      hash_combine_tup<Idx+1>(seed, tup);
    }

public:
  size_t operator()(std::tuple<TupleArgs...> tupleValue) const
    {
      size_t seed = 0;
      hash_combine_tup<0>(seed, tupleValue);
      return seed;
    }
};


template< typename TMemberFunctionPointer,
          typename TKey,
          unsigned int TArity = ::detail::FunctionTraits<TMemberFunctionPointer>::arity>
class MemberFunctionFactoryBase;


/** \class MemberFunctionFactoryBase
 * \brief A base class for the MemberFunctionFactory
 *
 *  This class is for specialization needed for different arity for
 *  the templated member function pointer
 */
template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 0> :
    protected NonCopyable
{
protected:

  using MemberFunctionType = TMemberFunctionPointer;
  using ObjectType = typename ::detail::FunctionTraits<MemberFunctionType>::ClassType;
  using MemberFunctionResultType = typename ::detail::FunctionTraits<MemberFunctionType>::ResultType;


  MemberFunctionFactoryBase( )
    :  m_PFunction( 3*typelist::Length<InstantiatedPixelIDTypeList>::Result )
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  using FunctionObjectType = std::function< MemberFunctionResultType ( ) >;


protected:

  using KeyType = TKey;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object.
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return std::bind( pfunc,objectPointer );
    }

  using FunctionMapType = std::unordered_map< TKey, FunctionObjectType, hash<TKey> >;

  // maps of Keys to pointers to member functions
  FunctionMapType m_PFunction;


};


/** \class MemberFunctionFactoryBase
 * \brief A base class for the MemberFunctionFactory
 *
 *  This class is for specialization needed for different arity for
 *  the templated member function pointer
 */
template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 1> :
    protected NonCopyable
{
protected:

  using MemberFunctionType = TMemberFunctionPointer;
  using ObjectType = typename ::detail::FunctionTraits<MemberFunctionType>::ClassType;
  using MemberFunctionResultType = typename ::detail::FunctionTraits<MemberFunctionType>::ResultType;
  using MemberFunctionArgumentType = typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type;


  MemberFunctionFactoryBase( )
    :  m_PFunction( 3 * typelist::Length<InstantiatedPixelIDTypeList>::Result )
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  using FunctionObjectType = std::function< MemberFunctionResultType ( MemberFunctionArgumentType ) >;


protected:

  using KeyType = TKey;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object.
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace std::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return std::bind( pfunc,objectPointer, _1 );
    }


  using FunctionMapType = std::unordered_map< TKey, FunctionObjectType, hash<TKey> >;

  // maps of Keys to pointers to member functions
  FunctionMapType m_PFunction;

};


template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 2> :
    protected NonCopyable
{
protected:

  using MemberFunctionType = TMemberFunctionPointer;
  using MemberFunctionResultType = typename ::detail::FunctionTraits<MemberFunctionType>::ResultType;
  using MemberFunctionArgument0Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type;
  using MemberFunctionArgument1Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument1Type;
  using ObjectType = typename ::detail::FunctionTraits<MemberFunctionType>::ClassType;


  MemberFunctionFactoryBase( )
    :  m_PFunction( 3 * typelist::Length<InstantiatedPixelIDTypeList>::Result )
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object
   */
  using FunctionObjectType = std::function< MemberFunctionResultType ( MemberFunctionArgument0Type,  MemberFunctionArgument1Type) >;


protected:

  using KeyType = TKey;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace std::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return std::bind( pfunc, objectPointer, _1, _2 );
    }

  using FunctionMapType = std::unordered_map< TKey, FunctionObjectType, hash<TKey> >;

  // maps of Keys to pointers to member functions
  FunctionMapType m_PFunction;

};


template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 3> :
    protected NonCopyable
{
protected:

  using MemberFunctionType = TMemberFunctionPointer;
  using MemberFunctionResultType = typename ::detail::FunctionTraits<MemberFunctionType>::ResultType;
  using MemberFunctionArgument0Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type;
  using MemberFunctionArgument1Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument1Type;
  using MemberFunctionArgument2Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument2Type;
  using ObjectType = typename ::detail::FunctionTraits<MemberFunctionType>::ClassType;


  MemberFunctionFactoryBase( )
    :  m_PFunction( 3 * typelist::Length<InstantiatedPixelIDTypeList>::Result )
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  using FunctionObjectType = std::function< MemberFunctionResultType ( MemberFunctionArgument0Type, MemberFunctionArgument1Type,  MemberFunctionArgument2Type) >;


protected:

  using KeyType = TKey;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace std::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return std::bind( pfunc, objectPointer, _1, _2, _3 );
    }

  using FunctionMapType = std::unordered_map< TKey, FunctionObjectType, hash<TKey> >;

  // maps of Keys to pointers to member functions
  FunctionMapType m_PFunction;

};


template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 4> :
    protected NonCopyable
{
protected:

  using MemberFunctionType = TMemberFunctionPointer;
  using MemberFunctionResultType = typename ::detail::FunctionTraits<MemberFunctionType>::ResultType;
  using MemberFunctionArgument0Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type;
  using MemberFunctionArgument1Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument1Type;
  using MemberFunctionArgument2Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument2Type;
  using MemberFunctionArgument3Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument3Type;
  using ObjectType = typename ::detail::FunctionTraits<MemberFunctionType>::ClassType;


  MemberFunctionFactoryBase( )
    :  m_PFunction( 3 * typelist::Length<InstantiatedPixelIDTypeList>::Result )
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  using FunctionObjectType = std::function< MemberFunctionResultType ( MemberFunctionArgument0Type, MemberFunctionArgument1Type, MemberFunctionArgument2Type,  MemberFunctionArgument3Type) >;


protected:

  using KeyType = TKey;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace std::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return std::bind( pfunc, objectPointer, _1, _2, _3, _4 );
    }

  using FunctionMapType = std::unordered_map< TKey, FunctionObjectType, hash<TKey> >;

  // maps of Keys to pointers to member functions
  FunctionMapType m_PFunction;

};

template< typename TMemberFunctionPointer, typename TKey>
class MemberFunctionFactoryBase<TMemberFunctionPointer, TKey, 5> :
    protected NonCopyable
{
protected:

  using MemberFunctionType = TMemberFunctionPointer;
  using MemberFunctionResultType = typename ::detail::FunctionTraits<MemberFunctionType>::ResultType;
  using MemberFunctionArgument0Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument0Type;
  using MemberFunctionArgument1Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument1Type;
  using MemberFunctionArgument2Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument2Type;
  using MemberFunctionArgument3Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument3Type;
  using MemberFunctionArgument4Type = typename ::detail::FunctionTraits<MemberFunctionType>::Argument4Type;
  using ObjectType = typename ::detail::FunctionTraits<MemberFunctionType>::ClassType;


  MemberFunctionFactoryBase( )
    :  m_PFunction( 3 * typelist::Length<InstantiatedPixelIDTypeList>::Result )
    { }

public:

  /**  the pointer MemberFunctionType redefined ad a tr1::function
   * object */
  typedef std::function< MemberFunctionResultType (
    MemberFunctionArgument0Type,
    MemberFunctionArgument1Type,
    MemberFunctionArgument2Type,
    MemberFunctionArgument3Type,
    MemberFunctionArgument4Type ) >
  FunctionObjectType;


protected:

  using KeyType = TKey;

  /** A function which binds the objectPointer to the calling object
   *  argument in the member function pointer, and returns a function
   *  object
   */
  static FunctionObjectType  BindObject( MemberFunctionType pfunc, ObjectType *objectPointer)
    {
      // needed for _1 place holder
      using namespace std::placeholders;

      // this is really only needed because std::bind1st does not work
      // with tr1::function... that is with tr1::bind, we need to
      // specify the other arguments, and can't just bind the first
      return std::bind( pfunc, objectPointer, _1, _2, _3, _4, _5 );
    }


  using FunctionMapType = std::unordered_map< TKey, FunctionObjectType, hash<TKey> >;

  // maps of Keys to pointers to member functions
  FunctionMapType m_PFunction;


};

} // end namespace detail
} // end namespace simple
} // end namespace itk

#endif // sitkMemberFunctionFactoryBase_h
