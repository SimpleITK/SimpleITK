set(ITK_TEST_DRIVER  "itkTestDriver")

# Test data directory
set(TEST_HARNESS_TEMP_DIRECTORY ${SimpleITK_BINARY_DIR}/Testing/Temporary)
set(TEST_HARNESS_DATA_DIRECTORY ${SimpleITK_BINARY_DIR}/ExternalData/Testing/Data)

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



#
# Python Examples
#
sitk_add_python_test( Example.SimpleGaussian
  "${SimpleITKExamples_SOURCE_DIR}/SimpleGaussian.py"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd" )

sitk_add_python_test( Example.SimpleGaussianProcedural
  "${SimpleITKExamples_SOURCE_DIR}/SimpleGaussianProcedural.py"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussianProcedural.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussianProcedural.nrrd" )

sitk_add_python_test( Example.ImageCreateAndSet
  "${SimpleITKExamples_SOURCE_DIR}/ImageCreateAndSet.py" )

sitk_add_python_test( Example.CannyEdge
  "${SimpleITKExamples_SOURCE_DIR}/CannyEdge.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd} )

sitk_add_python_test( Example.ExtractSlice
  "${SimpleITKExamples_SOURCE_DIR}/ExtractSlice.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "30"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.ExtractSlice.nrrd")

sitk_add_python_test( Example.BoarderSegmentation
  "${SimpleITKExamples_SOURCE_DIR}/BoarderSegmentation.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.BoarderSegmentation.nrrd"
  "5000"
  "150" )

 sitk_add_python_test( Example.N4BiasFieldCorrection
  "${SimpleITKExamples_SOURCE_DIR}/N4BiasFieldCorrection.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Example.N4BiasFieldCorrection.nrrd"
  "1" )

sitk_add_python_test( Example.ReadAndShow
  "${SimpleITKExamples_SOURCE_DIR}/ReadAndShow.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/VM1111Shrink-RGB.png} )

sitk_add_python_test( Example.GeodesicActiceContourSegmentation
  "${SimpleITKExamples_SOURCE_DIR}/GeodesicActiceContourSegmentation.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1.png}
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Example.GeodesicActiceContourSegmentation.nrrd"
  .3 10 .9 50 55
  )

sitk_add_python_test( Example.FFTConvolution
  "${SimpleITKExamples_SOURCE_DIR}/FFTConvolution.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1-Float.mha}
  DATA{${SimpleITK_DATA_ROOT}/Input/Gaussian_1.5.nrrd}
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Examples.FFTConvolution.nrrd"
  )

if ( WRAP_PYTHON )
  sitk_add_python_test( Example.FilterProgressReporting
    "${SimpleITKExamples_SOURCE_DIR}/FilterProgressReporting.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonFilterProgressReporting.nrrd"
    )

  set_tests_properties( Python.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )
endif()

sitk_add_python_test( Example.DicomSeriesReader
  "${SimpleITKExamples_SOURCE_DIR}/DicomSeriesReader.py"
  --compare-MD5
  "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  "8e65f711d450b6b466c6d76a667ecb72"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  )

sitk_add_python_test( Example.DicomSeriesReader2
  "${SimpleITKExamples_SOURCE_DIR}/DicomSeriesReader2.py"
  --compare-MD5
  "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader2.nrrd"
  "8e65f711d450b6b466c6d76a667ecb72"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader2.nrrd"
  )

sitk_add_python_test( Example.Segmentation.ConnectedThresholdImageFilter1
  "${SimpleITKExamples_SOURCE_DIR}/Segmentation/ConnectedThresholdImageFilter.py"
  --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold1.png"
    "d4ff9c512f9c18a84729677de800db0d"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold1.png"
  150 180
  60 116
  )

sitk_add_python_test( Example.Segmentation.ConnectedThresholdImageFilter2
  "${SimpleITKExamples_SOURCE_DIR}/Segmentation/ConnectedThresholdImageFilter.py"
  --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold2.png"
    "a9695df04cde5b9c5481d8c253a5b3aa"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold2.png"
  210 250
  81 112
  )

sitk_add_python_test( Example.Segmentation.NeighborhoodConnectedImageFilter1
  "${SimpleITKExamples_SOURCE_DIR}/Segmentation/NeighborhoodConnectedImageFilter.py"
  --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationNeighborhoodConnected1.png"
    "311d9d4b492e1ea625e3b0b295814dce"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationNeighborhoodConnected1.png"
  150 180
  60 116
  )

sitk_add_python_test( Example.ImageRegistrationMethod1
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethod1.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod11Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod11Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )

sitk_add_python_test( Example.ImageRegistrationMethod2
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethod2.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod2Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod2Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )

sitk_add_python_test( Example.ImageRegistrationMethod3Test1
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethod3.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod3Test1.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod3Test1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test1.mha}
    0.02
  )

sitk_add_python_test( Example.ImageRegistrationMethod3Test2
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethod3.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17S12.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod3Test2.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod3Test2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test2.mha}
    0.03
  )


sitk_add_python_test( Example.ImageRegistrationMethod4Test1
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethod4.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test1.hdf5
  24 1.0
  )

sitk_add_python_test( Example.ImageRegistrationMethod4Test2
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethod4.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test2.hdf5
  24 0.1
  )

sitk_add_python_test( Example.ImageRegistrationMethod4Test3
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethod4.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test3.hdf5
  5 0.4
  )


sitk_add_python_test(Example.ImageRegistrationMethodBSpline1
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethodBSpline1.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodBSpline1.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodBSpline1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline1.mha}
    0.02
  )


sitk_add_python_test(Example.ImageRegistrationMethodBSpline2
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethodBSpline2.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodBSpline2.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodBSpline2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline2.mha}
    0.02
  )

sitk_add_python_test(Example.ImageRegistrationMethodDisplacement1
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethodDisplacement1.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodDisplacement1.hdf5
 TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodDisplacement1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodDisplacement1.mha}
    0.02
  )

