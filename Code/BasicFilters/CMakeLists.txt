
file ( GLOB SimpleITKBasicFiltersSource *.cxx *.h )

set(MEMBER_VARIABLES_INITIALIZATION "")
set(MEMBER_VARIABLES_SERIALIZATION "")
set(MEMBER_VARIABLES_TRANSFER "")

macro( process_member_variable VARIABLE_NAME VARIABLE_TYPE VARIABLE_VALUE )

  set(MEMBER_VARIABLES_INITIALIZATION ${MEMBER_VARIABLES_INITIALIZATION}
    "this->m_${VARIABLE_NAME} = ${VARIABLE_VALUE}"
    )

  set(MEMBER_VARIABLES_SERIALIZATION ${MEMBER_VARIABLES_SERIALIZATION}
    "<< \"\t${VARIABLE_NAME}: \" << this->m_${VARIABLE_NAME} << \"\n\" "
    )

  set(MEMBER_VARIABLES_TRANSFER ${MEMBER_VARIABLES_TRANSFER}
    "filter->Set${VARIABLE_NAME}( this->m_${VARIABLE_NAME} )"
    )
endmacro()


macro( process_filter_descriptor  FILTER_FILE_NAME )

set( FILTER_PARAMETER_FILE_NAME "${FILTER_FILE_NAME}.in" )

if( EXISTS "${FILTER_PARAMETER_FILE_NAME}" )

  file( STRINGS "${FILTER_PARAMETER_FILE_NAME}" variable_records )

  foreach(  variable_line ${variable_records} )
    message( "${variable_line}" )
  endforeach()

endif()

endmacro()


macro( generate_dual_filter FILTERNAME )

  set(FILTERNAME  ${FILTERNAME})

  process_filter_descriptor( ${FILTERNAME} )

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/sitkDualImageFilterTemplate.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.h"
    )

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/sitkDualImageFilterTemplate.cxx.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.cxx"
    )

  set(SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource}
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.cxx")

endmacro()

macro( generate_single_filter FILTERNAME )

  set(FILTERNAME  ${FILTERNAME})

  process_filter_descriptor( ${FILTERNAME} )

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageFilterTemplate.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.h"
    )

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageFilterTemplate.cxx.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.cxx"
    )

  set(SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource}
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.cxx")

endmacro()

generate_dual_filter( BinaryThreshold )

generate_dual_filter( Subtract )
generate_dual_filter( Divide )
generate_dual_filter( Multiply )
generate_dual_filter( Add )
generate_dual_filter( Atan2 )
generate_dual_filter( Mask )
generate_dual_filter( MaskNegated )
generate_dual_filter( Minimum )
generate_dual_filter( Maximum )
generate_dual_filter( SquaredDifference )
generate_dual_filter( BinaryMagnitude )

generate_single_filter( Cos )
generate_single_filter( Sin )
generate_single_filter( Tan )

include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 )


add_library ( SimpleITKBasicFilters ${SimpleITKBasicFiltersSource} )
target_link_libraries ( SimpleITKBasicFilters SimpleITKCommon ITKBasicFilters )
