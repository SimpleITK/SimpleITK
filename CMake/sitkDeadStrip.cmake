#
# Discard unreferenced functions and data and fold identical functions at
# link time. Intended for distribution builds; GCC and Clang on ELF only.
#
option(
  SimpleITK_DEAD_STRIP
  "Discard unreferenced code and data and fold identical functions at link time (GCC/Clang on ELF)."
  OFF
)
mark_as_advanced(SimpleITK_DEAD_STRIP)

if(SimpleITK_DEAD_STRIP AND NOT MSVC AND NOT APPLE)
  include(sitkUseGoldLinker)

  foreach(_lang C CXX)
    string(
      STRIP
      "${CMAKE_${_lang}_FLAGS} -ffunction-sections -fdata-sections"
      CMAKE_${_lang}_FLAGS
    )
  endforeach()

  set(_sitk_dead_strip_flags "-Wl,--gc-sections")
  if(
    USE_GOLD_LINKER
    AND
      (
        CMAKE_VERSION
          VERSION_LESS
          "3.29"
        OR
          CMAKE_LINKER_TYPE
            STREQUAL
            "GOLD"
      )
  )
    set(_sitk_have_icf_safe 1)
  else()
    include(CheckLinkerFlag)
    # One cached probe result per CMAKE_LINKER_TYPE, so a changed type is probed again.
    set(_sitk_icf_safe_var "_sitk_have_icf_safe_${CMAKE_LINKER_TYPE}")
    check_linker_flag(
      CXX
      "-Wl,--icf=safe"
      ${_sitk_icf_safe_var}
    )
    set(_sitk_have_icf_safe "${${_sitk_icf_safe_var}}")
  endif()
  if(_sitk_have_icf_safe)
    string(APPEND _sitk_dead_strip_flags " -Wl,--icf=safe")
  endif()

  foreach(_kind EXE MODULE SHARED)
    string(
      STRIP
      "${CMAKE_${_kind}_LINKER_FLAGS} ${_sitk_dead_strip_flags}"
      CMAKE_${_kind}_LINKER_FLAGS
    )
  endforeach()
endif()
