project ( SimpleITK )
cmake_minimum_required ( VERSION 2.8 )


find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
endif()



# Put all files in a bin directory to keep things tidy.
# Output directories.
if(NOT LIBRARY_OUTPUT_PATH)
  set(LIBRARY_OUTPUT_PATH ${SimpleITK_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
endif()
if(NOT EXECUTABLE_OUTPUT_PATH)
  set(EXECUTABLE_OUTPUT_PATH ${SimpleITK_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")
endif()
mark_as_advanced(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

set ( SimpleITK_INCLUDE_DIR 
      ${CMAKE_SOURCE_DIR}/Code/Common
      ${CMAKE_SOURCE_DIR}/Code/Common/Ancillary
      ${CMAKE_SOURCE_DIR}/Code/BasicFilters
      ${CMAKE_SOURCE_DIR}/Code/IO
      ${CMAKE_BINARY_DIR}/Code/BasicFilters
      ${CMAKE_BINARY_DIR}
      )

include_directories( ${SimpleITK_INCLUDE_DIR} )

set ( SimpleITK_LIBRARIES ${ITK_LIBRARIES} SimpleITKCommon SimpleITKIO SimpleITKBasicFilters)

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
  ${SimpleITK_SOURCE_DIR}/CMake/static_assert.cxx
  OUTPUT_VARIABLE SITK_HAS_STATIC_ASSERT )


include(CheckIncludeFileCXX)

# check for the tr1/functional header
check_include_file_cxx( tr1/functional SITK_HAS_STLTR1_TR1_FUNCTIONAL )
check_include_file_cxx( functional SITK_HAS_STLTR1_FUNCTIONAL )

if ( NOT SITK_HAS_STLTR1_TR1_FUNCTIONAL AND NOT SITK_HAS_STLTR1_FUNCTIONAL )
message( FATAL_ERROR "SimpleITK requires usage of parts C++ Technical Report 1 (TR1)\n"
    "It may be available as an optional download for your compiler. Please see the FAQ for details." )
endif ( NOT SITK_HAS_STLTR1_TR1_FUNCTIONAL AND NOT SITK_HAS_STLTR1_FUNCTIONAL )



configure_file( ${SimpleITK_SOURCE_DIR}/sitkConfigure.h.in
  ${SimpleITK_BINARY_DIR}/sitkConfigure.h )




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
endif()

