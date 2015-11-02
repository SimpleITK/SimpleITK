#
# Packaging
#

if( WRAP_PYTHON )

  set(bdist_commands "bdist_egg")
  if( SimpleITK_PYTHON_WHEEL )
    set(bdist_commands ${bdist_commands} bdist_wheel)
  endif()

  if(SITK_PYTHON_USE_VIRTUALENV)
    add_custom_target( dist.Python
      ${VIRTUAL_PYTHON_EXECUTABLE} ${SimpleITK_BINARY_DIR}/Wrapping/Python/Packaging/setupegg.py ${bdist_commands}
      WORKING_DIRECTORY ${SimpleITK_BINARY_DIR}/Wrapping/Python
      DEPENDS ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
      COMMENT "Creating Python binary distribution" )

    add_dependencies( dist.Python PythonVirtualEnv)
    add_dependencies( dist dist.Python )
  elseif()
    message( STATUS "Not creating dist.Python target since SITK_FORBID_DOWNLOADS is enabled" )
  endif()

endif()
