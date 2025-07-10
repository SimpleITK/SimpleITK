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
CastImageFilter::RegisterMemberFactory2v(detail::DualMemberFunctionFactory<MemberFunctionType> & factory)
{
  // cast between vector images
  factory.RegisterMemberFunctions<VectorPixelIDTypeList, VectorPixelIDTypeList, 2, CastAddressor<MemberFunctionType>>();

  // basic to vector
  factory
    .RegisterMemberFunctions<BasicPixelIDTypeList, VectorPixelIDTypeList, 2, ToVectorAddressor<MemberFunctionType>>();
}

} // namespace itk::simple
