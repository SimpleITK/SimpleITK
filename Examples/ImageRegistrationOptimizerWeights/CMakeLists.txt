add_executable(
  ImageRegistrationOptimizerWeights
  ImageRegistrationOptimizerWeights.cxx
)
target_link_libraries(ImageRegistrationOptimizerWeights ${SimpleITK_LIBRARIES})

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(
  NAME CXX.Example.ImageRegistrationOptimizerWeightsTest
  COMMAND
    $<TARGET_FILE:ImageRegistrationOptimizerWeights>
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short_az0.35_tx3_ty4_tz2.nrrd}
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXImageRegistrationOptimizerWeightsTest.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXImageRegistrationOptimizerWeightsTest.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationOptimizerWeightsTest.nrrd}
    50.0
)

sitk_add_csharp_test(
  Example.ImageRegistrationOptimizerWeightsTest
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationOptimizerWeights.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short_az0.35_tx3_ty4_tz2.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  ${SimpleITK_TEST_OUTPUT_DIR}/CSharpImageRegistrationOptimizerWeightsTest.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CSharpImageRegistrationOptimizerWeightsTest.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationOptimizerWeightsTest.nrrd}
    50.0
)

sitk_add_java_test(
  Example.ImageRegistrationOptimizerWeightsTest
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationOptimizerWeights.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short_az0.35_tx3_ty4_tz2.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  ${SimpleITK_TEST_OUTPUT_DIR}/JavaImageRegistrationOptimizerWeightsTest.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/JavaImageRegistrationOptimizerWeightsTest.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationOptimizerWeightsTest.nrrd}
    50.0
)

sitk_add_python_test(
  Example.ImageRegistrationOptimizerWeightsTest
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationOptimizerWeights.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short_az0.35_tx3_ty4_tz2.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationOptimizerWeightsTest.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationOptimizerWeightsTest.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationOptimizerWeightsTest.nrrd}
    50.0
)

sitk_add_r_test(
  Example.ImageRegistrationOptimizerWeightsTest
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationOptimizerWeights.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short_az0.35_tx3_ty4_tz2.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationOptimizerWeightsTest.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationOptimizerWeightsTest.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationOptimizerWeightsTest.nrrd}
    50.0
)
