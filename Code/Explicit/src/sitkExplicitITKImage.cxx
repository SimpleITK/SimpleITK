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
#include "sitkExplicitITKImage.h"
#undef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#include "sitkExplicitITK.h"

template class SITKExplicit_EXPORT itk::Image<bool, 2u>;
template class SITKExplicit_EXPORT itk::Image<bool, 3u>;
template class SITKExplicit_EXPORT itk::Image<char, 2u>;
template class SITKExplicit_EXPORT itk::Image<char, 3u>;
template class SITKExplicit_EXPORT itk::Image<double, 1u>;
template class SITKExplicit_EXPORT itk::Image<double, 2u>;
template class SITKExplicit_EXPORT itk::Image<double, 3u>;
template class SITKExplicit_EXPORT itk::Image<float, 1u>;
template class SITKExplicit_EXPORT itk::Image<float, 2u>;
template class SITKExplicit_EXPORT itk::Image<float, 3u>;
template class SITKExplicit_EXPORT itk::Image<int, 2u>;
template class SITKExplicit_EXPORT itk::Image<int, 3u>;
template class SITKExplicit_EXPORT itk::Image<itk::CovariantVector<double, 2u>, 2u>;
template class SITKExplicit_EXPORT itk::Image<itk::CovariantVector<double, 3u>, 3u>;
template class SITKExplicit_EXPORT itk::Image<itk::CovariantVector<float, 2u>, 2u>;
template class SITKExplicit_EXPORT itk::Image<itk::CovariantVector<float, 3u>, 3u>;
template class SITKExplicit_EXPORT itk::Image<itk::FixedArray<float, 2u>, 2u>;
template class SITKExplicit_EXPORT itk::Image<itk::FixedArray<float, 3u>, 3u>;
template class SITKExplicit_EXPORT itk::Image<itk::Offset<2u>, 2u>;
template class SITKExplicit_EXPORT itk::Image<itk::Offset<3u>, 3u>;
template class SITKExplicit_EXPORT itk::Image<itk::Vector<double, 1u>, 1u>;
template class SITKExplicit_EXPORT itk::Image<itk::Vector<double, 2u>, 2u>;
template class SITKExplicit_EXPORT itk::Image<itk::Vector<double, 3u>, 3u>;
template class SITKExplicit_EXPORT itk::Image<itk::Vector<float, 1u>, 3u>;
template class SITKExplicit_EXPORT itk::Image<itk::Vector<float, 2u>, 2u>;
template class SITKExplicit_EXPORT itk::Image<itk::Vector<float, 3u>, 3u>;
template class SITKExplicit_EXPORT itk::Image<long, 1u>;
template class SITKExplicit_EXPORT itk::Image<long, 2u>;
template class SITKExplicit_EXPORT itk::Image<long, 3u>;
template class SITKExplicit_EXPORT itk::Image<long long, 1u>;
template class SITKExplicit_EXPORT itk::Image<long long, 2u>;
template class SITKExplicit_EXPORT itk::Image<long long, 3u>;
template class SITKExplicit_EXPORT itk::Image<short, 2u>;
template class SITKExplicit_EXPORT itk::Image<short, 3u>;
template class SITKExplicit_EXPORT itk::Image<signed char, 2u>;
template class SITKExplicit_EXPORT itk::Image<signed char, 3u>;
template class SITKExplicit_EXPORT itk::Image<std::complex<double>, 2u>;
template class SITKExplicit_EXPORT itk::Image<std::complex<double>, 3u>;
template class SITKExplicit_EXPORT itk::Image<std::complex<float>, 2u>;
template class SITKExplicit_EXPORT itk::Image<std::complex<float>, 3u>;
template class SITKExplicit_EXPORT itk::Image<std::deque<itk::LabelObjectLine<2u>, std::allocator<itk::LabelObjectLine<2u> > >, 1u>;
template class SITKExplicit_EXPORT itk::Image<std::deque<itk::LabelObjectLine<3u>, std::allocator<itk::LabelObjectLine<3u> > >, 2u>;
template class SITKExplicit_EXPORT itk::Image<unsigned char, 1u>;
template class SITKExplicit_EXPORT itk::Image<unsigned char, 2u>;
template class SITKExplicit_EXPORT itk::Image<unsigned char, 3u>;
template class SITKExplicit_EXPORT itk::Image<unsigned int, 2u>;
template class SITKExplicit_EXPORT itk::Image<unsigned int, 3u>;
template class SITKExplicit_EXPORT itk::Image<unsigned long, 2u>;
template class SITKExplicit_EXPORT itk::Image<unsigned long, 3u>;
template class SITKExplicit_EXPORT itk::Image<unsigned long long, 2u>;
template class SITKExplicit_EXPORT itk::Image<unsigned long long, 3u>;
template class SITKExplicit_EXPORT itk::Image<unsigned short, 2u>;
template class SITKExplicit_EXPORT itk::Image<unsigned short, 3u>;
