
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test( Example.ImageRegistrationMethodLandmark
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodLandmark.py"
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethodLandmark.hdf5
  )
