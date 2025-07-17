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

#include "sitkImage.hxx"
#include "sitkMemberFunctionFactory.h"

namespace itk::simple
{

/** An addressor of AllocateInternal to be utilized with
 * registering member functions with the factory.
 */
struct AllocateMemberFunctionAddressor
{
  template <typename TImageType>
  constexpr auto
  operator()() const
  {
    return &Image::template AllocateInternal<TImageType>;
  }
};

struct DispatchedInternalInitialiationAddressor
{
  template <typename TImageType>
  constexpr auto
  operator()() const
  {
    return &Image::template DispatchedInternalInitialization<TImageType>;
  }
};

struct ToVectorAddressor
{
  template <typename TImageType>
  constexpr auto
  operator()() const
  {
    return &Image::template ToVectorInternal<TImageType>;
  }
};

struct ToScalarAddressor
{
  template <typename TImageType>
  constexpr auto
  operator()() const
  {
    return &Image::template ToScalarInternal<TImageType>;
  }
};

void
Image::InternalInitialization(PixelIDValueType type, unsigned int dimension, itk::DataObject * image)
{
  using PixelIDTypeList = AllPixelIDTypeList;
  using Addressor = DispatchedInternalInitialiationAddressor;
  typedef PimpleImageBase * (Self::*MemberFunctionType)(itk::DataObject *);

  static const auto memberFactory = []() {
    detail::MemberFunctionFactory<MemberFunctionType> factory;
    factory.RegisterMemberFunctions<PixelIDTypeList, 2, SITK_MAX_DIMENSION, Addressor>();
    return factory;
  }();

  this->m_PimpleImage.reset(memberFactory.GetMemberFunction(type, dimension, this)(image));
}

void
Image::Allocate(const std::vector<unsigned int> & _size, PixelIDValueEnum ValueEnum, unsigned int numberOfComponents)
{
  // The pixel IDs supported
  using PixelIDTypeList = AllPixelIDTypeList;
  typedef void (Self::*MemberFunctionType)(const std::vector<unsigned int> &, unsigned int);
  using AllocateAddressor = AllocateMemberFunctionAddressor;

  static const auto allocateMemberFactory = []() {
    detail::MemberFunctionFactory<MemberFunctionType> factory;
    factory.RegisterMemberFunctions<PixelIDTypeList, 2, SITK_MAX_DIMENSION, AllocateAddressor>();
    return factory;
  }();

  if (ValueEnum == sitkUnknown)
  {
    sitkExceptionMacro("Unable to construct image of unsupported pixel type");
  }

  if (_size.size() < 2 || _size.size() > SITK_MAX_DIMENSION)
  {
    sitkExceptionMacro("Unsupported number of dimensions specified by size: "
                       << _size << "!\n"
                       << "The maximum supported Image dimension is " << SITK_MAX_DIMENSION << ".");
  }

  allocateMemberFactory.GetMemberFunction(ValueEnum, _size.size(), this)(_size, numberOfComponents);
}


Image
Image::ToVectorImage(bool inPlace)
{
  assert(m_PimpleImage);

  using PixelIDTypeList = typelist2::append<ScalarPixelIDTypeList, VectorPixelIDTypeList>::type;
  typedef Image (Self::*MemberFunctionType)(bool);

  static const auto toVectorMemberFactory = []() {
    detail::MemberFunctionFactory<MemberFunctionType> factory;
    factory.RegisterMemberFunctions<PixelIDTypeList, 3, SITK_MAX_DIMENSION, ToVectorAddressor>();
    factory.RegisterMemberFunctions<VectorPixelIDTypeList, 2, 2, ToVectorAddressor>();
    return factory;
  }();

  if (!toVectorMemberFactory.HasMemberFunction(this->GetPixelID(), this->GetDimension()))
  {
    sitkExceptionMacro("Unable to convert an image with pixel type: " << this->GetPixelID() << " and dimension: "
                                                                      << this->GetDimension() << " to a vector image!");
  }

  return toVectorMemberFactory.GetMemberFunction(this->GetPixelID(), this->GetDimension(), this)(inPlace);
}

Image
Image::ToScalarImage(bool inPlace)
{
  assert(m_PimpleImage);

  using PixelIDTypeList = typelist2::append<ScalarPixelIDTypeList, VectorPixelIDTypeList>::type;
  typedef Image (Self::*MemberFunctionType)(bool);

  static const auto toScalarMemberFactory = []() {
    detail::MemberFunctionFactory<MemberFunctionType> factory;
    factory.RegisterMemberFunctions<PixelIDTypeList, 2, SITK_MAX_DIMENSION - 1, ToScalarAddressor>();
    factory.RegisterMemberFunctions<ScalarPixelIDTypeList, SITK_MAX_DIMENSION, SITK_MAX_DIMENSION, ToScalarAddressor>();
    return factory;
  }();

  if (!toScalarMemberFactory.HasMemberFunction(this->GetPixelID(), this->GetDimension()))
  {
    sitkExceptionMacro("Unable to convert an image with pixel type: " << this->GetPixelID() << " and dimension: "
                                                                      << this->GetDimension() << " to a scalar image!");
  }

  return toScalarMemberFactory.GetMemberFunction(this->GetPixelID(), this->GetDimension(), this)(inPlace);
}

} // namespace itk::simple
