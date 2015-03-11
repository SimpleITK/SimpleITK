# remove me
set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include(${ITK_USE_FILE})

set ( SimpleITKUnitTestSourceBase
  SimpleITKTestHarness.cxx
  sitkImageCompare.cxx
  sitkTransformCompare.cxx
)
add_library ( SimpleITKUnitTestBase STATIC ${SimpleITKUnitTestSourceBase} )
add_dependencies( SimpleITKUnitTestBase BasicFiltersSourceCode )
target_link_libraries( SimpleITKUnitTestBase gtest ${SimpleITK_LIBRARIES} )

add_executable( sitkTransformCompareDriver sitkTransformCompareDriver.cxx )
target_link_libraries( sitkTransformCompareDriver gtest SimpleITKUnitTestBase ${SimpleITK_LIBRARIES} )
# Find tests generated in the binary directory
# To add a new file, just add it to this list.  Any GoogleTests inside will be automatically
# added to ctest.
set ( SimpleITKUnitTestSource
  sitkImageTests.cxx
  sitkCommonTests.cxx
  sitkImageRegistrationMethodTests.cxx
  sitkImageIOTests.cxx
  sitkTypeListsTests.cxx
  sitkBasicFiltersTests.cxx
  sitkLabelStatisticsTest.cxx
  sitkTransformToDisplacementFieldFilterTest.cxx
  sitkOperatorTests.cxx
  sitkExceptionsTests.cxx
  sitkTransformTests.cxx
  sitkImportImageTest.cxx
  itkHashImageFilterTest.cxx
  itkSliceImageFilterTest.cxx
  )

if ( SITK_4D_IMAGES )
  list(APPEND SimpleITKUnitTestSource sitkImage4DTests.cxx )
endif()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/PythonTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/LuaTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/TclTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RubyTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/JavaTests/org/itk/simple/testing)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CSharpTests)

# Adjust Python to run in the virtualenv
set( PythonVirtualenvHome ${SimpleITK_BINARY_DIR}/Testing/Installation/PythonVirtualenv )


add_executable(SimpleITKUnitTestDriver0 SimpleITKUnitTestDriver.cxx ${SimpleITKUnitTestSource})
target_link_libraries ( SimpleITKUnitTestDriver0 gtest SimpleITKUnitTestBase ${SimpleITK_LIBRARIES} )

#
# Glob for necessary template files up front, before the foreach loop over
# the filters:
#
file ( GLOB CXX_TEMPLATE_FILES "*Template*.cxx.in" )
file ( GLOB LUA_TEMPLATE_FILES "*Template*.lua.in" )
file ( GLOB PYTHON_TEMPLATE_FILES "*Template*py.in" )
file ( GLOB TCL_TEMPLATE_FILES "*Template*.tcl.in" )
file ( GLOB R_TEMPLATE_FILES "*Template*.R.in" )
file ( GLOB RUBY_TEMPLATE_FILES "*Template*rb.in" )
file ( GLOB JAVA_TEMPLATE_FILES "*Template*.java.in" )
file ( GLOB CSHARP_TEMPLATE_FILES "*Template*.cs.in" )


