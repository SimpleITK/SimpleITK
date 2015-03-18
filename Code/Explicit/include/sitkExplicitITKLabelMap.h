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
#ifndef sitkExplicitITKLabelMap_h__
#define sitkExplicitITKLabelMap_h__
#include "sitkExplicit.h"
#include "itkLabelMap.h"

#ifndef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::AttributeLabelObject<unsigned long, 2u, bool> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::AttributeLabelObject<unsigned long, 3u, bool> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::AttributeLabelObject<unsigned long long, 2u, bool> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::AttributeLabelObject<unsigned long long, 3u, bool> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned char, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned char, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned int, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned int, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned long long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned short, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::LabelObject<unsigned short, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::ShapeLabelObject<unsigned long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::ShapeLabelObject<unsigned long, 3u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::ShapeLabelObject<unsigned long long, 2u> >;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::LabelMap<itk::ShapeLabelObject<unsigned long long, 3u> >;
#endif // SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#endif // sitkExplicitITKLabelMap_h__
