cmake_minimum_required ( VERSION 2.8.1 FATAL_ERROR )


if(POLICY CMP0025)
  cmake_policy(SET CMP0025 OLD)
endif()


project (LUA C)

# Setup build locations.
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
endif()



#------------------------------------------------------------------------------
# Variables for use in install rules:

if(NOT LUA_INSTALL_RUNTIME_DIR)
  set(LUA_INSTALL_RUNTIME_DIR "bin")
endif()
if(NOT LUA_INSTALL_LIBRARY_DIR)
  set(LUA_INSTALL_LIBRARY_DIR "lib")
endif()
if(NOT LUA_INSTALL_ARCHIVE_DIR)
  set(LUA_INSTALL_ARCHIVE_DIR "lib")
endif()
if(NOT LUA_INSTALL_INCLUDE_DIR)
  set(LUA_INSTALL_INCLUDE_DIR "include")
endif()


if( MSVC )
  # suppress warning in Visual Studio about the securtiy of methods
  add_definitions (-D_CRT_SECURE_NO_WARNINGS)

  # suppress warning:
  # '<<' : result of 32-bit shift implicitly converted to 64 bits (was 64-bit shift intended?)
  SET( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} /wd4334" )
endif()

if( APPLE )
  if("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    # suppress Clang warnings about empty loop bodies and deprecated declarations (tmpnam)
    SET( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wno-empty-body -Wno-deprecated-declarations" )
  endif()
endif()

# define the lua core source files
set (LUA_CORE_SRCS src/lapi.c src/lcode.c src/ldebug.c src/ldo.c src/ldump.c
     src/lfunc.c src/lgc.c src/llex.c src/lmem.c src/lobject.c src/lopcodes.c
     src/lparser.c src/lstate.c src/lstring.c src/ltable.c src/ltm.c  src/lundump.c
     src/lvm.c src/lzio.c)

# define the lua lib source files
set (LUA_LIB_SRCS src/lauxlib.c src/lbaselib.c src/ldblib.c src/liolib.c
     src/lmathlib.c src/loslib.c src/ltablib.c src/lstrlib.c src/loadlib.c src/linit.c)

# create the library
add_library (lua ${LUA_LIB_SRCS} ${LUA_CORE_SRCS})

# create the lue executable and link it to the lib
add_executable (luaexec src/lua.c)
target_link_libraries (luaexec lua)

# name the executable lua just like the library
set_target_properties(luaexec PROPERTIES OUTPUT_NAME lua)

if ( UNIX )
  target_link_libraries ( luaexec m )
endif()

install ( TARGETS luaexec
  RUNTIME DESTINATION ${LUA_INSTALL_RUNTIME_DIR}
  LIBRARY DESTINATION ${LUA_INSTALL_LIBRARY_DIR}
  ARCHIVE DESTINATION ${LUA_INSTALL_ARCHIVE_DIR}
  )
