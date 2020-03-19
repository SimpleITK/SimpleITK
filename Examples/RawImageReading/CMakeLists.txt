
if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_python_test( Example.RawImageReading
  "${CMAKE_CURRENT_SOURCE_DIR}/RawImageReading.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/cxr.raw}
    "${SimpleITK_TEST_OUTPUT_DIR}/Python.little_endian.nrrd"
    false
    sitkUInt16 204 204
    IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/Python.little_endian.nrrd"
    c28bdf1f700f30a80ad5bf75c1087ed3
    )

sitk_add_python_test( Example.RawImageReading_BigEndian
  "${CMAKE_CURRENT_SOURCE_DIR}/RawImageReading.py"
    DATA{${SimpleITK_DATA_ROOT}/Input/cxr.raw}
    "${SimpleITK_TEST_OUTPUT_DIR}/Python.big_endian.nrrd"
    true
    sitkUInt16 204 204
    IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/Python.big_endian.nrrd"
    057b75854302ac4d73b2da723a01240a
  )

sitk_add_r_test( Example.RawImageReading
  "${CMAKE_CURRENT_SOURCE_DIR}/RawImageReading.R"
    DATA{${SimpleITK_DATA_ROOT}/Input/cxr.raw}
    "${SimpleITK_TEST_OUTPUT_DIR}/R.little_endian.nrrd"
    false
    sitkUInt16 204 204
    IMAGE_MD5_COMPARE
    "${SimpleITK_TEST_OUTPUT_DIR}/R.little_endian.nrrd"
    c28bdf1f700f30a80ad5bf75c1087ed3
  )
