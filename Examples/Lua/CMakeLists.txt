
sitk_add_lua_test( Example.DicomSeriesReader
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader.lua"
  --compare-MD5
  "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  "8e65f711d450b6b466c6d76a667ecb72"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  )

sitk_add_lua_test( Example.SimpleDerivative
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleDerivative.lua"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleDerivative.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleDerivative.nrrd}
    "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleDerivative.nrrd"
  )
