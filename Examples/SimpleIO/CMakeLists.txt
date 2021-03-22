

add_executable ( SimpleIO SimpleIO.cxx )
target_link_libraries ( SimpleIO ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.SimpleIO
  COMMAND $<TARGET_FILE:SimpleIO>
     DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png}
     "${SimpleITK_TEST_OUTPUT_DIR}/CXX.SimpleIO.png"
   IMAGE_COMPARE
     "${SimpleITK_TEST_OUTPUT_DIR}/CXX.SimpleIO.png"
     DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png} )

sitk_add_python_test( Example.SimpleIO
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleIO.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/Python.SimpleIO.png"
  IMAGE_COMPARE
      "${SimpleITK_TEST_OUTPUT_DIR}/Python.SimpleIO.png"
     DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png} )

sitk_add_r_test( Example.SimpleIO
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleIO.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/R.SimpleIO.png"
  IMAGE_COMPARE
  "${SimpleITK_TEST_OUTPUT_DIR}/R.SimpleIO.png"
     DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png} )

sitk_add_csharp_test( Example.SimpleIO
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleIO.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.SimpleIO.png"
  IMAGE_COMPARE
  "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.SimpleIO.png"
     DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png} )

sitk_add_java_test( Example.SimpleIO
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleIO.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/Java.SimpleIO.png"
  IMAGE_COMPARE
  "${SimpleITK_TEST_OUTPUT_DIR}/Java.SimpleIO.png"
     DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png} )

sitk_add_lua_test( Example.SimpleIO
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleIO.lua"
  DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/Lua.SimpleIO.png"
  IMAGE_COMPARE
  "${SimpleITK_TEST_OUTPUT_DIR}/Lua.SimpleIO.png"
     DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png} )

sitk_add_ruby_test( Example.SimpleIO
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleIO.rb"
  DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/Ruby.SimpleIO.png"
  IMAGE_COMPARE
  "${SimpleITK_TEST_OUTPUT_DIR}/Ruby.SimpleIO.png"
     DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png} )

sitk_add_tcl_test( Example.SimpleIO
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleIO.tcl"
  DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png}
  "${SimpleITK_TEST_OUTPUT_DIR}/Tcl.SimpleIO.png"
  IMAGE_COMPARE
  "${SimpleITK_TEST_OUTPUT_DIR}/Tcl.SimpleIO.png"
     DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.png} )
