file ( GLOB LUA_LIB_SOURCE lua-5.1.4/src/*.c )
list ( REMOVE_ITEM LUA_LIB_SOURCE lua-5.1.4/src/lua.c lua-5.1.4/src/luac.c )
add_library ( lua5 ${LUA_LIB_SOURCE} )

file ( GLOB LUA_SOURCE lua-5.1.4/src/lua.c )
add_executable ( lua ${LUA_SOURCE} )
target_link_libraries ( lua lua5 )


if ( UNIX )
  target_link_libraries ( lua curses m )
endif()
