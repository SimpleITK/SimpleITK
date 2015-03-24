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
#ifndef __sitkExplicit_h
#define __sitkExplicit_h

#include "sitkMacro.h"
#if defined( SITKDLL ) && !defined( SITK_SimpleITKExplit_STATIC )
  #ifdef SimpleITKExplicit_EXPORTS
    #define SITKExplicit_EXPORT SITK_ABI_EXPORT
  #else
    #define SITKExplicit_EXPORT SITK_ABI_IMPORT
  #endif  /* SimpleITKExplicit_EXPORTS */
#else
  // Don't hide symbols in the static SimpleITKExplicit library in case
  // -fvisibility=hidden is used
  #define SITKExplicit_EXPORT
#endif

#define SITKExplicit_HIDDEN SITK_ABI_HIDDEN


#if defined( SimpleITKExplicit_EXPORTS )
// don't use export
#define SITKExplicit_EXPORT_EXPLICIT
#else
// only import/hidden
#define SITKExplicit_EXPORT_EXPLICIT SITKExplicit_EXPORT
#endif

#endif // __sitkExplicit_h
