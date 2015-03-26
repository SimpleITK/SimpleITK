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
#include "sitkExplicitITKLabelMap.h"
#undef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#include "sitkExplicitITK.h"

template class SITKExplicit_EXPORT itk::LabelMap<itk::AttributeLabelObject<unsigned long, 2u, bool> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::AttributeLabelObject<unsigned long, 3u, bool> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::AttributeLabelObject<unsigned long long, 2u, bool> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::AttributeLabelObject<unsigned long long, 3u, bool> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::LabelObject<unsigned char, 2u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::LabelObject<unsigned char, 3u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::LabelObject<unsigned int, 2u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::LabelObject<unsigned int, 3u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::LabelObject<unsigned long, 2u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::LabelObject<unsigned long, 3u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::LabelObject<unsigned long long, 2u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::LabelObject<unsigned long long, 3u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::LabelObject<unsigned short, 2u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::LabelObject<unsigned short, 3u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::ShapeLabelObject<unsigned long, 2u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::ShapeLabelObject<unsigned long, 3u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::ShapeLabelObject<unsigned long long, 2u> >;
template class SITKExplicit_EXPORT itk::LabelMap<itk::ShapeLabelObject<unsigned long long, 3u> >;
