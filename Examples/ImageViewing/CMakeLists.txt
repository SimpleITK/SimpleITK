
if(NOT BUILD_TESTING)
  return()
endif()

if ( NOT SimpleITK_TESTING_NOSHOW )

sitk_add_python_test( Example.ImageViewing
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageViewing.py"
  )

sitk_add_r_test( Example.ImageViewing
  "${CMAKE_CURRENT_SOURCE_DIR}/ImageViewing.R"
  )

endif()
