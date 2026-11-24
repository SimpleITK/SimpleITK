if(DEFINED SimpleITK_PYTHON_PLAT_NAME)
  message(WARNING "SimpleITK_PYTHON_PLAT_NAME is deprecated.")
endif()

#
# Packaging
#
if(SimpleITK_PYTHON_WHEEL)
  if(NOT SimpleITK_PYTHON_USE_VIRTUALENV)
    message(
      STATUS
      "Not using SimpleITK's virtualenv for distribution!\n
Using unknown versions of pip, setuptools and/or wheel packages/"
    )
  endif()

  set(pip_wheel_commands "")

  set(
    pip_wheel_commands
    "-m"
    "pip"
    "wheel"
    "--no-deps"
    "--wheel-dir"
    "dist"
  )

  set(
    pip_wheel_commands
    ${pip_wheel_commands}
    "."
  )

  # Configure the platform tag for macOS wheels to contain the OSX deployment target
  if(CMAKE_OSX_DEPLOYMENT_TARGET)
    set(
      CMAKE_ENVIRONMENT_PREFIX
      ${CMAKE_COMMAND}
      -E
      env
      MACOSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET}
    )
  endif()

  add_custom_target(
    dist.Python
    COMMAND
      ${CMAKE_ENVIRONMENT_PREFIX} ${PYTHON_COMMAND_PREFIX}
      ${SimpleITK_PYTHON_TEST_EXECUTABLE} ${pip_wheel_commands}
    WORKING_DIRECTORY ${SimpleITK_Python_BINARY_DIR}
    DEPENDS
      ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
      ${CMAKE_CURRENT_BINARY_DIR}/pyproject.toml
    COMMENT "Creating Python binary distribution"
  )

  if(SimpleITK_PYTHON_USE_VIRTUALENV)
    add_dependencies(dist.Python PythonVirtualEnv)
  endif()
  add_dependencies(dist dist.Python)
endif()
