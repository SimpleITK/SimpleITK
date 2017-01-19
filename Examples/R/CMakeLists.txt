
sitk_add_r_test( Example.DicomSeriesReader
  "--file=${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader.R"
  --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/RDicomSeriesReader.nrrd"
    "8e65f711d450b6b466c6d76a667ecb72"
  --args
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${TEST_HARNESS_TEMP_DIRECTORY}/RDicomSeriesReader.nrrd"
  )


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
