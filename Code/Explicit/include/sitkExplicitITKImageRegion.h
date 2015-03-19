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
#ifndef sitkExplicitITKImageRegion_h__
#define sitkExplicitITKImageRegion_h__
#include "sitkExplicit.h"
#include "itkImageRegion.h"

#ifndef SITK_TEMPLATE_EXPLICIT_EXPLICITITK
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegion<1u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegion<2u>;
extern template class SITKExplicit_EXPORT_EXPLICIT itk::ImageRegion<3u>;
#endif // SITK_TEMPLATE_EXPLICIT_EXPLICITITK
#endif // sitkExplicitITKImageRegion_h__
