#
# Migrate SITK prefixed CMake options to SimpleITK
#
# sitk_legacy_naming( new_var_name [old_var_name] )
#   new_var_name - a variable name which has the prefix migrated from
# "SITK" to SimpleITK.
#
# This macro will print a warning if the old variable is set. Then
# sets the new variable value to the value of the old variable and
# delete the old variable from the cache.
#

# force set a value into the cache, but keep the properties
function(_force_cache_set var value)
  get_property( type CACHE ${var} PROPERTY TYPE )
  get_property( helpstring CACHE ${var} PROPERTY HELPSTRING )
  get_property( strings CACHE ${var} PROPERTY STRINGS )

  set( ${var} "${value}" CACHE "${type}" "${helpstring}" FORCE )

endfunction()

macro(sitk_legacy_naming new_var_name )


  if(NOT "x${ARGV1}x" STREQUAL "xx")
    set( old_var_name ${ARGV1} )
  else()
    string( REGEX REPLACE  "^SimpleITK_" "SITK_" old_var_name "${new_var_name}" )
  endif()

  if (DEFINED "${old_var_name}")
    message(WARNING "SimpleITK variable \"${old_var_name}\" is \
      deprecated use \"${new_var_name}\" instead.")

    _force_cache_set( ${new_var_name} ${${old_var_name}} )

    unset(${old_var_name} CACHE)

    list(LENGTH extra_macro_args num_extra_args)
    if (${num_extra_args} GREATER 0)
        list(GET extra_macro_args 0 optional_arg)
        message ("Got an optional arg: ${optional_arg}")
    endif ()
  endif()

endmacro()
