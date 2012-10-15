if( MSVC )
  # suppress warning in Visual Studio about the securtiy of methods
  add_definitions (-D_CRT_SECURE_NO_WARNINGS)
endif()

file ( GLOB LUA_LIB_SOURCE src/*.c )
list ( REMOVE_ITEM LUA_LIB_SOURCE src/lua.c )
add_library ( lua5 STATIC ${LUA_LIB_SOURCE} )

set ( LUA_SOURCE src/lua.c )
add_executable ( lua ${LUA_SOURCE} )
target_link_libraries ( lua lua5 )

if ( UNIX )
  target_link_libraries ( lua m )
endif()
 