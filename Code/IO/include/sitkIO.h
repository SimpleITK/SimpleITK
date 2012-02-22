#ifndef __sitkIO_h
#define __sitkIO_h

#include "sitkMacro.h"



#if defined( SITKDLL )
  #ifdef SimpleITKIO_EXPORTS
    #define SITKIO_EXPORT SITK_ABI_EXPORT
  #else
    #define SITKIO_EXPORT SITK_ABI_IMPORT
  #endif  /* SimpleITKIO_EXPORTS */
#else
  // Don't hide symbols in the static SimpleITKIO library in case
  // -fvisibility=hidden is used
  #define SITKIO_EXPORT

#endif

#define SITKCommon_HIDDEN SITK_ABI_HIDDEN

#endif // __sitkIO_h
