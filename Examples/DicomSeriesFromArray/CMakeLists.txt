
if(NOT BUILD_TESTING)
  return()
endif()

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/Python.DicomSeriesFromArray")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_python_test( Example.DicomSeriesFromArray
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesFromArray.py"
    "${out_dir}"
  )
