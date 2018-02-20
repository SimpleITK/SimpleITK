
add_executable ( DicomSeriesReader DicomSeriesReader.cxx )
target_link_libraries ( DicomSeriesReader ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.DicomSeriesReader
  COMMAND $<TARGET_FILE:DicomSeriesReader>
      DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
      "${SimpleITK_TEST_OUTPUT_DIR}/CXX.DicomSeriesReader.nrrd"
    IMAGE_MD5_COMPARE
      "${SimpleITK_TEST_OUTPUT_DIR}/CXX.DicomSeriesReader.nrrd"
      "8e65f711d450b6b466c6d76a667ecb72"

  )

sitk_add_python_test( Example.DicomSeriesReader
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${SimpleITK_TEST_OUTPUT_DIR}/DicomSeriesReader.nrrd"
  IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/DicomSeriesReader.nrrd"
    "8e65f711d450b6b466c6d76a667ecb72"
  )

sitk_add_lua_test( Example.DicomSeriesReader
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader.lua"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${SimpleITK_TEST_OUTPUT_DIR}/DicomSeriesReader.nrrd"
  IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/DicomSeriesReader.nrrd"
    "8e65f711d450b6b466c6d76a667ecb72"
  )

sitk_add_r_test( Example.DicomSeriesReader
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader.R"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${SimpleITK_TEST_OUTPUT_DIR}/RDicomSeriesReader.nrrd"
  IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/RDicomSeriesReader.nrrd"
    "8e65f711d450b6b466c6d76a667ecb72"
  )

sitk_add_java_test( Example.DicomSeriesReader
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReader.java"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${SimpleITK_TEST_OUTPUT_DIR}/Java.DicomSeriesReader.nrrd"
  IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/Java.DicomSeriesReader.nrrd"
    "8e65f711d450b6b466c6d76a667ecb72"
  )
