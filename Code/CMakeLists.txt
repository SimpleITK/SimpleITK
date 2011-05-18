
## SITK_MODULE_DEPENDANIES
## =======================
## Common
##  |  \___BasicFilters
##  |                  \___Registration
##   \___IO
##         \___Display
##

set ( SITK_MODULES Common BasicFilters Registration IO Display )
set ( SITK_MASTERHEADERS "" )

foreach ( CURRENT_SUBDIR ${SITK_MODULES} )
  add_subdirectory( ${CURRENT_SUBDIR} )
  set ( SITK_MASTERHEADERS "${SITK_MASTERHEADERS}" "SimpleITK${CURRENT_SUBDIR}.h" )
endforeach( CURRENT_SUBDIR )

## Now write the master SimpleITK.h headerfile
set ( LIBNAME SimpleITK )
set ( MASTERHEADER ${SimpleITK_BINARY_DIR}/include/${LIBNAME}.h )
 CreateLibMasterHeader( "${LIBNAME}" "${MASTERHEADER}"  "${SITK_MASTERHEADERS}")
