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
#ifndef sitkBasicFilters_h
#define sitkBasicFilters_h

#include "sitkMacro.h"

#include "sitkInterpolator.h"
#include "sitkRandomSeed.h"

// todo this should be moved to a more local place
#include "sitkTransform.h"

#if defined( SITKDLL )
  #ifdef SimpleITKBasicFilters0_EXPORTS
    #define SITKBasicFilters0_EXPORT SITK_ABI_EXPORT
  #else
    #define SITKBasicFilters0_EXPORT SITK_ABI_IMPORT
  #endif  /* SimpleITKBasicFilters0_EXPORTS */
#else
  // Don't hide symbols in the static SimpleITKBasicFilters library in case
  // -fvisibility=hidden is used
  #define SITKBasicFilters0_EXPORT
#endif

#if defined( SITKDLL )
  #ifdef SimpleITKBasicFilters_EXPORTS
    #define SITKBasicFilters_EXPORT SITK_ABI_EXPORT
  #else
    #define SITKBasicFilters_EXPORT SITK_ABI_IMPORT
  #endif  /* SimpleITKBasicFilters_EXPORTS */
#else
  // Don't hide symbols in the static SimpleITKBasicFilters library in case
  // -fvisibility=hidden is used
  #define SITKBasicFilters_EXPORT
#endif

#define SITKBasicFilters0_HIDDEN SITK_ABI_HIDDEN
#define SITKBasicFilters_HIDDEN SITK_ABI_HIDDEN

#endif // sitkBasicFilters_h
