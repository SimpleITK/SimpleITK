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
#ifndef sitkExplicitITKImportImageContainer_h__
#define sitkExplicitITKImportImageContainer_h__
#include "sitkExplicit.h"
#include "itkImportImageContainer.h"

#ifndef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, bool>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, double>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, float>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, int>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::CovariantVector<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::CovariantVector<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::CovariantVector<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::CovariantVector<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::FixedArray<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::FixedArray<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::Offset<2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::Offset<3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<double, 1u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<float, 1u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, long long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, short>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, signed char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, std::complex<double> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, std::complex<float> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, std::deque<itk::LabelObjectLine<2u>, std::allocator<itk::LabelObjectLine<2u> > > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, std::deque<itk::LabelObjectLine<3u>, std::allocator<itk::LabelObjectLine<3u> > > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, unsigned char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, unsigned int>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, unsigned long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, unsigned long long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, unsigned short>;
#endif // SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#endif // sitkExplicitITKImportImageContainer_h__
