cmake_minimum_required ( VERSION 3.10 FATAL_ERROR )

project( SimpleITK_Python )

include(../../CMake/sitkProjectLanguageCommon.cmake NO_POLICY_SCOPE)

if ( SITK_UNDEFINED_SYMBOLS_ALLOWED )
  set( _QUIET_LIBRARY "QUIET" )
else()
  set( _QUIET_LIBRARY "REQUIRED" )
endif()
find_package ( PythonInterp REQUIRED )
find_package ( PythonLibs ${_QUIET_LIBRARY} )
include_directories ( ${SimpleITK_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} )

#
# Options
#
option ( SimpleITK_PYTHON_THREADS "Enable threaded python usage by unlocking the GIL." ON )
mark_as_advanced( SimpleITK_PYTHON_THREADS )
option ( SimpleITK_PYTHON_EGG "Add building of python eggs to the dist target." OFF )
mark_as_advanced( SimpleITK_PYTHON_EGG )
option ( SimpleITK_PYTHON_WHEEL "Add building of python wheels to the dist target." ON )
mark_as_advanced( SimpleITK_PYTHON_WHEEL )


set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )

# Run swig
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS} -features autodoc=1 -keyword )
if( SimpleITK_PYTHON_THREADS )
  set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} -threads)
endif()
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/SimpleITK)
set(SWIG_MODULE_SimpleITK_EXTRA_DEPS ${SWIG_EXTRA_DEPS}
  ${CMAKE_CURRENT_SOURCE_DIR}/Python.i
  ${CMAKE_CURRENT_SOURCE_DIR}/sitkImage.i
  ${CMAKE_CURRENT_SOURCE_DIR}/sitkTransform.i )
SWIG_add_module ( SimpleITK python
  SimpleITK.i
  sitkPyCommand.cxx )
set(SWIG_MODULE_SimpleITKPython_TARGET_NAME "${SWIG_MODULE_SimpleITK_TARGET_NAME}")
target_link_libraries( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} ${SimpleITK_LIBRARIES} )
if(NOT PYTHON_DEBUG_LIBRARIES AND MSVC)
  # If there is not a specified debug library use the release library,
  # via a special sitkPython.h header.
  target_compile_definitions(${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
    PRIVATE
    $<$<CONFIG:Debug>:SWIG_PYTHON_INTERPRETER_NO_DEBUG>)
endif()
sitk_target_link_libraries_with_dynamic_lookup( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} ${PYTHON_LIBRARIES} )

target_include_directories( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
  PRIVATE
    ${PYTHON_INCLUDE_DIR} )
target_include_directories( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} )

set_target_properties( ${SWIG_MODULE_SimpleITK_TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SWIG_OUTDIR}")
if ( MSVC )
    foreach ( CMAKE_CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES} )
      string(TOUPPER ${CMAKE_CONFIGURATION_TYPE} CMAKE_CONFIGURATION_TYPE)
      set_target_properties(${SWIG_MODULE_SimpleITK_TARGET_NAME}
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${CMAKE_CONFIGURATION_TYPE} "${CMAKE_SWIG_OUTDIR}")
      set_target_properties(${SWIG_MODULE_SimpleITK_TARGET_NAME}
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${CMAKE_CONFIGURATION_TYPE} "${CMAKE_SWIG_OUTDIR}")
    endforeach( )
  endif()

# TODO add check to determine if compiler support linker script
if (UNIX AND NOT APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(VERSION_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/symbols.map")
  set_target_properties( ${SWIG_MODULE_SimpleITK_TARGET_NAME} PROPERTIES
    LINK_DEPENDS "${VERSION_SCRIPT}")
  set_property(TARGET ${SWIG_MODULE_SimpleITK_TARGET_NAME} APPEND_STRING PROPERTY
    LINK_FLAGS " -Wl,--version-script=${VERSION_SCRIPT}")
endif()

set_source_files_properties(${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-w")
sitk_strip_target( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} )



# Installation
set( SimpleITK_PYTHON_PACKAGE_DIR "${CMAKE_CURRENT_BINARY_DIR}" )
file( TO_NATIVE_PATH "${SimpleITK_PYTHON_PACKAGE_DIR}" SimpleITK_PYTHON_PACKAGE_DIR )

set(SimpleITK_PYTHON_TEST_EXECUTABLE "${PYTHON_EXECUTABLE}" CACHE INTERNAL "Python executable for testing." FORCE )


configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleITK/_version.py.in"
  "${CMAKE_CURRENT_BINARY_DIR}/SimpleITK/_version.py" )

set(SimpleITK_Py_Files "__init__.py" "extra.py" )

if(DEFINED SKBUILD)
  # Currently this installation
  install(FILES
      ${CMAKE_SWIG_OUTDIR}/SimpleITK.py
      ${SimpleITK_DOC_FILES}
      "${CMAKE_CURRENT_BINARY_DIR}/SimpleITK/_version.py"
    DESTINATION SimpleITK
    COMPONENT Runtime
    )

  foreach( _file ${SimpleITK_Py_Files})
    install(FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/SimpleITK/${_file}"
      DESTINATION SimpleITK
      COMPONENT Runtime
    )
  endforeach()

  install(TARGETS ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
    RUNTIME DESTINATION SimpleITK COMPONENT Runtime
    LIBRARY DESTINATION SimpleITK COMPONENT Runtime
    )
else()
  include(LegacyPackaging.cmake)
endif()



if (NOT CMAKE_PROJECT_NAME STREQUAL "SimpleITK" AND BUILD_TESTING)
  set(WRAP_PYTHON 1)

  add_subdirectory("${SimpleITK_SOURCE_DIR}/Testing/Unit/Python" "${CMAKE_BINARY_DIR}/Testing/Unit")

  if(BUILD_EXAMPLES)
    add_subdirectory("${SimpleITK_SOURCE_DIR}/Examples" "${CMAKE_BINARY_DIR}/Examples")
  endif()

  if(COMMAND ExternalData_Add_Target )
    ExternalData_Add_Target( SimpleITKData )
  endif()
endif()
