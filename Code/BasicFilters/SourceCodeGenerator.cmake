
macro( expand_template FILENAME ARITY )
  message ( "Generating source code for ${FILENAME}" )

  # Do this in one massive custom command.  Will result in code re-generating from time to time, but that is OK (hopefully!)

  add_custom_command (
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h" "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx" "${SimpleITK_BINARY_DIR}/Testing/Unit/sitk${FILENAME}ImageFilterTest.cxx"

    COMMAND lua ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.h.in ${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h 
    COMMAND lua ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.cxx.in ${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx 
    COMMAND lua ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${SimpleITK_SOURCE_DIR}/Testing/Unit/sitk${ARITY}ImageFilterTestTemplate.cxx.in ${SimpleITK_BINARY_DIR}/Testing/Unit/sitk${FILENAME}ImageFilterTest.cxx 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.h.in ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.cxx.in ${SimpleITK_SOURCE_DIR}/Testing/Unit/sitk${ARITY}ImageFilterTestTemplate.cxx.in
    )


#   add_custom_command (
#     OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h"
#     COMMAND lua ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.h.in ${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h 
#     DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.h.in
#     )
  set ( SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource} "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.h" )

#   add_custom_command (
#     OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx"
#     COMMAND lua ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.cxx.in ${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx 
#     DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.json ${CMAKE_CURRENT_SOURCE_DIR}/sitk${ARITY}ImageFilterTemplate.cxx.in
#     )
  set ( SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource} "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILENAME}ImageFilter.cxx" )

  # Make the list visible at the global scope
  set ( GENERATED_TEST_SOURCE_LIST ${GENERATED_TEST_SOURCE_LIST} "${SimpleITK_BINARY_DIR}/Testing/Unit/sitk${FILENAME}ImageFilterTest.cxx" CACHE INTERNAL "" )
  set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "BasicFilters.${FILENAME}" CACHE INTERNAL "" )
  set ( GENERATED_FILTER_LIST ${GENERATED_FILTER_LIST} ${FILENAME} CACHE INTERNAL "" )
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
expand_dual_template ( SquaredDifference )
expand_dual_template ( Subtract )

message ( "List of generated code: ${GENERATED_FILTER_LIST}" )

# clear the include files
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h "" )
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i "" )
foreach ( filter ${GENERATED_FILTER_LIST} )
  file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h "#include \"sitk${filter}ImageFilter.h\"\n" )
  file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i "%include \"sitk${filter}ImageFilter.h\"\n" )
endforeach()
