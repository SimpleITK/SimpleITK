#.rst:
# FindLuaInterp
# -------------
#
# Find Lua Interpreter
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ::
#
#   LUA_EXECUTABLE                - the full path to lua interpreter
#   LUA_EXECUTABLE_FOUND          - If false, don't attempt to use lua
#   LUA_EXECUTABLE_VERSION_STRING - version of lua found (e.g. "5.3.6")
#   LUA_EXECUTABLE_VERSION_MAJOR  - major version of lua found
#   LUA_EXECUTABLE_VERSION_MINOR  - minor version of lua found
#   LUA_EXECUTABLE_VERSION_PATCH  - patch version of lua found

# Build list of possible executable names, with versioned names first
set(_NAMES)

if(LuaInterp_FIND_VERSION_MAJOR)
  if(LuaInterp_FIND_VERSION_MINOR)
    # Prefer exact version match
    list(
      APPEND
      _NAMES
      lua${LuaInterp_FIND_VERSION_MAJOR}.${LuaInterp_FIND_VERSION_MINOR}
      lua${LuaInterp_FIND_VERSION_MAJOR}${LuaInterp_FIND_VERSION_MINOR}
    )
  endif()
  # Then try major version
  list(APPEND _NAMES lua${LuaInterp_FIND_VERSION_MAJOR})
endif()

# Finally try generic name
list(APPEND _NAMES lua)

find_program(LUA_EXECUTABLE NAMES ${_NAMES})

if(LUA_EXECUTABLE)
  # Get version from lua -v output
  execute_process(
    COMMAND
      ${LUA_EXECUTABLE} -v
    OUTPUT_VARIABLE _lua_version_output
    ERROR_VARIABLE _lua_version_output
    RESULT_VARIABLE _lua_version_result
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
  )

  if(_lua_version_result EQUAL 0)
    # Extract version number (e.g., "Lua 5.3.6" -> "5.3.6")
    if(_lua_version_output MATCHES "Lua ([0-9]+\\.[0-9]+\\.[0-9]+)")
      set(LUA_EXECUTABLE_VERSION_STRING "${CMAKE_MATCH_1}")
    elseif(_lua_version_output MATCHES "Lua ([0-9]+\\.[0-9]+)")
      set(LUA_EXECUTABLE_VERSION_STRING "${CMAKE_MATCH_1}")
    endif()

    # Parse version components
    if(
      LUA_EXECUTABLE_VERSION_STRING
        MATCHES
        "^([0-9]+)\\.([0-9]+)(\\.([0-9]+))?"
    )
      set(LUA_EXECUTABLE_VERSION_MAJOR "${CMAKE_MATCH_1}")
      set(LUA_EXECUTABLE_VERSION_MINOR "${CMAKE_MATCH_2}")
      set(LUA_EXECUTABLE_VERSION_PATCH "${CMAKE_MATCH_4}")
      if(NOT LUA_EXECUTABLE_VERSION_PATCH)
        set(LUA_EXECUTABLE_VERSION_PATCH "0")
      endif()
      set(LUA_EXECUTABLE_VERSION "${LUA_EXECUTABLE_VERSION_STRING}")
    endif()
  endif()
endif()

# Handle the QUIETLY and REQUIRED arguments and set LuaInterp_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  LuaInterp
  REQUIRED_VARS
    LUA_EXECUTABLE
  VERSION_VAR LUA_EXECUTABLE_VERSION_STRING
  HANDLE_VERSION_RANGE
)

mark_as_advanced(LUA_EXECUTABLE)

if(LuaInterp_FOUND)
  set(LUA_EXECUTABLE_FOUND TRUE)
endif()
