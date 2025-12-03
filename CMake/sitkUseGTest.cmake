#
# sitkUseGTest
#
#  This file uses FetchContent to download and configbuild Google Test
#  for SimpleITK.
#
# This file provides the "GTest::gtest" target.
#
# To specify a local Google Test installation set the following cache variable:
#
# ``GOOGLETEST_ROOT``
#   The root directory of the Google Test installation. If not specified, Google Test will be fetched automatically.

# find_package() uses upper-case <PACKAGENAME>_ROOT variables.
if(POLICY "CMP0144")
  cmake_policy(SET "CMP0144" NEW)
endif()

include(GoogleTest)
include(FetchContent)

if(TARGET GTest::main AND TARGET GTest::gtest)
  message(STATUS "Google Test targets already exist.")
  return()
endif()

# Fetch GTest using FetchContent
set(
  GOOGLETEST_GIT_REPOSITORY
  "https://github.com/google/googletest.git"
  CACHE STRING
  "Google Test repository"
)
set(GOOGLETEST_VERSION "1.17.0" CACHE STRING "Google Test version tag")
mark_as_advanced(
  GOOGLETEST_GIT_REPOSITORY
  GOOGLETEST_VERSION
)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY "${GOOGLETEST_GIT_REPOSITORY}"
  GIT_TAG "v${GOOGLETEST_VERSION}"
  EXCLUDE_FROM_ALL
  FIND_PACKAGE_ARGS
    "${GOOGLETEST_VERSION}"
    NAMES
    GTest
    COMPONENTS
    GTest::gtest
)

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE INTERNAL "" FORCE)
set(BUILD_GMOCK OFF CACHE INTERNAL "")
set(BUILD_GTEST ON CACHE INTERNAL "")

set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(googletest)

# Check if FetchContent used find_package() or fetched from source
FetchContent_GetProperties(googletest)
if(googletest_SOURCE_DIR)
  message(
    STATUS
    "Google Test fetched from ${GOOGLETEST_GIT_REPOSITORY} and built from source"
  )
elseif(TARGET GTest::gtest)
  message(STATUS "Google Test found and using existing local package")
else()
  message(STATUS "Google Test configured")
endif()
