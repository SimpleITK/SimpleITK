#ifndef __FunctionTraits_h
#define __FunctionTraits_h

namespace detail {

template<typename FunctionType> struct FunctionTraits;

template<typename R,
         typename C>
struct FunctionTraits<R (C::*)(void)> {
  static const unsigned int arity = 0;
  typedef C ClassType;
  typedef R ResultType;
};


template<typename R,
         typename C,
         typename A0>
struct FunctionTraits<R (C::*)(A0)> {
  static const unsigned int arity = 1;
  typedef C ClassType;
  typedef R ResultType;
  typedef A0 Argument0Type;
};


template<typename R,
         typename C,
         typename A0,
         typename A1>
struct FunctionTraits<R (C::*)(A0, A1)> {
  static const unsigned int arity = 2;
  typedef C ClassType;
  typedef R ResultType;
  typedef A0 Argument0Type;
  typedef A1 Argument1Type;
};


template<typename R,
         typename C,
         typename A0,
         typename A1,
         typename A2>
struct FunctionTraits<R (C::*)(A0, A1, A2)> {
  static const unsigned int arity = 3;
  typedef C ClassType;
  typedef R ResultType;
  typedef A0 Argument0Type;
  typedef A1 Argument1Type;
  typedef A2 Argument2Type;
};

template<typename R,
         typename C,
         typename A0,
         typename A1,
         typename A2,
         typename A3>
struct FunctionTraits<R (C::*)(A0, A1, A2, A3)> {
  static const unsigned int arity = 4;
  typedef C ClassType;
  typedef R ResultType;
  typedef A0 Argument0Type;
  typedef A1 Argument1Type;
  typedef A2 Argument2Type;
  typedef A3 Argument3Type;
};

}

#endif
