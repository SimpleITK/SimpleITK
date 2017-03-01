
add_executable ( DemonsRegistration1 DemonsRegistration1.cxx )
target_link_libraries ( DemonsRegistration1 ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.DemonsRegistration1
  COMMAND
    $<TARGET_FILE:DemonsRegistration1>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXDemonsRegistration1Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXDemonsRegistration1Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/DemonsRegistration1Test_displacement.mha}
    0.01
  )

sitk_add_python_test(Example.DemonsRegistration1
  "${CMAKE_CURRENT_SOURCE_DIR}/DemonsRegistration1.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonDemonsRegistration1Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonDemonsRegistration1Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/DemonsRegistration1Test_displacement.mha}
    0.005
  )
