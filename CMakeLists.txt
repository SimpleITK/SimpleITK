project ( SimpleITK )
cmake_minimum_required ( VERSION 2.8 )

find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
endif()


# Put all files in a bin directory to keep things tidy.
set(EXECUTABLE_OUTPUT_PATH ${SimpleITK_BINARY_DIR}/bin)


set ( SimpleITK_INCLUDE_DIR 
      ${CMAKE_SOURCE_DIR}/Code/Common
      ${CMAKE_SOURCE_DIR}/Code/Common/Ancillary
      ${CMAKE_SOURCE_DIR}/Code/BasicFilters
      ${CMAKE_SOURCE_DIR}/Code/IO)

include_directories( ${SimpleITK_INCLUDE_DIR} )

set ( SimpleITK_LIBRARIES ${ITK_LIBRARIES} SimpleITKCommon SimpleITKIO SimpleITKBasicFilters)
subdirs ( Code Wrapping Examples )


# Options for testing
option ( USE_TESTING "Build testing" ON )
option ( RUN_LONG_TESTS "Run long tests.  Some tests have been identified as long running, should these be run?" OFF )

if ( USE_TESTING )
  enable_testing()
  subdirs ( Testing )
  include(CTest)
  mark_as_advanced(RUN_LONG_TESTS)
endif()

