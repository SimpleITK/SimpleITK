
#------------------------------------------------------------------------------
# Strip Option

# Add option to strip wrapping libraries.
# Since the wrapping libraries don't get installed by the normal cmake
# installation process, this option enables stripping of the libraries
# as part of the build process. It should be used on the laguage
# targets and the the SimpleITK iterface, as those can be installed
# into the system.
option(SimpleITK_BUILD_STRIP "Strip executables and libraries after building." OFF)
mark_as_advanced(SimpleITK_BUILD_STRIP)
set(CMAKE_STRIP_FLAGS "-x" CACHE STRING "Flags used by strip in the post_build.")
mark_as_advanced(CMAKE_STRIP_FLAGS)
separate_arguments(CMAKE_STRIP_FLAGS)

function(sitk_strip_target tgt)
  if(NOT SimpleITK_BUILD_STRIP OR "${CMAKE_STRIP}" STREQUAL "" )
    return()
  endif()
  get_property(type TARGET ${tgt} PROPERTY TYPE)
  if(NOT type STREQUAL STATIC_LIBRARY)
    add_custom_command(
      TARGET ${tgt}
      POST_BUILD
      COMMAND ${CMAKE_STRIP} ${CMAKE_STRIP_FLAGS} "$<TARGET_FILE:${tgt}>"
      )
  endif()

endfunction()
