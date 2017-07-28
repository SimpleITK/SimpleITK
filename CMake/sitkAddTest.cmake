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
  set(oneValueArgs "NAME")
  set(multiValueArgs COMMAND TRANSFORM_COMPARE)
  cmake_parse_arguments("_" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

  if ( NOT "${__TRANSFORM_COMPARE}" STREQUAL "" )
    set(COMPARE_ARGS ${COMPARE_ARGS} --compareTransform ${__TRANSFORM_COMPARE})
  endif()

  if (COMPARE_ARGS)
    set(__COMMAND $<TARGET_FILE:sitkCompareDriver> ${COMPARE_ARGS} -- ${__COMMAND})
  endif()

   # Add test with data in the SimpleITKData group.
  ExternalData_add_test(SimpleITKData NAME ${__NAME} COMMAND ${__COMMAND} ${__UNPARSED_ARGUMENTS})


endfunction()


#
# This is a function which set up the environment for executing python examples and tests
#
function(sitk_add_python_test name)

  if ( NOT WRAP_PYTHON )
    return()
  endif()

  set(command "${SimpleITK_PYTHON_TEST_EXECUTABLE}")

  # add extra command which may be needed on some systems
  if(CMAKE_OSX_ARCHITECTURES)
    list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
    set(command arch -${test_arch} ${command})
  endif()

  sitk_add_test(NAME Python.${name}
    COMMAND "${ITK_TEST_DRIVER}"
    ${command}
    ${ARGN}
    )
  set_property(TEST Python.${name}
      PROPERTY ENVIRONMENT SITK_NOSHOW=YES
      )
  if (NOT SimpleITK_PYTHON_USE_VIRTUALENV)
    set_property(TEST Python.${name}
      APPEND PROPERTY ENVIRONMENT PYTHONPATH=${SimpleITK_BINARY_DIR}/Wrapping/Python
      )
  endif()

endfunction()


#
# This is a function which set up the enviroment for executing lua examples and tests
#
function(sitk_add_lua_test name)

  if ( NOT WRAP_LUA )
    return()
  endif()

  set(command "${LUA_EXECUTABLE}")

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
  set_property(TEST Lua.${name}
    PROPERTY ENVIRONMENT LUA_CPATH=$<TARGET_FILE:SimpleITKLuaModule_LUA>
    )
  set_property(TEST Lua.${name}
    APPEND PROPERTY ENVIRONMENT SITK_NOSHOW=YES
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
    ${command}
    ${ARGN}
    )

  set_property(TEST Ruby.${name}
    PROPERTY ENVIRONMENT RUBYLIB=$<TARGET_FILE_DIR:simpleitk_RUBY>
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
  set( _class_path "${CMAKE_CURRENT_BINARY_DIR}" )
  set(JAR_FILE "simpleitk-${SimpleITK_VERSION}.jar")  # from target?

  set( _JAVA_LIBRARY_PATH  "$<TARGET_FILE_DIR:SimpleITKJava_JAVA>")
  if(WIN32)
    set( _JAVA_CLASSPATH "${SimpleITK_BINARY_DIR}/Wrapping/Java/${JAR_FILE}$<SEMICOLON>${_class_path}" )
  else()
    set( _JAVA_CLASSPATH "${SimpleITK_BINARY_DIR}/Wrapping/Java/${JAR_FILE}:${_class_path}" )
  endif()

  if (NOT TARGET ${_java_class}Java)

    add_custom_command(
      OUTPUT "${_class_path}/${_java_file_class}"
      COMMAND "${CMAKE_COMMAND}"
        ARGS -E remove -f "${_class_path}/${_java_file_class}"
      COMMAND "${Java_JAVAC_EXECUTABLE}"
        ARGS -classpath "${_JAVA_CLASSPATH}"
          -d "${_class_path}"
          "${java_file}"
      DEPENDS ${java_file} ${SWIG_MODULE_SimpleITKJava_TARGET_NAME} org_itk_simple_jar
      COMMENT "Building ${_class_path}/${_java_file_class}"
      )
    add_custom_target( ${_java_class}Java ALL
      DEPENDS "${_class_path}/${_java_file_class}"
      SOURCES ${java_file}
      )
  endif()


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

  file(TO_NATIVE_PATH "${SimpleITK_BINARY_DIR}/Wrapping/R/R_libs" _native_path)
  set_property(TEST R.${name}
    PROPERTY ENVIRONMENT R_LIBS=${_native_path}
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


  if (NOT TARGET "${CSHARP_EXECUTABLE}")

    # add the target to compile the test
    csharp_add_executable(
      "${CSHARP_EXECUTABLE}"
      SimpleITKCSharpManaged.dll
      ${csharp_file}
      )
  endif()

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
