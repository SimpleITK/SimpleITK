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
#ifndef sitkTransformHelper_hxx
#define sitkTransformHelper_hxx


#define SITK_TRANSFORM_SET_MPF(NAME, ITK_TYPENAME, COMPONENT)                      \
  {                                                                     \
  this->m_pfSet##NAME = [t](const std::vector<COMPONENT> &arg){ t->Set##NAME(sitkSTLVectorToITK<ITK_TYPENAME>(arg));};\
  this->m_pfGet##NAME = [t](){ return sitkITKVectorToSTL<COMPONENT>(t->Get##NAME());}; \
  }

#define SITK_TRANSFORM_SET_MPF_GetMatrix()                              \
  {                                                                     \
  this->m_pfGetMatrix =[t](){ return sitkITKDirectionToSTL<typename TransformType::MatrixType>(t->GetMatrix());}; \
  }

#define SITK_TRANSFORM_SET_MPF_SetMatrix()                              \
  {                                                                     \
    this->m_pfSetMatrix = [t](const std::vector<double> &arg, double tolerance){t->SetMatrix(sitkSTLToITKDirection<typename TransformType::MatrixType>(arg), tolerance);}; \
  }


#endif // sitkTransformHelper_hxx