sitk_add_python_test(Example.ImageRegistrationMethodDisplacement1Test2
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethodDisplacement1.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/r16slice_rigid.nii.gz}
    DATA{${SimpleITK_DATA_ROOT}/Input/r64slice.nii.gz}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodDisplacement1Test2.hdf5
 TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodDisplacement1Test2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodDisplacement1Test2.mha}
    0.02
  )

sitk_add_python_test(Example.ImageRegistrationMethodExhaustiveTest1
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethodExhaustive.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodExhaustiveTest1.hdf5
 TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodExhaustiveTest1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodExhaustiveTest1.mha}
    1e-10
  )



sitk_add_python_test(Example.DemonsRegistration1
  "${SimpleITKExamples_SOURCE_DIR}/DemonsRegistration1.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonDemonsRegistration1Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonDemonsRegistration1Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/DemonsRegistration1Test_displacement.mha}
    0.005
  )

sitk_add_python_test(Example.DemonsRegistration2
  "${SimpleITKExamples_SOURCE_DIR}/DemonsRegistration2.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonDemonsRegistration2Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonDemonsRegistration2Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/DemonsRegistration2Test_displacement.mha}
    0.01
  )

#
# Lua Examples
#
sitk_add_lua_test( Example.SimpleGaussian
  "${SimpleITKExamples_SOURCE_DIR}/SimpleGaussian.lua"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleGaussian.nrrd" )

sitk_add_lua_test( Example.DicomSeriesReader
  "${SimpleITKExamples_SOURCE_DIR}/DicomSeriesReader.lua"
  --compare-MD5
  "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  "8e65f711d450b6b466c6d76a667ecb72"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  )

sitk_add_lua_test( Example.ImageRegistrationMethod1
  "${SimpleITKExamples_SOURCE_DIR}/ImageRegistrationMethod1.lua"
    ${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySliceBorder20.png
    ${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySliceShifted13x17y.png
    ${TEST_HARNESS_TEMP_DIRECTORY}/LuaImageRegistrationMethod1Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/LuaImageRegistrationMethod1Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
    )


#
# Ruby Examples
#
sitk_add_ruby_test( Example.SimpleGaussian
  "${SimpleITKExamples_SOURCE_DIR}/SimpleGaussian.rb"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Ruby.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Ruby.SimpleGaussian.nrrd" )



#
# TCL Examples
#
sitk_add_tcl_test( Example.SimpleGaussian
  "${SimpleITKExamples_SOURCE_DIR}/SimpleGaussian.tcl"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Tcl.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Tcl.SimpleGaussian.nrrd" )


#
# JAVA Examples
#
sitk_add_java_test( Example.SimpleGaussian
  "${SimpleITKExamples_SOURCE_DIR}/SimpleGaussian.java"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Java.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Java.SimpleGaussian.nrrd" )

if ( WRAP_JAVA )
  sitk_add_java_test( Example.FilterProgressReporting
    "${SimpleITKExamples_SOURCE_DIR}/FilterProgressReporting.java"
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Java.FilterProgressReporting.nrrd"
    )
  set_tests_properties( Java.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )
endif ( WRAP_JAVA )

# This test currently does not compile or work
#
#  add_java_test( Example.ImageConnection
#    "${SimpleITK_SOURCE_DIR}/Examples/ImageConnection.java" )



#
# R Examples
#
sitk_add_r_test( Example.SimpleGaussian
  "--file=${SimpleITKExamples_SOURCE_DIR}/SimpleGaussian.R"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  --args
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd"
  )


#
# CSharp Examples
#
sitk_add_csharp_test( Example.SimpleGaussian
  "${SimpleITKExamples_SOURCE_DIR}/SimpleGaussian.cs"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/CSharp.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/CSharp.SimpleGaussian.nrrd" )

if ( WRAP_CSHARP )
  sitk_add_csharp_test( Example.ImageGetBuffer
    "${SimpleITKExamples_SOURCE_DIR}/ImageGetBuffer.cs"
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd})
  set_tests_properties( CSharp.Example.ImageGetBuffer
    PROPERTIES PASS_REGULAR_EXPRESSION "total: 1009713" )

  sitk_add_csharp_test( Example.FilterProgressReporting
    "${SimpleITKExamples_SOURCE_DIR}/FilterProgressReporting.cs"
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/CSharp.FilterProgressReporting.nrrd"
    )
  set_tests_properties( CSharp.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )
endif ( WRAP_CSHARP )
