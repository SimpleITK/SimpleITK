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


namespace itk::simple
{


//----------------------------------------------------------------------------


CastImageFilter::~CastImageFilter() = default;

//
// Default constructor that initializes parameters
//
const detail::DualMemberFunctionFactory<CastImageFilter::MemberFunctionType> &
CastImageFilter::GetMemberFunctionFactory()
{
  static detail::DualMemberFunctionFactory<MemberFunctionType> static_factory = [] {
    detail::DualMemberFunctionFactory<MemberFunctionType> factory;
    RegisterMemberFactory2(factory);
    RegisterMemberFactory2v(factory);
    RegisterMemberFactory2l(factory);
    RegisterMemberFactory3(factory);
    RegisterMemberFactory3v(factory);
    RegisterMemberFactory3l(factory);
    RegisterMemberFactory4(factory);
    return factory;
  }();

  return static_factory;
}

CastImageFilter::CastImageFilter() = default;


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

  if (GetMemberFunctionFactory().HasMemberFunction(inputType, outputType, dimension))
  {
    return GetMemberFunctionFactory().GetMemberFunction(inputType, outputType, dimension, this)(image);
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
