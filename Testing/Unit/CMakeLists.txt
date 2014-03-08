# remove me
set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include(${ITK_USE_FILE})

set ( SimpleITKUnitTestSourceBase
  SimpleITKTestHarness.cxx
  sitkImageCompare.cxx
)
add_library ( SimpleITKUnitTestBase STATIC ${SimpleITKUnitTestSourceBase} )
add_dependencies( SimpleITKUnitTestBase  BasicFiltersSourceCode )
# Find tests generated in the binary directory
# To add a new file, just add it to this list.  Any GoogleTests inside will be automatically
# added to ctest.
set ( SimpleITKUnitTestSource
  sitkImageTests.cxx
  sitkCommonTests.cxx
  sitkRegistrationTests.cxx
  sitkImageIOTests.cxx
  sitkTypeListsTests.cxx
  sitkBasicFiltersTests.cxx
  sitkLabelStatisticsTest.cxx
  sitkOperatorTests.cxx
  sitkExceptionsTests.cxx
  sitkTransformTests.cxx
  sitkImportImageTest.cxx
  itkHashImageFilterTest.cxx
  itkSliceImageFilterTest.cxx
  )

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
  set (template_include_dir ${SimpleITK_SOURCE_DIR}/TemplateComponents)

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

#
# CXX Examples
#
if ( ${BUILD_EXAMPLES} )
  add_test(NAME CXX.Example.SimpleGaussian
    COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.SimpleGaussian.nrrd"
    5ef06ed0d5d8952c770348699b70f23e
    $<TARGET_FILE:SimpleGaussian>
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    2.0
    "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.SimpleGaussian.nrrd"
    )

  add_test(NAME CXX.Example.SimpleGaussianFunctional
    COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.SimpleGaussianFunctional.nrrd"
    5ef06ed0d5d8952c770348699b70f23e
    $<TARGET_FILE:SimpleGaussianFunctional>
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    2.0
    "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.SimpleGaussianFunctional.nrrd"
    )

   add_test(NAME CXX.Example.FilterProgressReporting
    COMMAND "${ITK_TEST_DRIVER}"
    $<TARGET_FILE:FilterProgressReporting>
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    2.0
    "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.FilterProgressReporting.nrrd"
    )
  set_tests_properties( CXX.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )


  add_test(NAME  CXX.Example.Segmentation.ConnectedThresholdImageFilter1
    COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationConnectedThreshold1.png"
      "d4ff9c512f9c18a84729677de800db0d"
    $<TARGET_FILE:ConnectedThresholdImageFilter>
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySlice.png"
    "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationConnectedThreshold1.png"
    150 180
    60 116
    )

  add_test(NAME  CXX.Example.Segmentation.ConnectedThresholdImageFilter2
    COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationConnectedThreshold2.png"
      "a9695df04cde5b9c5481d8c253a5b3aa"
    $<TARGET_FILE:ConnectedThresholdImageFilter>
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySlice.png"
    "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationConnectedThreshold2.png"
    210 250
    81 112
    )

  add_test( NAME CXX.Example.Segmentation.NeighborhoodConnectedImageFilter1
    COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationNeighborhoodConnected1.png"
      "311d9d4b492e1ea625e3b0b295814dce"
    $<TARGET_FILE:NeighborhoodConnectedImageFilter>
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySlice.png"
    "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationNeighborhoodConnected1.png"
    150 180
    60 116
    )

endif()

