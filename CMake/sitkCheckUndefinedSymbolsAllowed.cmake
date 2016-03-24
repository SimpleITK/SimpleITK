#
# Check if the linker allows undefined symbols for shared libraries.
#
# SITK_UNDEFINED_SYMBOLS_ALLOWED - true if the linker will allow
#   undefined symbols for shared libraries
#

function(_sitkCheckUndefinedSymbolsAllowed)

  set(VARIABLE "SITK_UNDEFINED_SYMBOLS_ALLOWED")
  set(cache_var "${VARIABLE}_hash")

  # hash the CMAKE_FLAGS passed and check cache to know if we need to rerun
  string(MD5 cmake_flags_hash "${CMAKE_SHARED_LINKER_FLAGS}")

  if(NOT DEFINED "${cache_var}" )
    unset("${VARIABLE}" CACHE)
  elseif(NOT "${${cache_var}}" STREQUAL "${cmake_flags_hash}" )
    unset("${VARIABLE}" CACHE)
  endif()

  if(NOT DEFINED "${VARIABLE}")
    set(test_project_dir "${PROJECT_BINARY_DIR}/CMakeTmp/${VARIABLE}")

    file(WRITE "${test_project_dir}/CMakeLists.txt"
"
project(undefined C)
add_library(foo SHARED \"foo.c\")
")

    file(WRITE "${test_project_dir}/foo.c"
"
extern int bar(void);
int foo(void) {return bar()+1;}
")

    try_compile(${VARIABLE}
      "${test_project_dir}"
      "${test_project_dir}"
      undefined
      CMAKE_FLAGS
       "-DCMAKE_SHARED_LINKER_FLAGS='${CMAKE_SHARED_LINKER_FLAGS}'"
      OUTPUT_VARIABLE output)

    set(${cache_var} "${cmake_flags_hash}" CACHE INTERNAL  "hashed try_compile flags")

    if(${VARIABLE})
      message(STATUS "Performing Test ${VARIABLE} - Success")
    else()
      message(STATUS "Performing Test ${VARIABLE} - Failed")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
        "Performing Test ${VARIABLE} failed with the following output:\n"
        "${OUTPUT}\n")
    endif()
  endif()
endfunction()

_sitkCheckUndefinedSymbolsAllowed()
