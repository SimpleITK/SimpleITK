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
// This file is based off of the work done in the Loki library but is
// substantially modified. It's a good book buy it.

////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The author or Addison-Welsey Longman make no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////


#ifndef __TypeList_H__
#define __TypeList_H__

#include "sitkMacro.h"

namespace typelist
{


/** \class  TypeList
 * \brief The building block of typelists of any length
 *
 * A TypeList is a type, not an object. It enables complex
 * compile-time manipulation of a set of types.
 *
 * Defines nested types:
 *     Head (first element, a non-typelist type by convention)
 *     Tail (second element, can be another typelist)
 */
template <typename H, typename T>
struct SITK_ABI_HIDDEN TypeList
{
  using Head = H;
  using Tail = T;
};

/** \class NullType
 * \brief a empty type to indicate end of list
 */
struct SITK_ABI_HIDDEN NullType {};



/**\class  MakeTypeList
 * \brief Generates a TypeList from it's template arguments
 *
 * The arguments are type names.
 * \code
 * MakeTypeList<T1, T2, T3>::Type
 * \endcode
 * returns a typelist that contains the types T1, T2, T3
 *
 * Example:
 * \code
 * using MyTypeList = typelist::MakeTypeList< int, char, short>::Type;
 * \endcode
 *
 */
template
<
  typename T1  = NullType, typename T2   = NullType, typename T3  = NullType,
  typename T4  = NullType, typename T5   = NullType, typename T6  = NullType,
  typename T7  = NullType, typename T8   = NullType, typename T9  = NullType,
  typename T10 = NullType, typename T11  = NullType, typename T12 = NullType,
  typename T13 = NullType, typename T14  = NullType, typename T15 = NullType,
  typename T16 = NullType, typename T17  = NullType, typename T18 = NullType,
  typename T19 = NullType, typename T20  = NullType, typename T21 = NullType,
  typename T22 = NullType, typename T23  = NullType, typename T24 = NullType,
  typename T25 = NullType, typename T26  = NullType, typename T27 = NullType,
  typename T28 = NullType, typename T29  = NullType, typename T30 = NullType
>
struct SITK_ABI_HIDDEN MakeTypeList
{
private:
  typedef typename MakeTypeList
  <
  T2,  T3,  T4,
  T5,  T6,  T7,
  T8,  T9,  T10,
  T11, T12, T13,
  T14, T15, T16,
  T17, T18, T19,
  T20, T21, T22,
  T23, T24, T25,
  T26, T27, T28,
  T29, T30
  >::Type TailType;
public:
  using Type = TypeList< T1, TailType >;
};
template <>
struct SITK_ABI_HIDDEN MakeTypeList<>
{
  using Type = NullType;
};



template <typename TTypeList> struct SITK_ABI_HIDDEN Length;
/**\class Length
 * \brief Computes the length of a typelist
 *
 * Example:
 * \code
 * using MyTypeList = typelist::MakeTypeList<int, char, short>::Type;
 * int len = typelist::Length<MyTypeList>::Result;
 * \endcode
 * returns a compile-time constant containing the length of TTypeList,
 * not counting the end terminator (which by convention is NullType)
 *
 */
template <typename H, typename T>
struct SITK_ABI_HIDDEN Length< TypeList<H, T> >
{
  enum { Result = 1 + Length<T>::Result };
};

/** \cond TYPELIST_IMPLEMENTATION */
template <> struct SITK_ABI_HIDDEN Length<NullType>
{
  enum { Result = 0 };
};
/** \endcond */



/**\class TypeAt
 * \brief Finds the type at a given index in a typelist
 *
 * Example:
 * \code
 * using MyTypeList = typelist::MakeTypeList<int, char, short>::Type;
 * typelist::TypeAt<MyTypeList, 0>::Result intVariable;
 * \endcode
 *
 * returns the type's position 'index' in TTypeList
 * If you pass an out-of-bounds index, the result is a compile-time
 * error
 *
 */
template <class TTypeList, unsigned int index> struct SITK_ABI_HIDDEN TypeAt;

template <class Head, class Tail>
struct SITK_ABI_HIDDEN TypeAt<TypeList<Head, Tail>, 0>
{
  using Result = Head;
};

template <class Head, class Tail, unsigned int i>
struct SITK_ABI_HIDDEN TypeAt<TypeList<Head, Tail>, i>
{
  using Result = typename TypeAt<Tail, i - 1>::Result;
};

template < unsigned int i>
struct SITK_ABI_HIDDEN TypeAt<NullType, i>
{
  using Result = NullType;
};


template <class TTypeList1, class TTypeList2> struct SITK_ABI_HIDDEN Append;
/**\class Append
 * \brief Appends a type or a typelist to another
 *
 * Example 1:
 * \code
 * using MyTypeList1 = typelist::MakeTypeList<int, char>::Type;
 * using MyTypeList2 = typelist::MakeTypeList<short, unsigned short>::Type;
 * using MyCombinedList = typelist::Append<MyList1, MyList2>::Type;
 * \endcode
 *
 * Example 2:
 * \code
 * using MyTypeList = typelist::MakeTypeList<int, char>::Type;
 * using MyAddedTypeList = typelist::Append<MyTypeList, short>::Type;
 * \endcode
 *
 *  returns a typelist that is TTypeList1 followed by TTypeList2
 *  terminated by NullType. TTypeList2 may be another typelist or a
 *  single type.
 *
 */
template <class Head, class Tail, class T>
struct SITK_ABI_HIDDEN Append<TypeList<Head, Tail>, T>
{
  using Type = TypeList<Head, typename Append<Tail, T>::Type>;
};

/** \cond TYPELIST_IMPLEMENTATION */
template <> struct SITK_ABI_HIDDEN Append<NullType, NullType>
{
  using Type = NullType;
};
template <class T> struct SITK_ABI_HIDDEN Append<NullType, T>
{
  using Type = TypeList<T,NullType>;
};
template <class T> struct SITK_ABI_HIDDEN Append<T, NullType>
{
  using Type = TypeList<T,NullType>;
};
template <class Head, class Tail>
struct SITK_ABI_HIDDEN Append<NullType, TypeList<Head, Tail> >
{
  using Type = TypeList<Head, Tail>;
};
template <class Head, class Tail>
struct SITK_ABI_HIDDEN Append<TypeList<Head, Tail>, NullType>
{
  using Type = TypeList<Head, Tail>;
};
/** \endcond */

/**\class IndexOf
 * \brief Finds the index of a type in a typelist
 *
 * Example:
 * \code
 * using MyTypeList = typelist::MakeTypeList<int, char>::Type;
 * int index = typelist::IndexOf<MyTypeList, int>::Result;
 * \endcode
 *
 * IndexOf<TTypeList, T>::Result
 * returns the position of T in TList, or NullType if T is not found in TList
 */
template <class TTypeList, class TType> struct SITK_ABI_HIDDEN IndexOf;
template <class TType>
struct SITK_ABI_HIDDEN IndexOf<NullType, TType>
{
  enum { Result = -1 };
};
template <class TType, class TTail>
struct SITK_ABI_HIDDEN IndexOf<TypeList<TType, TTail>, TType>
{
  enum { Result = 0 };
};
template <class Head, class TTail, class TType>
struct SITK_ABI_HIDDEN IndexOf<TypeList<Head, TTail>, TType>
{
private:
  enum { temp = IndexOf<TTail, TType>::Result };
public:
  enum { Result = (temp == -1 ? -1 : 1 + temp) };
};


/**\class HasType
 * \brief Queries the typelist for a type
 *
 * Example:
 * \code
 * using MyTypeList = typelist::MakeTypeList<int, char>::Type;
 * bool query = typelist::HasType<MyTypeList, short>::Result;
 * \endcode
 *
 * HasType<TList, T>::Result
 * evaluates to true if TList contains T, false otherwise.
 */
template <class TTypeList, class TType> struct SITK_ABI_HIDDEN HasType;
template <class TType>
struct SITK_ABI_HIDDEN HasType<NullType, TType>
{
  enum { Result = false };
};
template <class TType, class TTail>
struct SITK_ABI_HIDDEN HasType<TypeList<TType, TTail>, TType> {
  enum { Result = true };
};
template <class Head, class TTail, class TType>
struct SITK_ABI_HIDDEN HasType<TypeList<Head, TTail>, TType> {
  enum { Result = HasType<TTail, TType>::Result };
};


/**\class Visit
 * \brief Runs a templated predicate on each type in the list
 *
 * \code
 * struct Predicate
 * {
 *  template<class TType>
 *  void operator()( void ) const
 *     { std::cout << typeid(TType).name() << std::endl; }
 * }
 *
 * using MyTypeList = typelist::MakeTypeList<int, char>::Type;
 * typelist::Visit<MyTypeList>( Predicate() );
 *
 * \endcode
 *
 *
 */
template <class TTypeList>
struct SITK_ABI_HIDDEN Visit
{
  template < class Predicate >
  void operator()( Predicate &visitor )
  {
    using Head = typename TTypeList::Head;
    using Tail = typename TTypeList::Tail;
    visitor.CLANG_TEMPLATE operator()<Head>( );
    Visit<Tail> next;
    next.CLANG_TEMPLATE operator()<Predicate>( visitor );
  }
  template < class Predicate >
  void operator()( const Predicate &visitor )
  {
    using Head = typename TTypeList::Head;
    using Tail = typename TTypeList::Tail;
    visitor.CLANG_TEMPLATE operator()<Head>( );
    Visit<Tail> next;
    next.CLANG_TEMPLATE operator()<Predicate>( visitor );
  }
};
template <> struct SITK_ABI_HIDDEN Visit < NullType>
{
  template < class Predicate >
  void operator()( const Predicate &)
    {}
};


template < typename TLeftTypeList, typename TRightTypeList >
struct SITK_ABI_HIDDEN DualVisitImpl;

/**\class DualVisit
 * \brief Runs a templated predicate on each combination of the types
 * on the two lists
 *
 * \code
 * struct Predicate
 * {
 *  template<class TType1, TType2>
 *  void operator()( void ) const
 *     { std::cout << typeid(TType1).name() << " " << typeid(TType2.name() <<
 * std::endl; }
 * }
 *
 * using MyTypeList = typelist::MakeTypeList<int, char>::Type;
 * typelist::DualVisit<MyTypeList, MyTypeList>( Predicate() );
 *
 * \endcode
 *
 */
template < typename TLeftTypeList, typename TRightTypeList >
struct SITK_ABI_HIDDEN DualVisit
{

