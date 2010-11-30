
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

expand_template ( CurvatureFlow )
expand_template ( BinaryThreshold )
expand_template ( Add )
expand_template ( SquaredDifference )
expand_template ( Subtract )

# clear the include files
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h "" )
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i "" )
foreach ( filter ${GENERATED_FILTER_LIST} )
  file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.h "#include \"sitk${filter}ImageFilter.h\"\n" )
  file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKBasicFiltersGeneratedHeaders.i "%include \"sitk${filter}ImageFilter.h\"\n" )
endforeach()
