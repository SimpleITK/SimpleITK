
if(NOT BUILD_TESTING)
  return()
endif()

set(out_dir "${TEST_HARNESS_TEMP_DIRECTORY}/Python.DicomSeriesFromArray")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_python_test( Example.DicomSeriesFromArray
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesFromArray.py"
    "${out_dir}"
  )
