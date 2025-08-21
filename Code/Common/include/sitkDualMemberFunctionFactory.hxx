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
#ifndef sitkDualMemberFunctionFactory_hxx
#define sitkDualMemberFunctionFactory_hxx

#include "sitkDualMemberFunctionFactory.h"

#include "sitkPixelIDTokens.h"
#include "sitkExceptionObject.h"

namespace itk::simple::detail
{

// a privately declared predicate for use with the typelist2::visit
// algorithm
//
// \todo doc
//
// This predicate calls the member function factories AddressorType on
// each valid ImageType defined from the pixel type id, and the
// provided dimension
template <typename TMemberFunctionFactory, unsigned int VImageDimension, typename TAddressor>
struct DualMemberFunctionInstantiater
{
  constexpr explicit DualMemberFunctionInstantiater(TMemberFunctionFactory & factory)
    : m_Factory(factory)
  {}

  template <class TPixelIDType1, class TPixelIDType2 = TPixelIDType1>
  constexpr void
  operator()(TPixelIDType1 * t1 [[maybe_unused]] = nullptr, TPixelIDType2 * t2 [[maybe_unused]] = nullptr) const
  {
    if constexpr (IsInstantiated<TPixelIDType1, VImageDimension>::Value &&
                  IsInstantiated<TPixelIDType2, VImageDimension>::Value)
    {
      // conditionally instantiate the member function when PixelID is enabled

      using ImageType1 = typename PixelIDToImageType<TPixelIDType1, VImageDimension>::ImageType;
      using ImageType2 = typename PixelIDToImageType<TPixelIDType2, VImageDimension>::ImageType;
      using AddressorType = TAddressor;

      AddressorType addressor;
      m_Factory.Register(addressor.CLANG_TEMPLATE operator()<ImageType1, ImageType2>(),
                         static_cast<ImageType1 *>(nullptr),
                         static_cast<ImageType2 *>(nullptr));
    }
  }

private:
  TMemberFunctionFactory & m_Factory;
};

template <typename TMemberFunctionPointer, typename TContainer>
template <typename TImageType1, typename TImageType2>
constexpr void
DualMemberFunctionFactory<TMemberFunctionPointer, TContainer>::Register(MemberFunctionType pfunc,
                                                                        TImageType1 *,
                                                                        TImageType2 *)
{
  constexpr PixelIDValueType pixelID1 = ImageTypeToPixelIDValue<TImageType1>::value;
  constexpr PixelIDValueType pixelID2 = ImageTypeToPixelIDValue<TImageType2>::value;

  // this shouldn't occur, just may be useful for debugging
  static_assert(pixelID1 >= 0 && pixelID1 < typelist2::length<InstantiatedPixelIDTypeList>::value);
  static_assert(pixelID2 >= 0 && pixelID2 < typelist2::length<InstantiatedPixelIDTypeList>::value);

  static_assert(TImageType1::ImageDimension >= 2 && TImageType1::ImageDimension <= SITK_MAX_DIMENSION,
                "Image1 Dimension out of range");
  static_assert(TImageType2::ImageDimension >= 2 && TImageType2::ImageDimension <= SITK_MAX_DIMENSION,
                "Image2 Dimension out of range");
  static_assert(TImageType1::ImageDimension == TImageType2::ImageDimension, "Image Dimensions do not match");
  static_assert(IsInstantiated<TImageType1>::Value, "invalid pixel type for argument one");
  static_assert(IsInstantiated<TImageType2>::Value, "invalid pixel type for argument two");

  constexpr typename Superclass::KeyType key(
    TImageType1::GetImageDimension(), pixelID1, TImageType2::GetImageDimension(), pixelID2);

  Superclass::m_PFunction[key] = pfunc;
}

template <typename TMemberFunctionPointer, typename TContainer>
template <typename TPixelIDTypeList1, typename TPixelIDTypeList2, unsigned int VImageDimension, typename TAddressor>
constexpr void
DualMemberFunctionFactory<TMemberFunctionPointer, TContainer>::RegisterMemberFunctions()
{
  using InstantiaterType = DualMemberFunctionInstantiater<Self, VImageDimension, TAddressor>;

  // initialize function array with pointer
  typelist2::dual_visit<TPixelIDTypeList1, TPixelIDTypeList2> visitEachComboInLists;
  visitEachComboInLists(InstantiaterType(*this));
}


template <typename TMemberFunctionPointer, typename TContainer>
template <typename TPixelIDTypeList, unsigned int VImageDimension, typename TAddressor>
constexpr void
DualMemberFunctionFactory<TMemberFunctionPointer, TContainer>::RegisterMemberFunctions()
{

  using InstantiaterType = DualMemberFunctionInstantiater<Self, VImageDimension, TAddressor>;

  // initialize function array with pointer
  typelist2::visit<TPixelIDTypeList> visitEachComboInLists;
  visitEachComboInLists(InstantiaterType(*this));
}


template <typename TMemberFunctionPointer, typename TContainer>
bool
DualMemberFunctionFactory<TMemberFunctionPointer, TContainer>::HasMemberFunction(
  PixelIDValueType pixelID1,
  PixelIDValueType pixelID2,
  unsigned int     imageDimension) const noexcept
{
  typename Superclass::KeyType key(imageDimension, pixelID1, imageDimension, pixelID2);
  try
  {
    // check if tr1::function has been set in map
    return Superclass::m_PFunction.find(key) != Superclass::m_PFunction.end();
  }
  // we do not throw exceptions
  catch (...)
  {}
  return false;
}

template <typename TMemberFunctionPointer, typename TContainer>
typename DualMemberFunctionFactory<TMemberFunctionPointer, TContainer>::FunctionObjectType
DualMemberFunctionFactory<TMemberFunctionPointer, TContainer>::GetMemberFunction(
  PixelIDValueType                                                                     pixelID1,
  PixelIDValueType                                                                     pixelID2,
  unsigned int                                                                         imageDimension,
  typename DualMemberFunctionFactory<TMemberFunctionPointer, TContainer>::ObjectType * objectPointer) const
{
  if (pixelID1 >= typelist2::length<InstantiatedPixelIDTypeList>::value || pixelID1 < 0)
  {
    sitkExceptionMacro(<< "unexpected error pixelID1 is out of range " << pixelID1 << " " << typeid(ObjectType).name());
  }

  if (pixelID2 >= typelist2::length<InstantiatedPixelIDTypeList>::value || pixelID2 < 0)
  {
    sitkExceptionMacro(<< "unexpected error pixelID2 is out of range " << pixelID2 << " " << typeid(ObjectType).name());
  }

  typename Superclass::KeyType key(imageDimension, pixelID1, imageDimension, pixelID2);

  // check if tr1::function has been set
  auto ret_pair = Superclass::m_PFunction.find(key);
  if (ret_pair != Superclass::m_PFunction.end())
  {
    return Superclass::BindObject(ret_pair->second, objectPointer);
  }

  sitkExceptionMacro(<< "Pixel type: " << GetPixelIDValueAsString(pixelID1) << " is not supported in " << imageDimension
                     << "D by" << typeid(ObjectType).name());
}


} // namespace itk::simple::detail


#endif //  sitkDualMemberFunctionFactory_hxx
