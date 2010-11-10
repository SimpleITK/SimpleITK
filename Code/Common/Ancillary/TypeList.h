// This file is based off of the work done in the Loki library but is
// substantailly modified. It's a good book buy it.

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

namespace typelist
{

////////////////////////////////////////////////////////////////////////////////
// class template TypeList
// The building block of typelists of any length
//
// Defines nested types:
//     Head (first element, a non-typelist type by convention)
//     Tail (second element, can be another typelist)
////////////////////////////////////////////////////////////////////////////////
template <typename H, typename T>
struct TypeList
{
  typedef H Head;
  typedef T Tail;
};

/////
struct NullType {};


////////////////////////////////////////////////////////////////////////////////
// class template MakeTypeList
// Takes a number of arguments equal to its numeric suffix
// The arguments are type names.
// MakeTypeList<T1, T2, ...>::Result
// returns a typelist that is of T1, T2, ...
////////////////////////////////////////////////////////////////////////////////
template
<
  typename T1  = NullType, typename T2   = NullType, typename T3  = NullType,
  typename T4  = NullType, typename T5   = NullType, typename T6  = NullType,
  typename T7  = NullType, typename T8   = NullType, typename T9  = NullType,
  typename T10 = NullType, typename T11  = NullType, typename T12 = NullType,
  typename T13 = NullType, typename T14  = NullType, typename T15 = NullType,
  typename T16 = NullType, typename T17  = NullType, typename T18 = NullType,
  typename T19 = NullType, typename T20  = NullType, typename T21 = NullType,
  typename T22 = NullType, typename T23  = NullType, typename T24 = NullType
>
struct MakeTypeList
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
  T23, T24
  >::Type TailType;
public:
  typedef TypeList< T1, TailType > Type;
};
template <>
struct MakeTypeList<>
{
  typedef NullType Type;
};



////////////////////////////////////////////////////////////////////////////////
// class template Length
// Computes the length of a typelist
// Invocation (TList is a typelist):
// Length<TList>::value
// returns a compile-time constant containing the length of TList, not counting
//     the end terminator (which by convention is NullType)
////////////////////////////////////////////////////////////////////////////////
template <typename TTypeList> struct Length;
template <> struct Length<NullType>
{
  enum { Result = 0 };
};

template <typename H, typename T>
struct Length< TypeList<H, T> >
{
  enum { Result = 1 + Length<T>::Result };
};

////////////////////////////////////////////////////////////////////////////////
// class template TypeAt
// Finds the type at a given index in a typelist
// Invocation (TList is a typelist and index is a compile-time integral
//     constant):
// TypeAt<TList, index>::Result
// returns the type in position 'index' in TList
// If you pass an out-of-bounds index, the result is a compile-time error
////////////////////////////////////////////////////////////////////////////////
template <class TList, unsigned int index> struct TypeAt;

template <class Head, class Tail>
struct TypeAt<TypeList<Head, Tail>, 0>
{
  typedef Head Result;
};

template <class Head, class Tail, unsigned int i>
struct TypeAt<TypeList<Head, Tail>, i>
{
  typedef typename TypeAt<Tail, i - 1>::Result Result;
};





////////////////////////////////////////////////////////////////////////////////
// class template Append
// Appends a type or a typelist to another
// Invocation (TList is a typelist and T is either a type or a typelist):
// Append<TList, T>::Result
// returns a typelist that is TList followed by T and NullType-terminated
////////////////////////////////////////////////////////////////////////////////
template <class TTypeList1, class TTypeList2> struct Append;
template <> struct Append<NullType, NullType>
{
  typedef NullType Type;
};
template <class T> struct Append<NullType, T>
{
  typedef TypeList<T,NullType> Type;
};
template <class T> struct Append<T, NullType>
{
  typedef TypeList<T,NullType> Type;
};
template <class Head, class Tail>
struct Append<NullType, TypeList<Head, Tail> >
{
  typedef TypeList<Head, Tail> Type;
};
template <class Head, class Tail>
struct Append<TypeList<Head, Tail>, NullType>
{
  typedef TypeList<Head, Tail> Type;
};
template <class Head, class Tail, class T>
struct Append<TypeList<Head, Tail>, T>
{
  typedef TypeList<Head, typename Append<Tail, T>::Type>
  Type;
};

////////////////////////////////////////////////////////////////////////////////
// class template IndexOf
// Finds the index of a type in a typelist
// Invocation (TList is a typelist and T is a type):
// IndexOf<TList, T>::value
// returns the position of T in TList, or NullType if T is not found in TList
////////////////////////////////////////////////////////////////////////////////
template <class TTypeList, class TType> struct IndexOf;
template <class TType>
struct IndexOf<NullType, TType>
{
  enum { Result = -1 };
};
template <class TType, class TTail>
struct IndexOf<TypeList<TType, TTail>, TType>
{
  enum { Result = 0 };
};
template <class Head, class TTail, class TType>
struct IndexOf<TypeList<Head, TTail>, TType>
{
private:
  enum { temp = IndexOf<TTail, TType>::Result };
public:
  enum { Result = (temp == -1 ? -1 : 1 + temp) };
};


///// \todo document
template <class TTypeList, class TType> struct HasType;
template <class TType>
struct HasType<NullType, TType>
{
  enum { Result = false };
};
template <class TType, class TTail>
struct HasType<TypeList<TType, TTail>, TType> {
  enum { Result = true };
};
template <class Head, class TTail, class TType>
struct HasType<TypeList<Head, TTail>, TType> {
  enum { Result = HasType<TTail, TType>::Result };
};


//// \todo document
template <class TTypeList> struct ForEach;
template <> struct ForEach < NullType>
{
  template < class Predicate >
  void operator()( Predicate pred)
    {}
};
template <class THead, class TTail>
struct ForEach< TypeList<THead, TTail> >
{
  template < class Predicate >
  void operator()( Predicate visitor )
    {
      typedef THead Head;
      typedef TTail Tail;
      visitor( THead() );
      ForEach<TTail> next;
      next.operator()<Predicate>( visitor );
    }
};

}

#endif // __TypeList_H__
