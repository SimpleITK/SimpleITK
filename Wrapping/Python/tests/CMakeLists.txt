include(sitkAddTest)
include(sitkGenerateFilterSource)
#
# Python Tests
#
sitk_add_pytest_test(
  Test.ImageTests
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageTests.py"
)

sitk_add_pytest_test(
  Test.BasicFiltersTests
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkBasicFilterTests.py"
)

sitk_add_pytest_test(
  Test.TransformTests
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkTransformTests.py"
)

sitk_add_pytest_test(
  Test.ImageIndexing
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageIndexingTest.py"
)

sitk_add_pytest_test(
  Test.ExternalViewer
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkExternalViewerTest.py"
)

sitk_add_pytest_test(
  Test.FlatStaticMethod
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkFlatStaticMethod.py"
)

sitk_add_pytest_test(
  Test.GetGDCMSeriesIDs
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkGetGDCMSeriesIDs.py"
)

# Numpy test.
sitk_add_pytest_test(
  Test.Numpy
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkNumpyArrayConversionTest.py"
)

sitk_add_pytest_test(
  Test.ProcessObject
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkProcessObjectTest.py"
)

sitk_add_pytest_test(
  Test.ConcurrentImageRead
  "${CMAKE_CURRENT_SOURCE_DIR}/ConcurrentImageRead.py"
)

sitk_add_pytest_test(
  Test.ImageReadWrite
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageReadWrite.py"
)

sitk_add_pytest_test(
  Test.ImageBuffer
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageBufferTest.py"
)

sitk_add_pytest_test(
  Test.ImageProtocol
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageProtocolTest.py"
)

if(SimpleITK_USE_ELASTIX)
  sitk_add_pytest_test(
    Test.TransformixImageFilterTest
    "${CMAKE_CURRENT_SOURCE_DIR}/sitkTransformixImageFilterTest.py"
  )
endif()

if(TEST Python.Test.ConcurrentImageRead AND APPLE)
  set_tests_properties(
    Python.Test.ConcurrentImageRead
    PROPERTIES
      LABELS
        "UNSTABLE"
  )
endif()

sitk_add_pytest_test(
  Test.ArrayView
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkGetArrayViewFromImageTest.py"
)

# Test data directory
set(
  TEST_HARNESS_TEMP_DIRECTORY
  ${${CMAKE_PROJECT_NAME}_BINARY_DIR}/Testing/Temporary
)
set(TEST_HARNESS_DATA_DIRECTORY ${ExternalData_BINARY_ROOT}/Testing/Data)

# Define the Python template file
set(PYTHON_TEMPLATE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/)

message(CHECK_START "Configuring python tests")

# Generate conftest_constants.py
file(
  CONFIGURE
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/conftest_constants.py
  CONTENT
    [[
TEST_HARNESS_DATA_DIRECTORY = "@TEST_HARNESS_DATA_DIRECTORY@"
TEST_HARNESS_TEMP_DIRECTORY = "@TEST_HARNESS_TEMP_DIRECTORY@"
]]
)

# Copy conftest.py without substitution
file(
  COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/conftest.py
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/
)

set(_CMAKE_OUTPUT_CONTENT "")

foreach(filter_config_file ${GENERATED_CONFIG_LIST})
  get_filename_component(FILTERNAME ${filter_config_file} NAME_WE)

  set(
    cmd
    ${SimpleITK_Python_EXECUTABLE}
    ${SimpleITK_EXPANSION_SCRIPT}
    ${filter_config_file}
    -D
    ${CMAKE_CURRENT_SOURCE_DIR}
    ImageFilterCTestTemplate.cmake.jinja
  )
  execute_process(
    COMMAND
      ${cmd}
    RESULT_VARIABLE failed
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error
  )
  if(failed)
    string(REPLACE ";" " " cmd "${cmd}")
    message(
      FATAL_ERROR
      "Failed to generate CMake output for ${FILTERNAME}\nCOMMAND: ${cmd} \n${error}"
    )
  endif()
  string(APPEND _CMAKE_OUTPUT_CONTENT "${output}")

  set(OUTPUT_TEST_FILENAME "${CMAKE_CURRENT_BINARY_DIR}/${FILTERNAME}Test.py")

  add_custom_command(
    OUTPUT
      "${OUTPUT_TEST_FILENAME}"
    COMMAND
      ${SimpleITK_Python_EXECUTABLE} ${SimpleITK_EXPANSION_SCRIPT}
      ${filter_config_file} -D ${CMAKE_CURRENT_SOURCE_DIR}
      ImageFilterTestTemplate.py.jinja -o "${OUTPUT_TEST_FILENAME}"
    DEPENDS
      ${filter_config_file}
      ImageFilterTestTemplate.py.jinja
  )
  list(APPEND WRAPPED_GENERATED_TEST_SOURCE "${OUTPUT_TEST_FILENAME}")
endforeach()

# Write accumulated CMake content to a single file
set(PYTHON_TESTS_CMAKE_FILE "${CMAKE_CURRENT_BINARY_DIR}/PythonTests.cmake")
file(WRITE "${PYTHON_TESTS_CMAKE_FILE}" "${_CMAKE_OUTPUT_CONTENT}")

# Include the generated CMake file once
include("${PYTHON_TESTS_CMAKE_FILE}")

add_custom_target(
  PythonGeneratedTests
  ALL
  DEPENDS
    ${WRAPPED_GENERATED_TEST_SOURCE}
)
message(CHECK_PASS "done")
