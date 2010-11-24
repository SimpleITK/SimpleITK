
file ( GLOB SimpleITKBasicFiltersSource *.cxx *.h )

# Try the lua code
macro( expand_template FILENAME ARITY )
  add_custom_command (
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h"
    COMMAND lua ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.lua ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.h.in ${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.lua ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.h.in
    )
  set ( SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource} "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h" )

  add_custom_command (
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx"
    COMMAND lua ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.lua ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.cxx.in ${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.lua ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.cxx.in
    )
  set ( SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource} "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx" )

  set ( GENERATED_FILTER_LIST ${GENERATED_FILTER_LIST} ${FILENAME} )
endmacro()

# use expand_single_template when the filter has 1 input
macro( expand_single_template FILENAME )
  expand_template ( ${FILENAME} "" )
endmacro()

# use expand_dual_template when the filter has 2 inputs
macro( expand_dual_template FILENAME )
  expand_template ( ${FILENAME} "Dual" )
endmacro()

expand_single_template ( CurvatureFlow )
expand_single_template ( BinaryThreshold )
expand_dual_template ( Add )


# clear the include files
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h "" )
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i "" )
foreach ( filter ${GENERATED_FILTER_LIST} )
  file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h "#include \"sitk${filter}ImageFilter.h\"\n" )
  file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i "%include \"sitk${filter}ImageFilter.h\"\n" )
endforeach()

include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 )

add_library ( SimpleITKBasicFilters ${SimpleITKBasicFiltersSource} )
target_link_libraries ( SimpleITKBasicFilters SimpleITKCommon ITKBasicFilters )
