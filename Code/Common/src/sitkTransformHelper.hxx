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
#ifndef __sitkTransformHelper_hxx
#define __sitkTransformHelper_hxx


#define SITK_TRANSFORM_SET_MPF(NAME,ITK_TYPENAME, COMPONENT)                      \
  {                                                                     \
  typedef ITK_TYPENAME itkType;                                         \
  itkType (*pfSTLToITK)(const std::vector<COMPONENT> &) = &sitkSTLVectorToITK<itkType, COMPONENT>; \
  this->m_pfSet##NAME = nsstd::bind(&TransformType::Set##NAME,t,nsstd::bind(pfSTLToITK,nsstd::placeholders::_1)); \
                                                                        \
  std::vector<COMPONENT> (*pfITKToSTL)( const itkType &) = &sitkITKVectorToSTL<COMPONENT,itkType>; \
  this->m_pfGet##NAME = nsstd::bind(pfITKToSTL,nsstd::bind(&TransformType::Get##NAME,t)); \
  }

#endif // __sitkTransformHelper_hxx
