# Make sure this file is included only once
get_filename_component(CMAKE_CURRENT_LIST_FILENAME ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
if(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED)
  return()
endif()
set(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED 1)

set(proj Lua)

# follow the standard EP_PREFIX locations
set(lua_binary_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj}-build)
set(lua_source_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj})
set(lua_install_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj})


file(WRITE "${lua_binary_dir}/CMakeCacheInit.txt" "${ep_common_cache}" )

set(lua_PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/lua.cmake
  ${lua_source_dir}/CMakeLists.txt
)

ExternalProject_Add(Lua
  URL https://www.lua.org/ftp/lua-5.1.5.tar.gz
  URL_MD5 2e115fe26e435e33b0d5c022e4490567
  PATCH_COMMAND ${lua_PATCH_COMMAND}
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    --no-warn-unused-cli
    -C "${lua_binary_dir}/CMakeCacheInit.txt"
    ${ep_common_args}
    -D BUILD_SHARED_LIBS:BOOL=OFF
    -D CMAKE_INSTALL_PREFIX:PATH=${lua_install_dir}
)
set(SITK_LUA_EXECUTABLE  "${lua_install_dir}/bin/lua")
