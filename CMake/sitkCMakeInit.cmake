set(SITK_CMAKE_MINIMUM_REQUIRED_VERSION "3.23.0")
set(SITK_CMAKE_POLICY_VERSION "3.23")

# cache_list_append( <cache list name> [<element> ...])
#
# Appends elements to a list cache variable as an internal entry.
function(cache_list_append cache_variable)
  set(_list ${${cache_variable}})
  list(APPEND _list ${ARGN})
  set(${cache_variable} ${_list} CACHE INTERNAL "")
endfunction()
