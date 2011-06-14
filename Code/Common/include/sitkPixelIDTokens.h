#ifndef __sitkPixelIDTokens_h
#define __sitkPixelIDTokens_h

#include "sitkConfigure.h"

#ifdef SITK_HAS_STLTR1_TR1_TYPE_TRAITS
#include <tr1/type_traits>
#elif defined SITK_HAS_STLTR1_TYPE_TRAITS
#include <type_traits>
#else
#error "No system tr1 type traits available"
#endif

#include "sitkPixelIDValues.h"


namespace itk
{
namespace simple
{

typedef std::tr1::true_type  TrueType;
typedef std::tr1::false_type FalseType;

template <typename TPixelIDType>
struct IsBasic
{
  static const bool                      Value = FalseType::value;
  typedef typename FalseType::value_type ValueType;
  typedef typename FalseType::type       Type;
};
template <typename TPixelType>
struct IsBasic< BasicPixelID<TPixelType> >
{
  static const bool                     Value = TrueType::value;
  typedef typename TrueType::value_type ValueType;
  typedef typename TrueType::type       Type;
};
template <typename TPixelType, unsigned int VImageDimension>
struct IsBasic< itk::Image< TPixelType, VImageDimension> >
  : public IsBasic< typename ImageTypeToPixelID< itk::Image<TPixelType, VImageDimension> >::PixelIDType >
{};


template <typename TPixelIDType>
struct IsVector
{
  static const bool                      Value = FalseType::value;
  typedef typename FalseType::value_type ValueType;
  typedef typename FalseType::type       Type;
};
template <typename TPixelType>
struct IsVector< VectorPixelID<TPixelType> >
{
  static const bool                     Value = TrueType::value;
  typedef typename TrueType::value_type ValueType;
  typedef typename TrueType::type       Type;
};
template <typename TPixelType, unsigned int VImageDimension>
struct IsVector< itk::VectorImage< TPixelType, VImageDimension> >
  : public IsVector< typename ImageTypeToPixelID< itk::VectorImage<TPixelType, VImageDimension> >::PixelIDType >
{};


template <typename TPixelIDType>
struct IsLabel
{
  static const bool                      Value = FalseType::value;
  typedef typename FalseType::value_type ValueType;
  typedef typename FalseType::type       Type;
};
template <typename TPixelType>
struct IsLabel< LabelPixelID<TPixelType> >
{
  static const bool                     Value = TrueType::value;
  typedef typename TrueType::value_type ValueType;
  typedef typename TrueType::type       Type;
};
template <typename TLabelType, unsigned int VImageDimension>
struct IsLabel< itk::LabelMap<  itk::LabelObject< TLabelType, VImageDimension > > >
  : public IsLabel< typename ImageTypeToPixelID< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > >::PixelIDType >
{};


template <typename TPixelIDType>
struct IsInstantiated
{
  static const bool Value = ((int)PixelIDToPixelIDValue<TPixelIDType>::Result != (int)sitkUnknown);
  typedef typename std::tr1::integral_constant<bool, Value>::value_type ValueType;
  typedef typename std::tr1::integral_constant<bool, Value>::type       Type;
};
template <typename TPixelType, unsigned int VImageDimension>
struct IsInstantiated< itk::Image< TPixelType, VImageDimension> >
  : public IsInstantiated< typename ImageTypeToPixelID< itk::Image<TPixelType, VImageDimension> >::PixelIDType >
{};
template <typename TPixelType, unsigned int VImageDimension>
struct IsInstantiated< itk::VectorImage< TPixelType, VImageDimension> >
  : public IsInstantiated< typename ImageTypeToPixelID< itk::VectorImage<TPixelType, VImageDimension> >::PixelIDType >
{};
template <typename TLabelType, unsigned int VImageDimension>
struct IsInstantiated< itk::LabelMap<  itk::LabelObject< TLabelType, VImageDimension > > >
  : public IsInstantiated< typename ImageTypeToPixelID< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > >::PixelIDType >
{};

}
}

#endif // _sitkPixelIDTokens_h
