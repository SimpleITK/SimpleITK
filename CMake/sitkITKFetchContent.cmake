#-----------------------------------------------------------------------------
# Get and build ITK using FetchContent

include(FetchContent)

# Set ITK Git repository and tag
set(
  ITK_GIT_REPOSITORY
  "https://github.com/blowekamp/ITK.git"
  CACHE STRING
  "URL of ITK Git repository for FetchContent"
)
mark_as_advanced(ITK_GIT_REPOSITORY)

# The commit contains the ExternaData changes to work with SimpleITK
set(_DEFAULT_ITK_GIT_TAG "cmake_interface_module")
set(
  ITK_GIT_TAG
  "${_DEFAULT_ITK_GIT_TAG}"
  CACHE STRING
  "Tag in ITK git repo for FetchContent"
)
mark_as_advanced(ITK_GIT_TAG)

if(NOT DEFINED ITK_BUILD_DEFAULT_MODULES)
  set(ITK_BUILD_DEFAULT_MODULES ON)
endif()

set(
  _SimpleITK_DEFAULT_MODULES
  "Module_SimpleITKFilters"
  "Module_ITKIOTransformMINC"
  "Module_GenericLabelInterpolator"
  "Module_LabelErodeDilate"
  "Module_ITKReview"
)
foreach(_module ${_SimpleITK_DEFAULT_MODULES})
  if(NOT DEFINED ${_module})
    set(${_module} ON CACHE INTERNAL "")
  endif()
endforeach()

if(NOT DEFINED ITK_DEFAULT_THREADER)
  set(ITK_DEFAULT_THREADER "Pool")
endif()

# Configure ITK-specific options that need to be set before FetchContent_Declare
if(NOT ${BUILD_SHARED_LIBS})
  set(CMAKE_C_VISIBILITY_PRESET "hidden" CACHE STRING "" FORCE)
  set(CMAKE_CXX_VISIBILITY_PRESET "hidden" CACHE STRING "" FORCE)
  set(ITK_TEMPLATE_VISIBILITY_DEFAULT OFF CACHE BOOL "" FORCE)
endif()

# Set ITK build options
set(ITK_USE_KWSTYLE OFF)

# SimpleITK enables ccache by setting COMPILER_LAUNCHER variables. However, ITK_USE_CCACHE
# enforces additional contraints that are not require for SimpleITK. So we disable the
# ITK_USE_CCACHE option here, but ITK will still use ccache because the COMPILER_LAUNCHER
# variables are set.
set(ITK_USE_CCACHE OFF)
set(BUILD_TESTING OFF)
set(BUILD_EXAMPLES OFF)

FetchContent_Declare(
  ITK
  GIT_REPOSITORY "${ITK_GIT_REPOSITORY}"
  GIT_TAG "${ITK_GIT_TAG}"
  EXCLUDE_FROM_ALL
  FIND_PACKAGE_ARGS
    NAMES
    ITK
)

FetchContent_MakeAvailable(ITK)

# Check if FetchContent used find_package() or fetched from source
FetchContent_GetProperties(ITK)
if(ITK_SOURCE_DIR)
  message(STATUS "ITK fetched from repository and built from source")
  message(STATUS "  Source directory: ${ITK_SOURCE_DIR}")
  message(STATUS "  Binary directory: ${ITK_BINARY_DIR}")
  set(ITK_DIR "${ITK_BINARY_DIR}")

  include(${ITK_DIR}/ITKConfig.cmake)
elseif(DEFINED ITK_FOUND)
  message(STATUS "ITK found via find_package()")
  # ITK_DIR should already be set by find_package()
else()
  message(FATAL_ERROR "ITK configuration failed - no targets available")
endif()

# These ITK option conflict with SimpleITK.
# Allow a user's cache variable to be respected.
unset(BUILD_TESTING)
unset(BUILD_EXAMPLES)
