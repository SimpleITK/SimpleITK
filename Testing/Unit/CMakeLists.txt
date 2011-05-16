
# Find tests generated in the binary directory
# To add a new file, just add it to this list.  Any GoogleTests inside will be automatically
# added to ctest.
set ( TestSource
  ImageTests.cxx
  CommonTests.cxx
  RegistrationTests.cxx
  IOTests.cxx
  TypeListsTests.cxx
  BasicFiltersTests.cxx
  LabelStatisticsTest.cxx
  sitkExceptionsTests.cxx
  itkHashImageFilterTest.cxx
  CXXTests.cxx
  PythonTests.cxx
  RubyTests.cxx
  LuaTests.cxx
  TclTests.cxx
  JavaTests.cxx
  )

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/PythonTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/LuaTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/TclTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RubyTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/JavaTests/org/itk/simple/testing)

#
# Generate code for the tests in different languages
#
foreach ( FILTERNAME ${GENERATED_FILTER_LIST} )

  # Set up some convenience variables
  set (filter_json_file ${SimpleITK_SOURCE_DIR}/Code/BasicFilters/json/${FILTERNAME}.json)
  set (template_expansion_script ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua)
  set (template_include_dir ${SimpleITK_SOURCE_DIR}/TemplateComponents)

  file ( GLOB CXX_TEMPLATE_FILES "*Template*.cxx.in" )
  set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/sitk${FILTERNAME}ImageFilterTest.cxx")
  add_custom_command (
    OUTPUT  ${OUTPUT_TEST_FILENAME}
    COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/sitk ${template_include_dir} TestTemplate.cxx.in "${OUTPUT_TEST_FILENAME}"
    DEPENDS ${filter_json_file} ${CXX_TEMPLATE_FILES}
    )
  set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "BasicFilters.${FILTERNAME}")
  set ( GENERATED_TEST_SOURCE ${GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})

  if ( WRAP_LUA )
    file ( GLOB LUA_TEMPLATE_FILES "*Template*.lua.in" )
    set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/LuaTests/${FILTERNAME}ImageFilterTest.lua")
    add_custom_command (
      OUTPUT "${OUTPUT_TEST_FILENAME}"
      COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Lua ${template_include_dir} TestTemplate.lua.in "${OUTPUT_TEST_FILENAME}"
      DEPENDS ${filter_json_file} ${LUA_TEMPLATE_FILES}
      )
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Lua.${FILTERNAME}")
    set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
  endif()

  if ( WRAP_PYTHON )
    file ( GLOB PYTHON_TEMPLATE_FILES "*Template*py.in" )
    set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/PythonTests/${FILTERNAME}ImageFilterTest.py")
    add_custom_command (
      OUTPUT  "${OUTPUT_TEST_FILENAME}"
      COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Python ${template_include_dir} TestTemplate.py.in "${OUTPUT_TEST_FILENAME}"
      DEPENDS ${filter_json_file} ${PYTHON_TEMPLATE_FILES}
      )
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Python.${FILTERNAME}")
    set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
  endif()

  if ( WRAP_TCL )
    file ( GLOB TCL_TEMPLATE_FILES "*Template*.tcl.in" )
    set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/TclTests/${FILTERNAME}ImageFilterTest.tcl")
    add_custom_command (
      OUTPUT  "${OUTPUT_TEST_FILENAME}"
      COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Tcl ${template_include_dir} TestTemplate.tcl.in "${OUTPUT_TEST_FILENAME}"
      DEPENDS ${filter_json_file} ${TCL_TEMPLATE_FILES}
      )
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Tcl.${FILTERNAME}")
    set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
  endif()

  if ( WRAP_R )
    file ( GLOB R_TEMPLATE_FILES "*Template*.R.in" )
    set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/RTests/${FILTERNAME}ImageFilterTest.R")
    add_custom_command (
      OUTPUT  "${OUTPUT_TEST_FILENAME}"
      COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/R ${template_include_dir} TestTemplate.R.in "${OUTPUT_TEST_FILENAME}"
      DEPENDS ${filter_json_file} ${R_TEMPLATE_FILES}
      )
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "R.${FILTERNAME}")
    set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
  endif()

  if ( WRAP_RUBY )
    file ( GLOB RUBY_TEMPLATE_FILES "*Template*rb.in" )
    set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/RubyTests/${FILTERNAME}ImageFilterTest.rb")
    add_custom_command (
      OUTPUT  "${OUTPUT_TEST_FILENAME}"
      COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Ruby ${template_include_dir} TestTemplate.rb.in "${OUTPUT_TEST_FILENAME}"
      DEPENDS ${filter_json_file} ${RUBY_TEMPLATE_FILES}
      )
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Ruby.${FILTERNAME}")
    set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
  endif()

  # Java Tests
  if ( WRAP_JAVA )
    file ( GLOB JAVA_TEMPLATE_FILES "*Template*.java.in" )
    set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/JavaTests/org/itk/simple/testing/${FILTERNAME}ImageFilterTest.java")
    add_custom_command (
      OUTPUT  "${OUTPUT_TEST_FILENAME}"
      COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Java ${template_include_dir} TestTemplate.java.in "${OUTPUT_TEST_FILENAME}"
      COMMAND ${Java_JAVAC_EXECUTABLE} -classpath ${SimpleITK_BINARY_DIR}/Wrapping/org.itk.simple.jar ${SimpleITK_BINARY_DIR}/Testing/Unit/JavaTests/org/itk/simple/testing/${FILTERNAME}ImageFilterTest.java
      DEPENDS ${filter_json_file} ${JAVA_TEMPLATE_FILES} SimpleITKJava
      )
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Java.${FILTERNAME}")
    set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
  endif()

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
set(TEST_HARNESS_EXECUTABLE_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/" )

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

add_custom_target(WrappedGeneratedTests ALL
  DEPENDS ${WRAPPED_GENERATED_TEST_SOURCE}
)

# Add org.itk.simple.jar dependency if necessary
if( WRAP_JAVA )
  add_dependencies(WrappedGeneratedTests org_itk_simple_jar)
endif()

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
      string(REGEX REPLACE ".*\\(( *[A-Za-z_0-9]+)[, ]*([A-Za-z_0-9]+) *\\).*" "\\1.\\2" test_name ${hit})
      set ( AllTestsHits ${AllTestsHits} ${test_name} )
    endforeach()
    foreach(hit ${LongTests})
      string(REGEX REPLACE ".*\\(( *[A-Za-z_0-9]+)[, ]*([A-Za-z_0-9]+) *\\).*" "\\1.\\2" test_name ${hit})
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
add_google_tests ( ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SimpleITKUnitTestDriver ${TestSource})
