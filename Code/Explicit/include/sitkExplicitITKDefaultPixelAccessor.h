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
#ifndef sitkExplicitITKDefaultPixelAccessor_h__
#define sitkExplicitITKDefaultPixelAccessor_h__
#include "sitkExplicit.h"
#include "itkDefaultPixelAccessor.h"

#ifndef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<bool>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<double>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<float>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<int>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::CovariantVector<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::CovariantVector<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::CovariantVector<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::CovariantVector<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::Offset<2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::Offset<3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::Vector<double, 1u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::Vector<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::Vector<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::Vector<float, 1u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::Vector<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::Vector<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<long long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<short>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<signed char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<std::complex<double> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<std::complex<float> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<unsigned char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<unsigned int>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<unsigned long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<unsigned long long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<unsigned short>;
#endif // SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#endif // sitkExplicitITKDefaultPixelAccessor_h__
