set(
  SimpleITKUnitTestBaseSource
  SimpleITKTestHarness.cxx
  sitkImageCompare.cxx
  sitkTransformCompare.cxx
)

add_library(SimpleITKUnitTestBase STATIC ${SimpleITKUnitTestBaseSource})
target_link_libraries(
  SimpleITKUnitTestBase
  PUBLIC
    GTest::gtest
    ${SimpleITK_LIBRARIES}
  PRIVATE
    ITK::ITKKWSysModule
)

# Add headers using FILE_SET for automatic include directory management
target_sources(
  SimpleITKUnitTestBase
  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
      FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/SimpleITKTestHarness.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sitkImageCompare.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sitkTransformCompare.h
        ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKTestHarnessPaths.h
)

# FILE_SET automatically adds BASE_DIRS to INCLUDE_DIRECTORIES and INTERFACE_INCLUDE_DIRECTORIES
target_compile_options(
  SimpleITKUnitTestBase
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)

add_executable(sitkCompareDriver sitkCompareDriver.cxx)
target_link_libraries(
  sitkCompareDriver
  SimpleITKUnitTestBase
  ${SimpleITK_LIBRARIES}
  ITK::ITKKWSysModule
)
target_compile_options(
  sitkCompareDriver
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)

sitk_install_exported_target(sitkCompareDriver)

# Set some variables
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/SimpleITKTestHarnessPaths.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKTestHarnessPaths.h
  ESCAPE_QUOTES
)

#
# Tests for Compare driver CXX tests
#
sitk_add_test(
  NAME CompareDriver1
  COMMAND
    $<TARGET_FILE:sitkCompareDriver> --compareTransform
    DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
)

sitk_add_test(
  NAME CompareDriver2
  COMMAND
    ${CMAKE_COMMAND} -E echo "Running command"
  TRANSFORM_COMPARE
    DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
)

sitk_add_test(
  NAME CompareDriver3
  COMMAND
    $<TARGET_FILE:sitkCompareDriver> --compare
    DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.mha}
    DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.mha}
)
