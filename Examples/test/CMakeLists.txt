
#
# CXX Examples
#
sitk_add_test(NAME CXX.Example.SimpleGaussian
  COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.SimpleGaussian.nrrd"
      5ef06ed0d5d8952c770348699b70f23e
    $<TARGET_FILE:SimpleGaussian>
     DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
     2.0
     "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.SimpleGaussian.nrrd"
  )

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

sitk_add_test(NAME CXX.Example.FilterProgressReporting
  COMMAND "${ITK_TEST_DRIVER}"
    $<TARGET_FILE:FilterProgressReporting>
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    2.0
    "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.FilterProgressReporting.nrrd"
  )
set_tests_properties( CXX.Example.FilterProgressReporting
  PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )

sitk_add_test(NAME CXX.Example.DicomSeriesReader
  COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.DicomSeriesReader.nrrd"
      "8e65f711d450b6b466c6d76a667ecb72"
    $<TARGET_FILE:DicomSeriesReader>
      DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.DicomSeriesReader.nrrd"
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

sitk_add_test(NAME CXX.Example.ImageRegistrationMethod1
  COMMAND
  $<TARGET_FILE:ImageRegistrationMethod1>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXImageRegistrationMethod1Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXImageRegistrationMethod1Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )

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

sitk_add_test(NAME CXX.Example.DemonsRegistration1
  COMMAND
    $<TARGET_FILE:DemonsRegistration1>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXDemonsRegistration1Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXDemonsRegistration1Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/DemonsRegistration1Test_displacement.mha}
    0.01
  )

sitk_add_test(NAME CXX.Example.DemonsRegistration2
  COMMAND
   $<TARGET_FILE:DemonsRegistration2>
   DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
   DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
   DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
   ${TEST_HARNESS_TEMP_DIRECTORY}/CXXDemonsRegistration2Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXDemonsRegistration2Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/DemonsRegistration2Test_displacement.mha}
    0.01
  )






# This test currently does not compile or work
#
#  add_java_test( Example.ImageConnection
#    "${SimpleITK_SOURCE_DIR}/Examples/ImageConnection.java" )





