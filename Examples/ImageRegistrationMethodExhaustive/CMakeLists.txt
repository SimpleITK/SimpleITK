
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test(Example.ImageRegistrationMethodExhaustiveTest1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodExhaustive.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodExhaustiveTest1.hdf5
 TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodExhaustiveTest1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodExhaustiveTest1.mha}
    1e-10
  )
