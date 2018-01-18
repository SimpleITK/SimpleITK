

if(NOT BUILD_TESTING)
  return()
endif()

#
# CXX Examples
#

sitk_add_test(NAME CXX.Example.SimpleGaussianFunctional
  COMMAND $<TARGET_FILE:SimpleGaussianFunctional>
     DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
     2.0
     "${SimpleITK_TEST_OUTPUT_DIR}/CXX.SimpleGaussianFunctional.nrrd"
   IMAGE_MD5_COMPARE
      "${SimpleITK_TEST_OUTPUT_DIR}/CXX.SimpleGaussianFunctional.nrrd"
      5ef06ed0d5d8952c770348699b70f23e

  )


sitk_add_test(NAME  CXX.Example.Segmentation.ConnectedThresholdImageFilter1
  COMMAND $<TARGET_FILE:ConnectedThresholdImageFilter>
      DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
      "${SimpleITK_TEST_OUTPUT_DIR}/CXXSegmentationConnectedThreshold1.png"
      150 180
      60 116
    IMAGE_MD5_COMPARE
      "${SimpleITK_TEST_OUTPUT_DIR}/CXXSegmentationConnectedThreshold1.png"
      "d4ff9c512f9c18a84729677de800db0d"

  )

sitk_add_test(NAME  CXX.Example.Segmentation.ConnectedThresholdImageFilter2
  COMMAND $<TARGET_FILE:ConnectedThresholdImageFilter>
      DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
      "${SimpleITK_TEST_OUTPUT_DIR}/CXXSegmentationConnectedThreshold2.png"
      210 250
      81 112
    IMAGE_MD5_COMPARE
      "${SimpleITK_TEST_OUTPUT_DIR}/CXXSegmentationConnectedThreshold2.png"
      "a9695df04cde5b9c5481d8c253a5b3aa"

  )

sitk_add_test( NAME CXX.Example.Segmentation.NeighborhoodConnectedImageFilter1
  COMMAND $<TARGET_FILE:NeighborhoodConnectedImageFilter>
      DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
      "${SimpleITK_TEST_OUTPUT_DIR}/CXXSegmentationNeighborhoodConnected1.png"
      150 180
      60 116
    IMAGE_MD5_COMPARE
      "${SimpleITK_TEST_OUTPUT_DIR}/CXXSegmentationNeighborhoodConnected1.png"
      "311d9d4b492e1ea625e3b0b295814dce"

  )








# This test currently does not compile or work
#
#  add_java_test( Example.ImageConnection
#    "${SimpleITK_SOURCE_DIR}/Examples/ImageConnection.java" )





