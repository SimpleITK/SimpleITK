include(sitkExternalData)
include(CMakeParseArguments)

set(SimpleITK_DATA_ROOT ${SimpleITK_SOURCE_DIR}/Testing/Data)

#-----------------------------------------------------------------------------
# SimpleITK wrapper for add_test that adds support for external data,
# and post comparison processes.
#
# ARGUMENTS
#
# [ADD_TEST ARGUMENTS...]
#   The first arguments are passed to cmake's add_test function with
#   support for the DATA{} references to external data
# TRANSFORM_COMPARE <test transform> <baseline displacement> [tolerance]
function(sitk_add_test)
  set(options "")
  set(oneValueArgs "")
  set(multiValueArgs TRANSFORM_COMPARE)
  cmake_parse_arguments("_" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

  # Add test with data in the SimpleITKData group.
  ExternalData_add_test(SimpleITKData ${__UNPARSED_ARGUMENTS})

  if("NAME" STREQUAL "${ARGV0}")
    set(_iat_testname ${ARGV1})
  else()
    set(_iat_testname ${ARGV0})
  endif()

  if ( NOT "${__TRANSFORM_COMPARE}" STREQUAL "" )
    ExternalData_add_test(SimpleITKData NAME "${_iat_testname}Compare"
      COMMAND
        $<TARGET_FILE:sitkTransformCompareDriver>
        ${__TRANSFORM_COMPARE}
      )

    set_property(TEST "${_iat_testname}Compare" APPEND PROPERTY DEPENDS ${_iat_testname})
  endif()
endfunction()


#
# This is a function which set up the environment for executing python examples and tests
#
function(sitk_add_python_test name)

  if ( NOT WRAP_PYTHON )
    return()
  endif()

  set(command "${VIRTUAL_PYTHON_EXECUTABLE}")

  # add extra command which may be needed on some systems
  if(CMAKE_OSX_ARCHITECTURES)
    list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
    set(command arch -${test_arch} ${command})
  endif()

  sitk_add_test(NAME Python.${name}
    COMMAND "${ITK_TEST_DRIVER}"
    --add-before-env SITK_NOSHOW "YES"
    ${command}
    ${ARGN}
    )
endfunction()


#
# This is a function which set up the enviroment for executing lua examples and tests
#
function(sitk_add_lua_test name)

  if ( NOT WRAP_LUA )
    return()
  endif()

  set(command "$<TARGET_FILE:SimpleITKLua>")

  # add extra command which may be needed on some systems
  if(CMAKE_OSX_ARCHITECTURES)
    list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
    set(command arch -${test_arch} ${command})
  endif()

  sitk_add_test(NAME Lua.${name}
    COMMAND "${ITK_TEST_DRIVER}"
    ${command}
    ${ARGN}
    )
endfunction()


#
# This is a function which set up the enviroment for executing ruby examples and tests
#
function(sitk_add_ruby_test name)

  if ( NOT WRAP_RUBY )
    return()
  endif()

  set(command "${RUBY_EXECUTABLE}")

  # add extra command which may be needed on some systems
  if(CMAKE_OSX_ARCHITECTURES)
    list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
    set(command arch -${test_arch} ${command})
  endif()

  sitk_add_test(NAME Ruby.${name}
    COMMAND "${ITK_TEST_DRIVER}"
    --add-before-env RUBYLIB "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIGURATION>"
    --add-before-env RUBYLIB "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
    ${command}
    ${ARGN}
    )
endfunction()


#
# This is a function which set up the enviroment for executing TCL examples and tests
#
function(sitk_add_tcl_test name)

  if ( NOT WRAP_TCL )
    return()
  endif()

  set(command "$<TARGET_FILE:SimpleITKTclsh>")

  # add extra command which may be needed on some systems
  if(CMAKE_OSX_ARCHITECTURES)
    list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
    set(command arch -${test_arch} ${command})
  endif()

  sitk_add_test(NAME Tcl.${name}
    COMMAND "${ITK_TEST_DRIVER}"
    ${command}
    ${ARGN}
    )
endfunction()


#
# This is a function which set up the enviroment for executing JAVA examples and tests
#
function(sitk_add_java_test name java_file)

  if ( NOT WRAP_JAVA )
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
    COMMENT "Building ${CMAKE_CURRENT_BINARY_DIR}/${_java_file_class}"
    )
  add_custom_target( ${_java_class}Java ALL
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${_java_file_class}"
    SOURCES ${java_file})

  sitk_add_test(NAME Java.${name}
    COMMAND "${ITK_TEST_DRIVER}"
    "${Java_JAVA_EXECUTABLE}"
    "-Djava.library.path=${_JAVA_LIBRARY_PATH}"
    "-classpath" "${_JAVA_CLASSPATH}"
    "${_java_class}"
    ${ARGN}
    )
endfunction()


#
# This is a function which set up the enviroment for executing R examples and tests
#
function(sitk_add_r_test name)

  if ( NOT WRAP_R )
    return()
  endif()

  set(command "${R_COMMAND}")

  # add extra command which may be needed on some systems
  if(CMAKE_OSX_ARCHITECTURES)
    list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
    set(command arch -${test_arch} ${command})
  endif()

  sitk_add_test(NAME R.${name}
    COMMAND "${ITK_TEST_DRIVER}"
    ${command}
    ${ARGN}
    )

  set_property(TEST R.${name}
    PROPERTY ENVIRONMENT R_LIBS=${SimpleITK_BINARY_DIR}/Wrapping/RLib/
    )
endfunction()


#
# This is a function which compiles the program and set up the
# enviroment for executing CSharp examples and tests.
#
function(sitk_add_csharp_test name csharp_file)

  if ( NOT WRAP_CSHARP )
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
    sitk_add_test(NAME CSharp.${name}
      COMMAND "${ITK_TEST_DRIVER}"
      "${CSHARP_INTERPRETER}"
      "${CSHARP_BINARY_DIRECTORY}/${CSHARP_EXECUTABLE}.exe"
      ${ARGN}
      )
  else ()
    sitk_add_test(NAME CSharp.${name}
      COMMAND "${ITK_TEST_DRIVER}"
      "${CSHARP_BINARY_DIRECTORY}/${CSHARP_EXECUTABLE}.exe"
      ${ARGN}
      )
  endif()

endfunction()
