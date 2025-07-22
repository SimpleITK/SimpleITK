#-----------------------------------------------------------------------------
# CTest Related Settings
#-----------------------------------------------------------------------------
set(BUILDNAME "NoBuldNameGiven")
set(SITE "NoSiteGiven")
set(BUILD_TESTING_DEFAULT ON)
option(BUILD_TESTING "Turn on Testing for SimpleITK" ${BUILD_TESTING_DEFAULT})

configure_file(../CMake/CTestCustom.cmake.in CTestCustom.cmake)

enable_language(C)
enable_language(CXX)

#-----------------------------------------------------------------------------
# Platform check
#-----------------------------------------------------------------------------
set(PLATFORM_CHECK true)
if(PLATFORM_CHECK)
  # See CMake/Modules/Platform/Darwin.cmake)
  #   6.x == Mac OSX 10.2 (Jaguar)
  #   7.x == Mac OSX 10.3 (Panther)
  #   8.x == Mac OSX 10.4 (Tiger)
  #   9.x == Mac OSX 10.5 (Leopard)
  #  10.x == Mac OSX 10.6 (Snow Leopard)
  if(DARWIN_MAJOR_VERSION LESS "9")
    message(FATAL_ERROR "Only Mac OSX >= 10.5 are supported !")
  endif()
endif()

#-----------------------------------------------------------------------------
# Update CMake module path
#------------------------------------------------------------------------------

set(
  CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/SuperBuild
  ${CMAKE_BINARY_DIR}/CMake
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../CMake #  CMake directory
  ${CMAKE_CURRENT_SOURCE_DIR}/../Wrapping
  ${CMAKE_MODULE_PATH}
)

include(sitkPreventInSourceBuilds)
include(sitkPreventInBuildInstalls)
include(VariableList)
include(sitkExternalData)
include(sitkSITKLegacyNaming)
include(sitkUseCCache)
include(sitkUseGoldLinker)

add_custom_target(SuperBuildSimpleITKSource)

#
# sitkSourceDownload( <output variable> <filename> )
#
# A function to get a filename for an ExternalData source file used in
# a superbuild. Adds a target which downloads all source code
# needed for superbuild projects. The source file is cached with in
# the build tree, and can be locally cache with other ExternalData
# controlled environment variables.
#
# <output variable> is set to the downloaded file.
# <output variable>_HASH is set to a hash of the file of the form ALGO=HASH_VALUE
#
# The "SuperBuildSimpleITKSource" target needs to be manually added as
# a dependencies to the ExternalProject.
#
#   add_dependencies( PROJ "SuperBuildSimpleITKSource" )
#
function(sitkSourceDownload outVar filename)
  set(algo "SHA512")
  set(algo_extension ".sha512")
  set(link_file "${CMAKE_CURRENT_SOURCE_DIR}/ExternalSource/${filename}")
  if(NOT EXISTS "${link_file}${algo_extension}")
    message(
      FATALERROR
      "The source download file: \"${link_file}${algo_extension}\" does not exists."
    )
  endif()

  file(READ "${link_file}${algo_extension}" _HASH)
  string(STRIP "${_HASH}" _HASH)
  set(${outVar}_HASH "${algo}=${_HASH}" PARENT_SCOPE)

  ExternalData_Expand_Arguments(
    SuperBuildSimpleITKSourceReal
    link
    DATA{${link_file}}
  )
  set(${outVar} "${link}" PARENT_SCOPE)
endfunction()

function(sitkSourceDownloadDependency proj)
  ExternalProject_Add_StepDependencies(
    ${proj}
    download
    "SuperBuildSimpleITKSource"
  )
endfunction()

#-----------------------------------------------------------------------------
# Prerequisites
#------------------------------------------------------------------------------
#

# Compute -G arg for configuring external projects with the same CMake generator:
if(CMAKE_EXTRA_GENERATOR)
  set(gen "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}")
else()
  set(gen "${CMAKE_GENERATOR}")
endif()

#-----------------------------------------------------------------------------
# Use GIT protocol
#------------------------------------------------------------------------------
find_package(Git)
set(_SimpleITK_GIT_PROTOCOL_default "https")
if(GIT_VERSION_STRING VERSION_LESS "1.7.10")
  # minimum version for https support
  set(_SimpleITK_GIT_PROTOCOL_default "git")
