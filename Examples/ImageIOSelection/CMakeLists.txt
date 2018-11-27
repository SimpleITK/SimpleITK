
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test( Example.ImageIOSelection
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageIOSelection.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )

sitk_add_python_test( Example.IOSelection
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageIOSelection.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )
