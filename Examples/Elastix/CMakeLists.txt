# Add individual cxx executables
add_executable(elx elx.cxx)
target_link_libraries(elx ${SimpleITK_LIBRARIES})

add_executable(tfx tfx.cxx)
target_link_libraries(tfx ${SimpleITK_LIBRARIES})

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(
  NAME CXX.Example.Elastix
  COMMAND
    $<TARGET_FILE:elx>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${CMAKE_CURRENT_SOURCE_DIR}/par0001.txt
    ${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.elx.nii
    ${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.elx.TransformParameters.txt
)

sitk_add_test(
  NAME CXX.Example.Transformix
  COMMAND
    $<TARGET_FILE:tfx>
    DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
    ${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.elx.TransformParameters.txt
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXT.Example.tfx.nii
  IMAGE_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.elx.nii
    ${SimpleITK_TEST_OUTPUT_DIR}/CXXT.Example.tfx.nii
    40
)

set_tests_properties(
  CXX.Example.Transformix
  PROPERTIES
    DEPENDS
      "CXX.Example.Elastix"
)

# Python tests
sitk_add_python_test(
  Example.Elastix
  "${CMAKE_CURRENT_SOURCE_DIR}/elx.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${CMAKE_CURRENT_SOURCE_DIR}/par0001.txt
  ${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.elx.nii
  ${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.elx.TransformParameters.txt
)

sitk_add_python_test(
  Example.Transformix
  "${CMAKE_CURRENT_SOURCE_DIR}/tfx.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.elx.TransformParameters.txt
  ${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.tfx.nii
  IMAGE_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.elx.nii
    ${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.tfx.nii
    40
)

set_tests_properties(
  Python.Example.Transformix
  PROPERTIES
    DEPENDS
      "Python.Example.Elastix"
)

# Java tests
sitk_add_java_test(
  Example.Elastix
  "${CMAKE_CURRENT_SOURCE_DIR}/elx.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${CMAKE_CURRENT_SOURCE_DIR}/par0001.txt
  ${SimpleITK_TEST_OUTPUT_DIR}/Java.Example.elx.nii
  ${SimpleITK_TEST_OUTPUT_DIR}/Java.Example.elx.TransformParameters.txt
)

sitk_add_java_test(
  Example.Transformix
  "${CMAKE_CURRENT_SOURCE_DIR}/tfx.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/Java.Example.elx.TransformParameters.txt
  ${SimpleITK_TEST_OUTPUT_DIR}/Java.Example.tfx.nii
  IMAGE_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/Java.Example.elx.nii
    ${SimpleITK_TEST_OUTPUT_DIR}/Java.Example.tfx.nii
    40
)

set_tests_properties(
  Java.Example.Transformix
  PROPERTIES
    DEPENDS
      "Java.Example.Elastix"
)

# CSharp tests
sitk_add_csharp_test(
  Example.Elastix
  "${CMAKE_CURRENT_SOURCE_DIR}/elx.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${CMAKE_CURRENT_SOURCE_DIR}/par0001.txt
  ${SimpleITK_TEST_OUTPUT_DIR}/CSharp.Example.elx.nii
  ${SimpleITK_TEST_OUTPUT_DIR}/CSharp.Example.elx.TransformParameters.txt
)

sitk_add_csharp_test(
  Example.Transformix
  "${CMAKE_CURRENT_SOURCE_DIR}/tfx.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/CSharp.Example.elx.TransformParameters.txt
  ${SimpleITK_TEST_OUTPUT_DIR}/CSharp.Example.tfx.nii
  IMAGE_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/CSharp.Example.elx.nii
    ${SimpleITK_TEST_OUTPUT_DIR}/CSharp.Example.tfx.nii
    40
)

set_tests_properties(
  CSharp.Example.Transformix
  PROPERTIES
    DEPENDS
      "CSharp.Example.Elastix"
)

# Lua tests
sitk_add_lua_test(
  Example.Elastix
  "${CMAKE_CURRENT_SOURCE_DIR}/elx.lua"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${CMAKE_CURRENT_SOURCE_DIR}/par0001.txt
  ${SimpleITK_TEST_OUTPUT_DIR}/Lua.Example.elx.nii
  ${SimpleITK_TEST_OUTPUT_DIR}/Lua.Example.elx.TransformParameters.txt
)

sitk_add_lua_test(
  Example.Transformix
  "${CMAKE_CURRENT_SOURCE_DIR}/tfx.lua"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/Lua.Example.elx.TransformParameters.txt
  ${SimpleITK_TEST_OUTPUT_DIR}/Lua.Example.tfx.nii
  IMAGE_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/Lua.Example.elx.nii
    ${SimpleITK_TEST_OUTPUT_DIR}/Lua.Example.tfx.nii
    40
)

set_tests_properties(
  Lua.Example.Transformix
  PROPERTIES
    DEPENDS
      "Lua.Example.Elastix"
)

# R tests
sitk_add_r_test(
  Example.Elastix
  "${CMAKE_CURRENT_SOURCE_DIR}/elx.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${CMAKE_CURRENT_SOURCE_DIR}/par0001.txt
  ${SimpleITK_TEST_OUTPUT_DIR}/R.Example.elx.nii
  ${SimpleITK_TEST_OUTPUT_DIR}/R.Example.elx.TransformParameters.txt
)

sitk_add_r_test(
  Example.Transformix
  "${CMAKE_CURRENT_SOURCE_DIR}/tfx.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${SimpleITK_TEST_OUTPUT_DIR}/R.Example.elx.TransformParameters.txt
  ${SimpleITK_TEST_OUTPUT_DIR}/R.Example.tfx.nii
  IMAGE_COMPARE
    ${SimpleITK_TEST_OUTPUT_DIR}/R.Example.elx.nii
    ${SimpleITK_TEST_OUTPUT_DIR}/R.Example.tfx.nii
    40
)

set_tests_properties(
  R.Example.Transformix
  PROPERTIES
    DEPENDS
      "R.Example.Elastix"
)
