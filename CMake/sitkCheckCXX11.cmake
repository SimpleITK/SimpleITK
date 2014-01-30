#
# CMake Module to check for TR1 and C++11 features
#
# SITK_HAS_CXX11_STATIC_ASSERT    - True if "static_assert" keyword is supported


function(sitkCXX11Test VARIABLE)
  if("${VARIABLE}" MATCHES "^${VARIABLE}$")
    message(STATUS "Performing Test ${VARIABLE}")
    try_compile(SITK_HAS_CXX11_STATIC_ASSERT
      ${SimpleITK_BINARY_DIR}/CMakeTmp
      ${SimpleITK_SOURCE_DIR}/CMake/sitk_check_cxx11.cxx
      CMAKE_FLAGS
      -DCOMPILE_DEFINITIONS:STRING=-D${VARIABLE}
      OUTPUT_VARIABLE OUTPUT)
    if(${VARIABLE})
      set(${VARIABLE} 1 CACHE INTERNAL "VXL test ${FUNCTION}")
      message(STATUS "Performing Test ${VARIABLE} - Success")
    else()
      message(STATUS "Performing Test ${VARIABLE} - Failed")
      set(${VARIABLE} 0 CACHE INTERNAL "Test ${FUNCTION}")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
                 "Performing Test ${VARIABLE} failed with the following output:\n"
                 "${OUTPUT}\n")
    endif()
  endif()
endfunction()


sitkCXX11Test(SITK_HAS_CXX11_STATIC_ASSERT)


include(CheckIncludeFileCXX)

# check for the required tr1/functional header
check_include_file_cxx( tr1/functional SITK_HAS_STLTR1_TR1_FUNCTIONAL )
check_include_file_cxx( functional SITK_HAS_STLTR1_FUNCTIONAL )

# check for the required tr1/type_traits header
check_include_file_cxx( tr1/type_traits SITK_HAS_STLTR1_TR1_TYPE_TRAITS )
check_include_file_cxx( type_traits SITK_HAS_STLTR1_TYPE_TRAITS )


if ( (NOT SITK_HAS_STLTR1_TR1_FUNCTIONAL AND NOT SITK_HAS_STLTR1_FUNCTIONAL)
    OR
    (NOT SITK_HAS_STLTR1_TR1_TYPE_TRAITS AND NOT SITK_HAS_STLTR1_FUNCTIONAL) )
  message( FATAL_ERROR
    "SimpleITK requires usage of parts C++ Technical Report 1 (TR1).\n"
    "It may be available as an optional download for your compiler. Please see the FAQ for details.\n"
    "http://www.itk.org/Wiki/SimpleITK/FAQ#Do_I_need_to_download_an_option_package_for_TR1_support.3F" )
endif ( )

# check for the optional tr1/unordered_map header
check_include_file_cxx( tr1/unordered_map SITK_HAS_STLTR1_TR1_UNORDERED_MAP )
check_include_file_cxx( unordered_map SITK_HAS_STLTR1_UNORDERED_MAP )
if ( ${SITK_HAS_STLTR1_UNORDERED_MAP} )
  set( SITK_UNORDERED_MAP_FUNCTIONAL_DEFINITIONS "-DSITK_HAS_STLTR1_UNORDERED_MAP")
elseif ( ${SITK_HAS_STLTR1_TR1_UNORDERED_MAP} )
  set( SITK_UNORDERED_MAP_FUNCTIONAL_DEFINITIONS "-DSITK_HAS_STLTR1_TR1_UNORDERED_MAP" )
endif()
try_compile(SITK_UNORDERED_MAP_FUNCTIONAL
  ${SimpleITK_BINARY_DIR}/CMakeTmp
  ${SimpleITK_SOURCE_DIR}/CMake/tr1_unordered_map.cxx
  COMPILE_DEFINITIONS "${SITK_UNORDERED_MAP_FUNCTIONAL_DEFINITIONS}"
  OUTPUT_VARIABLE out )
