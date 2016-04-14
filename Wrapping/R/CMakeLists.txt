cmake_minimum_required ( VERSION 2.8.1 FATAL_ERROR )

project( SimpleITK_R )

include(../../CMake/sitkProjectLanguageCommon.cmake)

find_package ( R REQUIRED )
include_directories ( ${R_INCLUDE_DIR}  ${CMAKE_CURRENT_SOURCE_DIR})

set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )

# Run swig
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS})
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set(SWIG_MODULE_SimpleITK_EXTRA_DEPS ${SWIG_EXTRA_DEPS} ${CMAKE_CURRENT_SOURCE_DIR}/R.i )
SWIG_add_module ( SimpleITK r SimpleITK.i sitkRCommand.cxx )
target_link_libraries ( ${SWIG_MODULE_SimpleITK_TARGET_NAME} ${SimpleITK_LIBRARIES} )

sitk_target_link_libraries_with_dynamic_lookup ( ${SWIG_MODULE_SimpleITK_TARGET_NAME} ${R_LIBRARIES} )

set_source_files_properties(${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-w")

# set the output directory for the R library to the binary packaging location
set_target_properties( ${SWIG_MODULE_SimpleITK_TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK/src/)

sitk_strip_target( ${SWIG_MODULE_SimpleITK_TARGET_NAME} )
set(SWIG_MODULE_SimpleITKR_TARGET_NAME "${SWIG_MODULE_SimpleITK_TARGET_NAME}")


if (WIN32)
  execute_process(COMMAND "cmd" " /C date /T" OUTPUT_VARIABLE DATE OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REGEX REPLACE "(..)/(..)/(....).*" "\\3-\\2-\\1" ${DATE} DATE)
elseif(UNIX)
  execute_process(COMMAND "date" "+%Y-%m-%d" OUTPUT_VARIABLE DATE OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
  message(WARNING "date not implemented")
  set(DATE 00-00-0000)
endif()

# copy the R files a binary package
file( COPY "${CMAKE_CURRENT_SOURCE_DIR}/Packaging"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
  REGEX "(.*\\.in)|(.*\\.md5)" EXCLUDE )


set(SimpleITKR_VERSION "${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR}")
if(DEFINED SimpleITK_VERSION_PATCH)
  set(SimpleITK_VERSIONR "${SimpleITKR_VERSION}.${SimpleITK_VERSION_PATCH}")
  if(DEFINED SimpleITK_VERSION_TWEAK)
    set(SimpleITKR_VERSION "${SimpleITKR_VERSION}.${SimpleITK_VERSION_TWEAK}")
  endif()
endif()

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Packaging/SimpleITK/DESCRIPTION.in"
    "${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK/DESCRIPTION"
    @ONLY )

# download sample images, if allowed
if(NOT SITK_FORBID_DOWNLOADS)
  include(sitkExternalData)

  file( GLOB_RECURSE content_links RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.md5" )

  foreach(link ${content_links})
    string( REGEX REPLACE "\\.md5$" "" link ${link} )
    ExternalData_Expand_Arguments(  SimpleITKRpackageData
      link_location
      DATA{${link}}
      )
    set( COPY_DATA_COMMAND ${COPY_DATA_COMMAND} COMMAND ${CMAKE_COMMAND} -E copy ${link_location} ${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK/data/ )
  endforeach()

  if(COMMAND ExternalData_Add_Target )
    ExternalData_Add_Target( SimpleITKRpackageData )
  endif()
  add_dependencies( ${SWIG_MODULE_SimpleITK_TARGET_NAME} SimpleITKRpackageData )

  # copy sample images - used in vignette
  ## can't use file(copy as the sources are symbolic links
  add_custom_command( TARGET ${SWIG_MODULE_SimpleITK_TARGET_NAME}
    PRE_BUILD
    ${COPY_DATA_COMMAND}
    )

endif()


add_custom_command( TARGET ${SWIG_MODULE_SimpleITK_TARGET_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/R_libs
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/SimpleITK.R ${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK/R/
  # install for running tests and create binary package
  COMMAND ${R_COMMAND} CMD INSTALL --build ${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK --library=${CMAKE_CURRENT_BINARY_DIR}/R_libs
  COMMENT "Installing R package for testing and building binary version for distribution"
  )
