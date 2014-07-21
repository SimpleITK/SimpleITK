
#-----------------------------------------------------------------------------
# SimpleITK wrapper for add_test that automatically adds testing data...

function(sitk_add_test)
  # Add tests with data in the SimpleITKData group.
  ExternalData_add_test(SimpleITKData ${ARGN})

  if("NAME" STREQUAL "${ARGV0}")
    set(_iat_testname ${ARGV1})
  else()
    set(_iat_testname ${ARGV0})
  endif()

endfunction()


set(SITK_DATA_ROOT ${SimpleITK_SOURCE_DIR}/Testing/Data)

#
# Additional CXX tests
#
sitk_add_test(NAME TransformCompareDriver1
  COMMAND
    $<TARGET_FILE:sitkTransformCompareDriver>
    DATA{${SITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    DATA{${SITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
    DATA{${SITK_DATA_ROOT}/Input/cthead1-Float.mha}
    )
