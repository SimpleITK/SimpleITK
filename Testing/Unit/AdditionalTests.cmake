
#
# Additional CXX tests
#
sitk_add_test(NAME TransformCompareDriver1
  COMMAND
    $<TARGET_FILE:sitkTransformCompareDriver>
    DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
  )

sitk_add_test(NAME TransformCompareDriver2
  COMMAND
    ${CMAKE_COMMAND} -E echo "Running command"
  TRANSFORM_COMPARE
    DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
  )



if ( WRAP_PYTHON )
  #
  # Python Examples
  #
  sitk_add_python_test( Example.SimpleGaussian
    "${SimpleITK_SOURCE_DIR}/Examples/SimpleGaussian.py"
    --compare
      "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd"
      DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd" )

  sitk_add_python_test( Example.SimpleGaussianProcedural
    "${SimpleITK_SOURCE_DIR}/Examples/SimpleGaussianProcedural.py"
    --compare
      "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussianProcedural.nrrd"
      DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussianProcedural.nrrd" )

  sitk_add_python_test( Example.ImageCreateAndSet
    "${SimpleITK_SOURCE_DIR}/Examples/ImageCreateAndSet.py" )

  sitk_add_python_test( Example.CannyEdge
    "${SimpleITK_SOURCE_DIR}/Examples/CannyEdge.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd} )

  sitk_add_python_test( Example.ExtractSlice
    "${SimpleITK_SOURCE_DIR}/Examples/ExtractSlice.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
    "30"
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.ExtractSlice.nrrd")

  sitk_add_python_test( Example.BoarderSegmentation
    "${SimpleITK_SOURCE_DIR}/Examples/BoarderSegmentation.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.BoarderSegmentation.nrrd"
    "5000"
    "150" )

 sitk_add_python_test( Example.N4BiasFieldCorrection
    "${SimpleITK_SOURCE_DIR}/Examples/N4BiasFieldCorrection.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Example.N4BiasFieldCorrection.nrrd"
    "1" )

  sitk_add_python_test( Example.ReadAndShow
    "${SimpleITK_SOURCE_DIR}/Examples/ReadAndShow.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/VM1111Shrink-RGB.png} )

  sitk_add_python_test( Example.GeodesicActiceContourSegmentation
    "${SimpleITK_SOURCE_DIR}/Examples/GeodesicActiceContourSegmentation.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/cthead1.png}
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Example.GeodesicActiceContourSegmentation.nrrd"
    .3 10 .9 50 55
    )

  sitk_add_python_test( Example.FFTConvolution
    "${SimpleITK_SOURCE_DIR}/Examples/FFTConvolution.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/cthead1-Float.mha}
    DATA{${SimpleITK_DATA_ROOT}/Input/Gaussian_1.5.nrrd}
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.Examples.FFTConvolution.nrrd"
    )

  sitk_add_python_test( Example.FilterProgressReporting
    "${SimpleITK_SOURCE_DIR}/Examples/FilterProgressReporting.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    "2.0"
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonFilterProgressReporting.nrrd"
    )

  sitk_add_python_test( Example.DicomSeriesReader
    "${SimpleITK_SOURCE_DIR}/Examples/DicomSeriesReader.py"
    --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
    "8e65f711d450b6b466c6d76a667ecb72"
      DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
      "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
    )

  set_tests_properties( Python.Example.FilterProgressReporting
    PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )

  sitk_add_python_test( Example.Segmentation.ConnectedThresholdImageFilter1
    "${SimpleITK_SOURCE_DIR}/Examples/Segmentation/ConnectedThresholdImageFilter.py"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold1.png"
      "d4ff9c512f9c18a84729677de800db0d"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold1.png"
    150 180
    60 116
    )

  sitk_add_python_test( Example.Segmentation.ConnectedThresholdImageFilter2
    "${SimpleITK_SOURCE_DIR}/Examples/Segmentation/ConnectedThresholdImageFilter.py"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold2.png"
      "a9695df04cde5b9c5481d8c253a5b3aa"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationConnectedThreshold2.png"
    210 250
    81 112
    )

  sitk_add_python_test( Example.Segmentation.NeighborhoodConnectedImageFilter1
    "${SimpleITK_SOURCE_DIR}/Examples/Segmentation/NeighborhoodConnectedImageFilter.py"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationNeighborhoodConnected1.png"
      "311d9d4b492e1ea625e3b0b295814dce"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    "${TEST_HARNESS_TEMP_DIRECTORY}/PythonSegmentationNeighborhoodConnected1.png"
    150 180
    60 116
    )

  sitk_add_python_test( Example.ImageRegistrationMethod1
    "${SimpleITK_SOURCE_DIR}/Examples/ImageRegistrationMethod1.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod11Test.hdf5
    )

  sitk_add_python_test( Example.ImageRegistrationMethod2
    "${SimpleITK_SOURCE_DIR}/Examples/ImageRegistrationMethod2.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod2Test.hdf5
    )

  sitk_add_python_test( Example.ImageRegistrationMethod4Test1
    "${SimpleITK_SOURCE_DIR}/Examples/ImageRegistrationMethod4.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test1.hdf5
    24 1.0
    )

  sitk_add_python_test( Example.ImageRegistrationMethod4Test2
    "${SimpleITK_SOURCE_DIR}/Examples/ImageRegistrationMethod4.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test2.hdf5
    24 0.1
    )

  sitk_add_python_test( Example.ImageRegistrationMethod4Test3
    "${SimpleITK_SOURCE_DIR}/Examples/ImageRegistrationMethod4.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod4Test3.hdf5
    5 0.4
    )



  sitk_add_python_test(Example.DemonsRegistration1
      "${SimpleITK_SOURCE_DIR}/Examples/DemonsRegistration1.py"
      DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
      DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
      ${TEST_HARNESS_TEMP_DIRECTORY}/PythonDemonsRegistration1Test.hdf5
    )

  sitk_add_python_test(Example.DemonsRegistration2
      "${SimpleITK_SOURCE_DIR}/Examples/DemonsRegistration2.py"
      DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
      DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
      DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
      ${TEST_HARNESS_TEMP_DIRECTORY}/PythonDemonsRegistration2Test.hdf5
    )


  #
  # Python Tests
  #
  sitk_add_python_test( Test.ImageTests
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkImageTests.py" )
  sitk_add_python_test( Test.ImageIndexing
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/ImageIndexingTest.py" )

  sitk_add_python_test( Test.IOTest
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/IOTest.py"
    "${TEST_HARNESS_TEMP_DIRECTORY}")

  # Numpy test.
  sitk_add_python_test( Test.Numpy
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkNumpyArrayConversionTest.py"
  )

 sitk_add_python_test( Test.ProcessObject
    "${SimpleITK_SOURCE_DIR}/Testing/Unit/sitkProcessObjectTest.py"
  )



endif( WRAP_PYTHON )
