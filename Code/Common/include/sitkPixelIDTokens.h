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
#ifndef sitkPixelIDTokens_h
#define sitkPixelIDTokens_h

#include "sitkConfigure.h"
#include "sitkPixelIDValues.h"

#include <type_traits>

namespace itk
{
namespace simple
{

using TrueType = std::true_type;
using FalseType = std::false_type;

template <typename TPixelIDType>
struct IsBasic
{
  static const bool                      Value = FalseType::value;
  using ValueType = typename FalseType::value_type;
  using Type = typename FalseType::type;
};
template <typename TPixelType>
struct IsBasic< BasicPixelID<TPixelType> >
{
  static const bool                     Value = TrueType::value;
  using ValueType = typename TrueType::value_type;
  using Type = typename TrueType::type;
};
template <typename TPixelType, unsigned int VImageDimension>
struct IsBasic< itk::Image< TPixelType, VImageDimension> >
  : public IsBasic< typename ImageTypeToPixelID< itk::Image<TPixelType, VImageDimension> >::PixelIDType >
{};


template <typename TPixelIDType>
struct IsVector
{
  static const bool                      Value = FalseType::value;
  using ValueType = typename FalseType::value_type;
  using Type = typename FalseType::type;
};
template <typename TPixelType>
struct IsVector< VectorPixelID<TPixelType> >
{
  static const bool                     Value = TrueType::value;
  using ValueType = typename TrueType::value_type;
  using Type = typename TrueType::type;
};
template <typename TPixelType, unsigned int VImageDimension>
struct IsVector< itk::VectorImage< TPixelType, VImageDimension> >
  : public IsVector< typename ImageTypeToPixelID< itk::VectorImage<TPixelType, VImageDimension> >::PixelIDType >
{};


template <typename TPixelIDType>
struct IsLabel
{
  static const bool                      Value = FalseType::value;
  using ValueType = typename FalseType::value_type;
  using Type = typename FalseType::type;
};
template <typename TPixelType>
struct IsLabel< LabelPixelID<TPixelType> >
{
  static const bool                     Value = TrueType::value;
  using ValueType = typename TrueType::value_type;
  using Type = typename TrueType::type;
};
template <typename TLabelType, unsigned int VImageDimension>
struct IsLabel< itk::LabelMap<  itk::LabelObject< TLabelType, VImageDimension > > >
  : public IsLabel< typename ImageTypeToPixelID< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > >::PixelIDType >
{};


template <typename TPixelIDType, unsigned int VImageDimension =0>
struct IsInstantiated
{
  static const bool Value = ((int)PixelIDToPixelIDValue<TPixelIDType>::Result != (int)sitkUnknown)
    &&  ( (VImageDimension == 0) ||
          (VImageDimension >= 2 && VImageDimension <= SITK_MAX_DIMENSION));
  using ValueType = typename std::integral_constant<bool, Value>::value_type;
  using Type = typename std::integral_constant<bool, Value>::type;
};
          template <typename TPixelType, unsigned int VImageDimension >
struct IsInstantiated< itk::Image< TPixelType, VImageDimension>, 0 >
  : public IsInstantiated< typename ImageTypeToPixelID< itk::Image<TPixelType, VImageDimension> >::PixelIDType, VImageDimension >
{};
template <typename TPixelType, unsigned int VImageDimension>
struct IsInstantiated< itk::VectorImage< TPixelType, VImageDimension>, 0 >
  : public IsInstantiated< typename ImageTypeToPixelID< itk::VectorImage<TPixelType, VImageDimension> >::PixelIDType, VImageDimension >
{};
template <typename TLabelType, unsigned int VImageDimension>
struct IsInstantiated< itk::LabelMap<  itk::LabelObject< TLabelType, VImageDimension > >, 0 >
  : public IsInstantiated< typename ImageTypeToPixelID< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > >::PixelIDType, VImageDimension >
{};

}
}

#endif // _sitkPixelIDTokens_h
