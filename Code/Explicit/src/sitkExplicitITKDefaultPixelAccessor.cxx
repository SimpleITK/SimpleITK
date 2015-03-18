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
#include "sitkExplicitITKDefaultPixelAccessor.h"
#undef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#include "sitkExplicitITK.h"

template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<bool>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<char>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<double>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<float>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<int>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::CovariantVector<double, 2u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::CovariantVector<double, 3u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::CovariantVector<float, 2u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::CovariantVector<float, 3u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::Offset<2u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::Offset<3u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::Vector<double, 1u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::Vector<double, 2u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::Vector<double, 3u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::Vector<float, 1u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::Vector<float, 2u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<itk::Vector<float, 3u> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<long>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<long long>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<short>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<signed char>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<std::complex<double> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<std::complex<float> >;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<unsigned char>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<unsigned int>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<unsigned long>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<unsigned long long>;
template class SITKExplicit_EXPORT itk::DefaultPixelAccessor<unsigned short>;
