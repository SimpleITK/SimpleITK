#
# CSharp Examples
#
sitk_add_csharp_test( Example.SimpleGaussian
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.cs"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/CSharp.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/CSharp.SimpleGaussian.nrrd" )

sitk_add_csharp_test( Example.ImageGetBuffer
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageGetBuffer.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd})
set_tests_properties( CSharp.Example.ImageGetBuffer
  PROPERTIES PASS_REGULAR_EXPRESSION "total: 1009713" )

sitk_add_csharp_test( Example.FilterProgressReporting
  "${CMAKE_CURRENT_SOURCE_DIR}/FilterProgressReporting.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/CSharp.FilterProgressReporting.nrrd"
  )
set_tests_properties( CSharp.Example.FilterProgressReporting
  PROPERTIES PASS_REGULAR_EXPRESSION "DiscreteGaussianImageFilter Progress" )


sitk_add_csharp_test( Example.ImageRegistrationMethod1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod1.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceBorder20.png}
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySliceShifted13x17y.png}
  ${TEST_HARNESS_TEMP_DIRECTORY}/CSharpImageRegistrationMethod11Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/CSharpImageRegistrationMethod11Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
  )
