
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
    81 114 1.0 -0.5 3.0 100 110
  IMAGE_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXFastMarchingSegmentation1.mha
    DATA{${SimpleITK_DATA_ROOT}/Baseline/FastMarchingSegmentation1.mha}
    0.01
  )

sitk_add_python_test( Example.FastMarchingSegmentation1
  "${CMAKE_CURRENT_SOURCE_DIR}/FastMarchingSegmentation.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonFastMarchingSegmentation1.mha
    81 114 1.0 -0.5 3.0 100 110
  IMAGE_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonFastMarchingSegmentation1.mha
    DATA{${SimpleITK_DATA_ROOT}/Baseline/FastMarchingSegmentation1.mha}
    0.01
  )

sitk_add_csharp_test( Example.FastMarchingSegmentation1
  "${CMAKE_CURRENT_SOURCE_DIR}/FastMarchingSegmentation.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/CSharpFastMarchingSegmentation1.mha"
  81 114 1.0 -0.5 3.0 100 110
  IMAGE_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CSharpFastMarchingSegmentation1.mha
    DATA{${SimpleITK_DATA_ROOT}/Baseline/FastMarchingSegmentation1.mha}
    0.01
  )
