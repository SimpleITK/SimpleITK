project ( SimpleITK )
cmake_minimum_required ( VERSION 2.8 )

find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
endif()


# Put all files in a bin directory to keep things tidy.
set(EXECUTABLE_OUTPUT_PATH ${SimpleITK_BINARY_DIR}/bin)


set ( SimpleITK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Source)
set ( SimpleITK_LIBRARIES SimpleITK ${ITK_LIBRARIES} )


#DEBUG
include_directories ( ${CMAKE_CURRENT_SOURCE_DIR}/Source ${CMAKE_CURRENT_SOURCE_DIR}/Source/Ancillary )
add_executable(DebugTest DebugTest.cxx)
target_link_libraries(DebugTest ${ITK_LIBRARIES})
#subdirs ( Source Wrapping Examples )
#
#
## Options for testing
#option ( USE_TESTING "Build testing" ON )
#option ( RUN_LONG_TESTS "Run long tests.  Some tests have been identified as long running, should these be run?" OFF )
#
#if ( USE_TESTING )
#  enable_testing()
#  subdirs ( Testing )
#  include(CTest)
#  mark_as_advanced(RUN_LONG_TESTS)
#endif()

