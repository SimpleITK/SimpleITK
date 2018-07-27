
add_executable ( ImageRegistrationMethodBSpline1 ImageRegistrationMethodBSpline1.cxx )
target_link_libraries ( ImageRegistrationMethodBSpline1 ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.ImageRegistrationMethodBSpline1
  COMMAND
    $<TARGET_FILE:ImageRegistrationMethodBSpline1>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXImageRegistrationMethodBSpline1.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXImageRegistrationMethodBSpline1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline1.mha}
    0.02
  )


sitk_add_python_test(Example.ImageRegistrationMethodBSpline1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodBSpline1.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethodBSpline1.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethodBSpline1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline1.mha}
    0.02
  )

sitk_add_r_test(Example.ImageRegistrationMethodBSpline1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodBSpline1.R"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethodBSpline1.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethodBSpline1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodBSpline1.mha}
    0.02
  )
