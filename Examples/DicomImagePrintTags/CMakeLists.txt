sitk_add_python_test( Example.DicomImagePrintTags
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomImagePrintTags.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/Image0075.dcm}
  )
set_tests_properties( Python.Example.DicomImagePrintTags
  PROPERTIES PASS_REGULAR_EXPRESSION "\\(0008|0060\\) = = \"MR\"")

sitk_add_r_test( Example.DicomImagePrintTags
  "--file=${CMAKE_CURRENT_SOURCE_DIR}/DicomImagePrintTags.R"
  --args
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/Image0075.dcm}
  )
