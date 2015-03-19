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
#define  SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#include "sitkExplicitITKDefaultVectorPixelAccessor.h"
#undef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#include "sitkExplicitITK.h"

template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<double>;
template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<float>;
template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<int>;
template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<long>;
template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<long long>;
template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<short>;
template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<signed char>;
template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<unsigned char>;
template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<unsigned int>;
template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<unsigned long>;
template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<unsigned long long>;
template class SITKExplicit_EXPORT itk::DefaultVectorPixelAccessor<unsigned short>;
