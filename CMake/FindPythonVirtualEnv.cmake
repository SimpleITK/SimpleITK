#.rst:
# FindPythonVirtualEnv
# --------
#
# Find Python's VirtualEnv Utility
#
# ::
#
#   PYTHON_VIRTUALENV_SCRIPT           - the full path to virtualenv
#   PYTHON_VIRTUALENV_SCRIPT_FOUND     - If false, don't attempt to use lua
#   PYTHON_VIRTUALENV_VERSION_STRING   - version of lua found

find_program(PYTHON_VIRTUALENV_SCRIPT
  NAMES virtualenv.py virtualenv
  )

if(PYTHON_VIRTUALENV_SCRIPT)

  if ("${PYTHON_EXECUTABLE}" STREQUAL "")
    find_package(PythonInterp REQUIRED)
  endif()

  ### PYTHON_VIRTUALENV_VERSION
  execute_process(
    COMMAND ${PYTHON_EXECUTABLE} ${PYTHON_VIRTUALENV_SCRIPT} --version
    OUTPUT_VARIABLE
      PYTHON_VIRTUALENV_VERSION_STRING
    ERROR_VARIABLE
      PYTHON_VIRTUALENV_VERSION_STRING
    RESULT_VARIABLE
      PYTHON_VIRTUALENV_VERSION_RESULT_VARIABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
    )
  if (PYTHON_VIRTUALENV_VERSION_RESULT_VARIABLE)
    message(ERROR "Unable to determing PythonVirtualEnv version!\n${PYTHON_VIRTUALENV_VERSION_STRING}")
    set(PYTHON_VIRTUALENV_VERSION_STRING "")
  else()
    string( REGEX MATCH "([0-9]*)([.])([0-9]*)([.]*)([0-9]*)"
      PYTHON_VIRTUALENV_VERSION
      ${PYTHON_VIRTUALENV_VERSION_STRING} )
  endif()
endif()


# handle the QUIETLY and REQUIRED arguments and set PYTHON_VIRTUALENV_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PythonVirtualEnv
                                  REQUIRED_VARS PYTHON_VIRTUALENV_SCRIPT
                                  VERSION_VAR PYTHON_VIRTUALENV_VERSION_STRING)

mark_as_advanced(PYTHON_VIRTUALENV_SCRIPT)
