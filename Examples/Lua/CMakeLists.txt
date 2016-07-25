sitk_add_lua_test( Example.SimpleGaussian
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.lua"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd}
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleGaussian.nrrd" )

sitk_add_lua_test( Example.DicomSeriesReader
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader.lua"
  --compare-MD5
  "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  "8e65f711d450b6b466c6d76a667ecb72"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  )

sitk_add_lua_test( Example.ImageRegistrationMethod1
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageRegistrationMethod1.lua"
    ${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySliceBorder20.png
    ${TEST_HARNESS_DATA_DIRECTORY}/Input/BrainProtonDensitySliceShifted13x17y.png
    ${TEST_HARNESS_TEMP_DIRECTORY}/LuaImageRegistrationMethod1Test.hdf5
  TRANSFORM_COMPARE
    ${TEST_HARNESS_TEMP_DIRECTORY}/LuaImageRegistrationMethod1Test.hdf5
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_13x17y.mha}
    0.02
    )

sitk_add_lua_test( Example.SimpleDerivative
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleDerivative.lua"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleDerivative.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleDerivative.nrrd}
    "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleDerivative.nrrd"
  )