#
# Generate code for the tests in different languages
#
# Break all these source files into a bunch of separate executables
# base on every n files in the list.
set ( _stride 50 )
set ( _exec_i 1 ) # exec 0 is the manual tests
set ( _i 0 )
foreach ( FILTERNAME ${GENERATED_FILTER_LIST} )

  if ( NOT _i LESS _stride )
    add_executable(SimpleITKUnitTestDriver${_exec_i} SimpleITKUnitTestDriver.cxx ${GENERATED_TEST_SOURCE})
    target_link_libraries ( SimpleITKUnitTestDriver${_exec_i} gtest SimpleITKUnitTestBase ${SimpleITK_LIBRARIES} )
    math(EXPR _exec_i "${_exec_i}+1")
    set(GENERATED_TEST_SOURCE "")
    set ( _i 0 )
  endif ()

  # Set up some convenience variables
  set (filter_json_file ${SimpleITK_SOURCE_DIR}/Code/BasicFilters/json/${FILTERNAME}.json)
  set (template_expansion_script ${SimpleITK_SOURCE_DIR}/Utilities/ExpandTemplate.lua)
  set (template_include_dir
  ${SimpleITK_SOURCE_DIR}/TemplateComponents)


  ######
  # Figure out which template file gets used
  ######

  # Get the line from the json file that indicates the correct template
  file(STRINGS ${filter_json_file} template_line REGEX ".*template_test_filename.*")

  # strip down to what in between the "" after the :
  string(REGEX MATCH ":.*\"([^\"]+)\"" _out "${template_line}")
  set(template_name "${CMAKE_MATCH_1}" )

  if (template_name)
    set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/sitk${FILTERNAME}Test.cxx")
    add_custom_command (
      OUTPUT  ${OUTPUT_TEST_FILENAME}
      COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
      COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/sitk ${template_include_dir} TestTemplate.cxx.in "${OUTPUT_TEST_FILENAME}"
      DEPENDS ${filter_json_file} ${CXX_TEMPLATE_FILES}
      )
    add_test( NAME BasicFilters.${FILTERNAME} COMMAND SimpleITKUnitTestDriver${_exec_i} --gtest_filter=BasicFilters.${FILTERNAME}:BasicFilters.${FILTERNAME}_* )
    set ( GENERATED_TEST_SOURCE ${GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})

    if ( WRAP_LUA )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/LuaTests/${FILTERNAME}Test.lua")
      add_custom_command (
        OUTPUT "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Lua ${template_include_dir} TestTemplate.lua.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${LUA_TEMPLATE_FILES}
        )
      add_test( NAME Lua.${FILTERNAME} COMMAND SimpleITKUnitTestDriver${_exec_i} --gtest_filter=Lua.${FILTERNAME} )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    if ( WRAP_PYTHON )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/PythonTests/${FILTERNAME}Test.py")
      add_custom_command (
        OUTPUT  "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Python ${template_include_dir} TestTemplate.py.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${PYTHON_TEMPLATE_FILES}
        )
      add_test( NAME Python.${FILTERNAME} COMMAND SimpleITKUnitTestDriver${_exec_i} --gtest_filter=Python.${FILTERNAME} )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    if ( WRAP_TCL )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/TclTests/${FILTERNAME}Test.tcl")
      add_custom_command (
        OUTPUT  "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Tcl ${template_include_dir} TestTemplate.tcl.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${TCL_TEMPLATE_FILES}
        )
      add_test( NAME Tcl.${FILTERNAME} COMMAND SimpleITKUnitTestDriver${_exec_i} --gtest_filter=Tcl.${FILTERNAME} )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    if ( WRAP_R )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/RTests/${FILTERNAME}Test.R")
      add_custom_command (
        OUTPUT  "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/R ${template_include_dir} TestTemplate.R.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${R_TEMPLATE_FILES}
        )
      add_test( NAME R.${FILTERNAME} COMMAND SimpleITKUnitTestDriver${_exec_i} --gtest_filter=R.${FILTERNAME} )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    if ( WRAP_RUBY )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/RubyTests/${FILTERNAME}Test.rb")
      add_custom_command (
        OUTPUT  "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Ruby ${template_include_dir} TestTemplate.rb.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${RUBY_TEMPLATE_FILES}
        )
      add_test( NAME Ruby.${FILTERNAME} COMMAND SimpleITKUnitTestDriver${_exec_i} --gtest_filter=Ruby.${FILTERNAME} )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    # Java Tests
    if ( WRAP_JAVA )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/JavaTests/org/itk/simple/testing/${FILTERNAME}Test.java")
      add_custom_command (
        OUTPUT  "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Java ${template_include_dir} TestTemplate.java.in "${OUTPUT_TEST_FILENAME}"
        COMMAND ${Java_JAVAC_EXECUTABLE} -classpath ${SimpleITK_BINARY_DIR}/Wrapping/${JAR_FILE} ${SimpleITK_BINARY_DIR}/Testing/Unit/JavaTests/org/itk/simple/testing/${FILTERNAME}Test.java
        DEPENDS ${filter_json_file} ${JAVA_TEMPLATE_FILES} ${SWIG_MODULE_SimpleITKJava_TARGET_NAME}
        )
      add_test( NAME Java.${FILTERNAME} COMMAND SimpleITKUnitTestDriver${_exec_i} --gtest_filter=Java.${FILTERNAME} )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    # C# Tests
    if ( WRAP_CSHARP )
      set( OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/CSharpTests/Test${FILTERNAME}.cs" )
      if ( WIN32 )
        string( REPLACE "/" "\\" OUTPUT_TEST_FILENAME_SAFE ${OUTPUT_TEST_FILENAME} )
      else ( UNIX )
        string( REPLACE "\\" "/" OUTPUT_TEST_FILENAME_SAFE ${OUTPUT_TEST_FILENAME} )
      endif ( WIN32 )
      add_custom_command (
        OUTPUT "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/CSharp ${template_include_dir} TestTemplate.cs.in "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CSHARP_COMPILER}
          /t:exe /platform:${CSHARP_PLATFORM}
          /lib:${CSHARP_BINARY_DIRECTORY} /reference:System.dll /reference:SimpleITKCSharpManaged.dll
          /out:${CSHARP_BINARY_DIRECTORY}/Test${FILTERNAME}.exe ${OUTPUT_TEST_FILENAME_SAFE}
        DEPENDS ${filter_json_file} ${CSHARP_TEMPLATE_FILES}
        )
      add_test( NAME CSharp.${FILTERNAME} COMMAND SimpleITKUnitTestDriver${_exec_i} --gtest_filter=CSharp.${FILTERNAME} )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()
  endif() # if template_name
  math(EXPR _i "${_i}+1")

