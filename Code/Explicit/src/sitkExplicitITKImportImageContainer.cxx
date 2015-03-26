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
#include "sitkExplicitITKImportImageContainer.h"
#undef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#include "sitkExplicitITK.h"

template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, bool>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, char>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, double>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, float>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, int>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::CovariantVector<double, 2u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::CovariantVector<double, 3u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::CovariantVector<float, 2u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::CovariantVector<float, 3u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::FixedArray<float, 2u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::FixedArray<float, 3u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::Offset<2u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::Offset<3u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<double, 1u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<double, 2u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<double, 3u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<float, 1u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<float, 2u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<float, 3u> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, long>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, long long>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, short>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, signed char>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, std::complex<double> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, std::complex<float> >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, std::deque<itk::LabelObjectLine<2u>, std::allocator<itk::LabelObjectLine<2u> > > >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, std::deque<itk::LabelObjectLine<3u>, std::allocator<itk::LabelObjectLine<3u> > > >;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, unsigned char>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, unsigned int>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, unsigned long>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, unsigned long long>;
template class SITKExplicit_EXPORT itk::ImportImageContainer<itk::SizeValueType, unsigned short>;
