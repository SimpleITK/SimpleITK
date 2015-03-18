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
#ifndef sitkExplicitITKDefaultVectorPixelAccessor_h__
#define sitkExplicitITKDefaultVectorPixelAccessor_h__
#include "sitkExplicit.h"
#include "itkDefaultVectorPixelAccessor.h"

#ifndef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<double>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<float>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<int>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<long long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<short>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<signed char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<unsigned char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<unsigned int>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<unsigned long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<unsigned long long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultVectorPixelAccessor<unsigned short>;
#endif // SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#endif // sitkExplicitITKDefaultVectorPixelAccessor_h__
