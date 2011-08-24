option(USE_VIRTUALENV
  "Use a Python virtualenv for unit testing and installation testing." ON)
if(USE_VIRTUALENV)
  set( PythonVirtualenvHome ${SimpleITK_BINARY_DIR}/Testing/Installation/PythonVirtualenv )
  add_test(NAME Python.VirtualenvInstall
    COMMAND ${PYTHON_EXECUTABLE}
    ${SimpleITK_SOURCE_DIR}/Testing/PythonPackage/virtualenv.py
    --python=${PYTHON_EXECUTABLE}
    --distribute
    ${PythonVirtualenvHome} )
  set( PYTHON_EXECUTABLE ${PythonVirtualenvHome}/bin/python )

  add_test( NAME Python.Install
    COMMAND ${PYTHON_EXECUTABLE} ${SimpleITK_BINARY_DIR}/Wrapping/PythonPackage/setup.py
    install )
  set_tests_properties( Python.Install PROPERTIES DEPENDS Python.VirtualenvInstall )
endif()

add_subdirectory(Unit)
