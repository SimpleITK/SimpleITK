find_package ( R REQUIRED )
include_directories ( ${R_INCLUDE_DIR} )

set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )

# Run swig
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS})
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set(SWIG_MODULE_SimpleITK_EXTRA_DEPS ${SWIG_EXTRA_DEPS}
  ${CMAKE_CURRENT_SOURCE_DIR}/R.i )
SWIG_add_module ( SimpleITK r SimpleITK.i )
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

# copy the R files a binary package
add_custom_command( TARGET ${SWIG_MODULE_SimpleITK_TARGET_NAME}
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${SimpleITK_SOURCE_DIR}/Wrapping/R/Packaging ${CMAKE_CURRENT_BINARY_DIR}/Packaging
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK/data/
  )
add_custom_command( TARGET ${SWIG_MODULE_SimpleITK_TARGET_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/R_libs
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/SimpleITK.R ${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK/R/
  # copy sample images
  COMMAND ${CMAKE_COMMAND} -E copy ${SimpleITK_BINARY_DIR}/ExternalData/Testing/Data/Input/cthead1.png  ${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK/data/
  COMMAND ${CMAKE_COMMAND} -E copy ${SimpleITK_BINARY_DIR}/ExternalData/Testing/Data/Input/cthead1-Float.mha  ${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK/data/
  # install for running tests and create binary package
  COMMAND ${R_COMMAND} CMD INSTALL --build ${CMAKE_CURRENT_BINARY_DIR}/Packaging/SimpleITK --library=${CMAKE_CURRENT_BINARY_DIR}/R_libs
  COMMENT "Installing R package for testing and building binary version for distribution"
  )
