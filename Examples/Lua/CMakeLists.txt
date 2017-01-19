

sitk_add_lua_test( Example.SimpleDerivative
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleDerivative.lua"
  --compare
    "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleDerivative.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleDerivative.nrrd}
    "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleDerivative.nrrd"
  )
