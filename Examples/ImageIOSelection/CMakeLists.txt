
if(NOT BUILD_TESTING)
  return()
endif()


add_executable ( ImageIOSelection ImageIOSelection.cxx )
target_link_libraries ( ImageIOSelection ${SimpleITK_LIBRARIES} )


sitk_add_test( NAME CXX.Example.ImageIOSelection
  COMMAND $<TARGET_FILE:ImageIOSelection>
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )

sitk_add_python_test( Example.ImageIOSelection
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageIOSelection.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )

sitk_add_r_test( Example.ImageIOSelection
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageIOSelection.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )

sitk_add_java_test( Example.ImageIOSelection
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageIOSelection.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )

sitk_add_lua_test( Example.ImageIOSelection
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageIOSelection.lua"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )

sitk_add_ruby_test( Example.ImageIOSelection
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageIOSelection.rb"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )

sitk_add_tcl_test( Example.ImageIOSelection
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageIOSelection.tcl"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )

sitk_add_csharp_test( Example.ImageIOSelection
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageIOSelection.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )
