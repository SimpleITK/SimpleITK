
# remove me
set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include(${ITK_USE_FILE})

# Find tests generated in the binary directory
# To add a new file, just add it to this list.  Any GoogleTests inside will be automatically
# added to ctest.
set ( TestSource
  ImageTests.cxx
  CommonTests.cxx
  RegistrationTests.cxx
  sitkImageIOTests.cxx
  TypeListsTests.cxx
  sitkBasicFiltersTests.cxx
  LabelStatisticsTest.cxx
  sitkOperatorTests.cxx
  sitkExceptionsTests.cxx
  sitkTransformTests.cxx
  itkHashImageFilterTest.cxx
  ImportImageTest.cxx
  CXXTests.cxx
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

# HACK This needs to be set commonly between here and Wrapping.

# virtualenv places the python executable in different
# locations. Also note than on windows installations where python is
# installed only for a single user the may be a missing dll issue.
if( WIN32 )
  set( PYTHON_EXECUTABLE ${PythonVirtualenvHome}/Scripts/python )
else( )
  set( PYTHON_EXECUTABLE ${PythonVirtualenvHome}/bin/python )
endif()



#
# Glob for necessary template files up front, before the foreach loop over
# the filters:
#
file ( GLOB CXX_TEMPLATE_FILES "*Template*.cxx.in" )

if ( WRAP_LUA )
  file ( GLOB LUA_TEMPLATE_FILES "*Template*.lua.in" )
endif()

if ( WRAP_PYTHON )
  file ( GLOB PYTHON_TEMPLATE_FILES "*Template*py.in" )
endif()

if ( WRAP_TCL )
  file ( GLOB TCL_TEMPLATE_FILES "*Template*.tcl.in" )
endif()

if ( WRAP_R )
  file ( GLOB R_TEMPLATE_FILES "*Template*.R.in" )
endif()

if ( WRAP_RUBY )
  file ( GLOB RUBY_TEMPLATE_FILES "*Template*rb.in" )
endif()

if ( WRAP_JAVA )
  file ( GLOB JAVA_TEMPLATE_FILES "*Template*.java.in" )
endif()

if ( WRAP_CSHARP )
  file( GLOB CSHARP_TEMPLATE_FILES "*Template*.cs.in" )
endif()


#
# Generate code for the tests in different languages
#
foreach ( FILTERNAME ${GENERATED_FILTER_LIST} )

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
  set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "BasicFilters.${FILTERNAME}:BasicFilters.${FILTERNAME}_*" )
  set ( GENERATED_TEST_SOURCE ${GENERATED_TEST_SOURCE} ${OUTPUT_TEST_FILENAME})

  if ( WRAP_LUA )
    set(OUTPUT_TEST_FILENAME "${SimpleITK_BINARY_DIR}/Testing/Unit/LuaTests/${FILTERNAME}Test.lua")
    add_custom_command (
      OUTPUT "${OUTPUT_TEST_FILENAME}"
      COMMAND ${CMAKE_COMMAND} -E remove -f "${OUTPUT_TEST_FILENAME}"
      COMMAND lua ${template_expansion_script} test ${filter_json_file} ${SimpleITK_SOURCE_DIR}/Testing/Unit/Lua ${template_include_dir} TestTemplate.lua.in "${OUTPUT_TEST_FILENAME}"
      DEPENDS ${filter_json_file} ${LUA_TEMPLATE_FILES}
      )
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Lua.${FILTERNAME}")
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
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Python.${FILTERNAME}")
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
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Tcl.${FILTERNAME}")
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
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "R.${FILTERNAME}")
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
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Ruby.${FILTERNAME}")
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
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "Java.${FILTERNAME}")
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
    set ( GENERATED_TEST_LIST ${GENERATED_TEST_LIST} "CSharp.${FILTERNAME}")
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

add_executable(SimpleITKUnitTestDriver
  SimpleITKUnitTestDriver.cxx ${TestSource} ImageCompare.cxx
  ${GENERATED_TEST_SOURCE}
)
target_link_libraries ( SimpleITKUnitTestDriver gtest ${SimpleITK_LIBRARIES} )

add_executable(sitkShowTest
  sitkShowTest.cxx
  )
target_link_libraries ( sitkShowTest ${SimpleITK_LIBRARIES} )

add_executable( sitkSystemInformationTest
  sitkSystemInformationTest.cxx )
target_link_libraries( sitkSystemInformationTest
  ${SimpleITK_LIBRARIES} )
add_test( NAME sitkSystemInformaionTest COMMAND sitkSystemInformationTest ${CMAKE_BINARY_DIR} )


# Add all the tests by parsing the source code
# This macro searches for GoogleTest macros and adds them as test automatically
macro(ADD_GOOGLE_TESTS target)
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
  list ( REMOVE_DUPLICATES AllTestsHits )
  # Add all the remaining tests to CTest's test list
  foreach(hit ${AllTestsHits})
    # Take the first item in gtest list as the name
    string( REGEX MATCH "[^:]+" name ${hit} )
    #message ( STATUS "Adding test ${name} as ${target} --gtest_filter=${hit}" )
    add_test(NAME ${name} COMMAND ${target} --gtest_filter=${hit})
  endforeach()
endmacro()

# Here we add all the tests
add_google_tests(SimpleITKUnitTestDriver ${TestSource})


#######################################################
#
# Tests which use the itkTestDriver
#
#######################################################

set( ITK_TEST_DRIVER  "itkTestDriver" )


if ( WRAP_CSHARP )

  #
  # This is a macro which compiles the program and set up the
  # enviroment for executing CSharp examples and tests.
  #
  macro(add_csharp_test name csharp_file)

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

  endmacro()


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

endif ( WRAP_CSHARP )


if ( WRAP_JAVA )

  #
  # This is a macro which set up the enviroment for executing JAVA examples and tests
  #
  macro(add_java_test name java_file)

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

    add_test(NAME Java.${name}
      COMMAND "${ITK_TEST_DRIVER}"
      "${Java_JAVA_EXECUTABLE}"
      "-Djava.library.path=${_JAVA_LIBRARY_PATH}"
      "-classpath" "${_JAVA_CLASSPATH}"
      "${_java_class}"
      ${ARGN}
      )
  endmacro()


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
  # This is a macro which set up the enviroment for executing python examples and tests
  #
  macro(add_python_test name)

    set(command "${PYTHON_EXECUTABLE}")

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
  endmacro()

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
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Examples.FFTConvolution.nrrd" )

  #
  # Python Tests
  #
  add_python_test( Test.ImageTest
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/ImageTest.py" )

  add_python_test( Test.IOTest
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/IOTest.py"
    "${TEST_HARNESS_TEMP_DIRECTORY}")

  # Numpy test.
  add_python_test( Test.Numpy
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/NumpyArrayConversionTest.py" )

endif( WRAP_PYTHON )


if ( WRAP_LUA )

  #
  # This is a macro which set up the enviroment for executing lua examples and tests
  #
  macro(add_lua_test name)

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
  endmacro()


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
  # This is a macro which set up the enviroment for executing ruby examples and tests
  #
  macro(add_ruby_test name)

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
  endmacro()


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
  # This is a macro which set up the enviroment for executing TCL examples and tests
  #
  macro(add_tcl_test name)


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
  endmacro()


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
  # This is a macro which set up the enviroment for executing R examples and tests
  #
  macro(add_r_test name)

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
  endmacro()


  #
  # R tests and Examples
  #
  add_r_test( Arithmetic
    "--file=${SimpleITK_SOURCE_DIR}/Testing/Unit/RArithmeticTest.R"
     )

endif ( WRAP_R )
