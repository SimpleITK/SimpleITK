
add_executable ( ImageRegistrationMethodDisplacement1 ImageRegistrationMethodDisplacement1.cxx )
target_link_libraries ( ImageRegistrationMethodDisplacement1  ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.ImageRegistrationMethodDisplacement1
  COMMAND
    $<TARGET_FILE:ImageRegistrationMethodDisplacement1>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/ImageRegistrationMethodDisplacement1.hdf5
 TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/ImageRegistrationMethodDisplacement1.hdf5
     DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodDisplacement1.mha}
    0.02
  )


sitk_add_test(NAME CXX.Example.ImageRegistrationMethodDisplacement1Test2
  COMMAND
    $<TARGET_FILE:ImageRegistrationMethodDisplacement1>
    DATA{${SimpleITK_DATA_ROOT}/Input/r16slice_rigid.nii.gz}
    DATA{${SimpleITK_DATA_ROOT}/Input/r64slice.nii.gz}
    ${TEST_HARNESS_TEMP_DIRECTORY}/ImageRegistrationMethodDisplacement1Test2.hdf5
 TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/ImageRegistrationMethodDisplacement1Test2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodDisplacement1Test2.mha}
    0.02
  )


sitk_add_python_test(Example.ImageRegistrationMethodDisplacement1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodDisplacement1.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBSplined10.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodDisplacement1.hdf5
 TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodDisplacement1.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodDisplacement1.mha}
    0.02
  )

sitk_add_python_test(Example.ImageRegistrationMethodDisplacement1Test2
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethodDisplacement1.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/r16slice_rigid.nii.gz}
    DATA{${SimpleITK_DATA_ROOT}/Input/r64slice.nii.gz}
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodDisplacement1Test2.hdf5
 TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethodDisplacement1Test2.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/ImageRegistrationMethodDisplacement1Test2.mha}
    0.02
  )

