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

set(_NAMES lua)

if(NOT LuaInterp_FIND_VERSION_MAJOR EQUAL 0)
  list(INSERT _NAMES 0 lua${LuaInterp_FIND_VERSION_MAJOR})
  if(NOT LuaInterp_FIND_VERSION_MINOR EQUAL 0)
    list(
      INSERT
      _NAMES
      0
      lua${LuaInterp_FIND_VERSION_MAJOR}.${LuaInterp_FIND_VERSION_MINOR}
    )
  endif()
endif()

find_program(LUA_EXECUTABLE NAMES ${_NAMES})

if(LUA_EXECUTABLE)
  ### LUA_VERSION
  execute_process(
    COMMAND
      ${LUA_EXECUTABLE} -v
    OUTPUT_VARIABLE LUA_EXECUTABLE_VERSION_STRING
    ERROR_VARIABLE LUA_EXECUTABLE_VERSION_STRING
    RESULT_VARIABLE LUA_VERSION_RESULT_VARIABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
  )
  if(NOT LUA_VERSION_RESULT_VARIABLE)
    string(
      REGEX MATCH
      "([0-9]*)([.])([0-9]*)([.]*)([0-9]*)"
      LUA_EXECUTABLE_VERSION
      ${LUA_EXECUTABLE_VERSION_STRING}
    )
  endif()
endif()

if(CMAKE_VERSION VERSION_GREATER_EQUAL 2.19)
  set(_args "HANDLE_VERSION_RANGE")
endif()

# handle the QUIETLY and REQUIRED arguments and set LUA_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  LuaInterp
  REQUIRED_VARS
    LUA_EXECUTABLE
  VERSION_VAR LUA_EXECUTABLE_VERSION
  ${_args}
)
mark_as_advanced(LUA_EXECUTABLE)
