
set ( SimpleITKUnitTestBaseSource
  SimpleITKTestHarness.cxx
  sitkImageCompare.cxx
  sitkTransformCompare.cxx
)

add_library ( SimpleITKUnitTestBase STATIC ${SimpleITKUnitTestBaseSource} )
target_link_libraries( SimpleITKUnitTestBase
        PUBLIC
          GTest::GTest ${SimpleITK_LIBRARIES}
        PRIVATE
          ${ITK_LIBRARIES} )
target_include_directories( SimpleITKUnitTestBase
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_compile_options( SimpleITKUnitTestBase
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )


add_executable( sitkCompareDriver sitkCompareDriver.cxx )
target_link_libraries( sitkCompareDriver SimpleITKUnitTestBase ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES})
target_compile_options( sitkCompareDriver
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )

sitk_install_exported_target(sitkCompareDriver)


# Set some variables
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SimpleITKTestHarnessPaths.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/SimpleITKTestHarnessPaths.h ESCAPE_QUOTES)



#
# Tests for Compare dirver CXX tests
#
sitk_add_test(NAME CompareDriver1
  COMMAND
    $<TARGET_FILE:sitkCompareDriver>
    --compareTransform
      DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
      DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
  )

sitk_add_test(NAME CompareDriver2
  COMMAND
    ${CMAKE_COMMAND} -E echo "Running command"
  TRANSFORM_COMPARE
    DATA{${SimpleITK_DATA_ROOT}/Input/xforms/translation_-13x-17y.txt}
    DATA{${SimpleITK_DATA_ROOT}/Baseline/displacement_-13x-17y.mha}
  )


sitk_add_test(NAME CompareDriver3
        COMMAND
        $<TARGET_FILE:sitkCompareDriver>
        --compare
        DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.mha}
        DATA{${SimpleITK_DATA_ROOT}/Input/2th_cthead1.mha}
        )
