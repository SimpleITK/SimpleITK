#
# Packaging
#
if( SimpleITK_PYTHON_EGG OR SimpleITK_PYTHON_WHEEL )
  if( NOT SITK_PYTHON_USE_VIRTUALENV )
    message( STATUS "Not using SimpleITK's virtualenv for distribution!\
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

  add_custom_target( dist.Python
    ${VIRTUAL_PYTHON_EXECUTABLE} ${bdist_setup} ${bdist_commands}
    WORKING_DIRECTORY ${SimpleITK_Python_BINARY_DIR}
    DEPENDS ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
    COMMENT "Creating Python binary distribution" )

  add_dependencies( dist.Python PythonVirtualEnv)
  add_dependencies( dist dist.Python )
elseif()
  message( STATUS "Not creating dist.Python target since SITK_FORBID_DOWNLOADS is enabled" )
endif()
