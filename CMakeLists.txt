project ( SimpleITK )
cmake_minimum_required ( VERSION 2.8 )


find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
endif()

if( NOT ITK_USE_REVIEW )
# TODO need to check ITK configuration to verify that it has the needed modules
#  message(FATAL_ERROR "Please reconfigure ITK by turning ITK_USE_REVIEW ON")
endif()

# Setup build locations.
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
endif()

set ( SimpleITK_INCLUDE_DIR
      ${CMAKE_SOURCE_DIR}/Code/Common
      ${CMAKE_SOURCE_DIR}/Code/Registration
      ${CMAKE_SOURCE_DIR}/Code/Common/Ancillary
      ${CMAKE_SOURCE_DIR}/Code/BasicFilters/include
      ${CMAKE_SOURCE_DIR}/Code/IO
      ${CMAKE_BINARY_DIR}/Code/BasicFilters/include
      ${CMAKE_BINARY_DIR}
      )

include_directories( ${SimpleITK_INCLUDE_DIR} )

set ( SimpleITK_LIBRARIES SimpleITKCommon SimpleITKIO SimpleITKBasicFilters  ${ITK_LIBRARIES} )

# Be sure to clear these each time
set ( GENERATED_TEST_LIST "" CACHE INTERNAL "" )
set ( GENERATED_FILTER_LIST "" CACHE INTERNAL "" )
set ( GENERATED_TEST_SOURCE_LIST "" CACHE INTERNAL "" )

#----------------------------------------------------------
# Place all options to go into sitkConfigure.h here

# Setting this option will shorten compile times by reducing the
# amount of pixel types and generated code.
# NB: this option should _NOT_ be used for releases!
option ( SITK_EXPRESS_INSTANTIATEDPIXELS "Instantiate very few pixel types ( for use for development only )" OFF )
mark_as_advanced ( SITK_EXPRESS_INSTANTIATEDPIXELS )


#-----------------------------------------------------------
# Place all checks and try compile variable for sitkConfigure.h here

# check for C++0x static_assert
try_compile(SITK_SUPPORTS_STATIC_ASSERT
  ${SimpleITK_BINARY_DIR}/CMakeTmp
  ${SimpleITK_SOURCE_DIR}/CMake/static_assert.cxx )


include(CheckIncludeFileCXX)

# check for the tr1/functional header
check_include_file_cxx( tr1/functional SITK_HAS_STLTR1_TR1_FUNCTIONAL )
check_include_file_cxx( functional SITK_HAS_STLTR1_FUNCTIONAL )

# check for the tr1/functional header
check_include_file_cxx( tr1/type_traits SITK_HAS_STLTR1_TR1_TYPE_TRAITS )
check_include_file_cxx( type_traits SITK_HAS_STLTR1_TYPE_TRAITS )

if ( NOT SITK_HAS_STLTR1_TR1_FUNCTIONAL AND NOT SITK_HAS_STLTR1_FUNCTIONAL )
message( FATAL_ERROR "SimpleITK requires usage of parts C++ Technical Report 1 (TR1).\n"
    "It may be available as an optional download for your compiler. Please see the FAQ for details.\n" )
endif ( NOT SITK_HAS_STLTR1_TR1_FUNCTIONAL AND NOT SITK_HAS_STLTR1_FUNCTIONAL )

# check for stdint
# This generates a configuration error if the compiler is not supported
check_include_file_cxx( stdint.h SITK_HAS_STDINT )

if ( NOT SITK_HAS_STDINT )
message( FATAL_ERROR "SimpleITK requires usage of C99 stdint.\n"
    "It may be available as an optional download for your compiler.\n"
    "Please see the FAQ for details and to see if your compiler is supported.\n" )
endif ( NOT SITK_HAS_STDINT )




configure_file( ${SimpleITK_SOURCE_DIR}/sitkConfigure.h.in
  ${SimpleITK_BINARY_DIR}/sitkConfigure.h )


# Create cached list of all template components
file( GLOB template_components
      ${SimpleITK_SOURCE_DIR}/TemplateComponents/*.h.in
      ${SimpleITK_SOURCE_DIR}/TemplateComponents/*.cxx.in
    )
set ( template_components ${template_components} CACHE INTERNAL "" )

subdirs ( Utilities Code Wrapping Examples )


#-----------------------------------------------------------------------------
# ITK uses KWStyle for checking the coding style
include(${SimpleITK_SOURCE_DIR}/Utilities/KWStyle/KWStyle.cmake)

include(${SimpleITK_SOURCE_DIR}/Utilities/Doxygen/Doxygen.cmake)

# Options for testing
option ( USE_TESTING "Build testing" ON )

if ( USE_TESTING )
  enable_testing()
  subdirs ( Testing )
  include(CTest)
  option ( RUN_LONG_TESTS "Run long tests.  Some tests have been identified as long running, should these be run?" OFF )
  mark_as_advanced(RUN_LONG_TESTS)
  set(BUILDNAME "${BUILDNAME}" CACHE STRING "Name of build on the dashboard")
  configure_file(CTestCustom.cmake.in CTestCustom.cmake)
endif()


#-----------------------------------------------------------------------------
# Help other projects use SimpleITK

# Copy the UseITK.cmake file to the binary tree for backward compatability.
configure_file(${SimpleITK_SOURCE_DIR}/UseSimpleITK.cmake.in
               ${SimpleITK_BINARY_DIR}/UseSimpleITK.cmake COPYONLY IMMEDIATE)

# Create the SimpleITKConfig.cmake file containing the SimpleITK configuration.
include(${SimpleITK_SOURCE_DIR}/sitkGenerateSimpleITKConfig.cmake)


#-----------------------------------------------------------------------------
# Options for testing
option ( BUILD_DOCUMENTS "Build testing" OFF )

if ( BUILD_DOCUMENTS )
  subdirs ( Documentation )
endif()
