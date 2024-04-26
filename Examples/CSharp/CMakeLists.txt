
if(NOT BUILD_TESTING)
  return()
endif()

#
# CSharp Examples
#


sitk_add_csharp_test( Example.ImageGetSetBuffer
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageGetSetBuffer.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.SetBuffer.png"
  IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.SetBuffer.png"
    "0f67e91f82674c0e8560f17653fa9d59"
  )

sitk_add_csharp_test( Example.ConnectedThresholdSegmentation
  "${CMAKE_CURRENT_SOURCE_DIR}/ConnectedThresholdSegmentation.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.ConnectedThresholdOutput2.png"
      210 250
      81 112
  IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.ConnectedThresholdOutput2.png"
    "a9695df04cde5b9c5481d8c253a5b3aa"
  )

sitk_add_csharp_test( Example.CannySegmentationLevelSetImageFilter
  "${CMAKE_CURRENT_SOURCE_DIR}/CannySegmentationLevelSetImageFilter.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/ThresholdSegmentationLevelSetVentricle.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.CannySegmentationLevelSetImageFilter.png"
      7.0 0.1 -10.0
      127.5 15
  IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.CannySegmentationLevelSetImageFilter.png"
    "a275b65bab21559f1398e4cf5765938a")
