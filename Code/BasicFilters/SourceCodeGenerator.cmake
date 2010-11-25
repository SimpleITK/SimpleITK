
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

  foreach(  variable_line ${VARIABLES_RECORDS} )

    string( REGEX MATCH "[A-Za-z]* "   variable_name  "${variable_line}")
    string( REGEX MATCH " [a-z_0-9]* " variable_type  "${variable_line}")
    string( REGEX MATCH " [a-z.0-9]*$" variable_value "${variable_line}")

    if( variable_name )
      process_one_member_variable( ${variable_name} ${variable_type} ${variable_value} )
    endif()
  endforeach()

endmacro()


macro( process_filter_descriptor  FILTER_FILE_NAME )

  set( FILTER_PARAMETER_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/${FILTER_FILE_NAME}.in" )

  if( EXISTS "${FILTER_PARAMETER_FILE_NAME}" )

    file( STRINGS "${FILTER_PARAMETER_FILE_NAME}" variable_records NEWLINE_CONSUME)

    process_all_member_variables( ${variable_records} )

  endif()

endmacro()


macro( generate_dual_filter FILTERNAME PIXEL_TYPE_LIST)

  set(FILTERNAME  ${FILTERNAME})

  set(SUPPORTED_PIXEL_TYPES "typedef ${PIXEL_TYPE_LIST}  PixelTypeList;")

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

macro( generate_single_filter FILTERNAME PIXEL_TYPE_LIST)

  set(FILTERNAME  ${FILTERNAME})

  set(SUPPORTED_PIXEL_TYPES "typedef ${PIXEL_TYPE_LIST}  PixelTypeList;")

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

generate_single_filter( BinaryThreshold BasicPixelTypeList )
generate_single_filter( IntensityWindowing BasicPixelTypeList )
generate_single_filter( InvertIntensity BasicPixelTypeList )
generate_single_filter( RescaleIntensity BasicPixelTypeList )
generate_single_filter( Sigmoid BasicPixelTypeList )

generate_single_filter( Cos BasicPixelTypeList )
generate_single_filter( Sin BasicPixelTypeList )
generate_single_filter( Tan BasicPixelTypeList )
generate_single_filter( Acos BasicPixelTypeList )
generate_single_filter( Asin BasicPixelTypeList )
generate_single_filter( Atan BasicPixelTypeList )
generate_single_filter( Exp BasicPixelTypeList )
generate_single_filter( ExpNegative BasicPixelTypeList )
generate_single_filter( Log BasicPixelTypeList )
generate_single_filter( Log10 BasicPixelTypeList )
generate_single_filter( Sqrt BasicPixelTypeList )
generate_single_filter( Square BasicPixelTypeList )

generate_single_filter( And IntegerPixelTypeList )
generate_single_filter( Or  IntegerPixelTypeList )
generate_single_filter( Not IntegerPixelTypeList )
generate_single_filter( Xor IntegerPixelTypeList )

generate_single_filter( CurvatureFlow RealPixelTypeList )

generate_dual_filter( Subtract BasicPixelTypeList )
generate_dual_filter( Divide BasicPixelTypeList )
generate_dual_filter( Multiply BasicPixelTypeList )
generate_dual_filter( Add BasicPixelTypeList )
generate_dual_filter( Atan2 BasicPixelTypeList )
generate_dual_filter( Mask BasicPixelTypeList )
generate_dual_filter( MaskNegated BasicPixelTypeList )
generate_dual_filter( Minimum BasicPixelTypeList )
generate_dual_filter( Maximum BasicPixelTypeList )
generate_dual_filter( SquaredDifference BasicPixelTypeList )
generate_dual_filter( BinaryMagnitude BasicPixelTypeList )

