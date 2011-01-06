#ifndef __sitkPixelIDTokens_h
#define __sitkPixelIDTokens_h

#include <tr1/type_traits>

#include "sitkPixelIDValues.h"



namespace itk
{
namespace simple
{

template <bool, class T = void> struct EnableIf {};
template <class T> struct EnableIf<true, T> { typedef T Type; };

template <bool, class T = void> struct DisableIf {};
template <class T> struct DisableIf<false, T> { typedef T Type; };

typedef std::tr1::true_type TrueType;
typedef std::tr1::false_type FalseType;

template <typename TPixelIDType>
struct IsBasicPixel
{
  static const bool                      Value = FalseType::value;
  typedef typename FalseType::value_type ValueType;
  typedef typename FalseType::type       Type;
};
template <typename TPixelType>
struct IsBasicPixel< BasicPixelID<TPixelType> >
{
  static const bool                     Value = TrueType::value;
  typedef typename TrueType::value_type ValueType;
  typedef typename TrueType::type       Type;
};


template <typename TPixelIDType>
struct IsVectorPixel
{
  static const bool                      Value = FalseType::value;
  typedef typename FalseType::value_type ValueType;
  typedef typename FalseType::type       Type;
};
template <typename TPixelType>
struct IsVectorPixel< VectorPixelID<TPixelType> >
{
  static const bool                     Value = TrueType::value;
  typedef typename TrueType::value_type ValueType;
  typedef typename TrueType::type       Type;
};


template <typename TPixelIDType>
struct IsLabelPixel
{
  static const bool                      Value = FalseType::value;
  typedef typename FalseType::value_type ValueType;
  typedef typename FalseType::type       Type;
};
template <typename TPixelType>
struct IsLabelPixel< LabelPixelID<TPixelType> >
{
  static const bool                     Value = TrueType::value;
  typedef typename TrueType::value_type ValueType;
  typedef typename TrueType::type       Type;
};


template <typename TPixelIDType>
struct IsInstantiated
{
  static const bool Value = ((int)PixelIDToPixelIDValue<TPixelIDType>::Result != (int)sitkUnknown);
  typedef typename std::tr1::integral_constant<bool, Value>::value_type ValueType;
  typedef typename std::tr1::integral_constant<bool, Value>::type       Type;
};

}
}

#endif // _sitkPixelIDTokens_h
