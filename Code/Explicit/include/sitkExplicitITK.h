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
#ifndef sitkExplicitITK_h
#define sitkExplicitITK_h

#include "sitkExplicit.h"

#if defined( SITKExplicit_EXPORTS )
// don't use export
#define SITKExplicit_EXPORT_EXPLICIT
#else
// only import/hidden
#define SITKExplicit_EXPORT_EXPLICIT SITKExplicit_EXPORT
#endif

#include "itkImageRegion.h"

#ifndef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegion<1u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegion<2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegion<3u>;
#endif

#include "itkDefaultPixelAccessor.h"
#include "itkDefaultVectorPixelAccessor.h"
#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkImageSource.h"
#include "itkImageToImageFilter.h"
#include "itkLabelMap.h"
#include "itkLabelObject.h"
#include "itkInPlaceImageFilter.h"
#include "itkComposeImageFilter.h"
#include "itkVectorIndexSelectionCastImageFilter.h"

#include "itkImageConstIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageScanlineConstIterator.h"
#include "itkImageScanlineIterator.h"


#ifndef SITK_TEMPLATE_EXPLICIT_EXPLICITITK

extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageBase<1u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageBase<2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageBase<3u>;


extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, unsigned long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, unsigned long long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, unsigned int>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, unsigned char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, bool>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, signed char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, std::complex<float> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, double>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, itk::Vector<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, int>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, short>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, std::complex<double> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, float>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, long long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImportImageContainer<itk::SizeValueType, unsigned short>;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<unsigned short>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<unsigned long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<unsigned long long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<std::complex<double> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<unsigned char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<float>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<short>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<signed char>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<double>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::Vector<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<std::complex<float> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<long long>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<int>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<unsigned int>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<bool>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::DefaultPixelAccessor<itk::Vector<double, 2u> >;

