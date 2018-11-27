
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test( Example.AdvancedImageReading
  "${CMAKE_CURRENT_SOURCE_DIR}/AdvancedImageReading.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )

sitk_add_python_test( Example.AdvancedImageReading
  "${CMAKE_CURRENT_SOURCE_DIR}/AdvancedImageReading.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/BrainProtonDensitySlice.png} )
