

sitk_add_r_test( Example.DicomImagePrintTags
  "--file=${CMAKE_CURRENT_SOURCE_DIR}/DicomImagePrintTags.R"
  --args
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/Image0075.dcm}
  )

