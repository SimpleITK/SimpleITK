# Add individual cxx executables
add_executable ( elx elx.cxx )
target_link_libraries ( elx ${SimpleITK_LIBRARIES} )

add_executable ( tfx tfx.cxx )
target_link_libraries ( tfx ${SimpleITK_LIBRARIES} )


if ( NOT BUILD_TESTING )
  return ()
endif ()

sitk_add_test(NAME CXX.Example.Elastix
  COMMAND
  $<TARGET_FILE:elx>
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${CMAKE_CURRENT_SOURCE_DIR}/par0001.txt
  ${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.elx.nii
  ${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.elx.TransformParameters.txt
  )

sitk_add_test(NAME CXX.Example.Transformix
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

set_tests_properties(CXX.Example.Transformix PROPERTIES DEPENDS "CXX.Example.Elastix")
