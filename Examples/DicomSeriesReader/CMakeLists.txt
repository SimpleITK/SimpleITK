
add_executable ( DicomSeriesReader DicomSeriesReader.cxx )
target_link_libraries ( DicomSeriesReader ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.DicomSeriesReader
  COMMAND "${ITK_TEST_DRIVER}"
    --compare-MD5
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.DicomSeriesReader.nrrd"
      "8e65f711d450b6b466c6d76a667ecb72"
    $<TARGET_FILE:DicomSeriesReader>
      DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
      "${TEST_HARNESS_TEMP_DIRECTORY}/CXX.DicomSeriesReader.nrrd"
  )

sitk_add_python_test( Example.DicomSeriesReader
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader.py"
  --compare-MD5
  "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  "8e65f711d450b6b466c6d76a667ecb72"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  )

sitk_add_lua_test( Example.DicomSeriesReader
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader.lua"
  --compare-MD5
  "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  "8e65f711d450b6b466c6d76a667ecb72"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${TEST_HARNESS_TEMP_DIRECTORY}/DicomSeriesReader.nrrd"
  )

sitk_add_r_test( Example.DicomSeriesReader
  "--file=${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader.R"
  --compare-MD5
    "${TEST_HARNESS_TEMP_DIRECTORY}/RDicomSeriesReader.nrrd"
    "8e65f711d450b6b466c6d76a667ecb72"
  --args
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${TEST_HARNESS_TEMP_DIRECTORY}/RDicomSeriesReader.nrrd"
  )

