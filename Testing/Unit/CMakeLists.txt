
# An option to build/run the long tests
option ( RUN_LONG_TESTS "Run long tests.  Some tests have been identified as long running, should these be run?" OFF )

# Build Google Test
find_package(Threads)
if (CMAKE_USE_PTHREADS_INIT)  # The pthreads library is available.
  set(cxx_base_flags "${cxx_base_flags} -DGTEST_HAS_PTHREAD=1")
endif()

# The gtest include file directories.
SET(GTEST_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/GoogleTest" PARENT_SCOPE)

# The gtest library directories.
SET(GTEST_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)


# Build Google Testing
set ( GTestSource
  GoogleTest/gtest/gtest-all.cc
)
include_directories ( GoogleTest )

add_library(gtest ${GTestSource})
link_libraries(gtest)
if (CMAKE_USE_PTHREADS_INIT)
  target_link_libraries(gtest ${CMAKE_THREAD_LIBS_INIT})
endif()


set ( TestSource 
  SimpleITKTesting.cxx )

add_executable(itkUnitTestDriver 
  itkUnitTestDriver.cxx ${TestSource} )

# Add all the tests by parsing the source code
# This macro searches for GoogleTest macros and adds them as test automatically
macro(ADD_GOOGLE_TESTS executable)
  foreach ( source ${ARGN} )
    file(READ "${source}" contents)

    # Find all test and long test lists
    string(REGEX MATCHALL "TEST_?F?\\(([A-Za-z_0-9 ,]+)\\) /\\* Long \\*/" LongTests ${contents})
    string(REGEX MATCHALL "TEST_?F?\\(([A-Za-z_0-9 ,]+)\\)" AllTests ${contents})

    # Convert the C++ code into a short test name
    set ( AllTestsHits "" )
    foreach(hit ${AllTests})
      string(REGEX REPLACE ".*\\(([A-Za-z_0-9]+)[, ]*([A-Za-z_0-9]+)\\).*" "\\1.\\2" test_name ${hit})
      set ( AllTestsHits ${AllTestsHits} ${test_name} )
    endforeach()
    set ( LongTestsHits "" )
    foreach(hit ${LongTests})
      string(REGEX REPLACE ".*\\(([A-Za-z_0-9]+)[, ]*([A-Za-z_0-9]+)\\).*" "\\1.\\2" test_name ${hit})
      set ( LongTestsHits ${LongTestsHits} ${test_name} )
    endforeach()
    

    # If we are not running the long tests, remove them from the AllTests list
    if ( NOT RUN_LONG_TESTS )
      foreach ( test ${LongTestsHits} )
        list ( REMOVE_ITEM AllTestsHits ${test} )
      endforeach()
    endif ()

    list ( SORT AllTestsHits )
    # Add all the remaining tests to CTest's test list
    foreach(hit ${AllTestsHits})
      message ( ${executable} )
      add_test(${hit} ${executable} --gtest_filter=${hit})
    endforeach(hit)
  endforeach()
endmacro()



# Here we add all the tests
add_google_tests ( itkUnitTestDriver ${TestSource})
