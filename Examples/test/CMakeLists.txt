
#
# CXX Examples
#

sitk_add_test(NAME CXX.Example.SimpleGaussianFunctional
  COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.SimpleGaussianFunctional.nrrd"
      5ef06ed0d5d8952c770348699b70f23e
    $<TARGET_FILE:SimpleGaussianFunctional>
     DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
     2.0
     "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.SimpleGaussianFunctional.nrrd"
  )


sitk_add_test(NAME  CXX.Example.Segmentation.ConnectedThresholdImageFilter1
  COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationConnectedThreshold1.png"
      "d4ff9c512f9c18a84729677de800db0d"
    $<TARGET_FILE:ConnectedThresholdImageFilter>
      DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationConnectedThreshold1.png"
      150 180
      60 116
  )

sitk_add_test(NAME  CXX.Example.Segmentation.ConnectedThresholdImageFilter2
  COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationConnectedThreshold2.png"
      "a9695df04cde5b9c5481d8c253a5b3aa"
    $<TARGET_FILE:ConnectedThresholdImageFilter>
      DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationConnectedThreshold2.png"
      210 250
      81 112
  )

sitk_add_test( NAME CXX.Example.Segmentation.NeighborhoodConnectedImageFilter1
  COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationNeighborhoodConnected1.png"
      "311d9d4b492e1ea625e3b0b295814dce"
    $<TARGET_FILE:NeighborhoodConnectedImageFilter>
      DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXXSegmentationNeighborhoodConnected1.png"
      150 180
      60 116
  )

sitk_add_test(NAME CXX.Example.ImageRegistrationMethodBSpline1
  COMMAND
    $<TARGET_FILE:ImageRegistrationMethodBSpline1>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXImageRegistrationMethodBSpline1.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXImageRegistrationMethodBSpline1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline1.mha}
    0.02
  )


sitk_add_test(NAME CXX.Example.ImageRegistrationMethodDisplacement1
  COMMAND
    $<TARGET_FILE:ImageRegistrationMethodDisplacement1>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/ImageRegistrationMethodDisplacement1.hdf5
 TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/ImageRegistrationMethodDisplacement1.hdf5
     DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodDisplacement1.mha}

    0.02
  )

sitk_add_test(NAME CXX.Example.ImageRegistrationMethodDisplacement1Test2
  COMMAND
    $<TARGET_FILE:ImageRegistrationMethodDisplacement1>
    DATA{${SimpleITK_DATA_ROOT}/Input/r16slice_rigid.nii.gz}
    DATA{${SimpleITK_DATA_ROOT}/Input/r64slice.nii.gz}
    ${TEST_HARNESS_TEMP_DIRECTORY}/ImageRegistrationMethodDisplacement1Test2.hdf5
 TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/ImageRegistrationMethodDisplacement1Test2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodDisplacement1Test2.mha}
    0.02
  )






# This test currently does not compile or work
#
#  add_java_test( Example.ImageConnection
#    "${SimpleITK_SOURCE_DIR}/Examples/ImageConnection.java" )





