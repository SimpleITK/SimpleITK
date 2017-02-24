# remove me
set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include(${ITK_USE_FILE})

include(sitkUseGTest)

set ( SimpleITKUnitTestSourceBase
  SimpleITKTestHarness.cxx
  sitkImageCompare.cxx
  sitkTransformCompare.cxx
)
add_library ( SimpleITKUnitTestBase STATIC ${SimpleITKUnitTestSourceBase} )
add_dependencies( SimpleITKUnitTestBase BasicFiltersSourceCode  )
target_link_libraries( SimpleITKUnitTestBase GTest::GTest ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} )
target_include_directories( SimpleITKUnitTestBase
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
target_compile_options( SimpleITKUnitTestBase
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )


add_executable( sitkCompareDriver sitkCompareDriver.cxx )
target_link_libraries( sitkCompareDriver SimpleITKUnitTestBase ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES})
target_compile_options( sitkCompareDriver
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )

sitk_install_exported_target(sitkCompareDriver)

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

if ( SimpleITK_4D_IMAGES )
  list(APPEND SimpleITKUnitTestSource sitkImage4DTests.cxx )
endif()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CTest)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/PythonTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/LuaTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/TclTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RubyTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/JavaTests)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CSharpTests)

# Test data directory
set(TEST_HARNESS_TEMP_DIRECTORY ${SimpleITK_BINARY_DIR}/Testing/Temporary)
set(TEST_HARNESS_DATA_DIRECTORY ${SimpleITK_BINARY_DIR}/ExternalData/Testing/Data)

set( ITK_TEST_DRIVER  "$<TARGET_FILE:itkTestDriver>" )

# Adjust Python to run in the virtualenv
set( PythonVirtualenvHome  ${SimpleITK_BINARY_DIR}/Testing/Installation/PythonVirtualenv )


