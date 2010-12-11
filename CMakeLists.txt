project ( SimpleITK )
cmake_minimum_required ( VERSION 2.8 )

find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
endif()


# Put all files in a bin directory to keep things tidy.
# Output directories.
if(NOT LIBRARY_OUTPUT_PATH)
  set(LIBRARY_OUTPUT_PATH ${SimpleITK_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
endif()
if(NOT EXECUTABLE_OUTPUT_PATH)
  set(EXECUTABLE_OUTPUT_PATH ${SimpleITK_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")
endif()
mark_as_advanced(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

set ( SimpleITK_INCLUDE_DIR 
      ${CMAKE_SOURCE_DIR}/Code/Common
      ${CMAKE_SOURCE_DIR}/Code/Common/Ancillary
      ${CMAKE_SOURCE_DIR}/Code/BasicFilters
      ${CMAKE_SOURCE_DIR}/Code/IO
      ${CMAKE_BINARY_DIR}/Code/BasicFilters
      ${CMAKE_BINARY_DIR}
      )

include_directories( ${SimpleITK_INCLUDE_DIR} )

set ( SimpleITK_LIBRARIES ${ITK_LIBRARIES} SimpleITKCommon SimpleITKIO SimpleITKBasicFilters)

# Be sure to clear these each time
set ( GENERATED_TEST_LIST "" CACHE INTERNAL "" )
set ( GENERATED_FILTER_LIST "" CACHE INTERNAL "" )
set ( GENERATED_TEST_SOURCE_LIST "" CACHE INTERNAL "" )

# Setting this option will shorten compile times by reducing the
# amount of pixel types and generated code.
# NB: this option should _NOT_ be used for releases!
option ( SHORT_COMPILE "Skip compiling most of the generated code." OFF )
if ( SHORT_COMPILE )
  add_definitions ( -DSIMPLEITK_SHORT_COMPILE )
endif()
mark_as_advanced ( SHORT_COMPILE )

try_compile(SITK_SUPPORTS_STATIC_ASSERT
  ${SimpleITK_BINARY_DIR}/CMakeTmp
  ${SimpleITK_SOURCE_DIR}/CMake/static_assert.cxx
  OUTPUT_VARIABLE SITK_HAS_STATIC_ASSERT )

configure_file( ${SimpleITK_SOURCE_DIR}/sitkConfigure.h.in
  ${SimpleITK_BINARY_DIR}/sitkConfigure.h )

subdirs ( Utilities Code Wrapping Examples )

# Options for testing
option ( USE_TESTING "Build testing" ON )

if ( USE_TESTING )
  enable_testing()
  subdirs ( Testing )
  include(CTest)
  option ( RUN_LONG_TESTS "Run long tests.  Some tests have been identified as long running, should these be run?" OFF )
  mark_as_advanced(RUN_LONG_TESTS)
  set(BUILDNAME "${BUILDNAME}" CACHE STRING "Name of build on the dashboard")
endif()

