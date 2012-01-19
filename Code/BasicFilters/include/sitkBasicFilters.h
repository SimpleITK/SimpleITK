#ifndef __sitkBasicFilters_h
#define __sitkBasicFilters_h

#include "sitkMacro.h"

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


#define SITKBasicFilters_HIDDEN SITK_ABI_HIDDEN

#endif // __sitkBasicFilters_h
