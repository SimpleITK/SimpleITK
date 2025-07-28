add_executable(ImageRegistrationMethod3 ImageRegistrationMethod3.cxx)
target_link_libraries(ImageRegistrationMethod3 ${SimpleITK_LIBRARIES})

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(
  NAME CXX.Example.ImageRegistrationMethod3Test1
  COMMAND
    $<TARGET_FILE:ImageRegistrationMethod3>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXImageRegistrationMethod3Test1.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXImageRegistrationMethod3Test1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test1.mha}
    0.02
)

sitk_add_test(
  NAME CXX.Example.ImageRegistrationMethod3Test2
  COMMAND
    $<TARGET_FILE:ImageRegistrationMethod3>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17S12.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXImageRegistrationMethod3Test2.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXImageRegistrationMethod3Test2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test2.mha}
    0.03
)

sitk_add_csharp_test(
  Example.ImageRegistrationMethod3Test1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod3.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/CSharpImageRegistrationMethod3Test1.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CSharpImageRegistrationMethod3Test1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test1.mha}
    0.02
)

sitk_add_csharp_test(
  Example.ImageRegistrationMethod3Test2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod3.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17S12.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/CSharpImageRegistrationMethod3Test2.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CSharpImageRegistrationMethod3Test2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test2.mha}
    0.03
)

sitk_add_java_test(
  Example.ImageRegistrationMethod3Test1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod3.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/JavaImageRegistrationMethod3Test1.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/JavaImageRegistrationMethod3Test1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test1.mha}
    0.02
)

sitk_add_java_test(
  Example.ImageRegistrationMethod3Test2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod3.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17S12.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/JavaImageRegistrationMethod3Test2.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/JavaImageRegistrationMethod3Test2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test2.mha}
    0.03
)

sitk_add_python_test(
  Example.ImageRegistrationMethod3Test1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod3.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethod3Test1.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethod3Test1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test1.mha}
    0.02
)

sitk_add_python_test(
  Example.ImageRegistrationMethod3Test2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod3.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17S12.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethod3Test2.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethod3Test2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test2.mha}
    0.03
)

sitk_add_r_test(
  Example.ImageRegistrationMethod3Test1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod3.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethod3Test1.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethod3Test1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test1.mha}
    0.02
)

sitk_add_r_test(
  Example.ImageRegistrationMethod3Test2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod3.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceR10X13Y17S12.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethod3Test2.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethod3Test2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethod3Test2.mha}
    0.03
)
