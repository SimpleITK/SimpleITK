
#
# Additional CXX tests
#
sitk_add_test(NAME CompareDriver1
  COMMAND
    $<TARGET_FILE:sitkCompareDriver>
    --compareTransform
      DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
      DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
  )

sitk_add_test(NAME CompareDriver2
  COMMAND
    ${CMAKE_COMMAND} -E echo "Running command"
  TRANSFORM_COMPARE
    DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
  )
