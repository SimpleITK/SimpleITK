
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test(Example.ImageRegistrationMethodBSpline3
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodBSpline3.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethodBSpline3.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethodBSpline3.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline3.mha}
    0.02
  )
