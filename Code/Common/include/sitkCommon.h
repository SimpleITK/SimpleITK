#ifndef __sitkCommon_h
#define __sitkCommon_h

#include "sitkMacro.h"

#ifndef __sitkMacro_h
#error "sitkMacro.h must be included before sitkCommon.h"
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

#endif // __sitkCommon_h
