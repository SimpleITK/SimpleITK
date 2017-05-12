cmake_minimum_required ( VERSION 2.8.1 FATAL_ERROR )

project( SimpleITK_Lua )

include(../../CMake/sitkProjectLanguageCommon.cmake NO_POLICY_SCOPE)



find_package ( Lua REQUIRED )

set( LUA_ADDITIONAL_LIBRARIES "" CACHE STRING "Additional libraries which may be needed for lua executable such as readline.")
mark_as_advanced( LUA_ADDITIONAL_LIBRARIES )

include_directories ( ${SimpleITK_INCLUDE_DIRS} )

set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )

# Run swig
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS})
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set(SWIG_MODULE_SimpleITKLua_EXTRA_DEPS ${SWIG_EXTRA_DEPS}
  ${CMAKE_CURRENT_SOURCE_DIR}/Lua.i )
SWIG_module_initialize ( SimpleITKLua lua )
SWIG_add_source_to_module ( SimpleITKLua  swig_generated_source SimpleITK.i ${SWIG_EXTRA_DEPS} )
set_source_files_properties(${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-w" )

# Create a standalone Lua executable that includes SimpleITK.
option( SimpleITK_LUA_BUILD_EXECUTABLE "Build a standalone SimpleITK-Lua executable" OFF)
sitk_legacy_naming(SimpleITK_LUA_BUILD_EXECUTABLE)
if ( SimpleITK_LUA_BUILD_EXECUTABLE )
  add_executable ( SimpleITKLua SimpleITKLuaMain.cxx ${swig_generated_file_fullname} )
  target_link_libraries ( SimpleITKLua ${SimpleITK_LIBRARIES} ${LUA_LIBRARIES} ${LUA_ADDITIONAL_LIBRARIES} )
  target_include_directories( SimpleITKLua
    PRIVATE
      ${LUA_INCLUDE_DIR} )
  sitk_strip_target( SimpleITKLua )
endif ()

# Create a SimpleITK Lua module that can be loaded into any Lua executable.
SWIG_add_module( SimpleITKLuaModule lua SimpleITK.i )
target_link_libraries( ${SWIG_MODULE_SimpleITKLuaModule_TARGET_NAME} ${SimpleITK_LIBRARIES} )
set_target_properties( ${SWIG_MODULE_SimpleITKLuaModule_TARGET_NAME} PROPERTIES PREFIX "" OUTPUT_NAME  "SimpleITK" )
sitk_target_link_libraries_with_dynamic_lookup( ${SWIG_MODULE_SimpleITKLuaModule_TARGET_NAME} ${LUA_LIBRARIES} )
target_include_directories( ${SWIG_MODULE_SimpleITKLuaModule_TARGET_NAME}
    SYSTEM
    PRIVATE
      ${LUA_INCLUDE_DIR} )
set_source_files_properties( ${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-w")
sitk_strip_target( ${SWIG_MODULE_SimpleITKLuaModule_TARGET_NAME} )

