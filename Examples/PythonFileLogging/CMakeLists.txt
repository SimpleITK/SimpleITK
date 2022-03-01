
if ( NOT BUILD_TESTING )
  return ()
endif ()


sitk_add_python_test( Example.PythonFileLogging
  "${CMAKE_CURRENT_SOURCE_DIR}/FileLogging.py"
  )
