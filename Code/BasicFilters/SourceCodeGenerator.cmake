set ( GENERATED_FILTER_LIST "" CACHE INTERNAL "" )

macro( expand_template FILENAME )
  # Do this in one massive custom command.  Will result in code re-generating from time to time, but that is OK (hopefully!)
  add_custom_command (
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h" "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx"
    COMMAND lua ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitkImageFilterTemplate.h.in ${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h 
    COMMAND lua ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitkImageFilterTemplate.cxx.in ${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitkImageFilterTemplate.h.in ${CMAKE_CURRENT_SOURCE_DIR}/sitkImageFilterTemplate.cxx.in
    )
  set ( SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource} "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h" )
  set ( SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource} "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx" )

  # Make the list visible at the global scope
  set ( GENERATED_FILTER_LIST ${GENERATED_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )
endmacro()

if ( SHORT_COMPILE )
  set ( JSON_CONFIG_FILES CurvatureFlow.json Cos.json Subtract.json )
else()
  file ( GLOB JSON_CONFIG_FILES *.json)
endif()


foreach ( f ${JSON_CONFIG_FILES} ) 
  get_filename_component ( class ${f} NAME_WE )
  expand_template ( ${class} )
endforeach()

# clear the include files
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h.tmp "" )
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i.tmp "" )
foreach ( filter ${GENERATED_FILTER_LIST} )
  file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h.tmp "#include \"sitk${filter}ImageFilter.h\"\n" )
  file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i.tmp "%include \"sitk${filter}ImageFilter.h\"\n" )
endforeach()
# Check if they have changed, and only in they have, copy them as new ones.
file( DIFFERENT GENERATED_HEADERS_CHANGED FILES
  ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h
  ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h.tmp )
file( DIFFERENT GENERATED_INTERFACES_CHANGED FILES
  ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i
  ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i.tmp )
if( GENERATED_HEADERS_CHANGED )
  configure_file(
    ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h.tmp
    ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h
    COPYONLY )
endif()
if( GENERATED_INTERFACES_CHANGED )
  configure_file(
    ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i.tmp
    ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i
    COPYONLY )
endif()

