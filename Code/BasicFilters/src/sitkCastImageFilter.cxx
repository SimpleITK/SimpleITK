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
#include "sitkCastImageFilter.h"
#include "sitkCastImageFilter.hxx"

namespace itk::simple
{


//----------------------------------------------------------------------------


CastImageFilter::~CastImageFilter() = default;

//
// Default constructor that initializes parameters
//
detail::DualMemberFunctionFactory<CastImageFilter::MemberFunctionType>
CastImageFilter::makeFactory()
{
  detail::DualMemberFunctionFactory<MemberFunctionType> factory{};

  // 2D registrations
  // cast between complex pixels and complex pixel
  factory
    .RegisterMemberFunctions<ComplexPixelIDTypeList, ComplexPixelIDTypeList, 2, CastAddressor<MemberFunctionType>>();
  // cast between basic pixels and complex number pixels
  factory.RegisterMemberFunctions<BasicPixelIDTypeList, ComplexPixelIDTypeList, 2, CastAddressor<MemberFunctionType>>();
  // cast between basic images
  factory.RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 2, CastAddressor<MemberFunctionType>>();

  // 2D vector registrations
  // cast between vector images
  factory.RegisterMemberFunctions<VectorPixelIDTypeList, VectorPixelIDTypeList, 2, CastAddressor<MemberFunctionType>>();
  // basic to vector
  factory
    .RegisterMemberFunctions<BasicPixelIDTypeList, VectorPixelIDTypeList, 2, ToVectorAddressor<MemberFunctionType>>();

  // 2D label registrations
  // basic to Label
  factory
    .RegisterMemberFunctions<IntegerPixelIDTypeList, LabelPixelIDTypeList, 2, ToLabelAddressor<MemberFunctionType>>();
  // Label to basic
  factory
    .RegisterMemberFunctions<LabelPixelIDTypeList, IntegerPixelIDTypeList, 2, LabelToAddressor<MemberFunctionType>>();

  // 3D registrations
  // cast between complex pixels and complex pixel
  factory
    .RegisterMemberFunctions<ComplexPixelIDTypeList, ComplexPixelIDTypeList, 3, CastAddressor<MemberFunctionType>>();
  // cast between basic pixels and complex number pixels
  factory.RegisterMemberFunctions<BasicPixelIDTypeList, ComplexPixelIDTypeList, 3, CastAddressor<MemberFunctionType>>();
  // cast between basic images
  factory.RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 3, CastAddressor<MemberFunctionType>>();

  // 3D vector registrations
  // cast between vector images
  factory.RegisterMemberFunctions<VectorPixelIDTypeList, VectorPixelIDTypeList, 3, CastAddressor<MemberFunctionType>>();
  // basic to vector
  factory
    .RegisterMemberFunctions<BasicPixelIDTypeList, VectorPixelIDTypeList, 3, ToVectorAddressor<MemberFunctionType>>();

  // 3D label registrations
  // basic to Label
  factory
    .RegisterMemberFunctions<IntegerPixelIDTypeList, LabelPixelIDTypeList, 3, ToLabelAddressor<MemberFunctionType>>();
  // Label to basic
  factory
    .RegisterMemberFunctions<LabelPixelIDTypeList, IntegerPixelIDTypeList, 3, LabelToAddressor<MemberFunctionType>>();

  // 4D registrations
#if SITK_MAX_DIMENSION >= 4 && defined(SITK_USE_ELASTIX)
  factory
    .RegisterMemberFunctions<ComplexPixelIDTypeList, ComplexPixelIDTypeList, 4, CastAddressor<MemberFunctionType>>();
  factory.RegisterMemberFunctions<BasicPixelIDTypeList, ComplexPixelIDTypeList, 4, CastAddressor<MemberFunctionType>>();
  factory.RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 4, CastAddressor<MemberFunctionType>>();
  factory
    .RegisterMemberFunctions<IntegerPixelIDTypeList, LabelPixelIDTypeList, 4, ToLabelAddressor<MemberFunctionType>>();
  factory
    .RegisterMemberFunctions<LabelPixelIDTypeList, IntegerPixelIDTypeList, 4, LabelToAddressor<MemberFunctionType>>();
  factory.RegisterMemberFunctions<VectorPixelIDTypeList, VectorPixelIDTypeList, 4, CastAddressor<MemberFunctionType>>();
  factory
    .RegisterMemberFunctions<BasicPixelIDTypeList, VectorPixelIDTypeList, 4, ToVectorAddressor<MemberFunctionType>>();
#endif

  return factory;
}

const detail::DualMemberFunctionFactory<CastImageFilter::MemberFunctionType> CastImageFilter::m_DualMemberFactory =
  makeFactory();

CastImageFilter::CastImageFilter()
  : m_OutputPixelType(sitkFloat32)

{
#if 0
  RegisterMemberFactory2(m_DualMemberFactory);
  RegisterMemberFactory2v(m_DualMemberFactory);
  RegisterMemberFactory2l(m_DualMemberFactory);
  RegisterMemberFactory3(m_DualMemberFactory);
  RegisterMemberFactory3v(m_DualMemberFactory);
  RegisterMemberFactory3l(m_DualMemberFactory);
  RegisterMemberFactory4(m_DualMemberFactory);
#endif
}


//
// ToString
//
std::string
CastImageFilter::ToString() const
{
  std::ostringstream out;
  out << "itk::simple::CastImageFilter\n"
      << "\tOutputPixelType: " << this->m_OutputPixelType << std::endl;
  out << ProcessObject::ToString();
  return out.str();
}

//
// Set/Get Methods for output pixel type
//

void
CastImageFilter::SetOutputPixelType(PixelIDValueEnum pixelID)
{
  this->m_OutputPixelType = pixelID;
}

PixelIDValueEnum
CastImageFilter::GetOutputPixelType() const
{
  return this->m_OutputPixelType;
}


//
// Execute
//
Image
CastImageFilter::Execute(const Image & image)
{

  const PixelIDValueEnum inputType = image.GetPixelID();
  const PixelIDValueEnum outputType = this->m_OutputPixelType;
  const unsigned int     dimension = image.GetDimension();

  if (this->m_DualMemberFactory.HasMemberFunction(inputType, outputType, dimension))
  {
    return this->m_DualMemberFactory.GetMemberFunction(inputType, outputType, dimension, this)(image);
  }

  sitkExceptionMacro(<< "Filter does not support casting from casting "
                     << itk::simple::GetPixelIDValueAsString(inputType) << " to "
                     << itk::simple::GetPixelIDValueAsString(outputType));
}


//----------------------------------------------------------------------------


Image
Cast(const Image & image, PixelIDValueEnum pixelID)
{
  CastImageFilter filter;
  filter.SetOutputPixelType(pixelID);
  return filter.Execute(image);
}


} // namespace itk::simple
