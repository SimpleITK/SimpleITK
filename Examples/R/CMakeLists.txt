

sitk_add_r_test( Example.DicomImagePrintTags
  "--file=${CMAKE_CURRENT_SOURCE_DIR}/DicomImagePrintTags.R"
  --args
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/Image0075.dcm}
  )

sitk_add_r_test( Example.FilterProgressReporting
  "--file=${CMAKE_CURRENT_SOURCE_DIR}/FilterProgressReporting.R"
  --args
    DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd}
    2.0
    "${TEST_HARNESS_TEMP_DIRECTORY}/R.FilterProgressReporting.nrrd"
  )
