# Add C++ executables
add_executable(ParameterMaps ParameterMaps.cxx)
target_link_libraries(ParameterMaps ${SimpleITK_LIBRARIES})

if(NOT BUILD_TESTING)
  return()
endif()

# C++ test
sitk_add_test(
  NAME CXX.Example.ParameterMaps
  COMMAND
    $<TARGET_FILE:ParameterMaps>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.ParameterMaps
)

# Python test
sitk_add_python_test(
  Example.ParameterMaps
  "${CMAKE_CURRENT_SOURCE_DIR}/ParameterMaps.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.ParameterMaps
)

# Java test
sitk_add_java_test(
  Example.ParameterMaps
  "${CMAKE_CURRENT_SOURCE_DIR}/ParameterMaps.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/Java.Example.ParameterMaps
)

# C# test
sitk_add_csharp_test(
  Example.ParameterMaps
  "${CMAKE_CURRENT_SOURCE_DIR}/ParameterMaps.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/CSharp.Example.ParameterMaps
)

# Lua test
sitk_add_lua_test(
  Example.ParameterMaps
  "${CMAKE_CURRENT_SOURCE_DIR}/ParameterMaps.lua"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/Lua.Example.ParameterMaps
)

# R test
sitk_add_r_test(
  Example.ParameterMaps
  "${CMAKE_CURRENT_SOURCE_DIR}/ParameterMaps.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/R.Example.ParameterMaps
)
