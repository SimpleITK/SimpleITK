
# A general packaging target, not built by default, to build packages for each
# language.  This should depend on all language specific targets.

add_custom_target( dist ${CMAKE_COMMAND} -E echo "Finished generating wrapped packages for distribution..." )

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
