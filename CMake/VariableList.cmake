
#
# Function converts a list of cmake cache varibles to a string of
# cmake code which set each cmake cache variable. The output in cache
# is suitable to be writen to a file for "-C file" command line
# argument for cmake.
#
function( VariableListToCache var_list cache )
  foreach( var IN LISTS ${var_list} )
    if( DEFINED var )
      set( value "${${var}}" )
      get_property( type CACHE ${var} PROPERTY TYPE )
      get_property( advanced CACHE ${var} PROPERTY ADVANCED )
      get_property( helpstring CACHE ${var} PROPERTY HELPSTRING )
      get_property( strings CACHE ${var} PROPERTY STRINGS )

      # apply escape sequences
      foreach( e "\\" "(" ")" "#" "$" "^" "@" )
        STRING( REPLACE "${e}" "\\${e}" value "${value}" )
      endforeach()

      if ( "${type}" STREQUAL "" )
        set( type STRING )
      endif()

      set( _cache "${_cache}
set( ${var} \"${value}\" CACHE \"${type}\" \"${helpstring}\" FORCE )")

      if( "${advanced}" )
              set( _cache "${_cache}
  mark_as_advanced( ${var} )")
       endif()
       if( NOT "${strings}" STREQUAL "" )
              set( _cache "${_cache}
  set_property(CACHE ${var} PROPERTY STRINGS \"${strings}\")")
       endif()
    endif()
  endforeach()
  set( ${cache} "${_cache}" PARENT_SCOPE)
endfunction( )

#
# Function which converts a list a cmake cache variable into a list of
# "-Dvar:type=value;" suitable for command line initialization.
#
function( VariableListToArgs var_list args )
  foreach( var IN LISTS ${var_list} )
    if( DEFINED ${var} AND NOT ${var} STREQUAL "" ) # if variable has been set
      get_property( type CACHE ${var} PROPERTY TYPE )
      if (NOT "${type}" STREQUAL "")
        set(type ":${type}")
      else()
        set(type ":UNINITIALIZED")
      endif()
      set(value ${${var}})
      STRING( REPLACE ";" "$<SEMICOLON>" value "${value}" )
      list( APPEND _args "-D${var}:${type}=${value}" )
    endif()
  endforeach()
  set( ${args} "${_args}" PARENT_SCOPE)
endfunction( )
