
# set_from_env
# ------------
#
# Sets a CMake variable from an environment variable. If the
# environment variable is not defined then the existing CMake value will
# persist. Next if a "DEFAULT" argument is provided then the "value"
# parameter will be used to set the variable.
#
# set_from_env( <variable> <environment variable> [REQUIRED|DEFAULT value] )
function(set_from_env var env_var)
  if( DEFINED ENV{${env_var}})
    message("Setting \"${var}\" to \"$ENV{${env_var}}\" from environment.")
    set(${var} $ENV{${env_var}} PARENT_SCOPE)
  elseif (DEFINED ${var})
    message("Using defined value for \"${var}\" of \"${${var}}\"")
  elseif (ARGV2 STREQUAL "REQUIRED")
    message(FATAL_ERROR "Required environment variable \"${env_var}\" not defined.")
  elseif (ARGV2 STREQUAL "DEFAULT")
    message("Setting \"${var}\" to default \"${ARGV3}\".")
    set(${var} ${ARGV3} PARENT_SCOPE)
  endif()
endfunction()

set_from_env(CTEST_SITE "RUNNER_NAME" REQUIRED)
set(CTEST_SITE "${CTEST_SITE}")

set_from_env(workspace "GITHUB_WORKSPACE" REQUIRED)
file(TO_CMAKE_PATH "${workspace}" CTEST_DASHBOARD_ROOT)


set(CTEST_UPDATE_VERSION_ONLY 1)
set_from_env(CTEST_SOURCE_DIRECTORY "CTEST_SOURCE_DIRECTORY" REQUIRED)
file(RELATIVE_PATH dashboard_source_name "${workspace}" "${CTEST_SOURCE_DIRECTORY}")
set_from_env(CTEST_BINARY_DIRECTORY "CTEST_BINARY_DIRECTORY")


include( ProcessorCount )
ProcessorCount( _processor_count )
set_from_env(PARALLEL_LEVEL "PARALLEL_LEVEL" DEFAULT "${_processor_count}" )
set( CTEST_TEST_ARGS ${CTEST_TEST_ARGS} PARALLEL_LEVEL ${PARALLEL_LEVEL})



# Make environment variables to CMake variables for CTest
set_from_env(CTEST_CMAKE_GENERATOR "CTEST_CMAKE_GENERATOR" DEFAULT "Ninja" )
set_from_env(CTEST_CMAKE_GENERATOR_TOOLSET "CTEST_CMAKE_GENERATOR_TOOLSET")
set_from_env(CTEST_CMAKE_GENERATOR_PLATFORM "CTEST_CMAKE_GENERATOR_PLATFORM")
set_from_env(CTEST_CONFIGURATION_TYPE "CTEST_CONFIGURATION_TYPE" DEFAULT "Release")
set_from_env(CTEST_BUILD_FLAGS "CTEST_BUILD_FLAGS")
set_from_env(CTEST_BUILD_TARGET "CTEST_BUILD_TARGET")
set_from_env(CTEST_TEST_ARGS "CTEST_TEST_ARGS")


set_from_env(CTEST_TEST_TIMEOUT "CTEST_TEST_TIMEOUT")
set_from_env(CTEST_OUTPUT_ON_FAILURE "CTEST_OUTPUT_ON_FAILURE")

set_from_env(DASHBOARD_BRANCH_DIRECTORY "DASHBOARD_BRANCH_DIRECTORY" REQUIRED)



set(dashboard_loop 0)

if( "$ENV{GITHUB_REF_NAME}" STREQUAL "master" OR  "$ENV{GITHUB_REF_NAME}" STREQUAL "release ")
  set(dashboard_model "Continuous")
else()
  set(dashboard_model "Experimental")
endif()


# Construct build name based on what is being built
if(NOT CTEST_BUILD_NAME)
  if( DEFINED ENV{GITHUB_HEAD_REF})
    # defined on pull_request or pull_request_target
    set(_branch "$ENV{GITHUB_REF_NAME}-$ENV{GITHUB_HEAD_REF}")
  else()
    set(_branch "$ENV{GITHUB_REF_NAME}")
  endif()

  set(CTEST_BUILD_NAME "${CTEST_SITE}-$ENV{RUNNER_OS}-$ENV{GITHUB_RUN_ID}-${_branch}")
endif()


SET (_dashboard_cache "
    BUILD_DOCUMENTS:BOOL=OFF
    BUILD_EXAMPLES:BOOL=OFF
    BUILD_SHARED_LIBS:BOOL=OFF
    BUILD_TESTING:BOOL=ON
    SimpleITK_EXPLICIT_INSTANTIATION:BOOL=OFF

    WRAP_DEFAULT:BOOL=OFF
" )

set_from_env(dashboard_cache "CTEST_CACHE" DEFAULT ${_dashboard_cache})

if ( NOT $ENV{GITHUB_REPOSITORY} STREQUAL "SimpleITK/SimpleITK" )
  message("Disabling CDash submit for repository $ENV{GITHUB_REPOSITORY}")
  set( dashboard_no_submit 1 )
endif()

string(TIMESTAMP build_date "%Y-%m-%d")
message("CDash Build Identifier: ${build_date} ${CTEST_BUILD_NAME}")

include("${DASHBOARD_BRANCH_DIRECTORY}/simpleitk_common.cmake")

function(print_if var)
  if( NOT ${${var}} EQUAL 0 )
    message(SEND_ERROR  "\tUnexpected result ${var}: ${${var}}")
  endif()
endfunction()


if(NOT ${configure_return} EQUAL 0 OR
   NOT ${build_return} EQUAL 0 OR
   NOT ${build_errors} EQUAL 0 OR
   NOT ${build_warnings} EQUAL 0 OR
   NOT ${test_return} EQUAL 0)
  message(FATAL_ERROR
    "Build did not complete without warnings, errors, or failures.")
  print_if(configure_return)
  print_if(build_return)
  print_if(build_errors)
  print_if(build_warnings)
  print_if(test_return)

else()
  return(0)
endif()
