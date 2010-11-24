
file ( GLOB SimpleITKBasicFiltersSource *.cxx *.h )

macro( process_one_member_variable VARIABLE_NAME VARIABLE_TYPE VARIABLE_VALUE )

  set(MEMBER_VARIABLES_SET_GET ${MEMBER_VARIABLES_SET_GET}
    "sitkSetGetMacro( ${VARIABLE_TYPE}, ${VARIABLE_NAME} );\n"
    )

  set(MEMBER_VARIABLES_DECLARATION ${MEMBER_VARIABLES_DECLARATION}
    "${VARIABLE_TYPE}  m_${VARIABLE_NAME};\n"
    )

  set(MEMBER_VARIABLES_INITIALIZATION ${MEMBER_VARIABLES_INITIALIZATION}
    "this->m_${VARIABLE_NAME} = ${VARIABLE_VALUE};\n"
    )

  set(MEMBER_VARIABLES_SERIALIZATION ${MEMBER_VARIABLES_SERIALIZATION}
    "out << \"\t${VARIABLE_NAME}: \" << this->m_${VARIABLE_NAME} << \"\\n\";\n"
    )

  set(MEMBER_VARIABLES_TRANSFER ${MEMBER_VARIABLES_TRANSFER}
    "filter->Set${VARIABLE_NAME}( this->m_${VARIABLE_NAME} );\n"
    )

endmacro()

macro( process_all_member_variables  VARIABLES_RECORDS )

  message( "${VARIABLES_RECORDS}" )

  foreach(  variable_line ${VARIABLES_RECORDS} )
    message( " --- START PARSING--- ${variable_line}" )
    string( REGEX MATCH "[A-Za-z]* "   variable_name  "${variable_line}")
    string( REGEX MATCH " [a-z]* "     variable_type  "${variable_line}")
    string( REGEX MATCH " [a-z.0-9]*$" variable_value "${variable_line}")
    message( "variable_name = ${variable_name}" )
    message( "variable_type = ${variable_type}" )
    message( "variable_value = ${variable_value}" )
    if( variable_name )
      process_one_member_variable( ${variable_name} ${variable_type} ${variable_value} )
    endif()
  endforeach()

endmacro()


macro( process_filter_descriptor  FILTER_FILE_NAME )

set( FILTER_PARAMETER_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/${FILTER_FILE_NAME}.in" )

message( "${FILTER_PARAMETER_FILE_NAME}" )

if( EXISTS "${FILTER_PARAMETER_FILE_NAME}" )

  file( STRINGS "${FILTER_PARAMETER_FILE_NAME}" variable_records NEWLINE_CONSUME)

  process_all_member_variables( ${variable_records} )

endif()

endmacro()


macro( generate_dual_filter FILTERNAME )

  set(FILTERNAME  ${FILTERNAME})

  set(MEMBER_VARIABLES_SET_GET "")
  set(MEMBER_VARIABLES_DECLARATION "")
  set(MEMBER_VARIABLES_INITIALIZATION "")
  set(MEMBER_VARIABLES_SERIALIZATION "")
  set(MEMBER_VARIABLES_TRANSFER "")

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

  set(MEMBER_VARIABLES_SET_GET "")
  set(MEMBER_VARIABLES_DECLARATION "")
  set(MEMBER_VARIABLES_INITIALIZATION "")
  set(MEMBER_VARIABLES_SERIALIZATION "")
  set(MEMBER_VARIABLES_TRANSFER "")

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

generate_single_filter( BinaryThreshold )
generate_single_filter( IntensityWindowing )
generate_single_filter( InvertIntensity )

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