if ( WRAP_CSHARP )

  #
  # This is a function which compiles the program and set up the
  # enviroment for executing CSharp examples and tests.
  #
  function(add_csharp_test name csharp_file)

    if ( NOT ${BUILD_EXAMPLES} AND "${name}" MATCHES "^Example." )
      return()
    endif()

    # the root is with out extension or path
    get_filename_component( CSHARP_EXECUTABLE ${csharp_file} NAME_WE )

    # make sure the executable has CSharp in it
    if ( NOT CSHARP_EXECUTABLE MATCHES "CSharp" )
      set( CSHARP_EXECUTABLE "CSharp${CSHARP_EXECUTABLE}" )
    endif()

    # add the target to compile the test
    csharp_add_executable(
        "${CSHARP_EXECUTABLE}"
        SimpleITKCSharpManaged.dll
        ${csharp_file}
    )

    # because each executable is it's own target we actually don't
    # need to make a target depend on this list
    list( APPEND compiled_csharp_tests "${CSHARP_BINARY_DIRECTORY}/${CSHARP_EXECUTABLE}.exe")

    add_dependencies("${CSHARP_EXECUTABLE}" SimpleITKCSharpManaged)

    # the interpreter is set to "" when none is needed
    if( CSHARP_INTERPRETER )
      add_test(NAME CSharp.${name}
        COMMAND "${ITK_TEST_DRIVER}"
        "${CSHARP_INTERPRETER}"
        "${CSHARP_BINARY_DIRECTORY}/${CSHARP_EXECUTABLE}.exe"
        ${ARGN}
        )
    else ()
      add_test(NAME CSharp.${name}
        COMMAND "${ITK_TEST_DRIVER}"
        "${CSHARP_BINARY_DIRECTORY}/${CSHARP_EXECUTABLE}.exe"
        ${ARGN}
        )
    endif()

  endfunction()

  #
  # CSharp Examples
  #
  add_csharp_test( Example.SimpleGaussian
    "${SimpleITK_SOURCE_DIR}/Examples/SimpleGaussian.cs"
    --compare
      "${TEST_HARNESS_TEMP_DIRECTORY}/CSharp.SimpleGaussian.nrrd"
      "${TEST_HARNESS_DATA_DIRECTORY}/Baseline/Example_SimpleGaussian_2.0.nrrd"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/CSharp.SimpleGaussian.nrrd" )

  add_csharp_test( Example.ImageGetBuffer
    "${SimpleITK_SOURCE_DIR}/Examples/ImageGetBuffer.cs"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd")
  set_tests_properties( CSharp.Example.ImageGetBuffer
    PROPERTIES PASS_REGULAR_EXPRESSION "total: 1009713" )

  add_csharp_test( Example.FilterProgressReporting
    "${SimpleITK_SOURCE_DIR}/Examples/FilterProgressReporting.cs"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/CSharp.FilterProgressReporting.nrrd"
    )
  set_tests_properties( CSharp.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )

  #
  # CSharp Tests
  #
  add_csharp_test( Test.ImageTest
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/CSharpImageTest.cs" )

endif ( WRAP_CSHARP )


if ( WRAP_JAVA )

  #
  # This is a function which set up the enviroment for executing JAVA examples and tests
  #
  function(add_java_test name java_file)

    if ( NOT ${BUILD_EXAMPLES} AND "${name}" MATCHES "^Example." )
      return()
    endif()

    # the root is with out extension or path, it is also assumed to the the name of the main class
    get_filename_component( _java_class ${java_file} NAME_WE )
    set( _java_file_class "${_java_class}.class" )

    if(WIN32)
      set( _JAVA_LIBRARY_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIGURATION>" )
      # Note: on windows this is a semi-colon separated list
      set( _JAVA_CLASSPATH "${SimpleITK_BINARY_DIR}/Wrapping/${JAR_FILE};${CMAKE_CURRENT_BINARY_DIR}" )
    else(WIN32)
      set( _JAVA_LIBRARY_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" )
      set( _JAVA_CLASSPATH "${SimpleITK_BINARY_DIR}/Wrapping/${JAR_FILE}:${CMAKE_CURRENT_BINARY_DIR}" )
    endif(WIN32)

    add_custom_command(
      OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_java_file_class}"
      COMMAND "${Java_JAVAC_EXECUTABLE}"
      ARGS -classpath "${_JAVA_CLASSPATH}"
      -d "${CMAKE_CURRENT_BINARY_DIR}"
      "${java_file}"
      DEPENDS ${java_file} ${SWIG_MODULE_SimpleITKJava_TARGET_NAME} org_itk_simple_jar
      )

    list( APPEND compiled_java_tests "${CMAKE_CURRENT_BINARY_DIR}/${_java_file_class}")

    # set in parent scope to accumulate list during function execution
    set( compiled_java_tests ${compiled_java_tests} PARENT_SCOPE)

    add_test(NAME Java.${name}
      COMMAND "${ITK_TEST_DRIVER}"
      "${Java_JAVA_EXECUTABLE}"
      "-Djava.library.path=${_JAVA_LIBRARY_PATH}"
      "-classpath" "${_JAVA_CLASSPATH}"
      "${_java_class}"
      ${ARGN}
      )
  endfunction()

  add_java_test( ProcessObjectTest
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkProcessObjectTest.java" )

  #
  # JAVA Examples
  #
  add_java_test( Example.SimpleGaussian
    "${SimpleITK_SOURCE_DIR}/Examples/SimpleGaussian.java"
    --compare
      "${TEST_HARNESS_TEMP_DIRECTORY}/Java.SimpleGaussian.nrrd"
      "${TEST_HARNESS_DATA_DIRECTORY}/Baseline/Example_SimpleGaussian_2.0.nrrd"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Java.SimpleGaussian.nrrd" )

  add_java_test( Example.FilterProgressReporting
    "${SimpleITK_SOURCE_DIR}/Examples/FilterProgressReporting.java"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Java.FilterProgressReporting.nrrd"
    )
  set_tests_properties( Java.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )

# This test currently does not compile or work
#
#  add_java_test( Example.ImageConnection
#    "${SimpleITK_SOURCE_DIR}/Examples/ImageConnection.java" )


  # after all add_java_tests are called, form a target so all the code
  # is built
  add_custom_target( CompileJavaTests ALL DEPENDS ${compiled_java_tests} )

endif ( WRAP_JAVA )


if ( WRAP_PYTHON )

  #
  # This is a function which set up the enviroment for executing python examples and tests
  #
  function(add_python_test name)

    if ( NOT ${BUILD_EXAMPLES} AND "${name}" MATCHES "^Example." )
      return()
    endif()

    set(command "${VIRTUAL_PYTHON_EXECUTABLE}")

    # add extra command which may be needed on some systems
    if(CMAKE_OSX_ARCHITECTURES)
      list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
      set(command arch -${test_arch} ${command})
    endif()

    add_test(NAME Python.${name}
      COMMAND "${ITK_TEST_DRIVER}"
      --add-before-env SITK_NOSHOW "YES"
      ${command}
      ${ARGN}
      )
  endfunction()

  #
  # Python Examples
  #
  add_python_test( Example.SimpleGaussian
    "${SimpleITK_SOURCE_DIR}/Examples/SimpleGaussian.py"
    --compare
      "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd"
      "${TEST_HARNESS_DATA_DIRECTORY}/Baseline/Example_SimpleGaussian_2.0.nrrd"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd" )

  add_python_test( Example.SimpleGaussianProcedural
    "${SimpleITK_SOURCE_DIR}/Examples/SimpleGaussianProcedural.py"
    --compare
      "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussianProcedural.nrrd"
      "${TEST_HARNESS_DATA_DIRECTORY}/Baseline/Example_SimpleGaussian_2.0.nrrd"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussianProcedural.nrrd" )

  add_python_test( Example.ImageCreateAndSet
    "${SimpleITK_SOURCE_DIR}/Examples/ImageCreateAndSet.py" )

  add_python_test( Example.CannyEdge
    "${SimpleITK_SOURCE_DIR}/Examples/CannyEdge.py"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd" )

  add_python_test( Example.ExtractSlice
    "${SimpleITK_SOURCE_DIR}/Examples/ExtractSlice.py"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd"
    "30"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.ExtractSlice.nrrd")

  add_python_test( Example.BoarderSegmentation
    "${SimpleITK_SOURCE_DIR}/Examples/BoarderSegmentation.py"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.BoarderSegmentation.nrrd"
    "5000"
    "150" )

 add_python_test( Example.N4BiasFieldCorrection
    "${SimpleITK_SOURCE_DIR}/Examples/N4BiasFieldCorrection.py"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Example.N4BiasFieldCorrection.nrrd"
    "1" )

  add_python_test( Example.ReadAndShow
    "${SimpleITK_SOURCE_DIR}/Examples/ReadAndShow.py"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/VM1111Shrink-RGB.png" )

  add_python_test( Example.GeodesicActiceContourSegmentation
    "${SimpleITK_SOURCE_DIR}/Examples/GeodesicActiceContourSegmentation.py"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/cthead1.png"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Example.GeodesicActiceContourSegmentation.nrrd"
    .3 10 .9 50 55
    )

  add_python_test( Example.FFTConvolution
    "${SimpleITK_SOURCE_DIR}/Examples/FFTConvolution.py"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/cthead1-Float.mha"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/Gaussian_1.5.nrrd"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Examples.FFTConvolution.nrrd"
    )

  add_python_test( Example.FilterProgressReporting
    "${SimpleITK_SOURCE_DIR}/Examples/FilterProgressReporting.py"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonFilterProgressReporting.nrrd"
    )
  set_tests_properties( Python.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )

  add_python_test( Example.Segmentation.ConnectedThresholdImageFilter1
    "${SimpleITK_SOURCE_DIR}/Examples/Segmentation/ConnectedThresholdImageFilter.py"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold1.png"
      "d4ff9c512f9c18a84729677de800db0d"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySlice.png"
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold1.png"
    150 180
    60 116
    )

  add_python_test( Example.Segmentation.ConnectedThresholdImageFilter2
    "${SimpleITK_SOURCE_DIR}/Examples/Segmentation/ConnectedThresholdImageFilter.py"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold2.png"
      "a9695df04cde5b9c5481d8c253a5b3aa"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySlice.png"
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold2.png"
    210 250
    81 112
    )

  add_python_test( Example.Segmentation.NeighborhoodConnectedImageFilter1
    "${SimpleITK_SOURCE_DIR}/Examples/Segmentation/NeighborhoodConnectedImageFilter.py"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationNeighborhoodConnected1.png"
      "311d9d4b492e1ea625e3b0b295814dce"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySlice.png"
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationNeighborhoodConnected1.png"
    150 180
    60 116
    )


  #
  # Python Tests
  #
  add_python_test( Test.ImageTests
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkImageTests.py" )
  add_python_test( Test.ImageIndexing
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/ImageIndexingTest.py" )

  add_python_test( Test.IOTest
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/IOTest.py"
    "${TEST_HARNESS_TEMP_DIRECTORY}")

  # Numpy test.
  add_python_test( Test.Numpy
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkNumpyArrayConversionTest.py"
  )

 add_python_test( Test.ProcessObject
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkProcessObjectTest.py"
  )



endif( WRAP_PYTHON )


if ( WRAP_LUA )

  #
  # This is a function which set up the enviroment for executing lua examples and tests
  #
  function(add_lua_test name)

    if ( NOT ${BUILD_EXAMPLES} AND "${name}" MATCHES "^Example." )
      return()
    endif()

    set(command "$<TARGET_FILE:SimpleITKLua>")

    # add extra command which may be needed on some systems
    if(CMAKE_OSX_ARCHITECTURES)
      list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
      set(command arch -${test_arch} ${command})
    endif()

    add_test(NAME Lua.${name}
      COMMAND "${ITK_TEST_DRIVER}"
      ${command}
      ${ARGN}
      )
  endfunction()


  #
  # Lua Examples
  #
  add_lua_test( Example.SimpleGaussian
    "${SimpleITK_SOURCE_DIR}/Examples/SimpleGaussian.lua"
    --compare
      "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleGaussian.nrrd"
      "${TEST_HARNESS_DATA_DIRECTORY}/Baseline/Example_SimpleGaussian_2.0.nrrd"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleGaussian.nrrd" )

endif ( WRAP_LUA )

if ( WRAP_RUBY )

  #
  # This is a function which set up the enviroment for executing ruby examples and tests
  #
  function(add_ruby_test name)

    if ( NOT ${BUILD_EXAMPLES} AND "${name}" MATCHES "^Example." )
      return()
    endif()

    set(command "${RUBY_EXECUTABLE}")

    # add extra command which may be needed on some systems
    if(CMAKE_OSX_ARCHITECTURES)
      list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
      set(command arch -${test_arch} ${command})
    endif()

    add_test(NAME Ruby.${name}
      COMMAND "${ITK_TEST_DRIVER}"
      --add-before-env RUBYLIB "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIGURATION>"
      --add-before-env RUBYLIB "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
      ${command}
      ${ARGN}
      )
  endfunction()


  #
  # Ruby Examples
  #
  add_ruby_test( Example.SimpleGaussian
    "${SimpleITK_SOURCE_DIR}/Examples/SimpleGaussian.rb"
    --compare
      "${TEST_HARNESS_TEMP_DIRECTORY}/Ruby.SimpleGaussian.nrrd"
      "${TEST_HARNESS_DATA_DIRECTORY}/Baseline/Example_SimpleGaussian_2.0.nrrd"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Ruby.SimpleGaussian.nrrd" )

endif ( WRAP_RUBY )


if ( WRAP_TCL )

  #
  # This is a function which set up the enviroment for executing TCL examples and tests
  #
  function(add_tcl_test name)

    if ( NOT ${BUILD_EXAMPLES} AND "${name}" MATCHES "^Example." )
      return()
    endif()


    set(command "$<TARGET_FILE:SimpleITKTclsh>")

    # add extra command which may be needed on some systems
    if(CMAKE_OSX_ARCHITECTURES)
      list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
      set(command arch -${test_arch} ${command})
    endif()

    add_test(NAME Tcl.${name}
      COMMAND "${ITK_TEST_DRIVER}"
      ${command}
      ${ARGN}
      )
  endfunction()


  #
  # TCL Examples
  #
  add_tcl_test( Example.SimpleGaussian
    "${SimpleITK_SOURCE_DIR}/Examples/SimpleGaussian.tcl"
    --compare
      "${TEST_HARNESS_TEMP_DIRECTORY}/Tcl.SimpleGaussian.nrrd"
      "${TEST_HARNESS_DATA_DIRECTORY}/Baseline/Example_SimpleGaussian_2.0.nrrd"
    "${TEST_HARNESS_DATA_DIRECTORY}/Input/RA-Short.nrrd"
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Tcl.SimpleGaussian.nrrd" )

endif ( WRAP_TCL )

if ( WRAP_R )

  #
  # This is a function which set up the enviroment for executing R examples and tests
  #
  function(add_r_test name)

    if ( NOT ${BUILD_EXAMPLES} AND "${name}" MATCHES "^Example." )
      return()
    endif()

    set(command "${R_COMMAND}")

    # add extra command which may be needed on some systems
    if(CMAKE_OSX_ARCHITECTURES)
      list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
      set(command arch -${test_arch} ${command})
    endif()

    add_test(NAME R.${name}
      COMMAND
      ${command}
      ${ARGN}
      )

    set_property(TEST R.${name}
                 PROPERTY ENVIRONMENT R_LIBS=${SimpleITK_BINARY_DIR}/Wrapping/RLib/
                 )
  endfunction()


  #
  # R tests and Examples
  #
  add_r_test( Arithmetic
    "--file=${SimpleITK_SOURCE_DIR}/Testing/Unit/RArithmeticTest.R"
     )

endif ( WRAP_R )
