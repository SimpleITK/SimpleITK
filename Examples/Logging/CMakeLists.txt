
if(NOT BUILD_TESTING)
  return()
endif()


sitk_add_python_test( Example.Logging
  "${CMAKE_CURRENT_SOURCE_DIR}/Logging.py"
  )
