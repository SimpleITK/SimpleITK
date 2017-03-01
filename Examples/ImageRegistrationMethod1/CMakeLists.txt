
add_executable ( ImageRegistrationMethod1 ImageRegistrationMethod1.cxx )
target_link_libraries ( ImageRegistrationMethod1 ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.ImageRegistrationMethod1
  COMMAND
  $<TARGET_FILE:ImageRegistrationMethod1>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXImageRegistrationMethod1Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/CXXImageRegistrationMethod1Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )

sitk_add_csharp_test( Example.ImageRegistrationMethod1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod1.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/CSharpImageRegistrationMethod11Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/CSharpImageRegistrationMethod11Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )

sitk_add_java_test( Example.ImageRegistrationMethod1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod1.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/JavaImageRegistrationMethod11Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/JavaImageRegistrationMethod11Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )

sitk_add_lua_test( Example.ImageRegistrationMethod1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod1.lua"
    ${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySliceBorder20.png
    ${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySliceShifted13x17y.png
    ${TEST_HARNESS_TEMP_DIRECTORY}/LuaImageRegistrationMethod1Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/LuaImageRegistrationMethod1Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
    )

sitk_add_python_test( Example.ImageRegistrationMethod1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod1.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod11Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/PythonImageRegistrationMethod11Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )

sitk_add_r_test( Example.ImageRegistrationMethod1
  "--file=${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod1.R"
  --args
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${TEST_HARNESS_TEMP_DIRECTORY}/RImageRegistrationMethod11Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/RImageRegistrationMethod11Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )

