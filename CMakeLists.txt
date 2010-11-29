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
      )

include_directories( ${SimpleITK_INCLUDE_DIR} )

set ( SimpleITK_LIBRARIES ${ITK_LIBRARIES} SimpleITKCommon SimpleITKIO SimpleITKBasicFilters)

# Be sure to clear these each time
set ( GENERATED_TEST_LIST "" CACHE INTERNAL "" )
set ( GENERATED_FILTER_LIST "" CACHE INTERNAL "" )
set ( GENERATED_TEST_SOURCE_LIST "" CACHE INTERNAL "" )

subdirs ( Utilities Code Wrapping Examples )

# Options for testing
option ( USE_TESTING "Build testing" ON )
option ( RUN_LONG_TESTS "Run long tests.  Some tests have been identified as long running, should these be run?" OFF )

if ( USE_TESTING )
  enable_testing()
  subdirs ( Testing )
  include(CTest)
  mark_as_advanced(RUN_LONG_TESTS)
endif()