  template <typename Visitor>
  void operator()( Visitor &visitor ) const
  {
    DualVisitImpl<TLeftTypeList, TRightTypeList > impl;
    return impl.CLANG_TEMPLATE operator()<Visitor>( visitor );
  }

  template <typename Visitor>
  void operator()( const Visitor &visitor ) const
  {
    DualVisitImpl<TLeftTypeList, TRightTypeList > impl;
    return impl.CLANG_TEMPLATE operator()<Visitor>( visitor );
  }
};

/** \cond TYPELIST_IMPLEMENTATION
*
* The procedural algorithm for this code is:
* \code
*  foreach leftType in TLeftTypList
*    foreach rightType in TRightTypeList
*      visit( leftType, rightTYpe )
* \endcode
*
* Where inner loop has been unwound in to a tail recursive templated
* meta-function visitRHS. The outer loop is recursively implemented in
* the operator().
*/
template < typename TLeftTypeList, typename TRightTypeList >
struct SITK_ABI_HIDDEN DualVisitImpl
{
  using LeftHead = typename TLeftTypeList::Head;
  using RightHead = typename TRightTypeList::Head;
  using LeftTail = typename TLeftTypeList::Tail;
  using RightTail = typename TRightTypeList::Tail;

  template <typename Visitor>
  void operator()( Visitor &visitor ) const
  {
    DualVisitImpl< TLeftTypeList, TRightTypeList> goRight;
    goRight.visitRHS<Visitor>( visitor );

    DualVisitImpl<LeftTail, TRightTypeList> goLeft;
    goLeft.CLANG_TEMPLATE operator()<Visitor>( visitor );
  }