endif()
set(
  SimpleITK_GIT_PROTOCOL
  ${_SimpleITK_GIT_PROTOCOL_default}
  CACHE STRING
  "If behind a firewall turn set this to 'https' or 'http'."
)
mark_as_advanced(SimpleITK_GIT_PROTOCOL)
set_property(
  CACHE
    SimpleITK_GIT_PROTOCOL
  PROPERTY
    STRINGS
      "https;http;git"
)
set(git_protocol ${SimpleITK_GIT_PROTOCOL})
sitk_legacy_naming(SimpleITK_GIT_PROTOCOL)

#-----------------------------------------------------------------------------
# SimpleITK options
#------------------------------------------------------------------------------

option(
  BUILD_EXAMPLES
  "Enable Building of the SimpleITK Examples as a separate project."
  ON
)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(
    CACHE
      CMAKE_BUILD_TYPE
    PROPERTY
      STRINGS
        "Debug"
        "Release"
        "MinSizeRel"
        "RelWithDebInfo"
  )
endif()

# Default to build shared libraries off
option(
  BUILD_SHARED_LIBS
  "Build SimpleITK ITK with shared libraries. This does not effect wrapped languages."
  OFF
)

# as this option does not robustly work across platforms it will be marked as advanced
mark_as_advanced(FORCE BUILD_SHARED_LIBS)

include(sitkMaxDimensionOption)

#-----------------------------------------------------------------------------
# Setup build type
#------------------------------------------------------------------------------

# By default, let's build as Debug
if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# let a dashboard override the default.
if(CTEST_BUILD_CONFIGURATION)
  set(CMAKE_BUILD_TYPE "${CTEST_BUILD_CONFIGURATION}")
endif()

#-------------------------------------------------------------------------
# augment compiler flags
#-------------------------------------------------------------------------
include(sitkCheckRequiredFlags)

#------------------------------------------------------------------------------
# BuildName used for dashboard reporting
#------------------------------------------------------------------------------
if(NOT BUILDNAME)
  set(
    BUILDNAME
    "Unknown-build"
    CACHE STRING
    "Name of build to report to dashboard"
  )
endif()

