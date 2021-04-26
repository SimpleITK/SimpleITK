
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test( Example.ImageRegistrationOptimizerWeightsTest
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationOptimizerWeights.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short_az0.35_tx3_ty4_tz2.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationOptimizerWeightsTest.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationOptimizerWeightsTest.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationOptimizerWeightsTest.nrrd}
    50.0
  )

sitk_add_r_test( Example.ImageRegistrationOptimizerWeightsTest
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationOptimizerWeights.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short_az0.35_tx3_ty4_tz2.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationOptimizerWeightsTest.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationOptimizerWeightsTest.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationOptimizerWeightsTest.nrrd}
    50.0
  )
