#
# sitkUseGTest
#
#  This file is a wrapper of CMake's FindGTest and GoogleTest's
# recommendation to add the Google Test source tree as a subdirectory
# of the project.
#
# This file is designed to provide the "GTest::GTest" target.
#
# The follow cache variable is used to find GTest:
#
# ``GTEST_ROOT``
#   The root directory of the Google Test installation or a source
# directory.


set(GTEST_ROOT "" CACHE PATH "Path to the root of a binary gtest \
installation where GTEST_ROOT/include/gtest/gtest.h can be found OR \
path to a Google Test source tree.")

include(GoogleTest)

function(_sitk_gtest_use_gtest_source)

  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE INTERNAL "")

  # Avoid CMP0063 warning
  set(CMAKE_C_VISIBILITY_PRESET)
  set(CMAKE_CXX_VISIBILITY_PRESET)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN)

  set(BUILD_GTEST ON CACHE INTERNAL "" FORCE )
  set(BUILD_GMOCK OFF CACHE INTERNAL "" FORCE )


  # google test does not properly use pthreads on mingw
  if (MINGW)
    set(gtest_disable_pthreads  ON CACHE INTERNAL "" FORCE)
  endif()

  # Must build GTest as static since EXCLUDE_FROM_ALL, would exclude
  # needed GTest shared libraries from being installed.
  set(BUILD_SHARED_LIBS OFF)

  # Add googletest directly to our build but exclude from using it's
  # target's and installation unless referenced by other dependencies.
  add_subdirectory("${GTEST_ROOT}"
    "${CMAKE_CURRENT_BINARY_DIR}/GTest-build" EXCLUDE_FROM_ALL)

endfunction()

#


if( DEFINED GTEST_ROOT AND EXISTS "${GTEST_ROOT}/CMakeLists.txt")

  find_path(GTEST_INCLUDE_DIRS gtest/gtest.h
    PATHS "${GTEST_ROOT}"
    NO_DEFAULT_PATH)

  if(NOT "${GTEST_INCLUDE_DIRS}" STREQUAL "")

    message(STATUS "Adding Google Test source directory as subdirectory.")
    set(GTEST_FOUND 1)
    set(GTEST_LIBRARIES gtest)
    set(GTEST_MAIN_LIBRARIES gtest_main)
    set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

    _sitk_gtest_use_gtest_source()

    target_compile_features(${GTEST_LIBRARIES} PUBLIC cxx_std_11)
    target_compile_features(${GTEST_MAIN_LIBRARIES} PUBLIC cxx_std_11)

    add_library(GTest::GTest ALIAS ${GTEST_LIBRARIES})
    add_library(GTest::Main ALIAS ${GTEST_MAIN_LIBRARIES})

  else()
    message(WARNING "GTEST_ROOT appears to be a source directory \
    but \"gtest/gtest.h\"  can not be found in source directory: \
    ${GTEST_ROOT}")
  endif()

else()

  find_package( GTest REQUIRED )

endif ()
