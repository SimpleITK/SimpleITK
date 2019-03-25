
add_executable ( FastMarchingSegmentation FastMarchingSegmentation.cxx  )
target_link_libraries ( FastMarchingSegmentation ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()


sitk_add_test(NAME CXX.Example.FastMarchingSegmentation1
  COMMAND
  $<TARGET_FILE:FastMarchingSegmentation>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXFastMarchingSegmentation1.mha
    81 114 1.0 -0.5 3.0 100 100
  IMAGE_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXFastMarchingSegmentation1.mha
    DATA{${SimpleITK_DATA_ROOT}/Baseline/FastMarchingSegmentation1.mha}
    0.01
  )
