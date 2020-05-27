
if(NOT BUILD_TESTING)
  return()
endif()

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/Python.DicomConvert")
file(MAKE_DIRECTORY ${out_dir})

sitk_add_python_test( Example.DicomConvert
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomConvert.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
  jpg
  --od "${out_dir}"
  --w 64
  )