#------------------------------------------------------------------------------
# Common Build Options to pass to all subsequent tools
#------------------------------------------------------------------------------
list(
  APPEND
  ep_common_list
  MAKECOMMAND
  CMAKE_BUILD_TYPE
  CMAKE_MAKE_PROGRAM
  CMAKE_C_COMPILER
  CMAKE_C_COMPILER_LAUNCHER
  CMAKE_C_FLAGS
  CMAKE_C_FLAGS_DEBUG
  CMAKE_C_FLAGS_MINSIZEREL
  CMAKE_C_FLAGS_RELEASE
  CMAKE_C_FLAGS_RELWITHDEBINFO
  CMAKE_C_STANDARD
  CMAKE_C_STANDARD_REQUIRED
  CMAKE_C_EXTENSIONS
  CMAKE_CXX_COMPILER
  CMAKE_CXX_COMPILER_LAUNCHER
  CMAKE_CXX_FLAGS
  CMAKE_CXX_FLAGS_DEBUG
  CMAKE_CXX_FLAGS_MINSIZEREL
  CMAKE_CXX_FLAGS_RELEASE
  CMAKE_CXX_FLAGS_RELWITHDEBINFO
  CMAKE_CXX_STANDARD
  CMAKE_CXX_STANDARD_REQUIRED
  CMAKE_CXX_EXTENSIONS
  CMAKE_LINKER
  CMAKE_EXE_LINKER_FLAGS
  CMAKE_EXE_LINKER_FLAGS_DEBUG
  CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
  CMAKE_EXE_LINKER_FLAGS_RELEASE
  CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO
  CMAKE_MODULE_LINKER_FLAGS
  CMAKE_MODULE_LINKER_FLAGS_DEBUG
  CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL
  CMAKE_MODULE_LINKER_FLAGS_RELEASE
  CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO
  CMAKE_SHARED_LINKER_FLAGS
  CMAKE_SHARED_LINKER_FLAGS_DEBUG
  CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL
  CMAKE_SHARED_LINKER_FLAGS_RELEASE
  CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO
  CMAKE_STRIP
  CMAKE_STRIP_FLAGS
  CMAKE_PREFIX_PATH
  CMAKE_INCLUDE_PATH
  CMAKE_LIBRARY_PATH
  CMAKE_PROGRAM_PATH
  CMAKE_IGNORE_PATH
  CMAKE_FIND_FRAMEWORK
  CMAKE_FRAMEWORK_PATH
  CMAKE_SYSTEM_FRAMEWORK_PATH
  CMAKE_APPBUNDLE_PATH
  CMAKE_FIND_APPBUNDLE
  CMAKE_SYSTEM_APPBUNDLE_PATH
  CMAKE_FIND_ROOT_PATH
  CMAKE_FIND_ROOT_PATH_MODE_INCLUDE
  CMAKE_FIND_ROOT_PATH_MODE_LIBRARY
  CMAKE_FIND_ROOT_PATH_MODE_PROGRAM
  CMAKE_FIND_ROOT_PATH_MODE_PACKAGE
  CMAKE_DL_LIBS
  CMAKE_THREAD_LIBS_INIT
  CMAKE_SYSTEM_PREFIX_PATH
  CMAKE_SYSTEM_INCLUDE_PATH
  CMAKE_SYSTEM_LIBRARY_PATH
  CMAKE_SYSTEM_PROGRAM_PATH
  CMAKE_SYSTEM_IGNORE_PATH
  CMAKE_JOB_POOLS
  CMAKE_JOB_POOL_LINK
  CMAKE_JOB_POOL_COMPILE
  CMAKE_C_VISIBILITY_PRESET
  CMAKE_CXX_VISIBILITY_PRESET
  CMAKE_VISIBILITY_INLINES_HIDDEN
  CMAKE_GENERATOR
  CMAKE_GENERATOR_INSTANCE
  CMAKE_GENERATOR_PLATFORM
  CMAKE_GENERATOR_TOOLSET
  CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE
  CMAKE_VS_PLATFORM_TOOLSET_VERSION
  CMAKE_VS_PLATFORM_TOOLSET
  CMAKE_EXTRA_GENERATOR
  MEMORYCHECK_COMMAND_OPTIONS
  MEMORYCHECK_SUPPRESSIONS_FILE
  MEMORYCHECK_COMMAND
  SITE
  BUILDNAME
  SKBUILD
  CMAKE_OSX_SYSROOT
  CMAKE_OSX_DEPLOYMENT_TARGET
)

variablelisttoargs( ep_common_list ep_common_args )

if(APPLE)
  list(APPEND ep_common_list CMAKE_OSX_ARCHITECTURES)
endif()
variablelisttocache( ep_common_list ep_common_cache )

#
# Use CMake file which present options for wrapped languages, and finds languages as needed
#
include(sitkLanguageOptions)

if(NOT CMAKE_VERSION VERSION_LESS 3.4)
  set(
    External_Project_USES_TERMINAL
    USES_TERMINAL_DOWNLOAD
    1
    USES_TERMINAL_CONFIGURE
    1
    USES_TERMINAL_BUILD
    1
    USES_TERMINAL_INSTALL
    1
  )
endif()

if(POLICY CMP0135)
  set(
    External_Project_USE_ARCHIVE_TIMESTAMP
    DOWNLOAD_EXTRACT_TIMESTAMP
    1
  )
endif()

#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
include(ExternalProject)

#------------------------------------------------------------------------------
# Swig
#------------------------------------------------------------------------------
option(
  SimpleITK_USE_SYSTEM_SWIG
  "Use a pre-compiled version of SWIG 4.0 previously configured for your system"
  OFF
)
sitk_legacy_naming( SimpleITK_USE_SYSTEM_SWIG USE_SYSTEM_SWIG )
mark_as_advanced(SimpleITK_USE_SYSTEM_SWIG)
if(SimpleITK_USE_SYSTEM_SWIG)
  find_package(SWIG 4 REQUIRED)
else()
  include(External_Swig)
  list(APPEND ${CMAKE_PROJECT_NAME}_DEPENDENCIES Swig)
