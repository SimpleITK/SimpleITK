add_executable(
  ImageRegistrationMethodBSpline2
  ImageRegistrationMethodBSpline2.cxx
)
target_link_libraries(ImageRegistrationMethodBSpline2 ${SimpleITK_LIBRARIES})

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(
  NAME CXX.Example.ImageRegistrationMethodBSpline2
  COMMAND
    $<TARGET_FILE:ImageRegistrationMethodBSpline2>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/CxxImageRegistrationMethodBSpline2.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CxxImageRegistrationMethodBSpline2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline2.mha,:}
    0.02
)

sitk_add_csharp_test(
  Example.ImageRegistrationMethodBSpline2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodBSpline2.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/CSharpImageRegistrationMethodBSpline2.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CSharpImageRegistrationMethodBSpline2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline2.mha,:}
    0.02
)

sitk_add_java_test(
  Example.ImageRegistrationMethodBSpline2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodBSpline2.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/JavaImageRegistrationMethodBSpline2.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/JavaImageRegistrationMethodBSpline2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline2.mha,:}
    0.02
)

sitk_add_python_test(
  Example.ImageRegistrationMethodBSpline2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodBSpline2.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethodBSpline2.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethodBSpline2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline2.mha,:}
    0.02
)

sitk_add_r_test(
  Example.ImageRegistrationMethodBSpline2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodBSpline2.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethodBSpline2.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethodBSpline2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline2.mha,:}
    0.02
)
