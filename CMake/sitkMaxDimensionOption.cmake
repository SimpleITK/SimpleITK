#
# A common CMake file for consistently initializing and verifying the
# SimpleITK_MAX_DIMENSION CMake variable.
#


set(SimpleITK_MAX_DIMENSION_DEFAULT 5)
# 1900 = VS 14.0 (Visual Studio 2015)
if(MSVC AND MSVC_VERSION VERSION_LESS 1900)
  set( SimpleITK_MAX_DIMENSION_DEFAULT 3 )
endif()

if (DEFINED SimpleITK_4D_Image)
  message(WARNING "SimpleITK variable \"SimpleITK_4D_Image\" is \
                   deprecated set \"SimpleITK_MAX_DIMENSION\" instead." )
  if (NOT SimpleITK_4D_Image)
    set( SimpleITK_MAX_DIMENSION_DEFAULT 3 )
  endif()
endif()

set( "SimpleITK_MAX_DIMENSION" "${SimpleITK_MAX_DIMENSION_DEFAULT}"
  CACHE STRING "Add Image and I/O support up to max dimension (integer)." )
mark_as_advanced( SimpleITK_MAX_DIMENSION )

if (NOT SimpleITK_MAX_DIMENSION MATCHES "^[0-9]+$")
  message(FATAL_ERROR "Expect \"SimpleITK_MAX_DIMENSION\" as an integer but got \"${SimpleITK_MAX_DIMENSION}\".")
elseif ( SimpleITK_MAX_DIMENSIONS LESS 3 )
  message(FATAL_ERROR "The minimum  supported value for \"SimpleITK_MAX_DIMENSION\" is 3.")
endif()
