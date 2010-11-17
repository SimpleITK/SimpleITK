

# To add a new file, just add it to this list.  Any GoogleTests inside will be automatically
# added to ctest.
set ( TestSource
  ImageTests.cxx
  IOTests.cxx
  TypeListsTests.cxx
  CXXTests.cxx
  )

if ( WRAP_LUA )
  set ( TestSource ${TestSource} LuaTests.cxx )
endif()

# Build Google Test
find_package(Threads)
if (CMAKE_USE_PTHREADS_INIT)  # The pthreads library is available.
  set(cxx_base_flags "${cxx_base_flags} -DGTEST_HAS_PTHREAD=1")
endif()

# The gtest include file directories.
SET(GTEST_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/GoogleTest" PARENT_SCOPE)

# The gtest library directories.
SET(GTEST_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)

# Test data directory
FIND_PATH(ITK_DATA_ROOT ITKData.readme ${ITKTesting_SOURCE_DIR}/Data $ENV{ITK_DATA_ROOT})
set(TEST_HARNESS_TEMP_DIRECTORY ${SimpleITK_BINARY_DIR}/Testing/Temporary)
set(TEST_HARNESS_DATA_DIRECTORY ${ITK_DATA_ROOT})
set(TEST_HARNESS_EXECUTABLE_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/" )

# Set some variables
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleITKTestHarnessPaths.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKTestHarnessPaths.h ESCAPE_QUOTES)

# Build Google Testing
set ( GTestSource
  GoogleTest/gtest/gtest-all.cc
)
include_directories ( GoogleTest ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_library(gtest ${GTestSource})
link_libraries(gtest)
if (CMAKE_USE_PTHREADS_INIT)
  target_link_libraries(gtest ${CMAKE_THREAD_LIBS_INIT})
endif()


include_directories ( ${SimpleITK_INCLUDE_DIR} )
add_executable(SimpleITKUnitTestDriver 
  SimpleITKUnitTestDriver.cxx ${TestSource} )
target_link_libraries ( SimpleITKUnitTestDriver ${ITK_LIBRARIES} ${SimpleITK_LIBRARIES} )

# Add all the tests by parsing the source code
# This macro searches for GoogleTest macros and adds them as test automatically
macro(ADD_GOOGLE_TESTS executable)
  foreach ( source ${ARGN} )
    file(READ "${source}" contents)

    # Find all test and long test lists
    string(REGEX MATCHALL "TEST_?F?\\(([A-Za-z_0-9 ,_]+)\\) /\\* Long \\*/" LongTests ${contents})
    string(REGEX MATCHALL "TEST_?F?\\(([A-Za-z_0-9 ,_]+)\\)" AllTests ${contents})

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
      message ( STATUS "Adding test ${executable} ${hit} ${TEST_HARNESS_DATA_DIRECTORY} ${TEST_HARNESS_TEMP_DIRECTORY}" )
      add_test(${hit} ${executable} --gtest_filter=${hit} ${TEST_HARNESS_EXECUTABLE_DIRECTORY})
    endforeach(hit)
  endforeach()
endmacro()



# Here we add all the tests
add_google_tests ( ${EXECUTABLE_OUTPUT_PATH}/SimpleITKUnitTestDriver ${TestSource})