endif()

#------------------------------------------------------------------------------
# Google Test
#------------------------------------------------------------------------------
option(SimpleITK_USE_SYSTEM_GTEST "Use an external version of GoogleTest. " OFF)
sitk_legacy_naming( SimpleITK_USE_SYSTEM_GTEST USE_SYSTEM_GTEST )
mark_as_advanced(SimpleITK_USE_SYSTEM_GTEST)
if(BUILD_TESTING)
  if(SimpleITK_USE_SYSTEM_GTEST)
    if(DEFINED GTEST_ROOT AND EXISTS "${GTEST_ROOT}/CMakeLists.txt")
      list(APPEND SimpleITK_VARS GTEST_ROOT)
    else()
      find_package(GTest REQUIRED)
      list(
        APPEND
        SimpleITK_VARS
        GTEST_LIBRARIES
        GTEST_INCLUDE_DIRS
        GTEST_MAIN_LIBRARIES
      )
    endif()
  else()
    include(External_GTest)
    list(APPEND SimpleITK_VARS GTEST_ROOT)
    list(APPEND ${CMAKE_PROJECT_NAME}_DEPENDENCIES GTest)
  endif()
endif()

#------------------------------------------------------------------------------
# ITK
#------------------------------------------------------------------------------

option(SimpleITK_USE_SYSTEM_ITK "Use a pre-built version of ITK" OFF)
sitk_legacy_naming( SimpleITK_USE_SYSTEM_ITK USE_SYSTEM_ITK )
mark_as_advanced(SimpleITK_USE_SYSTEM_ITK)
if(SimpleITK_USE_SYSTEM_ITK)
  find_package(ITK REQUIRED)
  #we require certain packages be turned on in ITK
  include(sitkCheckForITKModuleDependencies)
else()
  include(External_ITK)
  list(APPEND ${CMAKE_PROJECT_NAME}_DEPENDENCIES ITK)
endif()

#------------------------------------------------------------------------------
# Elastix
#------------------------------------------------------------------------------
option(SimpleITK_USE_ELASTIX "Use the Elastix image registration library" OFF)
if(SimpleITK_USE_ELASTIX)
  include(External_Elastix)
  list(APPEND ${CMAKE_PROJECT_NAME}_DEPENDENCIES Elastix)
endif()

#------------------------------------------------------------------------------
# Python Virtual Environment with uv
#------------------------------------------------------------------------------
set(_Python_venv_home "${CMAKE_CURRENT_BINARY_DIR}/venv")

if(WIN32)
  set(_SimpleITK_Python_EXECUTABLE "${_Python_venv_home}/Scripts/python.exe")
else()
  set(_SimpleITK_Python_EXECUTABLE "${_Python_venv_home}/bin/python")
endif()

if(NOT DEFINED SimpleITK_Python_EXECUTABLE)
  set(
    SimpleITK_Python_EXECUTABLE
    "${_SimpleITK_Python_EXECUTABLE}"
    CACHE FILEPATH
    "Python executable for SimpleITK build requirements."
  )
endif()

add_custom_target(SimpleITK_VENV DEPENDS "${SimpleITK_Python_EXECUTABLE}")

set(_SimpleITK_uv_PATH "${CMAKE_CURRENT_BINARY_DIR}/uv")
set(_SimpleITK_uv_EXECUTABLE "${_SimpleITK_uv_PATH}/bin/uv")
if(WIN32)
  set(_SimpleITK_uv_EXECUTABLE "${_SimpleITK_uv_EXECUTABLE}.exe")
endif()
set(_SimpleITK_uv_PYTHON_VERSION "3.12")

sitksourcedownload(UV_INSTALLER "uv_install.sh")

add_custom_command(
  OUTPUT
    "${_SimpleITK_uv_EXECUTABLE}"
  COMMAND
    "${CMAKE_COMMAND}" -E env "XDG_BIN_HOME=${_SimpleITK_uv_PATH}/bin"
    "XDG_CONFIG_HOME=${CMAKE_CURRENT_BINARY_DIR}" UV_NO_MODIFY_PATH=1 sh
    ${UV_INSTALLER} ${UV_INSTALLER} --quiet
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  DEPENDS
    "${UV_INSTALLER}"
)

