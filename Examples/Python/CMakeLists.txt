
sitk_add_python_test( Example.SimpleGaussianProcedural
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussianProcedural.py"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussianProcedural.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussianProcedural.nrrd" )

sitk_add_python_test( Example.ImageCreateAndSet
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageCreateAndSet.py" )

sitk_add_python_test( Example.CannyEdge
  "${CMAKE_CURRENT_SOURCE_DIR}/CannyEdge.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd} )

sitk_add_python_test( Example.ExtractSlice
  "${CMAKE_CURRENT_SOURCE_DIR}/ExtractSlice.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "30"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.ExtractSlice.nrrd")

sitk_add_python_test( Example.BoarderSegmentation
  "${CMAKE_CURRENT_SOURCE_DIR}/BoarderSegmentation.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.BoarderSegmentation.nrrd"
  "5000"
  "150" )

 sitk_add_python_test( Example.N4BiasFieldCorrection
  "${CMAKE_CURRENT_SOURCE_DIR}/N4BiasFieldCorrection.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Example.N4BiasFieldCorrection.nrrd"
  "1" )

sitk_add_python_test( Example.ReadAndShow
  "${CMAKE_CURRENT_SOURCE_DIR}/ReadAndShow.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/VM1111Shrink-RGB.png} )

sitk_add_python_test( Example.GeodesicActiceContourSegmentation
  "${CMAKE_CURRENT_SOURCE_DIR}/GeodesicActiceContourSegmentation.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1.png}
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Example.GeodesicActiceContourSegmentation.nrrd"
  .3 10 .9 50 55
  )

sitk_add_python_test( Example.FFTConvolution
  "${CMAKE_CURRENT_SOURCE_DIR}/FFTConvolution.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1-Float.mha}
  DATA{${SimpleITK_DATA_ROOT}/Input/Gaussian_1.5.nrrd}
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Examples.FFTConvolution.nrrd"
  )


sitk_add_python_test( Example.DicomSeriesReader2
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader2.py"
  --compare-MD5
  "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader2.nrrd"
  "8e65f711d450b6b466c6d76a667ecb72"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader2.nrrd"
  )




sitk_add_python_test( Example.ConnectedThresholdImageFilter1
  "${CMAKE_CURRENT_SOURCE_DIR}/ConnectedThresholdImageFilter.py"
  --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold1.png"
    "d4ff9c512f9c18a84729677de800db0d"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold1.png"
  150 180
  60 116
  )

sitk_add_python_test( Example.ConnectedThresholdImageFilter2
  "${CMAKE_CURRENT_SOURCE_DIR}/ConnectedThresholdImageFilter.py"
  --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold2.png"
    "a9695df04cde5b9c5481d8c253a5b3aa"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold2.png"
  210 250
  81 112
  )

sitk_add_python_test( Example.NeighborhoodConnectedImageFilter1
  "${CMAKE_CURRENT_SOURCE_DIR}/NeighborhoodConnectedImageFilter.py"
  --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationNeighborhoodConnected1.png"
    "311d9d4b492e1ea625e3b0b295814dce"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationNeighborhoodConnected1.png"
  150 180
  60 116
  )


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


sitk_add_python_test( Example.ImageRegistrationMethod4Test1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod4.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test1.hdf5
  24 1.0
  )

sitk_add_python_test( Example.ImageRegistrationMethod4Test2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod4.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test2.hdf5
  24 0.1
  )

sitk_add_python_test( Example.ImageRegistrationMethod4Test3
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod4.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test3.hdf5
  5 0.4
  )


sitk_add_python_test(Example.ImageRegistrationMethodBSpline2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodBSpline2.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodBSpline2.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodBSpline2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline2.mha}
    0.02
  )

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

sitk_add_python_test(Example.DicomModifyTags
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomModifyTags.py"
   DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/Image0075.dcm}
   ${TEST_HARNESS_TEMP_DIRECTORY}/modifiedTags.dcm
  )
