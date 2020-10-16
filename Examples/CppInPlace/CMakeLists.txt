
add_executable ( CppInPlace CppInPlace.cxx )
target_link_libraries ( CppInPlace ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.CppInPlace
      COMMAND
      $<TARGET_FILE:CppInPlace>
        DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
        "${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.CppInPlace.nrrd"
        1 2
      IMAGE_COMPARE
        "${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.CppInPlace.nrrd"
        DATA{${SimpleITK_DATA_ROOT}/Baseline/CppInPlace.mha}
        0.01
        )
