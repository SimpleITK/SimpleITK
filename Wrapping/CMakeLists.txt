
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
  find_package ( R REQUIRED )
  include_directories ( ${R_INCLUDE_DIR} )

  # Run swig
  set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS})
  set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
  set(SWIG_MODULE_SimpleITK_EXTRA_DEPS ${SWIG_EXTRA_DEPS}
    ${CMAKE_CURRENT_SOURCE_DIR}/R.i )
  SWIG_add_module ( SimpleITK r SimpleITK.i SimpleITKR_wrap.cxx )
  SWIG_link_libraries ( SimpleITK ${SimpleITK_LIBRARIES} )

  # on some platforms the r libraries are not required at link time...
  if(R_LIBRARIES)
    SWIG_link_libraries ( SimpleITK ${R_LIBRARIES} )
  endif()

  set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/SimpleITKR_wrap.cxx PROPERTIES COMPILE_FLAGS "-w")

  get_target_property( SIMPLEITKR_BINARY_MODULE ${SWIG_MODULE_SimpleITK_TARGET_NAME} LOCATION )
  file(TO_NATIVE_PATH "${SIMPLEITKR_BINARY_MODULE}" SIMPLEITKR_NATIVE_BINARY_MODULE )


  add_dependencies( ${SWIG_MODULE_SimpleITK_TARGET_NAME} ConfigureFileBuildtime )

  # set the output directory for the R library to the binary packaging location
  set_target_properties( ${SWIG_MODULE_SimpleITK_TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Rpackaging/SimpleITK/src/)

  sitk_strip_target( ${SWIG_MODULE_SimpleITK_TARGET_NAME} )

  # copy the R files a binary package
  add_custom_command( TARGET ${SWIG_MODULE_SimpleITK_TARGET_NAME}
      PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${SimpleITK_SOURCE_DIR}/Wrapping/Rpackaging ${CMAKE_CURRENT_BINARY_DIR}/Rpackaging
      COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/Rpackaging/SimpleITK/data/
  )
  add_custom_command( TARGET ${SWIG_MODULE_SimpleITK_TARGET_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/RLib
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/SimpleITK.R ${CMAKE_CURRENT_BINARY_DIR}/Rpackaging/SimpleITK/R/
      # copy sample images
      COMMAND ${CMAKE_COMMAND} -E copy ${SimpleITK_BINARY_DIR}/ExternalData/Testing/Data/Input/cthead1.png  ${CMAKE_CURRENT_BINARY_DIR}/Rpackaging/SimpleITK/data/
      COMMAND ${CMAKE_COMMAND} -E copy ${SimpleITK_BINARY_DIR}/ExternalData/Testing/Data/Input/cthead1-Float.mha  ${CMAKE_CURRENT_BINARY_DIR}/Rpackaging/SimpleITK/data/
      # install for running tests and create binary package
      COMMAND ${R_COMMAND} CMD INSTALL --build ${CMAKE_CURRENT_BINARY_DIR}/Rpackaging/SimpleITK --library=${CMAKE_CURRENT_BINARY_DIR}/RLib

      COMMENT "Installing R package for testing and building binary version for distribution"
       )

endif()
