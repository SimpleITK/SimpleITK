
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test( Example.LandmarkRegistration
  "${CMAKE_CURRENT_SOURCE_DIR}/LandmarkRegistration.py"
  ${SimpleITK_TEST_OUTPUT_DIR}/LandmarkRegistration.hdf5
  )
