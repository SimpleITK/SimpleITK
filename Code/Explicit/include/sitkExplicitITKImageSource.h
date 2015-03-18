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
#ifndef sitkExplicitITKImageSource_h__
#define sitkExplicitITKImageSource_h__
#include "sitkExplicit.h"
#include "itkImageSource.h"

#ifndef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<bool, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<bool, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<itk::CovariantVector<double, 2u>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<itk::CovariantVector<double, 3u>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<itk::Vector<double, 1u>, 1u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<itk::Vector<double, 2u>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<itk::Vector<double, 3u>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<itk::Vector<float, 1u>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<itk::Vector<float, 2u>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<itk::Vector<float, 3u>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<std::complex<double>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<std::complex<double>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<std::complex<float>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<std::complex<float>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned char, 1u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::AttributeLabelObject<unsigned long, 2u, bool> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::AttributeLabelObject<unsigned long, 3u, bool> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::AttributeLabelObject<unsigned long long, 2u, bool> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::AttributeLabelObject<unsigned long long, 3u, bool> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::LabelObject<unsigned char, 2u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::LabelObject<unsigned char, 3u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::LabelObject<unsigned int, 2u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::LabelObject<unsigned int, 3u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::LabelObject<unsigned long, 2u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::LabelObject<unsigned long, 3u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::LabelObject<unsigned long long, 2u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::LabelObject<unsigned long long, 3u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::LabelObject<unsigned short, 2u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::LabelObject<unsigned short, 3u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::ShapeLabelObject<unsigned long, 2u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::ShapeLabelObject<unsigned long, 3u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::ShapeLabelObject<unsigned long long, 2u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::LabelMap<itk::ShapeLabelObject<unsigned long long, 3u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned short, 3u> >;
#endif // SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#endif // sitkExplicitITKImageSource_h__
