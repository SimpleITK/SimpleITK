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

#include "sitkHashImageFilter.h"
#include "sitkCastImageFilter.h"
#include "itkHashImageFilter.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"
#include "itkLabelObject.h"

#include <typeinfo>
#include <string>

namespace itk::simple
{

const detail::MemberFunctionFactory<HashImageFilter::MemberFunctionType> &
HashImageFilter::GetMemberFunctionFactory()
{
  static constexpr auto static_factory = []() SITK_CONSTEVAL {
    detail::MemberFunctionFactory<MemberFunctionType> factory;
    factory.RegisterMemberFunctions<PixelIDTypeList, 2, SITK_MAX_DIMENSION>();
    factory.RegisterMemberFunctions<LabelPixelIDTypeList,
                                    2,
                                    SITK_MAX_DIMENSION,
                                    detail::ExecuteInternalLabelImageAddressor<MemberFunctionType>>();
    return factory;
  }();
  return static_factory;
}


HashImageFilter::~HashImageFilter() = default;

HashImageFilter::HashImageFilter() = default;

std::string
HashImageFilter::ToString() const
{
  std::ostringstream out;
  out << "itk::simple::HashImageFilter" << std::endl
      << "Function Factory:" << std::endl
      << "  Load Factor: " << GetMemberFunctionFactory().GetLoadFactor() << std::endl
      << "  Maximum Load Factor: " << GetMemberFunctionFactory().GetMaximumLoadFactor() << std::endl;
  out << "HashFunction: ";
  switch (this->m_HashFunction)
  {
    case SHA1:
      out << "SHA1";
      break;
    case MD5:
      out << "MD5";
      break;
  }
  out << std::endl;
  out << ProcessObject::ToString();
  return out.str();
}

HashImageFilter::HashFunction
HashImageFilter::GetHashFunction() const
{
  return this->m_HashFunction;
}

void
HashImageFilter::SetHashFunction(HashImageFilter::HashFunction hashFunction)
{
  this->m_HashFunction = hashFunction;
}

std::string
HashImageFilter::Execute(const Image & image)
{

  PixelIDValueEnum type = image.GetPixelID();
  unsigned int     dimension = image.GetDimension();

  return GetMemberFunctionFactory().GetMemberFunction(type, dimension, this)(image);
}

template <class TLabelImageType>
std::string
HashImageFilter::ExecuteInternalLabelImage(const Image & inImage)
{
  using LabelImageType = TLabelImageType;

  using ScalarImageType = itk::Image<typename LabelImageType::PixelType, LabelImageType::ImageDimension>;

  // The image id for a scalar image of the label map image
  PixelIDValueEnum scalarID = static_cast<PixelIDValueEnum>(
    PixelIDToPixelIDValue<typename ImageTypeToPixelID<ScalarImageType>::PixelIDType>::Result);

  // convert the LabelMapImage to a scalar image
  Image img = Cast(inImage, scalarID);

  return this->Execute(img);
}

template <class TImageType>
std::string
HashImageFilter::ExecuteInternal(const Image & inImage)
{
  using InputImageType = TImageType;

  typename InputImageType::ConstPointer image = dynamic_cast<const InputImageType *>(inImage.GetITKBase());

  using HashFilterType = itk::HashImageFilter<InputImageType>;
  typename HashFilterType::Pointer hasher = HashFilterType::New();
  hasher->SetInput(image);
  hasher->InPlaceOff(); // pointless copy of data needed

  switch (this->GetHashFunction())
  {
    case SHA1:
      hasher->SetHashFunction(HashFilterType::SHA1);
      break;
    case MD5:
      hasher->SetHashFunction(HashFilterType::MD5);
      break;
  }

  this->PreUpdate(hasher.GetPointer());

  hasher->Update();

  return hasher->GetHash();
}

std::string
Hash(const Image & image, HashImageFilter::HashFunction function)
{
  HashImageFilter filter;
  filter.SetHashFunction(function);
  return filter.Execute(image);
}
} // namespace itk::simple