endforeach()

add_executable(SimpleITKUnitTestDriver${_exec_i} SimpleITKUnitTestDriver.cxx ${GENERATED_TEST_SOURCE})
target_link_libraries ( SimpleITKUnitTestDriver${_exec_i} gtest SimpleITKUnitTestBase ${SimpleITK_LIBRARIES} )

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
set(TEST_HARNESS_DATA_DIRECTORY ${SimpleITK_BINARY_DIR}/ExternalData/Testing/Data)

# Set some variables
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleITKTestHarnessPaths.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKTestHarnessPaths.h ESCAPE_QUOTES)

# Build Google Testing
set ( GTestSource
  GoogleTest/gtest/gtest-all.cc
)
include_directories ( GoogleTest ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_library(gtest STATIC ${GTestSource})
if (CMAKE_USE_PTHREADS_INIT)
  target_link_libraries(gtest ${CMAKE_THREAD_LIBS_INIT})
endif()

include_directories ( ${SimpleITK_INCLUDE_DIRS} )

add_custom_target(WrappedGeneratedTests ALL
  DEPENDS ${WRAPPED_GENERATED_TEST_SOURCE}
)

# Add org.itk.simple.jar dependency if necessary
if( WRAP_JAVA )
  add_dependencies(WrappedGeneratedTests org_itk_simple_jar)
endif()

# Add C# dependency if necessary
if( WRAP_CSHARP )
  add_dependencies(WrappedGeneratedTests SimpleITKCSharpManaged)
endif()

add_executable(sitkShowTest sitkShowTest.cxx )
target_link_libraries ( sitkShowTest ${SimpleITK_LIBRARIES} )

add_executable( sitkSystemInformationTest sitkSystemInformationTest.cxx )
target_link_libraries( sitkSystemInformationTest ${SimpleITK_LIBRARIES} )
add_test( NAME sitkSystemInformaionTest COMMAND sitkSystemInformationTest ${CMAKE_BINARY_DIR} )


# Add all the tests by parsing the source code
# This macro searches for GoogleTest macros and adds them as test automatically
macro(ADD_GOOGLE_TESTS target)
  # Add the generated tests
  set ( AllTestsHits "" )
  set ( LongTestsHits "" )

  foreach ( source ${ARGN} )
    file(READ "${source}" contents)

    # Find all test and long test lists
    string(REGEX MATCHALL "TEST_?F?\\(([A-Za-z_0-9 ,_]+)\\) /\\* Long \\*/" LongTests ${contents})
    string(REGEX MATCHALL "TEST_?F?\\(([A-Za-z_0-9 ,_]+)\\)" AllTests ${contents})

    # Convert the C++ code into a short test name
    foreach(hit ${AllTests})
      string(REGEX REPLACE ".*\\( *( *[A-Za-z_0-9]+)[, ]*([A-Za-z_0-9]+) *\\).*" "\\1.\\2" test_name ${hit})
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
  list ( REMOVE_DUPLICATES AllTestsHits )
  # Add all the remaining tests to CTest's test list
  foreach(hit ${AllTestsHits})
    # Take the first item in gtest list as the name
    string( REGEX MATCH "[^:]+" name ${hit} )
    add_test( NAME ${name} COMMAND ${target} --gtest_filter=${hit} )
  endforeach()
endmacro()

add_google_tests(SimpleITKUnitTestDriver0 ${SimpleITKUnitTestSource})


#######################################################
#
# Tests which use the itkTestDriver
#
#######################################################

set( ITK_TEST_DRIVER  "itkTestDriver" )

include(${CMAKE_CURRENT_SOURCE_DIR}/AdditionalTests.cmake)
