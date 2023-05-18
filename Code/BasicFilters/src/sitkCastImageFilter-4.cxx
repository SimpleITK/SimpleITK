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


void CastImageFilter::RegisterMemberFactory4()
{

#if SITK_MAX_DIMENSION >= 4
  // vector to basic
  // Instantiating 4d to 4d CastImageFilter
  m_DualMemberFactory->RegisterMemberFunctions<VectorPixelIDTypeList, BasicPixelIDTypeList, 3, VectorToImageAddressor<MemberFunctionType> > ();

#endif

#if SITK_MAX_DIMENSION >= 5
  // vector to basic
  m_DualMemberFactory->RegisterMemberFunctions<VectorPixelIDTypeList, BasicPixelIDTypeList, 4, VectorToImageAddressor<MemberFunctionType> > ();
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, VectorPixelIDTypeList, 5, ToVectorAddressor<MemberFunctionType> > ();
#endif
#if SITK_MAX_DIMENSION >= 4 && defined(SITK_USE_ELASTIX)
    m_DualMemberFactory->RegisterMemberFunctions<ComplexPixelIDTypeList, ComplexPixelIDTypeList, 4, CastAddressor<MemberFunctionType> > ();
    m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, ComplexPixelIDTypeList, 4, CastAddressor<MemberFunctionType> > ();
    m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 4, CastAddressor<MemberFunctionType> > ();
    m_DualMemberFactory->RegisterMemberFunctions<IntegerPixelIDTypeList, LabelPixelIDTypeList, 4, ToLabelAddressor<MemberFunctionType> > ();
    m_DualMemberFactory->RegisterMemberFunctions<LabelPixelIDTypeList, IntegerPixelIDTypeList, 4, LabelToAddressor<MemberFunctionType> > ();
    m_DualMemberFactory->RegisterMemberFunctions<VectorPixelIDTypeList, VectorPixelIDTypeList, 4, CastAddressor<MemberFunctionType> > ();
    m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, VectorPixelIDTypeList, 4, ToVectorAddressor<MemberFunctionType> > ();
#endif
}

} // end namespace simple
} // end namespace itk
