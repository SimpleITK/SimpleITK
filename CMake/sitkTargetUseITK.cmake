# target_use_itk
#
# This function has the following form:
#   sitk_target_use_itk(<target>
#                       <PRIVATE|PUBLIC|INTERFACE>
#                       [BUILD_INTERFACE]
#                       [itk_module [itk_module [...]]])
#
#   It configures the target, with the require include directories and
# link libraries to use the list of itk modules provided. The keyword
# to indicate interface of the library is also required. If the string
# BUILD_INTERFACE is provided, then the $<BUILD_INTERFACE:...>
# generator expression will be added to the itk modules include
# directories.

function(sitk_target_use_itk target_name interface_keyword)

  set(itk_modules ${ARGV})
  list(REMOVE_AT itk_modules 0 1)
  list(GET ARGV 2 build_interface)
  if(build_interface STREQUAL "BUILD_INTERFACE")
    list(REMOVE_AT itk_modules 0)
  else()
    unset(build_interface)
  endif()

  itk_module_config(_itk ${itk_modules})

  if(_itk_LIBRARY_DIRS)
    link_libraries(${_itk_LIBRARY_DIRS})
  endif()

  if(_itk_LIBRARIES)
    target_link_libraries( ${target_name}
      ${interface_keyword}
      ${_itk_LIBRARIES} )
  endif()
  if(_itk_INCLUDE_DIRS)
    if(build_interface)
      target_include_directories( ${target_name}
        ${interface_keyword}
        $<BUILD_INTERFACE:${_itk_INCLUDE_DIRS}> )
    else()
      target_include_directories( ${target_name}
        ${interface_keyword}
        ${_itk_INCLUDE_DIRS})
    endif()
  endif()

endfunction()