add_custom_command(
  OUTPUT
    "${_SimpleITK_Python_EXECUTABLE}"
  COMMAND
    "${_SimpleITK_uv_EXECUTABLE}" "venv" --no-cache "--python"
    "${_SimpleITK_uv_PYTHON_VERSION}" --managed-python --allow-existing
    --link-mode=copy # Suppress working with failure to hardlink files
    "${_Python_venv_home}"
  COMMAND
    "${CMAKE_COMMAND}" -E env "VIRTUAL_ENV=${_Python_venv_home}" "UV_NO_CACHE=1"
    "${_SimpleITK_uv_PATH}/bin/uv" "pip" "install" "jinja2~=3.1"
    "jsonschema~=4.24" "pyyaml~=6.0"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  DEPENDS
    "${_SimpleITK_uv_EXECUTABLE}"
  COMMENT "Creating python virtual environment..."
)

list(APPEND ${CMAKE_PROJECT_NAME}_DEPENDENCIES SimpleITK_VENV)

get_cmake_property(_varNames VARIABLES)

foreach(_varName ${_varNames})
  if(_varName MATCHES "^SimpleITK_" OR _varName MATCHES "^SITK_")
    if(
      NOT
        _varName
          MATCHES
          "^SITK_LANGUAGES_VARS"
      AND
        NOT
          _varName
            MATCHES
            "^SimpleITK_VARS"
      AND
        NOT
          _varName
            MATCHES
            "^SimpleITK_USE_SYSTEM"
      AND
        NOT
          _varName
            MATCHES
            "^SimpleITK_.*_COMPILE_OPTIONS"
      AND
        NOT
          _varName
            MATCHES
            "^SimpleITK_.*_DEFAULT"
      AND
        NOT
          _varName
            MATCHES
            "^SITK_UNDEFINED_SYMBOLS_ALLOWED"
    )
      message(
        STATUS
        "Passing variable \"${_varName}=${${_varName}}\" to SimpleITK external project."
      )
      list(APPEND SimpleITK_VARS ${_varName})
    endif()
  elseif(
    _varName
      MATCHES
      "^BUILD_DOCUMENTS$"
    OR
      _varName
        MATCHES
        "^BUILD_DOXYGEN$"
    OR
      _varName
        MATCHES
        "^DOXYGEN_"
    OR
      _varName
        MATCHES
        "^CMAKE_DISABLE_FIND_PACKAGE_"
    OR
      _varName
        MATCHES
        "^Python\_(ROOT\_DIR|INCLUDE\_DIR|LIBRARY|LIBRARY\_DEBUG|LIBRARY\_RELEASE|EXECUTABLE)$"
    # Support CMake < 3.24 by explicitly passing _Python_VERSION variables to workaround issue fixed
    # in kitware/cmake@ece3bedbf (FindPython: fix error on multiple queries with different COMPONENTS)
    # See https://gitlab.kitware.com/cmake/cmake/-/merge_requests/7410 for more details
    OR
      (
        _varName
          MATCHES
          "^\_Python\_VERSION$"
        AND
          CMAKE_VERSION
            VERSION_LESS
            "3.24"
      )
    OR
      (
        _varName
          MATCHES
          "^\_Python\_VERSION\_(MAJOR|MINOR|PATCH)$"
        AND
          CMAKE_VERSION
            VERSION_LESS
            "3.24"
      )
  )
    message(
      STATUS
      "Passing variable \"${_varName}=${${_varName}}\" to SimpleITK external project."
    )
    list(APPEND SimpleITK_VARS ${_varName})
  endif()
endforeach()

list(APPEND SimpleITK_VARS ExternalData_OBJECT_STORES)

variablelisttocache( SimpleITK_VARS  ep_simpleitk_cache )
variablelisttoargs( SimpleITK_VARS  ep_simpleitk_args )
variablelisttocache( SITK_LANGUAGES_VARS  ep_languages_cache )
variablelisttoargs( SITK_LANGUAGES_VARS  ep_languages_args )

