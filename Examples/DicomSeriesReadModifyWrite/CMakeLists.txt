
if(NOT BUILD_TESTING)
  return()
endif()

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/Python.DicomSeriesReadModifySeriesWrite")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_python_test( Example.DicomSeriesReadModifySeriesWrite
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReadModifySeriesWrite.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${out_dir}"
  )

sitk_add_r_test( Example.DicomSeriesReadModifySeriesWrite
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReadModifySeriesWrite.R"
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${out_dir}"
  )