  template <typename Visitor>
  void operator()( const Visitor &visitor ) const
  {
    DualVisitImpl< TLeftTypeList, TRightTypeList> goRight;
    goRight.visitRHS<Visitor>( visitor );

    DualVisitImpl<LeftTail, TRightTypeList> goLeft;
    goLeft.CLANG_TEMPLATE operator()<Visitor>( visitor );
  }

  template <typename Visitor>
  void visitRHS( Visitor &visitor ) const
  {
    visitor.CLANG_TEMPLATE operator()<LeftHead, RightHead>( );

    DualVisitImpl< TLeftTypeList, RightTail> goRight;
    goRight.CLANG_TEMPLATE visitRHS<Visitor>( visitor );
  }
  template <typename Visitor>
  void visitRHS( const Visitor &visitor ) const
  {
    visitor.CLANG_TEMPLATE operator()<LeftHead, RightHead>( );

    DualVisitImpl< TLeftTypeList, RightTail> goRight;
    goRight.CLANG_TEMPLATE visitRHS<Visitor>( visitor );
  }
};

template < typename TRightTypeList >
struct SITK_ABI_HIDDEN DualVisitImpl< typelist::NullType, TRightTypeList >
{
  template <typename Visitor>
  void operator()( const Visitor & ) const
  { }
};
template < typename TLeftTypeList >
struct SITK_ABI_HIDDEN DualVisitImpl< TLeftTypeList, typelist::NullType >
{
  template <typename Visitor>
  void operator()( const Visitor & ) const
  { }

  template <typename Visitor>
  void visitRHS( const Visitor & ) const {}
};

template < >
struct SITK_ABI_HIDDEN DualVisitImpl< typelist::NullType, typelist::NullType >
{
  template <typename Visitor>
  void operator()( const Visitor & ) const
  { }
};
/**\endcond*/

}

#endif // __TypeList_H__
