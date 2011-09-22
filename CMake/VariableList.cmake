
#
# Function converts a list of cmake cache varibles to a string of
# cmake code which set each cmake cache variable. The output in cache
# is suitable to be writen to a file for "-C file" command line
# argument for cmake.
#
function( VariableListToCache var_list cache )
  foreach( var IN LISTS ${var_list} )
    if( NOT ${var} STREQUAL "" ) # if variable has been set
      get_property( type CACHE ${var} PROPERTY TYPE )
      get_property( advanced CACHE ${var} PROPERTY ADVANCED )
      get_property( helpstring CACHE ${var} PROPERTY HELPSTRING )
      if ( NOT "${type}" )

        set( type STRING )
      endif()
      set( _cache "${_cache}
set( ${var} \"${${var}}\" CACHE \"${type}\" \"${helpstring}\" FORCE )
if( ${advanced} )
  mark_as_advanced( ${var} )
endif()" )
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
    if( NOT ${var} STREQUAL "" ) # if variable has been set
      get_property( type CACHE ${var} PROPERTY TYPE )
      list( APPEND _args "-D${var}:${type}=${${var}}" )
    endif()
  endforeach()
  set( ${args} "${_args}" PARENT_SCOPE)
endfunction( )
