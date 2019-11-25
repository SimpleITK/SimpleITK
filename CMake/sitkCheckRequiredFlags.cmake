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

foreach( _r ${required_flags_regex_to_test} )
  set(_HAS_FLAG 0)
  foreach(f ${cmake_cxx_flags_list})
    string(REGEX MATCH  ${_r} _match ${f} )
    if (_match )
      list(APPEND SimpleITK_PUBLIC_COMPILE_OPTIONS ${f})
      set(_HAS_FLAG ${_match})
    endif()
  endforeach()
endforeach()

set(HAS_CXX_STD_FLAG ${_HAS_FLAG})


#
# Let the user set the CXX_STANDARD via these CMake variable, although
# it is preferred to set it in the CXX_FLAGS, as it will be propagated
# to SimpleITK's public compile options.
#
if( DEFINED CMAKE_CXX_STANDARD
    OR DEFINED CMAKE_CXX_STANDARD_REQUIRED
    OR DEFINED CMAKE_CXX_EXTENSIONS )
  if(HAS_CXX_STD_FLAG)
    message(SEND_ERROR "CMake CXX standard variables are not supported
      concurrently with CXX flag: \"-std=\"! Use only one to configure CXX standard.")
  endif()
endif()

list(REMOVE_DUPLICATES SimpleITK_PUBLIC_COMPILE_OPTIONS)
list(REMOVE_DUPLICATES SimpleITK_PRIVATE_COMPILE_OPTIONS)
