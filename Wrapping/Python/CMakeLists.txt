find_package ( PythonLibs REQUIRED )
find_package ( PythonInterp REQUIRED )
include_directories ( ${PYTHON_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )

option ( SimpleITK_PYTHON_THREADS "Enable threaded python usage by unlocking the GIL." ON )
mark_as_advanced( SimpleITK_PYTHON_THREADS )
option ( SimpleITK_PYTHON_EGG "Add building of python eggs to the dist target." ON )
mark_as_advanced( SimpleITK_PYTHON_EGG )
option ( SimpleITK_PYTHON_WHEEL "Add building of python wheels to the dist target." OFF )
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
target_link_libraries ( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} ${SimpleITK_LIBRARIES} )
sitk_target_link_libraries_with_dynamic_lookup( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} ${PYTHON_LIBRARIES} )
set_source_files_properties(${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-w")
sitk_strip_target( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} )



# Installation
set( SIMPLEITK_PYTHON_PACKAGE_DIR "${SimpleITK_BINARY_DIR}/Wrapping/Python" )
file( TO_NATIVE_PATH "${SIMPLEITK_PYTHON_PACKAGE_DIR}" SIMPLEITK_PYTHON_PACKAGE_DIR )
get_target_property( SWIG_MODULE_SimpleITKPython_TARGET_LOCATION ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} OUTPUT_NAME )
add_custom_command(
  TARGET ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${SWIG_MODULE_SimpleITKPython_TARGET_NAME}>" "${CMAKE_CURRENT_BINARY_DIR}"
  )
get_target_property( SIMPLEITK_RELATIVE_BINARY_MODULE ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} LOCATION )
get_filename_component( SIMPLEITK_RELATIVE_BINARY_MODULE "${SIMPLEITK_RELATIVE_BINARY_MODULE}" NAME )


if ( SimpleITK_DOC_FILES )
  # create a python list for the import documents to include in
  # packaging

  # This string is targed for setup.py. It will be passed through
  # the build-time configuration script and as a command line
  # argument. This sequence is having portability issues with
  # quote. So Windows needs separate handling from Unix-like
  # platforms.
  if( WIN32 )
    set( _q "'" )
  else()
    set( _q "\\'")
  endif()

  # specially handle the first element
  list( GET SimpleITK_DOC_FILES 0 d )
  file(TO_NATIVE_PATH "${d}" d )
  set( SimpleITK_DOC_FILES_AS_LIST "[r${_q}${d}${_q}")
  set( _doc_list "${SimpleITK_DOC_FILES}" )
  list( REMOVE_AT _doc_list 0 )

  foreach( d ${_doc_list} )
    file(TO_NATIVE_PATH "${d}" d )
    set( SimpleITK_DOC_FILES_AS_LIST "${SimpleITK_DOC_FILES_AS_LIST},r${_q}${d}${_q}")
  endforeach()
  set( SimpleITK_DOC_FILES_AS_LIST "${SimpleITK_DOC_FILES_AS_LIST}]")

endif()

include( sitkConfigureFileBuildtime )
configure_file_buildtime( "${CMAKE_CURRENT_SOURCE_DIR}/Packaging/setup.py.in"
  "${CMAKE_CURRENT_BINARY_DIR}/Packaging/setup.py" )

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Packaging/setupegg.py"
  "${CMAKE_CURRENT_BINARY_DIR}/Packaging/setupegg.py"
  COPYONLY )

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Packaging/ez_setup.py"
  "${CMAKE_CURRENT_BINARY_DIR}/Packaging/ez_setup.py"
  COPYONLY )

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Packaging/__init__.py"
  "${CMAKE_CURRENT_BINARY_DIR}/__init__.py"
  COPYONLY )

option(SITK_PYTHON_USE_VIRTUALENV "Create a Python Virtual Environment for testing." ON)
mark_as_advanced(SITK_PYTHON_USE_VIRTUALENV)

if (SITK_PYTHON_USE_VIRTUALENV)

  # Executable to setup a new Python virtual environment
  # todo use a find_program and get version
  set( PYTHON_VIRTUALENV_EXECUTABLE "" CACHE FILEPATH "Python virtualenv executable")

  sitk_enforce_forbid_downloads( SITK_PYTHON_USE_VIRTUALENV )
  #
  # Setup Python Virtual Enviroment for testing and packaging
  #
  set( PythonVirtualenvHome "${SimpleITK_BINARY_DIR}/Testing/Installation/PythonVirtualenv" )

  # virtualenv places the python executable in different
  # locations. Also note than on windows installations where python is
  # installed only for a single user the may be a missing dll issue.
  if( WIN32 )
    set( VIRTUAL_PYTHON_EXECUTABLE
      "${PythonVirtualenvHome}/Scripts/python")
  else( )
    set( VIRTUAL_PYTHON_EXECUTABLE "${PythonVirtualenvHome}/bin/python" )
  endif()
  set(TEST_PYTHON_EXECUTABLE "${VIRTUAL_PYTHON_EXECUTABLE}"
    CACHE INTERNAL "Python executable for testing." FORCE )

  # configure a scripts which creates the virtualenv and installs numpy
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/PythonVirtualEnvInstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/PythonVirtualEnvInstall.cmake"
    @ONLY )

  set( PythonVirtualEnv_ALL "" )
  if ( BUILD_TESTING )
    set( PythonVirtualEnv_ALL "ALL" )
  endif()

  add_custom_target( PythonVirtualEnv ${PythonVirtualEnv_ALL}
    DEPENDS "${VIRTUAL_PYTHON_EXECUTABLE}"
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/PythonVirtualEnvInstall.cmake.in )

  add_custom_command( OUTPUT "${VIRTUAL_PYTHON_EXECUTABLE}"
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/PythonVirtualEnvInstall.cmake"
    DEPENDS
    "${SWIG_MODULE_SimpleITKPython_TARGET_NAME}"
    "${CMAKE_CURRENT_BINARY_DIR}/PythonVirtualEnvInstall.cmake"
    ConfigureFileBuildtime
    "${CMAKE_CURRENT_BINARY_DIR}/Packaging/ez_setup.py"
    COMMENT "Creating python virtual enviroment..."
    )
else()
  set(TEST_PYTHON_EXECUTABLE "${PYTHON_EXECUTABLE}"
    CACHE INTERNAL "Python executable for testing." FORCE )
endif()

# Packaging for distribution
add_subdirectory(dist)
