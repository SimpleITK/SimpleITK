include("${CMAKE_CURRENT_SOURCE_DIR}/../../CMake/sitkCMakeInit.cmake")
cmake_minimum_required(VERSION ${SITK_CMAKE_MINIMUM_REQUIRED_VERSION}...${SITK_CMAKE_POLICY_VERSION})



project( SimpleITK_Ruby )

include(../../CMake/sitkProjectLanguageCommon.cmake NO_POLICY_SCOPE)

find_package( Ruby REQUIRED )
include_directories( ${SimpleITK_INCLUDE_DIRS} )

set_source_files_properties( SimpleITK.i PROPERTIES CPLUSPLUS ON )

# Run swig
set(CMAKE_SWIG_FLAGS -autorename -module simpleitk ${CMAKE_SWIG_GLOBAL_FLAGS})
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set(SWIG_MODULE_simpleitk_EXTRA_DEPS ${SWIG_EXTRA_DEPS}
  ${CMAKE_CURRENT_SOURCE_DIR}/Ruby.i)

SWIG_add_module( simpleitk ruby SimpleITK.i  )
target_link_libraries( ${SWIG_MODULE_simpleitk_TARGET_NAME}
  ${SimpleITK_LIBRARIES} )


# Addresses register keyword usage in header, producing an compilation error with C++ >=std17
# print all varaible used below
if(APPLE AND CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
  target_compile_options(${SWIG_MODULE_simpleitk_TARGET_NAME} BEFORE PRIVATE "-Wno-register")
endif()
target_compile_options(${SWIG_MODULE_simpleitk_TARGET_NAME} PRIVATE -w)


sitk_target_link_libraries_with_dynamic_lookup( ${SWIG_MODULE_simpleitk_TARGET_NAME} ${Ruby_LIBRARY} )
target_include_directories( ${SWIG_MODULE_simpleitk_TARGET_NAME}
  PRIVATE
    ${Ruby_INCLUDE_DIRS} )
sitk_strip_target( ${SWIG_MODULE_simpleitk_TARGET_NAME} )
