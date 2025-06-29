cmake_minimum_required(VERSION 3.16.3...3.20)
project(SimpleITKExamples)

foreach(
  p
  CMP0156 # De-duplicate libraries on link lines based on linker capabilities.
)
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

if(NOT CMAKE_PROJECT_NAME STREQUAL "SimpleITK")
  find_package(SimpleITK REQUIRED)
endif()

option(
  SimpleITK_TESTING_NOSHOW
  "Disable the Show function in SimpleITK testing."
  ON
)
mark_as_advanced(SimpleITK_TESTING_NOSHOW)

add_executable(SimpleGaussianFunctional SimpleGaussianFunctional.cxx)
target_link_libraries(SimpleGaussianFunctional ${SimpleITK_LIBRARIES})

add_executable(BufferImportExport BufferImportExport.cxx)
target_link_libraries(BufferImportExport ${SimpleITK_LIBRARIES})

# Add subdirectories
add_subdirectory(Segmentation)

if(SimpleITK_USE_ELASTIX)
  add_subdirectory(Elastix)
endif()

# Test data directory
set(TEST_HARNESS_TEMP_DIRECTORY ${SimpleITK_BINARY_DIR}/Testing/Temporary)

# Add example organized sub-directories with multiple languages
add_subdirectory(HelloWorld)
add_subdirectory(FastMarchingSegmentation)
add_subdirectory(SimpleGaussian)
add_subdirectory(SimpleIO)
add_subdirectory(ImageIOSelection)
add_subdirectory(ImageRegistrationMethod1)
add_subdirectory(ImageRegistrationMethod2)
add_subdirectory(ImageRegistrationMethod3)
add_subdirectory(ImageRegistrationMethod4)
add_subdirectory(ImageRegistrationOptimizerWeights)
add_subdirectory(ImageRegistrationMethodBSpline1)
add_subdirectory(ImageRegistrationMethodBSpline2)
add_subdirectory(ImageRegistrationMethodBSpline3)
add_subdirectory(ImageRegistrationMethodDisplacement1)
add_subdirectory(ImageRegistrationMethodExhaustive)
add_subdirectory(LandmarkRegistration)
add_subdirectory(N4BiasFieldCorrection)
add_subdirectory(DicomSeriesReader)
add_subdirectory(DicomImagePrintTags)
add_subdirectory(DicomSeriesReadModifyWrite)
add_subdirectory(DicomConvert)
add_subdirectory(FilterProgressReporting)
add_subdirectory(DemonsRegistration1)
add_subdirectory(DemonsRegistration2)
add_subdirectory(RawImageReading)
add_subdirectory(CppCMake)
add_subdirectory(CppInPlace)
add_subdirectory(SliceBySliceDecorator)
add_subdirectory(Logging)

macro(add_language_subdirectory lang)
  string(TOUPPER ${lang} LANG)
  if(WRAP_${LANG})
    add_subdirectory(${lang})
  endif()
endmacro()

if(BUILD_TESTING)
  add_subdirectory(test)

  add_language_subdirectory( Java )
  add_language_subdirectory( CSharp )
  add_language_subdirectory( Python )
endif()
