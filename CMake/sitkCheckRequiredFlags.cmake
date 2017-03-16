#
# Sets the following variables:
#   SimpleITK_PRIVATE_COMPILE_OPTIONS
#   SimpleITK_PUBLIC_COMPILE_OPTIONS
#
# In particular, this marks the "-std=", and the "-stdlib=" as
# required, if present and check if c++11 is needed.

set( SimpleITK_PUBLIC_COMPILE_OPTIONS "")
set( SimpleITK_PRIVATE_COMPILE_OPTIONS "")

include(CheckCXXCompilerFlag)

if(MSVC)
  # /bigobj is required for windows builds because of the size of
  # some object files (CastImage for instance)
  # Also supress the pesky warning about std::vector not being marked
  # for export in the dll
  list(APPEND SimpleITK_PRIVATE_COMPILE_OPTIONS /bigobj /wd4251 )

  # Avoid some warnings
  add_definitions ( -D_SCL_SECURE_NO_WARNINGS )


  # force debug linking not to be incremental
  foreach( _varName
      CMAKE_EXE_LINKER_FLAGS_DEBUG
      CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO
      CMAKE_MODULE_LINKER_FLAGS_DEBUG
      CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO
      CMAKE_SHARED_LINKER_FLAGS_DEBUG
      CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO )
    if(DEFINED ${_varName})
      STRING(REGEX REPLACE "INCREMENTAL(:[a-zA-Z]+)?" "INCREMENTAL:NO" ${_varName} ${${_varName}})
    endif()
  endforeach()

endif()

if(MINGW)
  list(APPEND SimpleITK_PRIVATE_COMPILE_OPTIONS "-Wa,-mbig-obj" )
endif()


#
# Search CMAKE_CXX_FLAGS for flags that should be considered required,
# and propagated to other projects, via the
# SimpleITK_PUBLIC_COMPILE_OPTIONS variable.
#

string(REPLACE " " ";" cmake_cxx_flags_list "${CMAKE_CXX_FLAGS}")

# list of regular expressions flags that are to be required flags for SimpleITK
set(required_flags_regex_to_test
  "^-stdlib="
  "^-std=" # required to be last
)

foreach(f ${cmake_cxx_flags_list})
  foreach( _r ${required_flags_regex_to_test} )
    string(REGEX MATCH  ${_r} _HAS_FLAG ${f} )
    if (_HAS_FLAG )
      list(APPEND SimpleITK_PUBLIC_COMPILE_OPTIONS ${f})
    endif()
  endforeach()
endforeach()

#
# Check if we need to enable C++11 with a compiler flag
#

if(NOT _HAS_FLAG)

  check_cxx_compiler_flag( "-std=c++11" CXX_HAS_stdcxx11)
  if (CXX_HAS_stdcxx11)

    message(STATUS "Checking if c++11 is required...")
    try_compile(SITK_CHECK_CXX11
      "${PROJECT_BINARY_DIR}/CMakeTmp"
      "${CMAKE_CURRENT_LIST_DIR}/sitk_check_cxx11_required.cxx"
      OUTPUT_VARIABLE OUTPUT)
    if(${SITK_CHECK_CXX11})
      message(STATUS "Checking if c++11 is required... NO" )
    else()
      message(STATUS "Checking if c++11 is required... YES" )
      file(APPEND ${CMAKE_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/CMakeError.log
        "Checking if C++11 required try_compile failed with the following output:\n"
        "${OUTPUT}\n")
      list(APPEND SimpleITK_PUBLIC_COMPILE_OPTIONS "-std=c++11")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()

  endif()

endif()

list(REMOVE_DUPLICATES SimpleITK_PUBLIC_COMPILE_OPTIONS)
list(REMOVE_DUPLICATES SimpleITK_PRIVATE_COMPILE_OPTIONS)
