sitk_add_ruby_test( Example.SimpleGaussian
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.rb"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Ruby.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Ruby.SimpleGaussian.nrrd" )
