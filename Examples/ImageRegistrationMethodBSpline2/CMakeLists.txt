
if(NOT BUILD_TESTING)
  return()
endif()

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
