
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test( Example.ImageRegistrationMethod3Test1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod3.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod3Test1.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod3Test1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test1.mha}
    0.02
  )

sitk_add_python_test( Example.ImageRegistrationMethod3Test2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod3.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17S12.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod3Test2.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod3Test2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test2.mha}
    0.03
  )
