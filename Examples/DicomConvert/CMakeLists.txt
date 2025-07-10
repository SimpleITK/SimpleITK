add_executable(DicomConvert DicomConvert.cxx)
target_link_libraries(DicomConvert ${SimpleITK_LIBRARIES})

if(NOT BUILD_TESTING)
  return()
endif()

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/Python.DicomConvert")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_python_test(
  Example.DicomConvert
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomConvert.py"
  DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
  jpg
  --od
  "${out_dir}"
  --w
  64
)

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/R.DicomConvert")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_r_test(
  Example.DicomConvert
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomConvert.R"
  DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
  jpg
  --od
  "${out_dir}"
  --w
  64
)

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/Java.DicomConvert")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_java_test(
  Example.DicomConvert
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomConvert.java"
  DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
  jpg
  --w
  64
  --od
  "${out_dir}"
)

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/CSharp.DicomConvert")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_csharp_test(
  Example.DicomConvert
  "${CMAKE_CURRENT_SOURCE_DIR}/DicomConvert.cs"
  DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm}
  jpg
  --w
  64
  --od
  "${out_dir}"
)

set(out_dir "${SimpleITK_TEST_OUTPUT_DIR}/Cpp.DicomConvert")
file(MAKE_DIRECTORY ${out_dir})
sitk_add_test(
  NAME CXX.Example.DicomConvert
  COMMAND
    $<TARGET_FILE:DicomConvert>
    DATA{${SimpleITK_DATA_ROOT}/Input/DicomSeries/Image0076.dcm}
    "${out_dir}/result.jpg" --w 64
)
