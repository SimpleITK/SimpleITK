
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test( Example.SimpleGaussianProcedural
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussianProcedural.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${SimpleITK_TEST_OUTPUT_DIR}/Python.SimpleGaussianProcedural.nrrd"
  IMAGE_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/Python.SimpleGaussianProcedural.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd} )

sitk_add_python_test( Example.ImageCreateAndSet
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageCreateAndSet.py" )

sitk_add_python_test( Example.CannyEdge
  "${CMAKE_CURRENT_SOURCE_DIR}/CannyEdge.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd} )

sitk_add_python_test( Example.ExtractSlice
  "${CMAKE_CURRENT_SOURCE_DIR}/ExtractSlice.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "30"
  "${SimpleITK_TEST_OUTPUT_DIR}/Python.ExtractSlice.nrrd")

sitk_add_python_test( Example.BoarderSegmentation
  "${CMAKE_CURRENT_SOURCE_DIR}/BoarderSegmentation.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "${SimpleITK_TEST_OUTPUT_DIR}/Python.BoarderSegmentation.nrrd"
  "5000"
  "150" )

sitk_add_python_test( Example.ReadAndShow
  "${CMAKE_CURRENT_SOURCE_DIR}/ReadAndShow.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/VM1111Shrink-RGB.png} )

sitk_add_python_test( Example.GeodesicActiceContourSegmentation
  "${CMAKE_CURRENT_SOURCE_DIR}/GeodesicActiceContourSegmentation.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.GeodesicActiceContourSegmentation.nrrd"
  .3 10 .9 50 55
  )

sitk_add_python_test( Example.FFTConvolution
  "${CMAKE_CURRENT_SOURCE_DIR}/FFTConvolution.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1-Float.mha}
  DATA{${SimpleITK_DATA_ROOT}/Input/Gaussian_1.5.nrrd}
  "${SimpleITK_TEST_OUTPUT_DIR}/Python.Examples.FFTConvolution.nrrd"
  )


sitk_add_python_test( Example.DicomSeriesReader2
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader2.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${SimpleITK_TEST_OUTPUT_DIR}/DicomSeriesReader2.nrrd"
  IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/DicomSeriesReader2.nrrd"
    "8e65f711d450b6b466c6d76a667ecb72"

  )




sitk_add_python_test( Example.ConnectedThresholdImageFilter1
  "${CMAKE_CURRENT_SOURCE_DIR}/ConnectedThresholdImageFilter.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/PythonSegmentationConnectedThreshold1.png"
  150 180
  60 116
  IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/PythonSegmentationConnectedThreshold1.png"
    "d4ff9c512f9c18a84729677de800db0d"

  )

sitk_add_python_test( Example.ConnectedThresholdImageFilter2
  "${CMAKE_CURRENT_SOURCE_DIR}/ConnectedThresholdImageFilter.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/PythonSegmentationConnectedThreshold2.png"
  210 250
  81 112
  IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/PythonSegmentationConnectedThreshold2.png"
    "a9695df04cde5b9c5481d8c253a5b3aa"
  )

sitk_add_python_test( Example.NeighborhoodConnectedImageFilter1
  "${CMAKE_CURRENT_SOURCE_DIR}/NeighborhoodConnectedImageFilter.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/PythonSegmentationNeighborhoodConnected1.png"
  150 180
  60 116
  IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/PythonSegmentationNeighborhoodConnected1.png"
    "311d9d4b492e1ea625e3b0b295814dce"

  )


sitk_add_python_test(Example.DicomModifyTags
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomModifyTags.py"
   DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/Image0075.dcm}
   ${SimpleITK_TEST_OUTPUT_DIR}/modifiedTags.dcm
  )
