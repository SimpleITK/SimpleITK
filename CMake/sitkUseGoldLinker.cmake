# Add CMake option for linker flags to enable GNU's gold linker.
#
# By default the if the "use-ld=gold" flag is supported by the
# compiler then it is used.
#
# USE_GOLD_LINKER - a CMake option used to control the usage of the
# gold linker.

include(CheckCXXCompilerFlag)

function(sitk_check_gold_linker output_var)
  if (MSVC)
    set(have_fold 0)
  else()
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -fuse-ld=gold")
    check_cxx_source_compiles("int main() {return 0;}" have_gold)
  endif()
  set("${output_var}" "${have_gold}" PARENT_SCOPE)
endfunction()

if(NOT DEFINED USE_GOLD_LINKER)
  sitk_check_gold_linker(_USE_GOLD_LINKER_default)
endif()

option(USE_GOLD_LINKER "Use ld.gold linker (decreases linking time if available)" ${_USE_GOLD_LINKER_default})
mark_as_advanced(USE_GOLD_LINKER)
if(USE_GOLD_LINKER)
  set(CMAKE_EXE_LINKER_FLAGS "-fuse-ld=gold ${CMAKE_EXE_LINKER_FLAGS}")
  set(CMAKE_MODULE_LINKER_FLAGS "-fuse-ld=gold ${CMAKE_MODULE_LINKER_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "-fuse-ld=gold ${CMAKE_SHARED_LINKER_FLAGS}")
endif()
