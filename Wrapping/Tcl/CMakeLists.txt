cmake_minimum_required ( VERSION 3.10 FATAL_ERROR )

project( SimpleITK_TCL )

include(../../CMake/sitkProjectLanguageCommon.cmake NO_POLICY_SCOPE)

find_package ( TCL REQUIRED )
include_directories ( ${SimpleITK_INCLUDE_DIRS} )

set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )

# Run swig
set(CMAKE_SWIG_FLAGS "-nosafe" ${CMAKE_SWIG_GLOBAL_FLAGS})
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set(SWIG_MODULE_SimpleITKTCL_EXTRA_DEPS ${SWIG_EXTRA_DEPS} ${CMAKE_CURRENT_SOURCE_DIR}/Tcl.i )
set(SWIG_MODULE_SimpleITKTcl_EXTRA_DEPS  ${SWIG_MODULE_SimpleITKTCL_EXTRA_DEPS})
#  SWIG_add_module ( SimpleITKTcl tcl SimpleITK.i SimpleITKTCL_wrap.cxx )
#  target_link_libraries ( ${SWIG_MODULE_SimpleITKTcl_TARGET_NAME} ${SimpleITK_LIBRARIES} )
#  sitk_target_link_libraries_with_dynamic_lookup( ${SWIG_MODULE_SimpleITKTcl_TARGET_NAME} ${TCL_LIBRARY} )
#  set_source_files_properties(${swig_generated_file_fullname}  PROPERTIES COMPILE_FLAGS "-w")
#  add_executable ( SimpleITKTclsh ${swig_generated_file_fullname} )
#  target_link_libraries ( SimpleITKTclsh ${SimpleITK_LIBRARIES} ${TCL_LIBRARY})

SWIG_module_initialize ( SimpleITKTCL tcl )
SWIG_add_source_to_module ( SimpleITKTCL swig_generated_source SimpleITK.i ${SWIG_EXTRA_DEPS} )
set_source_files_properties(${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-w" )
add_executable ( SimpleITKTclsh ${swig_generated_file_fullname} )
target_link_libraries ( SimpleITKTclsh ${SimpleITK_LIBRARIES} ${TCL_LIBRARY} )
target_include_directories( SimpleITKTclsh
  PRIVATE
   ${TCL_INCLUDE_PATH} )
sitk_strip_target( SimpleITKTclsh )
