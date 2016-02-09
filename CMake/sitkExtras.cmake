
#
# Link a library to a target such that the symbols are resolved at
# run-time not link-time. This should be used when compiling a
# loadable module when the symbols should be resolve from the run-time
# environment where the module is loaded, and not a specific system
# library.
#
# Specifically, for OSX it uses undefined dynamic_lookup. This is
# simular to using "-shared" on Linux where undefined symbols are
# ignored.
#
# http://blog.tim-smith.us/2015/09/python-extension-modules-os-x/
#
macro( sitk_target_link_libraries_with_dynamic_lookup target )
  if ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    set_target_properties( ${target} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup" )
  else()
    target_link_libraries ( ${target} ${ARGN}  )
  endif()
endmacro()