file(
  WRITE
  "${CMAKE_CURRENT_BINARY_DIR}/SimpleITK-build/CMakeCacheInit.txt"
  "${ep_simpleitk_cache}${ep_common_cache}\n${ep_languages_cache}"
)

set(proj SimpleITK)
ExternalProject_Add(
  ${proj}
  DOWNLOAD_COMMAND
    ""
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..
  BINARY_DIR SimpleITK-build
  INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    --no-warn-unused-cli -C
    "${CMAKE_CURRENT_BINARY_DIR}/SimpleITK-build/CMakeCacheInit.txt"
    ${ep_simpleitk_args} ${ep_common_args}
    -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DCMAKE_LIBRARY_OUTPUT_DIRECTORY:PATH=<BINARY_DIR>/lib
    -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY:PATH=<BINARY_DIR>/lib
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY:PATH=<BINARY_DIR>/bin
    -DCMAKE_BUNDLE_OUTPUT_DIRECTORY:PATH=<BINARY_DIR>/bin ${ep_languages_args}
    # ITK
    -DITK_DIR:PATH=${ITK_DIR}
    # Swig
    -DSWIG_DIR:PATH=${SWIG_DIR} -DSWIG_EXECUTABLE:PATH=${SWIG_EXECUTABLE}
    -DBUILD_TESTING:BOOL=${BUILD_TESTING} -DWRAP_LUA:BOOL=${WRAP_LUA}
    -DWRAP_PYTHON:BOOL=${WRAP_PYTHON} -DWRAP_RUBY:BOOL=${WRAP_RUBY}
    -DWRAP_JAVA:BOOL=${WRAP_JAVA} -DWRAP_TCL:BOOL=${WRAP_TCL}
    -DWRAP_CSHARP:BOOL=${WRAP_CSHARP} -DWRAP_R:BOOL=${WRAP_R}
    -DBUILD_EXAMPLES:BOOL=${BUILD_EXAMPLES} -DElastix_DIR:PATH=${Elastix_DIR}
  DEPENDS
    ${${CMAKE_PROJECT_NAME}_DEPENDENCIES}
    ${External_Project_USES_TERMINAL}
  STEP_TARGETS
    configure
    build
    doc
  BUILD_ALWAYS 1
)

# explicitly add a non-default step to build SimpleITK docs
ExternalProject_Add_Step(
  ${proj}
  doc
  COMMAND
    ${CMAKE_COMMAND} --build <BINARY_DIR> --target Documentation
  DEPENDEES
    configure
  EXCLUDE_FROM_MAIN 1
  LOG 1
)

# Load the SimpleITK version variables, scope isolated in a function.
function(_set_simpleitk_install_path outVar)
  include(../Version.cmake)
  ExternalProject_Get_Property(
    ${proj}
    install_dir
  )
  set(
    ${outVar}
    "${install_dir}/lib/cmake/SimpleITK-${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR}"
    PARENT_SCOPE
  )
endfunction()
_set_simpleitk_install_path(SIMPLEITK_DIR)

#------------------------------------------------------------------------------
# SimpleITKExamples
#------------------------------------------------------------------------------

# We build SimpleITKExamples as an enternal project to verify
# installation of SimpleITK

include(External_SimpleITKExamples)

#------------------------------------------------------------------------------
# List of external projects
#------------------------------------------------------------------------------
set(
  external_project_list
  ITK
  Swig
  SimpleITKExamples
  PCRE2
  GTest
  Elastix
  ${CMAKE_PROJECT_NAME}
)

#-----------------------------------------------------------------------------
# Dump external project dependencies
#-----------------------------------------------------------------------------
set(ep_dependency_graph "# External project dependencies")
foreach(ep ${external_project_list})
  set(
    ep_dependency_graph
    "${ep_dependency_graph}\n${ep}: ${${ep}_DEPENDENCIES}"
  )
endforeach()
file(
  WRITE
  ${CMAKE_CURRENT_BINARY_DIR}/ExternalProjectDependencies.txt
  "${ep_dependency_graph}\n"
)

if(COMMAND ExternalData_Add_Target)
  ExternalData_Add_Target(SuperBuildSimpleITKSourceReal)
  add_dependencies(SuperBuildSimpleITKSource SuperBuildSimpleITKSourceReal)
endif()
