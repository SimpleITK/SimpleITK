#
# sitkPythonTestingEnvironment.cmake
#
# Sets up a Python virtual environment for SimpleITK testing and packaging.
# Creates a clean, isolated Python environment with required dependencies
# (numpy, pytest) and installs the SimpleITK Python package into it.
# The virtual environment executable is cached in SimpleITK_PYTHON_TEST_EXECUTABLE
# for use by test targets. Can be disabled by setting SimpleITK_PYTHON_USE_VIRTUALENV
# to OFF.
#

option(
  SimpleITK_PYTHON_USE_VIRTUALENV
  "Create a Python Virtual Environment for testing."
  ON
)
mark_as_advanced(SimpleITK_PYTHON_USE_VIRTUALENV)
sitk_legacy_naming(SimpleITK_PYTHON_USE_VIRTUALENV)

set(PYTHON_COMMAND_PREFIX "")
# add extra command which may be needed on some systems
if(CMAKE_OSX_ARCHITECTURES)
  list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
  set(
    PYTHON_COMMAND_PREFIX
    arch
    -${test_arch}
  )
endif()

if(SimpleITK_PYTHON_USE_VIRTUALENV)
  #TODO Check python version

  #
  # Setup Python Virtual Environment for testing and packaging
  #
  set(
    PythonVirtualenvHome
    "${${CMAKE_PROJECT_NAME}_BINARY_DIR}/Testing/Installation/pyvenv"
  )
  get_filename_component(_Python_EXECUTABLE_NAME ${Python_EXECUTABLE} NAME)

  # virtualenv places the python executable in different
  # locations. Also note than on windows installations where python is
  # installed only for a single user the may be a missing dll issue.
  if(WIN32)
    set(
      VIRTUAL_PYTHON_EXECUTABLE
      "${PythonVirtualenvHome}/Scripts/${_Python_EXECUTABLE_NAME}"
    )
  else()
    set(
      VIRTUAL_PYTHON_EXECUTABLE
      "${PythonVirtualenvHome}/bin/${_Python_EXECUTABLE_NAME}"
    )
  endif()
  set(
    SimpleITK_PYTHON_TEST_EXECUTABLE
    "${VIRTUAL_PYTHON_EXECUTABLE}"
    CACHE INTERNAL
    "Python executable for testing."
  )

  set(PythonVirtualEnv_ALL "")
  if(BUILD_TESTING)
    set(PythonVirtualEnv_ALL "ALL")
  endif()

  add_custom_target(
    PythonVirtualEnv
    ${PythonVirtualEnv_ALL}
    DEPENDS
      "${VIRTUAL_PYTHON_EXECUTABLE}"
  )

  add_custom_command(
    OUTPUT
      "${VIRTUAL_PYTHON_EXECUTABLE}"
    COMMAND
      ${PYTHON_COMMAND_PREFIX} "${Python_EXECUTABLE}" "-m" "venv" "--clear"
      "${PythonVirtualenvHome}"
    COMMAND
      ${PYTHON_COMMAND_PREFIX} "${VIRTUAL_PYTHON_EXECUTABLE}" "-m" "pip"
      "install" "--upgrade" "pip"
    COMMAND
      ${PYTHON_COMMAND_PREFIX} "${VIRTUAL_PYTHON_EXECUTABLE}" "-m" "pip"
      "install" "numpy!=1.24.1,!=1.24.0" "pytest" "."
    WORKING_DIRECTORY "${SimpleITK_Python_BINARY_DIR}"
    DEPENDS
      "${SWIG_MODULE_SimpleITKPython_TARGET_NAME}"
    COMMENT "Creating python virtual environment..."
  )

  if(NOT SimpleITK_PYTHON_PACKAGE_NAME STREQUAL "SimpleITK")
    # When the package is renamed (e.g. SimpleElastix), install a SimpleITK
    # shim module into the venv so that "import SimpleITK as sitk" still works.
    set(_shim_file "${CMAKE_CURRENT_BINARY_DIR}/SimpleITK.py")
    set(_install_shim_script "${CMAKE_CURRENT_BINARY_DIR}/install_sitk_shim.py")
    file(
      CONFIGURE
      OUTPUT "${_shim_file}"
      CONTENT
        "# SimpleITK compatibility shim - re-exports @SimpleITK_PYTHON_PACKAGE_NAME@ as SimpleITK\nfrom @SimpleITK_PYTHON_PACKAGE_NAME@ import *\n"
      @ONLY
    )
    file(
      CONFIGURE
      OUTPUT "${_install_shim_script}"
      CONTENT
        "import sysconfig, shutil\nshutil.copy('@_shim_file@', sysconfig.get_path('purelib') + '/SimpleITK.py')\n"
      @ONLY
    )
    add_custom_command(
      OUTPUT
        "${VIRTUAL_PYTHON_EXECUTABLE}"
      COMMAND
        ${VIRTUAL_PYTHON_EXECUTABLE} "${_install_shim_script}"
      COMMENT
        "Installing SimpleITK compatibility shim into virtual environment..."
      APPEND
    )
  endif()
else()
  set(
    SimpleITK_PYTHON_TEST_EXECUTABLE
    "${Python_EXECUTABLE}"
    CACHE INTERNAL
    "Python executable for testing."
  )
endif()
