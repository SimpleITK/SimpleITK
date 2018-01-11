
set ( SimpleITKUnitTestBaseSource
  SimpleITKTestHarness.cxx
  sitkImageCompare.cxx
  sitkTransformCompare.cxx
)

add_library ( SimpleITKUnitTestBase STATIC ${SimpleITKUnitTestBaseSource} )
target_link_libraries( SimpleITKUnitTestBase GTest::GTest ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} )
target_include_directories( SimpleITKUnitTestBase
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
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
