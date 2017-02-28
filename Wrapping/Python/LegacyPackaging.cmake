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
  "${CMAKE_CURRENT_SOURCE_DIR}/Packaging/__init__.py"
  "${CMAKE_CURRENT_BINARY_DIR}/__init__.py"
  COPYONLY )

option(SimpleITK_PYTHON_USE_VIRTUALENV "Create a Python Virtual Environment for testing." ON)
mark_as_advanced(SimpleITK_PYTHON_USE_VIRTUALENV)
sitk_legacy_naming(SimpleITK_PYTHON_USE_VIRTUALENV)

if (SimpleITK_PYTHON_USE_VIRTUALENV)

  # Executable to setup a new Python virtual environment
  find_package( PythonVirtualEnv REQUIRED )

  sitk_enforce_forbid_downloads( SimpleITK_PYTHON_USE_VIRTUALENV )

  if (SimpleITK_PYTHON_WHEEL AND PYTHON_VIRTUALENV_VERSION_STRING VERSION_LESS "13")
    message(SEND_ERROR "In sufficient version of virutalenv for \
      building wheels. Require virtualenv>=13.0.")
  endif()

  #
  # Setup Python Virtual Enviroment for testing and packaging
  #
  set( PythonVirtualenvHome "${${CMAKE_PROJECT_NAME}_BINARY_DIR}/Testing/Installation/PythonVirtualenv" )

  # virtualenv places the python executable in different
  # locations. Also note than on windows installations where python is
  # installed only for a single user the may be a missing dll issue.
  if( WIN32 )
    set( VIRTUAL_PYTHON_EXECUTABLE
      "${PythonVirtualenvHome}/Scripts/python")
  else( )
    set( VIRTUAL_PYTHON_EXECUTABLE "${PythonVirtualenvHome}/bin/python" )
  endif()
  set(SimpleITK_PYTHON_TEST_EXECUTABLE "${VIRTUAL_PYTHON_EXECUTABLE}"
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
    COMMENT "Creating python virtual enviroment..."
    )
endif()

# Packaging for distribution
add_subdirectory(dist)
