cmake_minimum_required(VERSION 2.8)
project(SimpleITKExamples)

foreach(p
    CMP0042 # CMake 3.0
    CMP0063 # CMake 3.3.2
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

if(NOT CMAKE_PROJECT_NAME STREQUAL "SimpleITK")
  find_package(SimpleITK REQUIRED)

endif()

# Add individual cxx executables

add_executable ( SimpleGaussianFunctional SimpleGaussianFunctional.cxx )
target_link_libraries ( SimpleGaussianFunctional ${SimpleITK_LIBRARIES} )

add_executable ( BufferImportExport BufferImportExport.cxx )
target_link_libraries ( BufferImportExport ${SimpleITK_LIBRARIES} )

# Add subdirectories
add_subdirectory(Segmentation)

# Test data directory
set(TEST_HARNESS_TEMP_DIRECTORY ${SimpleITK_BINARY_DIR}/Testing/Temporary)
set(TEST_HARNESS_DATA_DIRECTORY ${SimpleITK_BINARY_DIR}/ExternalData/Testing/Data)
set(ITK_TEST_DRIVER  "$<TARGET_FILE:itkTestDriver>")


# Add example organized sub-directories with multiple languages
add_subdirectory(SimpleGaussian)
add_subdirectory(ImageRegistrationMethod1)
add_subdirectory(ImageRegistrationMethod2)
add_subdirectory(ImageRegistrationMethod3)
add_subdirectory(ImageRegistrationMethod4)
add_subdirectory(ImageRegistrationMethodBSpline1)
add_subdirectory(ImageRegistrationMethodBSpline2)
add_subdirectory(ImageRegistrationMethodDisplacement1)
add_subdirectory(ImageRegistrationMethodExhaustive)
add_subdirectory(N4BiasFieldCorrection)
add_subdirectory(DicomSeriesReader)
add_subdirectory(DicomImagePrintTags)
add_subdirectory(DicomSeriesReadModifyWrite)
add_subdirectory(FilterProgressReporting)
add_subdirectory(DemonsRegistration1)
add_subdirectory(DemonsRegistration2)

macro(add_language_subdirectory lang)
  string(TOUPPER ${lang} LANG)
  if ( WRAP_${LANG} )
    add_subdirectory(${lang})
  endif()
endmacro()

if ( BUILD_TESTING )
  add_subdirectory( test )

  add_language_subdirectory( CSharp )
  add_language_subdirectory( Python )

endif()
