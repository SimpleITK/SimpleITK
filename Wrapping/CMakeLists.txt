
if(POLICY CMP0026)
  # Allow use of the LOCATION target property.
  #
  # These locations are use in a convoluted fashion with the runtime
  # configuration. This system should be refactored to support
  # generator expression. This would allow the use of the new policy.
  cmake_policy(SET CMP0026 OLD)
endif()
#
# General SWIG configuration
#
if ( WRAP_LUA OR WRAP_PYTHON OR WRAP_JAVA OR WRAP_CSHARP OR WRAP_TCL OR WRAP_R OR WRAP_RUBY )
  find_package ( SWIG 2 REQUIRED )

  include (UseSWIGLocal)

  set_source_files_properties ( SimpleITK.i PROPERTIES CPLUSPLUS ON )

  file(GLOB SWIG_EXTRA_DEPS
    "${SimpleITK_SOURCE_DIR}/Code/Common/include/*.h"
    "${SimpleITK_SOURCE_DIR}/Code/Registration/include/*.h"
    "${SimpleITK_SOURCE_DIR}/Code/IO/include/*.h")

  # make a manual list of dependencies for the Swig.i files
  list( APPEND SWIG_EXTRA_DEPS "${SimpleITK_BINARY_DIR}/Code/BasicFilters/include/SimpleITKBasicFiltersGeneratedHeaders.i"
    "${SimpleITK_BINARY_DIR}/Code/BasicFilters/include/SimpleITKBasicFiltersGeneratedHeaders.h"
    ${SimpleITKBasicFiltersGeneratedHeader}
     )

  # check if uint64_t is the same as unsigned long
  try_compile(SITK_ULONG_SAME_AS_UINT64
    ${SimpleITK_BINARY_DIR}/CMakeTmp
    ${SimpleITK_SOURCE_DIR}/CMake/same_uint64_ulong.cxx )

  # when "-DSWIGWORDSIZE64" is defined SWIG used unsigned long for uint64_t types
  if(${SITK_ULONG_SAME_AS_UINT64} )
    set ( CMAKE_SWIG_GLOBAL_FLAGS "-DSWIGWORDSIZE64" )
  endif()

endif()


# A general packaging target, not built by default, to build packages for each
# language.  This should depend on all language specific targets.
add_custom_target( dist cmake -E echo "Finished generating wrapped packages for distribution..." )


#
# lua SWIG configuration
#
if ( WRAP_LUA )
  add_subdirectory ( Lua )
endif()

#
# python SWIG configuration
#
if ( WRAP_PYTHON )
  add_subdirectory ( Python )
endif()

#
# ruby SWIG configuration
#
if ( WRAP_RUBY )
  add_subdirectory ( Ruby )
endif()

#
# JAVA SWIG configuration
#
if ( WRAP_JAVA )
  add_subdirectory( Java )
endif()

#
# C# SWIG configuration
#
if ( WRAP_CSHARP )
  add_subdirectory ( CSharp )
endif()

#
# TCL SWIG configuration
#
if ( WRAP_TCL )
  add_subdirectory ( Tcl )
endif()

#
# R SWIG configuration
#
if ( WRAP_R )
  add_subdirectory( R )
endif()
