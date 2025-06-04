#[=======================================================================[.rst:
.. command:: sitk_check_python_module_version

  Checks if a Python module is available with version constraints::


    sitk_check_python_module_version(
      MODULE_NAME jsonschema
      MINIMUM_VERSION 4.0.0
      [MAXIMUM_VERSION 5.0.0]
      PYTHON_EXECUTABLE "${Python_EXECUTABLE}"
      RESULT_VERSION_VAR <variable>
      [RESULT_STATUS_VAR <variable>]
      [REQUIRED]
    )

  This function checks if a specified Python module is available with the required
  version using importlib.metadata. The version found is stored in the
  RESULT_VERSION_VAR variable, which will be undefined if the module is not found
  or the version doesn't meet the constraints.

  Arguments:

  ``MODULE_NAME``
    Name of the Python module to check.

  ``MINIMUM_VERSION``
    Minimum required version of the module.

  ``MAXIMUM_VERSION``
    Optional maximum allowed version of the module.

  ``PYTHON_EXECUTABLE``
    Path to the Python executable.

  ``RESULT_VERSION_VAR``
    Variable name to store the module version.

  ``RESULT_STATUS_VAR``
    Variable name to store the result status (TRUE if module found with required version).
    If not provided, defaults to "${RESULT_VERSION_VAR}_FOUND".

  ``REQUIRED``
    If set, a SEND_ERROR message will be generated if the module is not found
    or the version constraints are not satisfied.

#]=======================================================================]
function(sitk_check_python_module_version)
    set(options REQUIRED)
    set(oneValueArgs MODULE_NAME MINIMUM_VERSION MAXIMUM_VERSION PYTHON_EXECUTABLE RESULT_VERSION_VAR RESULT_STATUS_VAR)
    set(multiValueArgs )
    cmake_parse_arguments(SCPMV "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Check required arguments
    foreach(arg MODULE_NAME MINIMUM_VERSION PYTHON_EXECUTABLE RESULT_VERSION_VAR)
        if(NOT DEFINED SCPMV_${arg})
            message(FATAL_ERROR "sitk_check_python_module_version requires ${arg}")
        endif()
    endforeach()

    if(NOT DEFINED SCPMV_RESULT_STATUS_VAR)
        set(SCPMV_RESULT_STATUS_VAR "${SCPMV_RESULT_VERSION_VAR}_FOUND")
    endif()

    # Clear the output variables in parent scope
    unset(${SCPMV_RESULT_VERSION_VAR} PARENT_SCOPE)
    set(${SCPMV_RESULT_STATUS_VAR} FALSE PARENT_SCOPE)

    # Check if Python executable exists
    if ( NOT EXISTS "${SCPMV_PYTHON_EXECUTABLE}" )
        message(SEND_ERROR "Python executable not found: ${SCPMV_PYTHON_EXECUTABLE}")
        return()
    endif()

    execute_process(
            COMMAND "${SCPMV_PYTHON_EXECUTABLE}" -c "import importlib.metadata; print(importlib.metadata.version('${SCPMV_MODULE_NAME}'))"
            OUTPUT_VARIABLE MODULE_VERSION
            ERROR_VARIABLE MODULE_ERROR
            RESULT_VARIABLE MODULE_RESULT_VARIABLE
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_STRIP_TRAILING_WHITESPACE
    )

    if(MODULE_ERROR)
        message(DEBUG "Error when checking module: ${MODULE_ERROR}")
    endif()

    if (NOT MODULE_RESULT_VARIABLE EQUAL 0)
        message(DEBUG "Error when checking module: ${MODULE_ERROR}")
        if(SCPMV_REQUIRED)
            message(SEND_ERROR "Python ${SCPMV_MODULE_NAME} module is missing. Please install it.")
        else()
            message(STATUS "Python ${SCPMV_MODULE_NAME} module is not found, but this is not required.")
        endif()
        return()
    endif()

    set(VERSION_CONSTRAINTS_SATISFIED TRUE)

    # Check minimum version constraint
    if(NOT MODULE_VERSION GREATER_EQUAL ${SCPMV_MINIMUM_VERSION})
        set(VERSION_CONSTRAINTS_SATISFIED FALSE)
    endif()

    # Check maximum version constraint if specified
    if(DEFINED SCPMV_MAXIMUM_VERSION)
        if(MODULE_VERSION VERSION_GREATER "${SCPMV_MAXIMUM_VERSION}")
            set(VERSION_CONSTRAINTS_SATISFIED FALSE)
        endif()
    endif()

    if(VERSION_CONSTRAINTS_SATISFIED)
        message(STATUS "Python ${SCPMV_MODULE_NAME} module version: ${MODULE_VERSION}")
        set(${SCPMV_RESULT_VERSION_VAR} ${MODULE_VERSION} PARENT_SCOPE)
        set(${SCPMV_RESULT_STATUS_VAR} TRUE PARENT_SCOPE)
    else()
        message(DEBUG "Python ${SCPMV_MODULE_NAME} module version ${MODULE_VERSION} does not satisfy required version constraints.")
        set(${SCPMV_RESULT_VERSION_VAR} "" PARENT_SCOPE)
        set(${SCPMV_RESULT_STATUS_VAR} FALSE PARENT_SCOPE)

        if(SCPMV_REQUIRED)
            set(VERSION_CONSTRAINT_MSG "version >= ${SCPMV_MINIMUM_VERSION}")
            if(DEFINED SCPMV_MAXIMUM_VERSION)
                set(VERSION_CONSTRAINT_MSG "${VERSION_CONSTRAINT_MSG} and <= ${SCPMV_MAXIMUM_VERSION}")
            endif()
            message(SEND_ERROR "Python ${SCPMV_MODULE_NAME} module does not satisfy required ${VERSION_CONSTRAINT_MSG}")
        else()
            message(STATUS "Python ${SCPMV_MODULE_NAME} module version does not satisfy optional constraints.")
        endif()
    endif()

endfunction()
