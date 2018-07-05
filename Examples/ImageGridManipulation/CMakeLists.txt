
if ( NOT BUILD_TESTING )
  return ()
endif ()

sitk_add_python_test( Example.ImageGridManipulation
"${CMAKE_CURRENT_SOURCE_DIR}/ImageGridManipulation.py"
)

sitk_add_r_test( Example.ImageGridManipulation
"${CMAKE_CURRENT_SOURCE_DIR}/ImageGridManipulation.R"
)
