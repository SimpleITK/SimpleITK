
add_executable ( SliceBySliceDecorator SliceBySliceDecorator.cxx )
target_link_libraries ( SliceBySliceDecorator ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.SliceBySliceDecorator
      COMMAND
      $<TARGET_FILE:SliceBySliceDecorator>
        DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
        "${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.SliceBySliceDecorator.nrrd"
      IMAGE_COMPARE
        "${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.SliceBySliceDecorator.nrrd"
        DATA{${SimpleITK_DATA_ROOT}/Baseline/SliceBySliceDecorator.mha}
        0.005
      )


sitk_add_python_test( Example.SliceBySliceDecorator
        "${CMAKE_CURRENT_SOURCE_DIR}/SliceBySliceDecorator.py"
        DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
        "${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.SliceBySliceDecorator.nrrd"
      IMAGE_COMPARE
        "${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.SliceBySliceDecorator.nrrd"
        DATA{${SimpleITK_DATA_ROOT}/Baseline/SliceBySliceDecorator.mha}
        0.005
      )
