/*=========================================================================
*
*  Copyright Insight Software Consortium
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
#ifndef __sitkPixelIDTokens_h
#define __sitkPixelIDTokens_h

#include "sitkConfigure.h"
#include "sitkPixelIDValues.h"
#include "nsstd/type_traits.h"


namespace itk
{
namespace simple
{

typedef nsstd::true_type  TrueType;
typedef nsstd::false_type FalseType;

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
  typedef typename nsstd::integral_constant<bool, Value>::value_type ValueType;
  typedef typename nsstd::integral_constant<bool, Value>::type       Type;
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
