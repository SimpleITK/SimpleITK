
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test( Example.ImageRegistrationMethod4Test1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod4.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethod4Test1.hdf5
  24 1.0
  )

sitk_add_python_test( Example.ImageRegistrationMethod4Test2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod4.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethod4Test2.hdf5
  24 0.1
  )

sitk_add_python_test( Example.ImageRegistrationMethod4Test3
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod4.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonImageRegistrationMethod4Test3.hdf5
  5 0.4
  )

sitk_add_r_test( Example.ImageRegistrationMethod4Test1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod4.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethod4Test1.hdf5
  24 1.0
  )

sitk_add_r_test( Example.ImageRegistrationMethod4Test2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod4.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainT1SliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethod4Test2.hdf5
  24 0.1
  )

sitk_add_r_test( Example.ImageRegistrationMethod4Test3
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod4.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20Mask.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/RImageRegistrationMethod4Test3.hdf5
  5 0.4
  )
