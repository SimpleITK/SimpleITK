
sitk_add_r_test( Example.SimpleGaussian
  "--file=${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.R"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/R.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  --args
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/R.SimpleGaussian.nrrd"
  )

sitk_add_r_test( Example.FilterProgressReporting
  "--file=${CMAKE_CURRENT_SOURCE_DIR}/FilterProgressReporting.R"
  --args
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    2.0
    "${TEST_HARNESS_TEMP_DIRECTORY}/R.FilterProgressReporting.nrrd"
  )

sitk_add_r_test( Example.ImageRegistrationMethod1
  "--file=${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod1.R"
  --args
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/RImageRegistrationMethod11Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/RImageRegistrationMethod11Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )
