
if(NOT BUILD_TESTING)
  return()
endif()

 sitk_add_python_test( Example.N4BiasFieldCorrection
  "${CMAKE_CURRENT_SOURCE_DIR}/N4BiasFieldCorrection.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.N4BiasFieldCorrection.nrrd"
  "1" )

 sitk_add_python_test( Example.N4BiasFieldCorrection_2
  "${CMAKE_CURRENT_SOURCE_DIR}/N4BiasFieldCorrection.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.N4BiasFieldCorrection_2.nrrd"
  "2" )


 sitk_add_r_test( Example.N4BiasFieldCorrection
  "${CMAKE_CURRENT_SOURCE_DIR}/N4BiasFieldCorrection.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "${SimpleITK_TEST_OUTPUT_DIR}/R.Example.N4BiasFieldCorrection.nrrd"
  "1" )

 sitk_add_r_test( Example.N4BiasFieldCorrection_2
  "${CMAKE_CURRENT_SOURCE_DIR}/N4BiasFieldCorrection.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
  "${SimpleITK_TEST_OUTPUT_DIR}/R.Example.N4BiasFieldCorrection_2.nrrd"
  "2" )
