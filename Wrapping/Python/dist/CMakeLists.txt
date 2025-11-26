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

  if(SimpleITK_PYTHON_WHEEL)
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

    add_custom_target(
      dist.Python
      ${PYTHON_COMMAND_PREFIX} ${VIRTUAL_PYTHON_EXECUTABLE}
      ${pip_wheel_commands}
      WORKING_DIRECTORY ${SimpleITK_Python_BINARY_DIR}
      DEPENDS
        ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
      COMMENT "Creating Python binary distribution"
    )
  endif()

  if(SimpleITK_PYTHON_USE_VIRTUALENV)
    add_dependencies(dist.Python PythonVirtualEnv)
  endif()
  add_dependencies(dist dist.Python)
else()
  message(
    STATUS
    "Not creating dist.Python target since SimpleITK_FORBID_DOWNLOADS is enabled"
  )
endif()
