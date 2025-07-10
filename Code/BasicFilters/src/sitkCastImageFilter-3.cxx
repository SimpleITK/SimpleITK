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

#include "sitkCastImageFilter.hxx"


namespace itk::simple
{


void
CastImageFilter::RegisterMemberFactory3(detail::DualMemberFunctionFactory<MemberFunctionType> & factory)
{
  // cast between complex pixels and complex pixel
  factory
    .RegisterMemberFunctions<ComplexPixelIDTypeList, ComplexPixelIDTypeList, 3, CastAddressor<MemberFunctionType>>();

  // cast between basic pixels and complex number pixels
  factory.RegisterMemberFunctions<BasicPixelIDTypeList, ComplexPixelIDTypeList, 3, CastAddressor<MemberFunctionType>>();

  // cast between basic images
  factory.RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 3, CastAddressor<MemberFunctionType>>();
}

} // namespace itk::simple
