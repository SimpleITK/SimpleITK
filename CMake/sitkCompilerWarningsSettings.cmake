# trict-null-sentinel Check the set of common warning flags supported by C and C++ compilers
# check_compiler_warning_flags(<c_flags_var> <cxx_flags_var>)
#  <c_flags_var> - variable to store valid C warning flags
#  <cxx_flags_var> - variable to store valid CXX warning flags
# This internally calls the check_c_compiler_flag and check_cxx_compiler_flag macros.

# To create a portable build system, it is best to not
# test for platforms, but to test for features.
#
# Instead of testing "if Windows then do this", test for
# "if the -Wno-invalid-offsetof flag works then use it".
# You can do that with the CheckCCompilerFlag module,
# for example:

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

#
# this functions loops through the list to add the flags
# supported by the current compiler
function(test_cc_flags c_flag_var flag_list)
  set(local_c_flags "")
  foreach(flag IN LISTS ${flag_list})
    string(REPLACE "=" "_" flag_var ${flag} )
    check_c_compiler_flag(${flag} C_HAS${flag_var})
    if(${C_HAS${flag_var}})
      set(local_c_flags "${local_c_flags} ${flag}")
    endif()
  endforeach(flag)
  set(${c_flag_var} "${local_c_flags}" PARENT_SCOPE)
endfunction(test_cc_flags)

#
# this functions loops through the list to add the flags
# supported by the current compiler
function(test_cxx_flags cxx_flag_var flag_list)
  set(local_cxx_flags "")
  foreach(flag IN LISTS ${flag_list})
    string(REPLACE "=" "_" flag_var ${flag} )
    check_cxx_compiler_flag(${flag} CXX_HAS${flag_var})
    if(${CXX_HAS${flag_var}})
      set(local_cxx_flags "${local_cxx_flags} ${flag}")
    endif()
  endforeach(flag)
  set(${cxx_flag_var} "${local_cxx_flags}" PARENT_SCOPE)
endfunction(test_cxx_flags)


# On windows, the most verbose compiler options
# is reporting 1000's of wanings in windows
# header files, for now, limit the number of
# warnings to level 3
if( WIN32 )
  set(VerboseWarningsFlag -W3 )
  # A better solution would be to use -Wall,
  # and then disable warnings one by one
  # set(VerboseWarningsFlag -Wall -wd4820 -wd4682 )
else()
  set(VerboseWarningsFlag -Wall )
endif()

set(warning_flags_to_test
  ${VerboseWarningsFlag}
  -Wno-long-double           # needed on APPLE
  -Wno-long-long             # needed on gcc 4.5.2
  -Wno-unused-local-typedefs # needed with gcc 4.8
  -Wno-strict-overflow       # needed with gcc 4.8
  -Wextra
  -Wformat=2
  -Wno-format-nonliteral
  -Wunused
  -Wpointer-arith
  -Winvalid-pch
  -Wcast-align
  -Wdisabled-optimization
  -Woverloaded-virtual
  -Wshadow
  -Wwrite-strings
  -Wstrict-null-sentinel
)

# add C++ only flag
set(cxx_flags_to_test ${warning_flags_to_test} -Wno-invalid-offsetof )

test_cxx_flags(CXX_ADDITIONAL_WARNING_FLAGS cxx_flags_to_test)

