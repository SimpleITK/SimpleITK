file ( GLOB LUA_SOURCE lua-5.1.4/src/*.c )
list ( REMOVE_ITEM LUA_SOURCE lua-5.1.4/src/luac.c )
add_executable ( lua ${LUA_SOURCE} )
