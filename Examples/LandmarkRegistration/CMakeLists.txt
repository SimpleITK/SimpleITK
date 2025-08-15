add_executable(LandmarkRegistration LandmarkRegistration.cxx)
target_link_libraries(LandmarkRegistration ${SimpleITK_LIBRARIES})

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_csharp_test(
  Example.LandmarkRegistration
  "${CMAKE_CURRENT_SOURCE_DIR}/LandmarkRegistration.cs"
  ${SimpleITK_TEST_OUTPUT_DIR}/CSharpLandmarkRegistration.hdf5
)

sitk_add_test(
  NAME CXX.Example.LandmarkRegistration
  COMMAND
    $<TARGET_FILE:LandmarkRegistration>
    ${SimpleITK_TEST_OUTPUT_DIR}/CxxLandmarkRegistration.hdf5
)

sitk_add_java_test(
  Example.LandmarkRegistration
  "${CMAKE_CURRENT_SOURCE_DIR}/LandmarkRegistration.java"
  ${SimpleITK_TEST_OUTPUT_DIR}/JavaLandmarkRegistration.hdf5
)

sitk_add_python_test(
  Example.LandmarkRegistration
  "${CMAKE_CURRENT_SOURCE_DIR}/LandmarkRegistration.py"
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonLandmarkRegistration.hdf5
)

sitk_add_r_test(
  Example.LandmarkRegistration
  "${CMAKE_CURRENT_SOURCE_DIR}/LandmarkRegistration.R"
  ${SimpleITK_TEST_OUTPUT_DIR}/RLandmarkRegistration.hdf5
)
