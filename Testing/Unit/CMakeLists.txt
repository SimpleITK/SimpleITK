
# Find tests generated in the binary directory
message("GENERATED TESTS DIR ${CMAKE_CURRENT_BINARY_DIR}")
message("GENERATED TESTS ${GENERATED_FILTER_LIST}")

# To add a new file, just add it to this list.  Any GoogleTests inside will be automatically
# added to ctest.
set ( TestSource
  ImageTests.cxx
  CommonTests.cxx
  IOTests.cxx
  TypeListsTests.cxx
  BasicFiltersTests.cxx
  sitkExceptionsTests.cxx
  sitkIndexTests.cxx
  CXXTests.cxx
  )

if ( WRAP_LUA )
  set ( TestSource ${TestSource} LuaTests.cxx )
  add_definitions ( -DWRAP_LUA )
endif()

if ( WRAP_PYTHON )
  find_package ( PythonInterp REQUIRED )
  set ( TestSource ${TestSource} PythonTests.cxx )
  add_definitions ( -DWRAP_PYTHON )
endif()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/PythonTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/LuaTests)

# template type variables
set ( image_filter_template 0 )
set ( region_growing_image_filter_template 1 )

macro( expand_test_template FILENAME TEMPLATE_TYPE )
  
  # Set common variables
  set ( expand_template_script ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua )
  set ( output_cpp "${SimpleITK_BINARY_DIR}/Testing/Unit/sitk${FILENAME}ImageFilterTest.cxx" )
  set ( output_lua "${SimpleITK_BINARY_DIR}/Testing/Unit/LuaTests/${FILENAME}ImageFilterTest.lua" )
  set ( output_py "${SimpleITK_BINARY_DIR}/Testing/Unit/PythonTests/${FILENAME}ImageFilterTest.py" )

  # Use the ImageFilterTemplate if specified
  if ( ${TEMPLATE_TYPE} EQUAL ${image_filter_template} )
    set ( input_json_file ${SimpleITK_SOURCE_DIR}/Code/BasicFilters/${FILENAME}.json )
    set ( template_file_cpp
      ${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkImageFilterTestTemplate.cxx.in )
    set ( template_file_lua
      ${SimpleITK_SOURCE_DIR}/Testing/Unit/LuaImageFilterTestTemplate.lua.in )
    set ( template_file_py
      ${SimpleITK_SOURCE_DIR}/Testing/Unit/PythonImageFilterTestTemplate.py.in )

  # Use the RegionGrowingImageFilterTemplate if specified
  elseif ( ${TEMPLATE_TYPE} EQUAL ${region_growing_image_filter_template} )
    set ( input_json_file
      ${SimpleITK_SOURCE_DIR}/Code/BasicFilters/${FILENAME}_RegionGrowing.json )
    set ( template_file_cpp
      ${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkRegionGrowingImageFilterTestTemplate.cxx.in )
    set ( template_file_lua
      ${SimpleITK_SOURCE_DIR}/Testing/Unit/LuaRegionGrowingImageFilterTestTemplate.lua.in )
    set ( template_file_py
      ${SimpleITK_SOURCE_DIR}/Testing/Unit/PythonRegionGrowingImageFilterTestTemplate.py.in )
  endif()

    add_custom_command (
    OUTPUT ${output_cpp} ${output_lua} ${output_py}
    COMMAND lua ${expand_template_script} ${input_json_file} ${template_file_cpp} ${output_cpp}
    COMMAND lua ${expand_template_script} ${input_json_file} ${template_file_lua} ${output_lua}
    COMMAND lua ${expand_template_script} ${input_json_file} ${template_file_py} ${output_py}
    DEPENDS ${input_json_file} ${template_file_cxx} ${template_file_lua} ${template_file_py} ${template_file_cpp} ${template_file_lua} ${template_file_py}
    )
  set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "BasicFilters.${FILENAME}")
  if ( WRAP_LUA )
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Lua.${FILENAME}")
  endif()
  if ( WRAP_PYTHON )
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Python.${FILENAME}")
  endif()
  set ( GENERATED_TEST_SOURCE ${GENERATED_TEST_SOURCE} ${output_cpp} )

endmacro()

# Generate tests for ImageFilter templated filters
foreach ( FILENAME ${IMAGE_FILTER_LIST} )
  expand_test_template( ${FILENAME} ${image_filter_template} )
endforeach()

# Generate tests for RegionGrowingImageFilter templated filters
foreach ( FILENAME ${REGION_GROWING_FILTER_LIST} )
  expand_test_template( ${FILENAME} ${region_growing_image_filter_template} )
endforeach()


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
set(TEST_HARNESS_TEMP_DIRECTORY ${SimpleITK_BINARY_DIR}/Testing/Temporary)
set(TEST_HARNESS_DATA_DIRECTORY ${SimpleITK_SOURCE_DIR}/Testing/Data)
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
  SimpleITKUnitTestDriver.cxx ${TestSource} ImageCompare.cxx 
  ${GENERATED_TEST_SOURCE}
)
target_link_libraries ( SimpleITKUnitTestDriver ${ITK_LIBRARIES} ${SimpleITK_LIBRARIES} )

# Add all the tests by parsing the source code
# This macro searches for GoogleTest macros and adds them as test automatically
macro(ADD_GOOGLE_TESTS executable)
  # Add the generated tests
  set ( AllTestsHits ${GENERATED_TEST_LIST} )
  set ( LongTestsHits "" )

  foreach ( source ${ARGN} )
    file(READ "${source}" contents)

    # Find all test and long test lists
    string(REGEX MATCHALL "TEST_?F?\\(([A-Za-z_0-9 ,_]+)\\) /\\* Long \\*/" LongTests ${contents})
    string(REGEX MATCHALL "TEST_?F?\\(([A-Za-z_0-9 ,_]+)\\)" AllTests ${contents})

    # Convert the C++ code into a short test name
    foreach(hit ${AllTests})
      string(REGEX REPLACE ".*\\(([A-Za-z_0-9]+)[, ]*([A-Za-z_0-9]+)\\).*" "\\1.\\2" test_name ${hit})
      set ( AllTestsHits ${AllTestsHits} ${test_name} )
    endforeach()
    foreach(hit ${LongTests})
      string(REGEX REPLACE ".*\\(([A-Za-z_0-9]+)[, ]*([A-Za-z_0-9]+)\\).*" "\\1.\\2" test_name ${hit})
      set ( LongTestsHits ${LongTestsHits} ${test_name} )
    endforeach()
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
    # message ( STATUS "Adding test ${executable} ${hit} ${TEST_HARNESS_DATA_DIRECTORY} ${TEST_HARNESS_TEMP_DIRECTORY}" )
    add_test(${hit} ${executable} --gtest_filter=${hit})
  endforeach()
endmacro()



# Here we add all the tests
add_google_tests ( ${EXECUTABLE_OUTPUT_PATH}/SimpleITKUnitTestDriver ${TestSource})
