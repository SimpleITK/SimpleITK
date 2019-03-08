
# set_from_env
# ------------
#
# Sets a CMake variable from an environment variable. If the
# environment variable  is not  defined then either a fatal error is
# generated or the CMake variable is not modified.
#
# set_from_env( <variable> <environment variable> [REQUIRED|DEFAULT value] )
function(set_from_env var env_var)
  if(NOT DEFINED ENV{${env_var}})
    if (ARGV2 STREQUAL "REQUIRED")
      message(FATAL_ERROR "Required environment variable \"${env_var}\" not defined.")
    elseif (ARGV2 STREQUAL "DEFAULT")
      message("Setting \"${var}\" to default \"${ARGV3}\".")
      set(${var} ${ARGV3} PARENT_SCOPE)
    endif()
  else()
    message("Setting \"${var}\" to \"$ENV{${env_var}}\" from environment.")
    set(${var} $ENV{${env_var}} PARENT_SCOPE)
  endif()
endfunction()

set_from_env(CTEST_SITE "AGENT_MACHINENAME" REQUIRED)
set(CTEST_SITE "Azure.${CTEST_SITE}")
set(CTEST_UPDATE_VERSION_ONLY 1)

set_from_env(PARALLEL_LEVEL "PARALLEL_LEVEL" DEFAULT 2 )
set( CTEST_TEST_ARGS ${CTEST_TEST_ARGS} PARALLEL_LEVEL ${PARALLEL_LEVEL})
set_from_env(workspace "AGENT_BUILDDIRECTORY" REQUIRED)
file(TO_CMAKE_PATH "${workspace}" CTEST_DASHBOARD_ROOT)
file(RELATIVE_PATH dashboard_source_name "${workspace}" "$ENV{BUILD_SOURCESDIRECTORY}")

# Make environment variables to CMake variables for CTest
set_from_env(CTEST_CMAKE_GENERATOR "CTEST_CMAKE_GENERATOR" DEFAULT "Ninja" )
set_from_env(CTEST_CONFIGURATION_TYPE "CTEST_CONFIGURATION_TYPE" DEFAULT "Release")
set_from_env(CTEST_SOURCE_DIRECTORY "BUILD_SOURCESDIRECTORY" REQUIRED)
#set_from_env(CTEST_BINARY_DIRECTORY "CTEST_BINARY_DIRECTORY")
set_from_env(CTEST_BUILD_FLAGS "CTEST_BUILD_FLAGS")
set_from_env(CTEST_BUILD_TARGET "CTEST_BUILD_TARGET")
set_from_env(CTEST_TEST_ARGS "CTEST_TEST_ARGS")


set_from_env(DASHBOARD_BRANCH_DIRECTORY "DASHBOARD_BRANCH_DIRECTORY" REQUIRED)


set_from_env(dashboard_do_coverage "DASHBOARD_DO_COVERAGE" 0)
set_from_env(CTEST_COVERAGE_COMMAND "CTEST_COVERAGE_COMMAND")

# Construct build name based on what is being built
set(dashboard_loop 0)


if(NOT CTEST_BUILD_NAME)
  if(DEFINED ENV{SYSTEM_PULLREQUEST_SOURCEBRANCH})
    set(branch "-$ENV{SYSTEM_PULLREQUEST_SOURCEBRANCH}")
    set(dashboard_model "Experimental")
  elseif("$ENV{BUILD_SOURCEBRANCHNAME}" STREQUAL "master")
    set(branch "-master")
    set(dashboard_model "Continuous")
  else()
    set(branch "-$ENV{BUILD_SOURCEBRANCHNAME}")
    set(dashboard_model "Experimental")
  endif()

  if(DEFINED ENV{SYSTEM_PULLREQUEST_PULLREQUESTNUMBER})
    set(pr "-PR$ENV{SYSTEM_PULLREQUEST_PULLREQUESTNUMBER}")
  else()
    set(pr "")
  endif()

  set(CTEST_BUILD_NAME "$ENV{AGENT_NAME}-$ENV{AGENT_JOBNAME}-$ENV{BUILD_BUILDID}${pr}${branch}")
endif()

if ( EXISTS "${CTEST_SOURCE_DIRECTORY}/azure.yml")
  list(APPEND CTEST_NOTES_FILES
    "${CTEST_SOURCE_DIRECTORY}/azure.yml"
    )
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

endif()




string(TIMESTAMP build_date "%Y-%m-%d")
message("CDash Build Identifier: ${build_date} ${CTEST_BUILD_NAME}")

include("${DASHBOARD_BRANCH_DIRECTORY}/simpleitk_common.cmake")
