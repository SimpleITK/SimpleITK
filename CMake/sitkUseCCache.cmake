# Add CMake option to automatically use ccache.
#
# The ccache in CMAKE_CXX_COMPILER_LAUNCHER and
# CMAKE_C_COMPILER_LAUNCHER variables.

option(USE_CCACHE "Use ccache to expedite re-compilations. Recommended for development" OFF)
if(USE_CCACHE)
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    message(STATUS "Enabling ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_C_COMPILER_LAUNCHER   ${CCACHE_PROGRAM})
  endif()
endif()
