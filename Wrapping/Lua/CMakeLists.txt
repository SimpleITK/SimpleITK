cmake_minimum_required ( VERSION 2.8.1 FATAL_ERROR )

project( SimpleITK_Lua )

include(../../CMake/sitkProjectLanguageCommon.cmake)


if (CMAKE_VERSION VERSION_LESS "3")
  find_package ( Lua51 ${_QUIET} )
  if ( NOT LUA_FOUND )
    find_package ( Lua50 ${_QUIET} )
  endif()
else()
  find_package ( Lua ${_QUIET} )
endif()

set( LUA_ADDITIONAL_LIBRARIES "" CACHE STRING "Additional libraries which may be needed for lua such as readline.")
mark_as_advanced( LUA_ADDITIONAL_LIBRARIES )

include_directories ( ${LUA_INCLUDE_DIR} )

set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )

# Run swig
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS})
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set(SWIG_MODULE_SimpleITKLua_EXTRA_DEPS ${SWIG_EXTRA_DEPS}
  ${CMAKE_CURRENT_SOURCE_DIR}/Lua.i )
SWIG_module_initialize ( SimpleITKLua lua )
SWIG_add_source_to_module ( SimpleITKLua  swig_generated_source SimpleITK.i ${SWIG_EXTRA_DEPS} )
set_source_files_properties(${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-w" )

add_executable ( SimpleITKLua SimpleITKLuaMain.cxx ${swig_generated_file_fullname} )
target_link_libraries ( SimpleITKLua ${SimpleITK_LIBRARIES} ${LUA_LIBRARIES} ${LUA_ADDITIONAL_LIBRARIES} )
sitk_strip_target( SimpleITKLua )
