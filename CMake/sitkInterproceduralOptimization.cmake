#------------------------------------------------------------------------------
# Interprocedural optimization (LTO) option
#
# The CMAKE_INTERPROCEDURAL_OPTIMIZATION_<CONFIG> variables are set here,
# before ITK is added, so that FetchContent and SuperBuild ITK builds are
# compiled with IPO too. Debug builds are left unchanged.
option(
  SimpleITK_INTERPROCEDURAL_OPTIMIZATION
  "Enable interprocedural optimization (LTO) for optimized build types. Reduces binary size at the cost of longer build times and larger static libraries."
  OFF
)

if(SimpleITK_INTERPROCEDURAL_OPTIMIZATION)
  include(CheckIPOSupported)
  check_ipo_supported(
    RESULT _sitk_ipo_supported
    OUTPUT _sitk_ipo_output
    LANGUAGES
      C
      CXX
  )
  if(NOT _sitk_ipo_supported)
    message(
      FATAL_ERROR
      "SimpleITK_INTERPROCEDURAL_OPTIMIZATION is ON but IPO is not supported: ${_sitk_ipo_output}"
    )
  endif()
  foreach(_config RELEASE RELWITHDEBINFO MINSIZEREL)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_${_config} ON)
  endforeach()
endif()