add_executable(SimpleITKUnitTestDriver0 SimpleITKUnitTestDriver.cxx ${SimpleITKUnitTestSource})
target_link_libraries ( SimpleITKUnitTestDriver0 GTest::GTest SimpleITKUnitTestBase ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} )
target_compile_options( SimpleITKUnitTestDriver0
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )


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
message( STATUS "Generating tests...")
set ( _stride 50 )
set ( _exec_i 1 ) # exec 0 is the manual tests
set ( _i 0 )
foreach ( FILTERNAME ${GENERATED_FILTER_LIST} )

  if ( NOT _i LESS _stride )
    add_executable(SimpleITKUnitTestDriver${_exec_i} SimpleITKUnitTestDriver.cxx ${GENERATED_TEST_SOURCE})
    target_link_libraries ( SimpleITKUnitTestDriver${_exec_i} GTest::GTest SimpleITKUnitTestBase ${SimpleITK_LIBRARIES} )
    target_compile_options( SimpleITKUnitTestDriver${_exec_i}
      PRIVATE
        ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )

    math(EXPR _exec_i "${_exec_i}+1")
    set(GENERATED_TEST_SOURCE "")
    set ( _i 0 )
  endif ()

  # Set up some convenience variables
  set (filter_json_file ${SimpleITK_SOURCE_DIR}/Code/BasicFilters/json/${FILTERNAME}.json)
  set (template_expansion_script ${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/ExpandTemplate.lua)
  set (template_include_dir
  ${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/Components)


  ######
  # Figure out which template file gets used
  ######

  # Get the line from the json file that indicates the correct template
  file(STRINGS ${filter_json_file} template_line REGEX ".*template_test_filename.*")

  # strip down to what in between the "" after the :
  string(REGEX MATCH ":.*\"([^\"]+)\"" _out "${template_line}")
  set(template_name "${CMAKE_MATCH_1}" )

  if (template_name)
    set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/CTest/${FILTERNAME}.cmake")
    file(REMOVE "${OUTPUT_TEST_FILENAME}")
    set(cmd ${SimpleITK_LUA_EXECUTABLE} ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/ ${template_include_dir} CTestTemplate.cmake.in "${OUTPUT_TEST_FILENAME}")
    execute_process(
      COMMAND ${cmd}
      RESULT_VARIABLE failed
      ERROR_VARIABLE error
      )
    if ( failed )
      string (REPLACE ";" " " cmd "${cmd}")
      message( FATAL_ERROR "Failed to generate \"${OUTPUT_TEST_FILENAME}\"\nCOMMAND: ${cmd} \n${error}" )
    endif()
    include("${OUTPUT_TEST_FILENAME}")

    set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/sitk${FILTERNAME}Test.cxx")
    add_custom_command (
      OUTPUT  ${OUTPUT_TEST_FILENAME}
      COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
      COMMAND ${SimpleITK_LUA_EXECUTABLE} ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/sitk ${template_include_dir} TestTemplate.cxx.in "${OUTPUT_TEST_FILENAME}"
      DEPENDS ${filter_json_file} ${CXX_TEMPLATE_FILES}
      )
    add_test( NAME BasicFilters.${FILTERNAME} COMMAND SimpleITKUnitTestDriver${_exec_i} --gtest_filter=BasicFilters.${FILTERNAME}:BasicFilters.${FILTERNAME}_* )
    set ( GENERATED_TEST_SOURCE ${GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})

    if ( WRAP_LUA )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/LuaTests/${FILTERNAME}Test.lua")
      add_custom_command (
        OUTPUT "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND ${SimpleITK_LUA_EXECUTABLE} ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Lua ${template_include_dir} TestTemplate.lua.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${LUA_TEMPLATE_FILES}
        )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    if ( WRAP_PYTHON )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/PythonTests/${FILTERNAME}Test.py")
      add_custom_command (
        OUTPUT  "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND ${SimpleITK_LUA_EXECUTABLE} ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Python ${template_include_dir} TestTemplate.py.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${PYTHON_TEMPLATE_FILES}
        )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    if ( WRAP_TCL )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/TclTests/${FILTERNAME}Test.tcl")
      add_custom_command (
        OUTPUT  "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND ${SimpleITK_LUA_EXECUTABLE} ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Tcl ${template_include_dir} TestTemplate.tcl.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${TCL_TEMPLATE_FILES}
        )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    if ( WRAP_R )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/RTests/${FILTERNAME}Test.R")
      add_custom_command (
        OUTPUT  "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND ${SimpleITK_LUA_EXECUTABLE} ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/R ${template_include_dir} TestTemplate.R.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${R_TEMPLATE_FILES}
        )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    if ( WRAP_RUBY )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/RubyTests/${FILTERNAME}Test.rb")
      add_custom_command (
        OUTPUT  "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND ${SimpleITK_LUA_EXECUTABLE} ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Ruby ${template_include_dir} TestTemplate.rb.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${RUBY_TEMPLATE_FILES}
        )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    # Java Tests
    if ( WRAP_JAVA )
      set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/JavaTests/${FILTERNAME}Test.java")
      add_custom_command (
        OUTPUT  "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND ${SimpleITK_LUA_EXECUTABLE} ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Java ${template_include_dir} TestTemplate.java.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${JAVA_TEMPLATE_FILES}  ${SWIG_MODULE_SimpleITKJava_TARGET_NAME}        )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()

    # C# Tests
    if ( WRAP_CSHARP )
      set( OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/CSharpTests/${FILTERNAME}Test.cs" )
      add_custom_command (
        OUTPUT "${OUTPUT_TEST_FILENAME}"
        COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
        COMMAND ${SimpleITK_LUA_EXECUTABLE} ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/CSharp ${template_include_dir} TestTemplate.cs.in "${OUTPUT_TEST_FILENAME}"
        DEPENDS ${filter_json_file} ${CSHARP_TEMPLATE_FILES}
        )
      set ( WRAPPED_GENERATED_TEST_SOURCE ${WRAPPED_GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})
    endif()
  endif() # if template_name
  math(EXPR _i "${_i}+1")

endforeach()

message( STATUS "Generating tests...Done")

add_executable(SimpleITKUnitTestDriver${_exec_i} SimpleITKUnitTestDriver.cxx ${GENERATED_TEST_SOURCE})
target_link_libraries ( SimpleITKUnitTestDriver${_exec_i} GTest::GTest SimpleITKUnitTestBase ${SimpleITK_LIBRARIES} )
target_compile_options( SimpleITKUnitTestDriver${_exec_i}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )

# Set some variables
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleITKTestHarnessPaths.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKTestHarnessPaths.h ESCAPE_QUOTES)

add_custom_target(WrappedGeneratedTests ALL
  DEPENDS ${WRAPPED_GENERATED_TEST_SOURCE}
)

if(MSVC_VERSION EQUAL 1700)
  # Tuples are limited by _VARIADIC_MAX in VS11. The variadic
  # templates are not deep enough by default. We are not currently
  # using the GTest features which require tuple, so just disable them
  # and hope that upstream premanetly addresses the problem, with out
  # required more CMake core for compiler issues.
  add_definitions(-DGTEST_HAS_TR1_TUPLE=0 )
endif()

add_executable(sitkShowTest sitkShowTest.cxx )
target_link_libraries ( sitkShowTest  GTest::GTest ${SimpleITK_LIBRARIES} SimpleITKUnitTestBase )
target_compile_options( sitkShowTest
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )


add_executable( sitkSystemInformationTest sitkSystemInformationTest.cxx )
target_link_libraries( sitkSystemInformationTest ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES})
add_test( NAME sitkSystemInformaionTest COMMAND sitkSystemInformationTest ${CMAKE_BINARY_DIR} )
target_compile_options( sitkSystemInformationTest
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )



gtest_add_tests(SimpleITKUnitTestDriver0 "" ${SimpleITKUnitTestSource})


#######################################################
#
# Tests which use the itkTestDriver
#
#######################################################


include(${CMAKE_CURRENT_SOURCE_DIR}/AdditionalTests.cmake)

