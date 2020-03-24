
if(NOT BUILD_TESTING)
  return()
endif()

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/Python.DicomSeriesFromArray")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_python_test( Example.DicomSeriesFromArray
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesFromArray.py"
    "${out_dir}"
    "float64"
  )

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/R.DicomSeriesFromArray")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_r_test( Example.DicomSeriesFromArray
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesFromArray.R"
    "${out_dir}"
    "int"
  )
