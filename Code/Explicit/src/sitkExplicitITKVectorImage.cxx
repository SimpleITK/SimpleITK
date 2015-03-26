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
#include "sitkExplicitITKVectorImage.h"
#undef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#include "sitkExplicitITK.h"

template class SITKExplicit_EXPORT itk::VectorImage<double, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<double, 3u>;
template class SITKExplicit_EXPORT itk::VectorImage<float, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<float, 3u>;
template class SITKExplicit_EXPORT itk::VectorImage<int, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<int, 3u>;
template class SITKExplicit_EXPORT itk::VectorImage<long, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<long, 3u>;
template class SITKExplicit_EXPORT itk::VectorImage<long long, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<long long, 3u>;
template class SITKExplicit_EXPORT itk::VectorImage<short, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<short, 3u>;
template class SITKExplicit_EXPORT itk::VectorImage<signed char, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<signed char, 3u>;
template class SITKExplicit_EXPORT itk::VectorImage<unsigned char, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<unsigned char, 3u>;
template class SITKExplicit_EXPORT itk::VectorImage<unsigned int, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<unsigned int, 3u>;
template class SITKExplicit_EXPORT itk::VectorImage<unsigned long, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<unsigned long, 3u>;
template class SITKExplicit_EXPORT itk::VectorImage<unsigned long long, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<unsigned long long, 3u>;
template class SITKExplicit_EXPORT itk::VectorImage<unsigned short, 2u>;
template class SITKExplicit_EXPORT itk::VectorImage<unsigned short, 3u>;
