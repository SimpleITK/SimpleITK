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

  # Add compiler flags needed to use SimpleITK.
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SimpleITK_REQUIRED_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SimpleITK_REQUIRED_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
endif()

# Add individual cxx executables

add_executable ( SimpleGaussianFunctional SimpleGaussianFunctional.cxx )
target_link_libraries ( SimpleGaussianFunctional ${SimpleITK_LIBRARIES} )

add_executable ( BufferImportExport BufferImportExport.cxx )
target_link_libraries ( BufferImportExport ${SimpleITK_LIBRARIES} )

add_executable ( FilterProgressReporting FilterProgressReporting.cxx )
target_link_libraries ( FilterProgressReporting ${SimpleITK_LIBRARIES} )

add_executable ( DicomSeriesReader DicomSeriesReader.cxx )
target_link_libraries ( DicomSeriesReader ${SimpleITK_LIBRARIES} )

add_executable ( ImageRegistrationMethod2 ImageRegistrationMethod2.cxx )
target_link_libraries ( ImageRegistrationMethod2 ${SimpleITK_LIBRARIES} )

add_executable ( ImageRegistrationMethodBSpline1 ImageRegistrationMethodBSpline1.cxx )
target_link_libraries ( ImageRegistrationMethodBSpline1 ${SimpleITK_LIBRARIES} )

add_executable ( ImageRegistrationMethodDisplacement1 ImageRegistrationMethodDisplacement1.cxx )
target_link_libraries ( ImageRegistrationMethodDisplacement1  ${SimpleITK_LIBRARIES} )


add_executable ( DemonsRegistration1 DemonsRegistration1.cxx )
target_link_libraries ( DemonsRegistration1 ${SimpleITK_LIBRARIES} )

add_executable ( DemonsRegistration2 DemonsRegistration2.cxx )
target_link_libraries ( DemonsRegistration2 ${SimpleITK_LIBRARIES} )

# Add subdirectories
add_subdirectory(Segmentation)

# Test data directory
set(TEST_HARNESS_TEMP_DIRECTORY ${SimpleITK_BINARY_DIR}/Testing/Temporary)
set(TEST_HARNESS_DATA_DIRECTORY ${SimpleITK_BINARY_DIR}/ExternalData/Testing/Data)
set(ITK_TEST_DRIVER  "$<TARGET_FILE:itkTestDriver>")


if ( BUILD_TESTING )
  # Add example organized sub-directories with multiple languages
  add_subdirectory(SimpleGaussian)
  add_subdirectory(ImageRegistrationMethod1)
endif()

macro(add_language_subdirectory lang)
  string(TOUPPER ${lang} LANG)
  if ( WRAP_${LANG} )
    add_subdirectory(${lang})
  endif()
endmacro()

if ( BUILD_TESTING )
  add_subdirectory( test )

  add_language_subdirectory( CSharp )
  add_language_subdirectory( Java )
  add_language_subdirectory( Lua )
  add_language_subdirectory( Python )
  add_language_subdirectory( R )
  add_language_subdirectory( Ruby )
  add_language_subdirectory( Tcl )

endif()
