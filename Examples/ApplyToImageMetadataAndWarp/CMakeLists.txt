if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test(
  Example.ApplyToImageMetadataAndWarp
  "${CMAKE_CURRENT_SOURCE_DIR}/ApplyToImageMetadataAndWarp.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1-Float.mha}
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1-dis1.nrrd}
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonApplyToImageMetadataAndWarpTest.mha
)

sitk_add_python_test(
  Example.ApplyToImageMetadataAndWarp.CompareToCompositeTransform
  "${CMAKE_CURRENT_SOURCE_DIR}/CompareToCompositeTransform.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1-Float.mha}
  DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
  DATA{${SimpleITK_DATA_ROOT}/Input/cthead1-dis1.nrrd}
  ${SimpleITK_TEST_OUTPUT_DIR}/PythonApplyToImageMetadataAndWarpTest.mha
)

if(WRAP_PYTHON)
  set_tests_properties(
    Python.Example.ApplyToImageMetadataAndWarp
    PROPERTIES
      FIXTURES_SETUP
        ApplyToImageMetadataAndWarpOutput
  )
  set_tests_properties(
    Python.Example.ApplyToImageMetadataAndWarp.CompareToCompositeTransform
    PROPERTIES
      FIXTURES_REQUIRED
        ApplyToImageMetadataAndWarpOutput
  )
endif()
