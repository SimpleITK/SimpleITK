include(sitkExternalData)
include(CMakeParseArguments)

set(SimpleITK_DATA_ROOT ${SimpleITK_SOURCE_DIR}/Testing/Data)

#-----------------------------------------------------------------------------
# SimpleITK wrapper for add_test that adds support for external data,
# and post comparison processes.
#
# ARGUMENTS
#
# [ADD_TEST ARGUMENTS...]
#   The first arguments are passed to cmake's add_test function with
#   support for the DATA{} references to external data
# TRANSFORM_COMPARE <test transform> <baseline displacement> [tolerance]
function(sitk_add_test)
  set(options "")
  set(oneValueArgs "")
  set(multiValueArgs TRANSFORM_COMPARE)
  cmake_parse_arguments("_" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

  # Add test with data in the SimpleITKData group.
  ExternalData_add_test(SimpleITKData ${__UNPARSED_ARGUMENTS})

  if("NAME" STREQUAL "${ARGV0}")
    set(_iat_testname ${ARGV1})
  else()
    set(_iat_testname ${ARGV0})
  endif()

  if ( NOT "${__TRANSFORM_COMPARE}" STREQUAL "" )
    ExternalData_add_test(SimpleITKData NAME "${_iat_testname}Compare"
      COMMAND
        $<TARGET_FILE:sitkTransformCompareDriver>
        ${__TRANSFORM_COMPARE}
      )

    set_property(TEST "${_iat_testname}Compare" APPEND PROPERTY DEPENDS ${_iat_testname})
  endif()
endfunction()

