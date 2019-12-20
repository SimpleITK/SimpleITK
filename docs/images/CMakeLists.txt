cmake_minimum_required ( VERSION 3.0 FATAL_ERROR )

project( SimpleITKSphinx-Data LANGUAGES NONE )

if (NOT CMAKE_PROJECT_NAME STREQUAL "SimpleITK" )
  set( SimpleITK_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../.." )
  list(INSERT CMAKE_MODULE_PATH 0 "${SimpleITK_SOURCE_DIR}/CMake")
endif()

# Use ExternalData module to either download data to get from local
# data store.
include(sitkExternalData)

set(_target "SimpleITKSphinx-Data")
set(_output_path "${CMAKE_CURRENT_SOURCE_DIR}/")

set(_algo "sha512")
file( GLOB_RECURSE image_links RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.${_algo}" )

foreach(link ${image_links})
  string( REGEX REPLACE "\\.${_algo}$" "" link ${link} )
  ExternalData_Expand_Arguments( "${_target}"
    image_location
    DATA{${link}}
    )
  set( COPY_DATA_COMMAND ${COPY_DATA_COMMAND} COMMAND ${CMAKE_COMMAND}
  -E copy ${image_location}  "${_output_path}" )
endforeach()

ExternalData_Add_Target( "${_target}" )

add_custom_command( TARGET "${_target}"
  POST_BUILD
  ${COPY_DATA_COMMAND}
  )
