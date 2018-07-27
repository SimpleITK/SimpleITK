
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test(Example.ImageRegistrationMethodExhaustiveTest1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodExhaustive.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethodExhaustiveTest1.hdf5
 TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethodExhaustiveTest1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodExhaustiveTest1.mha}
    1e-10
  )

sitk_add_r_test(Example.ImageRegistrationMethodExhaustiveTest1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodExhaustive.R"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethodExhaustiveTest1.hdf5
 TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethodExhaustiveTest1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodExhaustiveTest1.mha}
    1e-10
  )
