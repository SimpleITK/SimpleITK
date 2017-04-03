
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test( Example.DicomSeriesReadModifySeriesWrite
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReadModifySeriesWrite.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries}
    ${TEST_HARNESS_TEMP_DIRECTORY}
  )
