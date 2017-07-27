cmake_minimum_required ( VERSION 2.8.1 FATAL_ERROR )

project( SimpleITK_Python )


if(POLICY CMP0026)
  # Allow use of the LOCATION target property.
  #
  # These locations are use in a convoluted fashion with the runtime
  # configuration. This system should be refactored to support
  # generator expression. This would allow the use of the new policy.
  cmake_policy(SET CMP0026 OLD)
endif()

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
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set(SWIG_MODULE_SimpleITK_EXTRA_DEPS ${SWIG_EXTRA_DEPS}
  ${CMAKE_CURRENT_SOURCE_DIR}/Python.i )
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

set_target_properties( ${SWIG_MODULE_SimpleITK_TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
if ( MSVC )
    foreach ( CMAKE_CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES} )
      string(TOUPPER ${CMAKE_CONFIGURATION_TYPE} CMAKE_CONFIGURATION_TYPE)
      set_target_properties(${SWIG_MODULE_SimpleITK_TARGET_NAME}
        PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${CMAKE_CONFIGURATION_TYPE} "${CMAKE_CURRENT_BINARY_DIR}")
      set_target_properties(${SWIG_MODULE_SimpleITK_TARGET_NAME}
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${CMAKE_CONFIGURATION_TYPE} "${CMAKE_CURRENT_BINARY_DIR}")
    endforeach( )
endif()
set_source_files_properties(${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-w")
sitk_strip_target( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} )



# Installation
set( SimpleITK_PYTHON_PACKAGE_DIR "${CMAKE_CURRENT_BINARY_DIR}" )
file( TO_NATIVE_PATH "${SimpleITK_PYTHON_PACKAGE_DIR}" SimpleITK_PYTHON_PACKAGE_DIR )
get_target_property( SimpleITK_BINARY_MODULE ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} LOCATION )
get_filename_component( SimpleITK_BINARY_MODULE "${SimpleITK_BINARY_MODULE}" NAME )
set( SimpleITK_BINARY_MODULE "${CMAKE_CURRENT_BINARY_DIR}/${SimpleITK_BINARY_MODULE}" )

set(SimpleITK_PYTHON_TEST_EXECUTABLE "${PYTHON_EXECUTABLE}" CACHE INTERNAL "Python executable for testing." FORCE )

if(DEFINED SKBUILD)
  # Currently this installation
  install(FILES
      ${CMAKE_CURRENT_BINARY_DIR}/SimpleITK.py
      ${CMAKE_CURRENT_SOURCE_DIR}/Packaging/__init__.py
      ${SimpleITK_DOC_FILES}
    DESTINATION SimpleITK
    COMPONENT Runtime
    )

  install(TARGETS ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
    RUNTIME DESTINATION SimpleITK
    LIBRARY DESTINATION SimpleITK
    COMPONENT Runtime
    )
else()
  include(LegacyPackaging.cmake)
endif()
