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
CastImageFilter::RegisterMemberFactory2l(detail::DualMemberFunctionFactory<MemberFunctionType> & factory)
{
  // basic to Label
  factory
    .RegisterMemberFunctions<IntegerPixelIDTypeList, LabelPixelIDTypeList, 2, ToLabelAddressor<MemberFunctionType>>();

  // Label to basic
  factory
    .RegisterMemberFunctions<LabelPixelIDTypeList, IntegerPixelIDTypeList, 2, LabelToAddressor<MemberFunctionType>>();
}

} // namespace itk::simple
