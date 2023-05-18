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


namespace itk
{
namespace simple
{


void CastImageFilter::RegisterMemberFactory3()
{
  // cast between complex pixels and complex pixel
  m_DualMemberFactory->RegisterMemberFunctions<ComplexPixelIDTypeList, ComplexPixelIDTypeList, 3, CastAddressor<MemberFunctionType> > ();

  // cast between basic pixels and complex number pixels
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, ComplexPixelIDTypeList, 3, CastAddressor<MemberFunctionType> > ();

  // cast between basic images
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 3, CastAddressor<MemberFunctionType> > ();

  // basic to Label
  m_DualMemberFactory->RegisterMemberFunctions<IntegerPixelIDTypeList, LabelPixelIDTypeList, 3, ToLabelAddressor<MemberFunctionType> > ();

  // Label to basic
  m_DualMemberFactory->RegisterMemberFunctions<LabelPixelIDTypeList, IntegerPixelIDTypeList, 3, LabelToAddressor<MemberFunctionType> > ();

  // cast between vector images
  m_DualMemberFactory->RegisterMemberFunctions<VectorPixelIDTypeList, VectorPixelIDTypeList, 3, CastAddressor<MemberFunctionType> > ();

  // vector to basic
  // Instantiating 3d to 3d CastImageFilter, similar to the functions above
  m_DualMemberFactory->RegisterMemberFunctions<VectorPixelIDTypeList, BasicPixelIDTypeList, 2, VectorToImageAddressor<MemberFunctionType> > ();


#if SITK_MAX_DIMENSION >= 4
  // basic to vector reducing a dimension
  // Instantiating 3d to 3d CastImageFilter, similar to the functions above
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, VectorPixelIDTypeList, 4, ToVectorAddressor<MemberFunctionType> > ();
#endif
}

} // end namespace simple
} // end namespace itk
