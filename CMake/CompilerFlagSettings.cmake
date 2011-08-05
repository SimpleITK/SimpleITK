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
    check_c_compiler_flag(${flag} C_HAS${flag})
    if(${C_HAS${flag}})
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
    check_cxx_compiler_flag(${flag} CXX_HAS${flag})
    if(${CXX_HAS${flag}})
      set(local_cxx_flags "${local_cxx_flags} ${flag}")
    endif()
  endforeach(flag)
  set(${cxx_flag_var} "${local_cxx_flags}" PARENT_SCOPE)
endfunction(test_cxx_flags)

set(common_flags_to_test
-Wlong-long
-Wno-deprecated
-Wall
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

# Detection does not appear to work correctly for C
#set(cc_flags_to_test ${common_flags_to_test})
#test_cc_flags(C_RELEASE_DESIRED_FLAGS cc_flags_to_test)
#test_cc_flags(C_DEBUG_DESIRED_FLAGS cc_flags_to_test)

set(cxx_flags_to_test ${common_flags_to_test} -Wno-invalid-offsetof )
test_cxx_flags(CXX_RELEASE_DESIRED_FLAGS cxx_flags_to_test)
test_cxx_flags(CXX_DEBUG_DESIRED_FLAGS cxx_flags_to_test)

