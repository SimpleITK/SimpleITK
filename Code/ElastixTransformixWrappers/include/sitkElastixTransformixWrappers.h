/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#ifndef sitkElastixTransformixWrappers_h
#define sitkElastixTransformixWrappers_h

#include "sitkMacro.h"

#if defined(SITKDLL)
#  ifdef SITKElastix_EXPORTS
#    define SITKElastix_EXPORT SITK_ABI_EXPORT
#  else
#    define SITKElastix_EXPORT SITK_ABI_IMPORT
#  endif
#else
// Don't hide symbols in the static library in case
// -fvisibility=hidden is used
#  define SITKElastix_EXPORT
#endif

#define SITKElastix_HIDDEN SITK_ABI_HIDDEN

#endif // sitkElastixTransformixWrappers_h
