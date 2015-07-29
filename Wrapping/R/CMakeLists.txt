find_package ( R REQUIRED )
include_directories ( ${R_INCLUDE_DIR}  ${CMAKE_CURRENT_SOURCE_DIR})

set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )

# Run swig
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS})
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set(SWIG_MODULE_SimpleITK_EXTRA_DEPS ${SWIG_EXTRA_DEPS} ${CMAKE_CURRENT_SOURCE_DIR}/R.i )
SWIG_add_module ( SimpleITK r SimpleITK.i sitkRCommand.cxx )
SWIG_link_libraries ( SimpleITK ${SimpleITK_LIBRARIES} )

# on some platforms the r libraries are not required at link time...
if(R_LIBRARIES)
  SWIG_link_libraries ( SimpleITK ${R_LIBRARIES} )
endif()

set_source_files_properties(${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-w")

get_target_property( SIMPLEITKR_BINARY_MODULE ${SWIG_MODULE_SimpleITK_TARGET_NAME} LOCATION )
file(TO_NATIVE_PATH "${SIMPLEITKR_BINARY_MODULE}" SIMPLEITKR_NATIVE_BINARY_MODULE )


# set the output directory for the R library to the binary packaging location
set_target_properties( ${SWIG_MODULE_SimpleITK_TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK/src/)

sitk_strip_target( ${SWIG_MODULE_SimpleITK_TARGET_NAME} )
set(SWIG_MODULE_SimpleITKR_TARGET_NAME "${SWIG_MODULE_SimpleITK_TARGET_NAME}")


# copy the R files a binary package
add_custom_command( TARGET ${SWIG_MODULE_SimpleITK_TARGET_NAME}
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${SimpleITK_SOURCE_DIR}/Wrapping/R/Packaging ${CMAKE_CURRENT_BINARY_DIR}/Packaging
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK/data/
  )

# download sample images, if allowed
if(NOT SITK_FORBID_DOWNLOADS)
  include(sitkExternalData)

  foreach(link  ${SimpleITK_SOURCE_DIR}/Testing/Data/Input/cthead1.png.md5  ${SimpleITK_SOURCE_DIR}/Testing/Data/Input/cthead1-Float.mha.md5)
    string( REGEX REPLACE "\\.md5$" "" link ${link} )
    ExternalData_Expand_Arguments( SimpleITKRpackageData
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
