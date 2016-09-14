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
#ifndef sitkCommon_h
#define sitkCommon_h

#include "sitkMacro.h"

#ifndef sitkMacro_h
#error "sitkMacro.h must be included before sitkCommon.h"
#endif

#ifdef SITK_USE_EXPLICITITK
#include "sitkExplicitITK.h"
#endif


#if defined( SITKDLL )
  #ifdef SimpleITKCommon_EXPORTS
    #define SITKCommon_EXPORT SITK_ABI_EXPORT
  #else
    #define SITKCommon_EXPORT SITK_ABI_IMPORT
  #endif  /* SimpleITKCommon_EXPORTS */
#else
  // Don't hide symbols in the static SimpleITKCommon library in case
  // -fvisibility=hidden is used
  #define SITKCommon_EXPORT
#endif

#define SITKCommon_HIDDEN SITK_ABI_HIDDEN

#endif // sitkCommon_h
