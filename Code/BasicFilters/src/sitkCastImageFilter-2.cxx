/*=========================================================================
*
*  Copyright Insight Software Consortium
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


void CastImageFilter::RegisterMemberFactory2()
{
  // cast between complex pixels and complex pixel
  m_DualMemberFactory->RegisterMemberFunctions<ComplexPixelIDTypeList, ComplexPixelIDTypeList, 2, CastAddressor<MemberFunctionType> > ();

  // cast between basic pixels and complex number pixels
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, ComplexPixelIDTypeList, 2, CastAddressor<MemberFunctionType> > ();

  // cast between basic images
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 2, CastAddressor<MemberFunctionType> > ();

}

} // end namespace simple
} // end namespace itk