extern template class itk::DefaultVectorPixelAccessor<int>;
extern template class itk::DefaultVectorPixelAccessor<signed char>;
extern template class itk::DefaultVectorPixelAccessor<unsigned char>;
extern template class itk::DefaultVectorPixelAccessor<unsigned long>;
extern template class itk::DefaultVectorPixelAccessor<unsigned long long>;
extern template class itk::DefaultVectorPixelAccessor<float>;
extern template class itk::DefaultVectorPixelAccessor<unsigned short>;
extern template class itk::DefaultVectorPixelAccessor<unsigned int>;
extern template class itk::DefaultVectorPixelAccessor<short>;
extern template class itk::DefaultVectorPixelAccessor<long long>;
extern template class itk::DefaultVectorPixelAccessor<double>;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<float, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<itk::Vector<double, 3u>, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<double, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<std::complex<float>, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<long, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<long long, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<long, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<long long, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<unsigned long, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<unsigned long long, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<double, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<unsigned char, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<unsigned char, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<long, 1u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<long long, 1u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<unsigned short, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<std::complex<float>, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<unsigned short, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<std::complex<double>, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<signed char, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<short, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<bool, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<signed char, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<int, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<unsigned int, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<short, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<unsigned int, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<bool, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<float, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<int, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<unsigned long, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<unsigned long long, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<std::complex<double>, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::Image<itk::Vector<double, 2u>, 2u>;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<unsigned int, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<float, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<unsigned long, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<unsigned long long, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<float, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<short, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<signed char, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<int, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<unsigned short, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<int, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<double, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<double, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<long, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<long long, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<unsigned char, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<unsigned char, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<unsigned long, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<unsigned long long, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<long, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<long long, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<unsigned short, 3u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<unsigned int, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<short, 2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorImage<signed char, 3u>;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned short, 2u> >;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<itk::Vector<double, 2u>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<std::complex<float>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<itk::Vector<double, 3u>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<std::complex<float>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<bool, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<bool, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<std::complex<double>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::VectorImage<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<std::complex<double>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageSource<itk::Image<unsigned short, 3u> >;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 2u>, itk::VectorImage<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 3u>, itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned char, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned int, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::Image<std::complex<double>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<short, 2u>, itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned int, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned int, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<std::complex<float>, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 3u>, itk::VectorImage<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 2u>, itk::VectorImage<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 3u>, itk::VectorImage<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned int, 2u>, itk::VectorImage<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 3u>, itk::VectorImage<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<bool, 3u>, itk::Image<bool, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned int, 3u>, itk::VectorImage<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<std::complex<double>, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned long, 2u>, itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<double, 2u>, itk::VectorImage<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::LabelMap<itk::LabelObject<unsigned int, 2u> >, itk::LabelMap<itk::LabelObject<unsigned int, 2u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 2u>, itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<std::complex<double>, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::LabelMap<itk::LabelObject<unsigned long, 2u> >, itk::LabelMap<itk::LabelObject<unsigned long, 2u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned int, 2u>, itk::VectorImage<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::LabelMap<itk::LabelObject<unsigned long, 3u> >, itk::LabelMap<itk::LabelObject<unsigned long, 3u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 2u>, itk::VectorImage<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned char, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<int, 3u>, itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 2u>, itk::VectorImage<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned char, 3u>, itk::VectorImage<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned long, 3u>, itk::VectorImage<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<float, 2u>, itk::VectorImage<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 2u>, itk::VectorImage<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 2u>, itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned int, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned long, 2u>, itk::VectorImage<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<signed char, 2u>, itk::VectorImage<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::Image<std::complex<float>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 2u>, itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned long, 3u>, itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 3u>, itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::VectorImage<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<double, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned int, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::LabelMap<itk::LabelObject<unsigned char, 2u> >, itk::LabelMap<itk::LabelObject<unsigned char, 2u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned short, 3u>, itk::VectorImage<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned char, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned int, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::LabelMap<itk::LabelObject<unsigned char, 3u> >, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<bool, 2u>, itk::Image<bool, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned int, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 2u>, itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned short, 3u>, itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<int, 2u>, itk::VectorImage<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<long, 2u>, itk::VectorImage<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<signed char, 3u>, itk::VectorImage<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned char, 3u>, itk::VectorImage<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 3u>, itk::VectorImage<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<std::complex<float>, 2u>, itk::Image<std::complex<float>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::Image<std::complex<double>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::LabelMap<itk::LabelObject<unsigned short, 3u> >, itk::LabelMap<itk::LabelObject<unsigned short, 3u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<short, 2u>, itk::VectorImage<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned int, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 2u>, itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::LabelMap<itk::LabelObject<unsigned char, 3u> >, itk::LabelMap<itk::LabelObject<unsigned char, 3u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<signed char, 3u>, itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned char, 2u>, itk::VectorImage<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::Image<std::complex<float>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned char, 2u>, itk::VectorImage<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::VectorImage<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<std::complex<double>, 3u>, itk::Image<std::complex<double>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 2u>, itk::VectorImage<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned char, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<signed char, 3u>, itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned int, 3u>, itk::VectorImage<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<short, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<long, 3u>, itk::VectorImage<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<double, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<float, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned int, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::VectorImage<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<short, 3u>, itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<float, 3u>, itk::VectorImage<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::LabelMap<itk::LabelObject<unsigned short, 2u> >, itk::LabelMap<itk::LabelObject<unsigned short, 2u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned char, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<std::complex<float>, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::VectorImage<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<long, 2u>, itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<std::complex<double>, 2u>, itk::Image<std::complex<double>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned short, 2u>, itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<signed char, 2u>, itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::LabelMap<itk::LabelObject<unsigned char, 2u> >, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned long, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<float, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned short, 2u>, itk::VectorImage<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<unsigned int, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<unsigned char, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 3u>, itk::VectorImage<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<int, 3u>, itk::VectorImage<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<int, 3u>, itk::VectorImage<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<double, 3u>, itk::VectorImage<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<short, 3u>, itk::VectorImage<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<std::complex<float>, 3u>, itk::Image<std::complex<float>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::LabelMap<itk::LabelObject<unsigned int, 3u> >, itk::LabelMap<itk::LabelObject<unsigned int, 3u> > >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<long, 3u>, itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::VectorImage<int, 2u>, itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<long, 3u>, itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<float, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageToImageFilter<itk::Image<double, 2u>, itk::Image<float, 2u> >;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 2u>, itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<int, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned short, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 2u>, itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned char, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<short, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<signed char, 3u>, itk::VectorImage<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<float, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<signed char, 3u>, itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned int, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned long, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned short, 2u>, itk::VectorImage<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 2u>, itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned short, 2u>, itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned long, 3u>, itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned char, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned int, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<float, 3u>, itk::VectorImage<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<double, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<float, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<short, 2u>, itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<float, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<long, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned long, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned int, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<signed char, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<float, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned int, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 3u>, itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned long, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned int, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned long, 2u>, itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<short, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<signed char, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<short, 2u>, itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<double, 3u>, itk::VectorImage<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<long, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<long, 2u>, itk::VectorImage<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<float, 2u>, itk::VectorImage<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<signed char, 2u>, itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned long, 3u>, itk::VectorImage<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned long, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<int, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<short, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<long, 3u>, itk::VectorImage<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned char, 3u>, itk::VectorImage<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<long, 3u>, itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned long, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<int, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<std::complex<double>, 2u>, itk::Image<std::complex<double>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<int, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned long, 2u>, itk::VectorImage<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 3u>, itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 3u>, itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 2u>, itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 2u>, itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<int, 2u>, itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 3u>, itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<signed char, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<std::complex<double>, 3u>, itk::Image<std::complex<double>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<double, 2u>, itk::VectorImage<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned short, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<double, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned long, 2u>, itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<float, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<signed char, 3u>, itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned short, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<float, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<long, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned short, 3u>, itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<int, 2u>, itk::VectorImage<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<short, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned long, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned int, 2u>, itk::VectorImage<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<long, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned int, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned int, 3u>, itk::VectorImage<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<long, 2u>, itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<int, 3u>, itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<std::complex<float>, 3u>, itk::Image<std::complex<float>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<short, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned long, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<std::complex<float>, 2u>, itk::Image<std::complex<float>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<float, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<short, 3u>, itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<int, 3u>, itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<long, 2u>, itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<short, 3u>, itk::VectorImage<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<int, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<long, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned int, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<signed char, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<short, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned char, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned char, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned char, 2u>, itk::VectorImage<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned short, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<signed char, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<int, 2u>, itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<short, 2u>, itk::VectorImage<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<int, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 3u>, itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<signed char, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned int, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned char, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<signed char, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<int, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<signed char, 2u>, itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<short, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned char, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<float, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 2u>, itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<long, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<long, 3u>, itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<int, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<unsigned short, 3u>, itk::VectorImage<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned int, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned int, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<double, 3u>, itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<int, 3u>, itk::VectorImage<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<long, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned long, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<unsigned long, 3u>, itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<signed char, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<long, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::VectorImage<signed char, 2u>, itk::VectorImage<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::InPlaceImageFilter<itk::Image<short, 3u>, itk::Image<float, 3u> >;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<unsigned short, 3u>, itk::VectorImage<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<signed char, 3u>, itk::VectorImage<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<long, 2u>, itk::VectorImage<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<short, 2u>, itk::VectorImage<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<double, 3u>, itk::VectorImage<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<unsigned long, 3u>, itk::VectorImage<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<float, 3u>, itk::VectorImage<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<unsigned char, 3u>, itk::VectorImage<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<long, 3u>, itk::VectorImage<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<signed char, 2u>, itk::VectorImage<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<unsigned char, 2u>, itk::VectorImage<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<int, 2u>, itk::VectorImage<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<double, 2u>, itk::VectorImage<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<int, 3u>, itk::VectorImage<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<unsigned int, 3u>, itk::VectorImage<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<unsigned int, 2u>, itk::VectorImage<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<unsigned long, 2u>, itk::VectorImage<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<float, 2u>, itk::VectorImage<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<short, 3u>, itk::VectorImage<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ComposeImageFilter<itk::Image<unsigned short, 2u>, itk::VectorImage<unsigned short, 2u> >;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<float, 3u>, itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<unsigned int, 2u>, itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<float, 2u>, itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<unsigned char, 2u>, itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<unsigned char, 3u>, itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<short, 2u>, itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<unsigned long, 2u>, itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<int, 3u>, itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<long, 2u>, itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<unsigned int, 3u>, itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<long, 3u>, itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<unsigned long, 3u>, itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<signed char, 3u>, itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<short, 3u>, itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<unsigned short, 3u>, itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<double, 2u>, itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<signed char, 2u>, itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<int, 2u>, itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<double, 3u>, itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::VectorIndexSelectionCastImageFilter<itk::VectorImage<unsigned short, 2u>, itk::Image<unsigned short, 2u> >;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<itk::Vector<double, 2u>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<itk::Vector<double, 3u>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<std::complex<float>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<bool, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<std::complex<float>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<std::complex<double>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<std::complex<double>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<unsigned long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<bool, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<unsigned long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageConstIterator<itk::Image<float, 3u> >;


extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<std::complex<double>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<std::complex<float>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<bool, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<itk::Vector<double, 3u>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<itk::Vector<double, 2u>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<std::complex<float>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<bool, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<std::complex<double>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegionConstIterator<itk::Image<int, 2u> >;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<std::complex<float>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<std::complex<float>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<std::complex<double>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<itk::Vector<double, 3u>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<std::complex<double>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<itk::Vector<double, 2u>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineConstIterator<itk::Image<short, 3u> >;

extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<signed char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<std::complex<double>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<double, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<signed char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<std::complex<float>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<itk::Vector<double, 3u>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<float, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<std::complex<double>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<itk::Vector<double, 2u>, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<float, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<std::complex<float>, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<double, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageScanlineIterator<itk::Image<unsigned short, 2u> >;

#endif //  SITK_TEMPLATE_EXPLICIT_EXPLICITITK

#endif // sitkExplicitITK_h
