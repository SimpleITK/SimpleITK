add_executable ( ImageRegistrationMethod2 ImageRegistrationMethod2.cxx )
target_link_libraries ( ImageRegistrationMethod2 ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()


sitk_add_test(NAME CXX.Example.ImageRegistrationMethod2
  COMMAND
    $<TARGET_FILE:ImageRegistrationMethod2>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXImageRegistrationMethod2Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXImageRegistrationMethod2Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )

sitk_add_python_test( Example.ImageRegistrationMethod2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod2.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod2Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod2Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )


