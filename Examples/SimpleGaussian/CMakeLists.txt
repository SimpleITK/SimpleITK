

add_executable ( SimpleGaussian SimpleGaussian.cxx )
target_link_libraries ( SimpleGaussian ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_csharp_test( Example.SimpleGaussian
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/CSharp.SimpleGaussian.nrrd"
  IMAGE_COMPARE
    "${TEST_HARNESS_TEMP_DIRECTORY}/CSharp.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd} )

sitk_add_test(NAME CXX.Example.SimpleGaussian
  COMMAND $<TARGET_FILE:SimpleGaussian>
     DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
     2.0
     "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.SimpleGaussian.nrrd"
   IMAGE_MD5_COMPARE
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.SimpleGaussian.nrrd"
      5ef06ed0d5d8952c770348699b70f23e )

sitk_add_java_test( Example.SimpleGaussian
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Java.SimpleGaussian.nrrd"
  IMAGE_COMPARE
    "${TEST_HARNESS_TEMP_DIRECTORY}/Java.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd} )

sitk_add_lua_test( Example.SimpleGaussian
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.lua"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleGaussian.nrrd"
  IMAGE_COMPARE
    "${TEST_HARNESS_TEMP_DIRECTORY}/Lua.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd} )

sitk_add_python_test( Example.SimpleGaussian
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd"
  IMAGE_COMPARE
    "${TEST_HARNESS_TEMP_DIRECTORY}/Python.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd} )

sitk_add_r_test( Example.SimpleGaussian
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.R"
     DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
     "2.0"
     "${TEST_HARNESS_TEMP_DIRECTORY}/R.SimpleGaussian.nrrd"
  IMAGE_COMPARE
    "${TEST_HARNESS_TEMP_DIRECTORY}/R.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd} )

sitk_add_ruby_test( Example.SimpleGaussian
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.rb"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Ruby.SimpleGaussian.nrrd"
  IMAGE_COMPARE
    "${TEST_HARNESS_TEMP_DIRECTORY}/Ruby.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd} )

sitk_add_tcl_test( Example.SimpleGaussian
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.tcl"
  DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
  "2.0"
  "${TEST_HARNESS_TEMP_DIRECTORY}/Tcl.SimpleGaussian.nrrd"
  IMAGE_COMPARE
    "${TEST_HARNESS_TEMP_DIRECTORY}/Tcl.SimpleGaussian.nrrd"
    DATA{${SimpleITK_DATA_ROOT}/Baseline/Example_SimpleGaussian_2.0.nrrd} )
