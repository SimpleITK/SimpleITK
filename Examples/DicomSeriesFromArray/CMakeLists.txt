if(NOT BUILD_TESTING)
  return()
endif()

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/Python.DicomSeriesFromArray")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_python_test(
  Example.DicomSeriesFromArray
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesFromArray.py"
  "${out_dir}"
  "float64"
)

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/R.DicomSeriesFromArray")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_r_test(
  Example.DicomSeriesFromArray
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesFromArray.R"
  "${out_dir}"
  "int"
)

add_executable(DicomSeriesFromArray DicomSeriesFromArray.cxx)
target_link_libraries(DicomSeriesFromArray ${SimpleITK_LIBRARIES})

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/CXX.DicomSeriesFromArray")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_test(
  NAME CXX.Example.DicomSeriesFromArray
  COMMAND
    $<TARGET_FILE:DicomSeriesFromArray> "${out_dir}" "float64"
)

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/Java.DicomSeriesFromArray")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_java_test(
  Example.DicomSeriesFromArray
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesFromArray.java"
  "${out_dir}"
  "float64"
)

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.DicomSeriesFromArray")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_csharp_test(
  Example.DicomSeriesFromArray
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesFromArray.cs"
  "${out_dir}"
  "float64"
)
