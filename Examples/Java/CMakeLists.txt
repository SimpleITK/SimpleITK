
sitk_add_java_test( Example.SimpleGaussian
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.java"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Java.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Java.SimpleGaussian.nrrd" )

sitk_add_java_test( Example.FilterProgressReporting
  "${CMAKE_CURRENT_SOURCE_DIR}/FilterProgressReporting.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Java.FilterProgressReporting.nrrd"
  )
set_tests_properties( Java.Example.FilterProgressReporting
  PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )

