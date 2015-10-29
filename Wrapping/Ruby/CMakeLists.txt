
find_package( Ruby REQUIRED )
include_directories( ${RUBY_INCLUDE_DIRS} )

set_source_files_properties( SimpleITK.i PROPERTIES CPLUSPLUS ON )

# Run swig
set(CMAKE_SWIG_FLAGS -autorename -module simpleitk ${CMAKE_SWIG_GLOBAL_FLAGS})
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set(SWIG_MODULE_simpleitk_EXTRA_DEPS ${SWIG_EXTRA_DEPS}
  ${CMAKE_CURRENT_SOURCE_DIR}/Ruby.i)

SWIG_add_module( simpleitk ruby SimpleITK.i  )
SWIG_link_libraries( simpleitk ${SimpleITK_LIBRARIES} ${RUBY_LIBRARY})
set_source_files_properties( ${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-w")
sitk_strip_target( ${SWIG_MODULE_simpleitk_TARGET_NAME} )
