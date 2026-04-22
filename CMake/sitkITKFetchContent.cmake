#-----------------------------------------------------------------------------
# Get and build ITK using FetchContent

include(FetchContent)

# Set ITK Git repository and tag (shared)
include("${CMAKE_CURRENT_LIST_DIR}/sitkITKGitOptions.cmake")

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

# ITKConfig.cmake does not set the composite ITK_VERSION variable.
if(NOT ITK_VERSION)
  set(
    ITK_VERSION
    "${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR}.${ITK_VERSION_PATCH}"
  )
endif()

# When ITK is consumed via FetchContent, CMake generates a stub itk-config.cmake
# in CMAKE_FIND_PACKAGE_REDIRECTS_DIR that includes ITKExtra.cmake (OPTIONAL).
# Write that file now so all subsequent find_package(ITK) calls — including those
# made internally by Elastix's CMakeLists.txt and from ElastixConfig.cmake —
# load the real ITKConfig.cmake and have all version variables available.
# Also overwrite the auto-generated itk-config-version.cmake so that calls with
# an EXACT version requirement (e.g. find_package(ITK "6.0.0" EXACT REQUIRED))
# succeed with the real version rather than the stub's version-agnostic logic.
if(DEFINED CMAKE_FIND_PACKAGE_REDIRECTS_DIR AND ITK_DIR)
  file(
    WRITE
    "${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/ITKExtra.cmake"
    "# Written by SimpleITK's sitkITKFetchContent.cmake.\n"
    "# Provides ITK version variables and the full ITK config to all\n"
    "# find_package(ITK) calls redirected here by FetchContent.\n"
    "include(\"${ITK_DIR}/ITKConfig.cmake\")\n"
    "if(NOT ITK_VERSION)\n"
    "  set(ITK_VERSION \"${ITK_VERSION}\")\n"
    "endif()\n"
  )
  file(
    WRITE
    "${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/itk-config-version.cmake"
    "# Written by SimpleITK's sitkITKFetchContent.cmake.\n"
    "set(PACKAGE_VERSION \"${ITK_VERSION}\")\n"
    "if(PACKAGE_FIND_VERSION VERSION_EQUAL PACKAGE_VERSION)\n"
    "  set(PACKAGE_VERSION_EXACT TRUE)\n"
    "endif()\n"
    "if(NOT PACKAGE_FIND_VERSION VERSION_GREATER PACKAGE_VERSION)\n"
    "  set(PACKAGE_VERSION_COMPATIBLE TRUE)\n"
    "endif()\n"
  )
endif()

# These ITK option conflict with SimpleITK.
# Allow a user's cache variable to be respected.
unset(BUILD_TESTING)
unset(BUILD_EXAMPLES)
