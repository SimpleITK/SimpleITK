
add_executable ( DemonsRegistration2 DemonsRegistration2.cxx )
target_link_libraries ( DemonsRegistration2 ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.DemonsRegistration2
  COMMAND
   $<TARGET_FILE:DemonsRegistration2>
   DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
   DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
   DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
   ${SimpleITK_TEST_OUTPUT_DIR}/CXXDemonsRegistration2Test.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXDemonsRegistration2Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/DemonsRegistration2Test_displacement.mha}
    0.01
  )

sitk_add_python_test( Example.DemonsRegistration2
  "${CMAKE_CURRENT_SOURCE_DIR}/DemonsRegistration2.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonDemonsRegistration2Test.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/PythonDemonsRegistration2Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/DemonsRegistration2Test_displacement.mha}
    0.01
  )

sitk_add_r_test( Example.DemonsRegistration2
  "${CMAKE_CURRENT_SOURCE_DIR}/DemonsRegistration2.R"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    ${SimpleITK_TEST_OUTPUT_DIR}/RDemonsRegistration2Test.hdf5
  TRANSFORM_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/RDemonsRegistration2Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/DemonsRegistration2Test_displacement.mha}
    0.01
  )
