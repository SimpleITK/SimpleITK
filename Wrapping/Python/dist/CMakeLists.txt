#
# Packaging
#
if( SimpleITK_PYTHON_EGG OR SimpleITK_PYTHON_WHEEL )
  if( NOT SimpleITK_PYTHON_USE_VIRTUALENV )
    message( STATUS "Not using SimpleITK's virtualenv for distribution!\n
Using unknown versions of pip, setuptools and/or wheel packages/" )
  endif()

  set(bdist_setup "${SimpleITK_Python_BINARY_DIR}/Packaging/setupegg.py")
  set(bdist_commands "")

  if( SimpleITK_PYTHON_EGG )
    set(bdist_commands "bdist_egg")
  endif()

  if( SimpleITK_PYTHON_WHEEL )
    set(bdist_commands ${bdist_commands} "bdist_wheel")
  endif()

  set( SimpleITK_PYTHON_PLAT_NAME "" CACHE STRING
    "Optional value passed to setup.py with the '--plat-name' argument")

  if( NOT "${SimpleITK_PYTHON_PLAT_NAME}" STREQUAL "" )
    set(bdist_commands ${bdist_commands} "--plat-name" "${SimpleITK_PYTHON_PLAT_NAME}")
  endif()

  add_custom_target( dist.Python
    ${VIRTUAL_PYTHON_EXECUTABLE} ${bdist_setup} ${bdist_commands}
    WORKING_DIRECTORY ${SimpleITK_Python_BINARY_DIR}
    DEPENDS ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
    COMMENT "Creating Python binary distribution" )

  if( SimpleITK_PYTHON_USE_VIRTUALENV )
    add_dependencies( dist.Python PythonVirtualEnv)
  endif()
  add_dependencies( dist dist.Python )
elseif()
  message( STATUS "Not creating dist.Python target since SimpleITK_FORBID_DOWNLOADS is enabled" )
endif()
