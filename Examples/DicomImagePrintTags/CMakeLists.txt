
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test( Example.DicomImagePrintTags
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomImagePrintTags.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/Image0075.dcm}
  )
if( WRAP_PYTHON )
  set_tests_properties( Python.Example.DicomImagePrintTags
    PROPERTIES PASS_REGULAR_EXPRESSION "\\(0008|0060\\) = = \"MR\"")
endif()

sitk_add_r_test( Example.DicomImagePrintTags
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomImagePrintTags.R"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/Image0075.dcm}
  )
if(WRAP_R)
  set_tests_properties( R.Example.DicomImagePrintTags
    PROPERTIES PASS_REGULAR_EXPRESSION "\\(0008|0060\\) = = \"MR\"")
endif()
