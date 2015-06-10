#.rst:
# FindLuaInterp
# --------
#
# Find Lua Interpreter
#
# ::
#
#   LUA_EXECUTABLE     - the full path to lua
#   LUA_EXECUTABLE_FOUND          - If false, don't attempt to use lua
#   LUA_EXECUTABLE_VERSION_STRING - version of lua found

find_program(LUA_EXECUTABLE
  NAMES lua
  )

if(LUA_EXECUTABLE)
  ### LUA_VERSION
  execute_process(
    COMMAND ${LUA_EXECUTABLE} -v
    OUTPUT_VARIABLE
      LUA_EXECUTABLE_VERSION_STRING
    ERROR_VARIABLE
      LUA_EXECUTABLE_VERSION_STRING
    RESULT_VARIABLE
      LUA_VERSION_RESULT_VARIABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
    )
  if (NOT LUA_VERSION_RESULT_VARIABLE)
    string( REGEX MATCH "([0-9]*)([.])([0-9]*)([.]*)([0-9]*)"
      LUA_EXECUTABLE_VERSION
      ${LUA_EXECUTABLE_VERSION_STRING} )
  endif()
endif()


# handle the QUIETLY and REQUIRED arguments and set LUA_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Lua
                                  REQUIRED_VARS LUA_EXECUTABLE
                                  VERSION_VAR LUA_VERSION_STRING)

mark_as_advanced(LUA_EXECUTABLE)
