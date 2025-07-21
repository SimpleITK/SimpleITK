if(NOT BUILD_TESTING)
  return()
endif()

set(
  out_dir
  "${SimpleITK_TEST_OUTPUT_DIR}/Python.DicomSeriesReadModifySeriesWrite"
)
file(MAKE_DIRECTORY ${out_dir})
sitk_add_python_test(
  Example.DicomSeriesReadModifySeriesWrite
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReadModifySeriesWrite.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
  "${out_dir}"
)

set(out_dir_r "${SimpleITK_TEST_OUTPUT_DIR}/R.DicomSeriesReadModifySeriesWrite")
file(MAKE_DIRECTORY ${out_dir_r})
sitk_add_r_test(
  Example.DicomSeriesReadModifySeriesWrite
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReadModifySeriesWrite.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
  "${out_dir_r}"
)

set(
  out_dir_cxx
  "${SimpleITK_TEST_OUTPUT_DIR}/Cxx.DicomSeriesReadModifySeriesWrite"
)
file(MAKE_DIRECTORY ${out_dir_cxx})

add_executable(
  DicomSeriesReadModifySeriesWrite
  DicomSeriesReadModifySeriesWrite.cxx
)
target_link_libraries(DicomSeriesReadModifySeriesWrite ${SimpleITK_LIBRARIES})
sitk_add_test(
  NAME CXX.Example.DicomSeriesReadModifySeriesWrite
  COMMAND
    $<TARGET_FILE:DicomSeriesReadModifySeriesWrite>
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
    "${out_dir_cxx}"
)

set(
  out_dir_cs
  "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.DicomSeriesReadModifySeriesWrite"
)
file(MAKE_DIRECTORY ${out_dir_cs})
sitk_add_csharp_test(
  Example.DicomSeriesReadModifySeriesWrite
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReadModifySeriesWrite.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
  "${out_dir_cs}"
)

set(
  out_dir_java
  "${SimpleITK_TEST_OUTPUT_DIR}/Java.DicomSeriesReadModifySeriesWrite"
)
file(MAKE_DIRECTORY ${out_dir_java})
sitk_add_java_test(
  Example.DicomSeriesReadModifySeriesWrite
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomSeriesReadModifySeriesWrite.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
  "${out_dir_java}"
)
