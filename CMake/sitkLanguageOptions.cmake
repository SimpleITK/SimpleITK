#
# - This module finds the languages supported by SimpleITK, and
#present the option to enable support
#

#
# Currently this will search for Python, Java, TCL, Ruby, C#, R
# Additionally it give the option to wrap LUA.
#

include(sitkTargetLinkLibrariesWithDynamicLookup)

sitk_check_dynamic_lookup(MODULE
  SHARED
  SITK_UNDEFINED_SYMBOLS_ALLOWED
  )

if ( SITK_UNDEFINED_SYMBOLS_ALLOWED )
  set( _REQUIRED_LIBRARY "QUIET" )
else ( )
  set( _REQUIRED_LIBRARY "REQUIRED" )
endif ( )


option(WRAP_DEFAULT "The default initial value for wrapping a language when it is detected on the system." ON)
mark_as_advanced(WRAP_DEFAULT)

#
# Setup the option for each language
#

#-----------------------------------------------------------
# Lua

if ( DEFINED WRAP_LUA )
  set ( WRAP_LUA_DEFAULT ${WRAP_LUA} )
elseif ( NOT WRAP_DEFAULT )
  set( WRAP_LUA_DEFAULT OFF )
else ( )
  find_package ( Lua QUIET )
  if ( LUA_FOUND )
    set( WRAP_LUA_DEFAULT ${WRAP_DEFAULT} )
  else ( )
    set( WRAP_LUA_DEFAULT OFF )
  endif ( )
endif ( )

option ( WRAP_LUA "Wrap Lua" ${WRAP_LUA_DEFAULT} )

if ( WRAP_LUA )
  set( LUA_ADDITIONAL_LIBRARIES "" CACHE STRING "Additional libraries which may be needed for lua such as readline.")
  mark_as_advanced( LUA_ADDITIONAL_LIBRARIES )
  find_package ( Lua REQUIRED )
  find_package( LuaInterp REQUIRED )
  list( APPEND SITK_LANGUAGES_VARS
    LUA_EXECUTABLE
    LUA_LIBRARIES
    LUA_INCLUDE_DIR
    LUA_VERSION_STRING
    LUA_MATH_LIBRARY
    LUA_ADDITIONAL_LIBRARIES
    )
endif()



#-----------------------------------------------------------
# Python

if ( DEFINED WRAP_PYTHON )
  set ( WRAP_PYTHON_DEFAULT ${WRAP_PYTHON} )
elseif ( NOT WRAP_DEFAULT )
  set ( WRAP_PYTHON_DEFAULT OFF )
else ( )
  find_package ( PythonInterp QUIET)
  if ( PYTHONINTERP_FOUND )
    find_package ( PythonLibs ${PYTHON_VERSION_STRING} EXACT QUIET )
  else ()
    find_package ( PythonLibs QUIET )
  endif ( )
  if ( PYTHONLIBS_FOUND AND PYTHONINTERP_FOUND
      AND (PYTHON_VERSION_STRING VERSION_EQUAL PYTHONLIBS_VERSION_STRING) )
    set( WRAP_PYTHON_DEFAULT ${WRAP_DEFAULT} )
  else ( )
    set( WRAP_PYTHON_DEFAULT OFF )
  endif ( )
endif ( )

option( WRAP_PYTHON "Wrap Python" ${WRAP_PYTHON_DEFAULT} )

if ( WRAP_PYTHON )
  find_package ( PythonInterp REQUIRED)
  if ( PYTHONINTERP_FOUND )
    find_package ( PythonLibs ${PYTHON_VERSION_STRING} EXACT ${_REQUIRED_LIBRARY} )
  else ()
    find_package ( PythonLibs ${_REQUIRED_LIBRARY} )
  endif()
  if ( PYTHON_VERSION_STRING VERSION_LESS 2.7 )
    message( WARNING "Python version less than 2.7: \"${PYTHON_VERSION_STRING}\"." )
  endif()

  list( APPEND SITK_LANGUAGES_VARS
    PYTHON_DEBUG_LIBRARY
    PYTHON_EXECUTABLE
    PYTHON_LIBRARY
    PYTHON_INCLUDE_DIR
    #  PYTHON_INCLUDE_PATH ( deprecated )
    )
# Debian "jessie" has this additional variable required to match
# python versions.
  if(PYTHON_INCLUDE_DIR2)
    list( APPEND SITK_LANGUAGES_VARS
      PYTHON_INCLUDE_DIR2
      )
  endif()
endif ()


#-----------------------------------------------------------
# Java

if ( DEFINED WRAP_JAVA )
  set( WRAP_JAVA_DEFAULT ${WRAP_JAVA} )
elseif ( NOT WRAP_DEFAULT )
  set ( WRAP_JAVA_DEFAULT OFF )
else ( )
  find_package ( Java COMPONENTS Development Runtime QUIET )
  find_package ( JNI QUIET )
  if ( JAVA_FOUND AND JNI_FOUND )
    set( WRAP_JAVA_DEFAULT ${WRAP_DEFAULT} )
  else ( ${JAVA_FOUND} AND JNI_FOUND )
    set( WRAP_JAVA_DEFAULT OFF )
  endif ( )
endif ( )

option ( WRAP_JAVA "Wrap Java" ${WRAP_JAVA_DEFAULT} )

if ( WRAP_JAVA )
  find_package ( Java COMPONENTS Development Runtime REQUIRED )
  find_package ( JNI REQUIRED )
  list( APPEND SITK_LANGUAGES_VARS
    Java_JAVA_EXECUTABLE
    Java_JAVAC_EXECUTABLE
    Java_JAR_EXECUTABLE
    Java_JAVADOC_EXECUTABLE
    Java_JAVAH_EXECUTABLE
    Java_VERSION_STRING
    Java_VERSION_MAJOR
    Java_VERSION_MINOR
    Java_VERSION_PATCH
    Java_VERSION_TWEAK
    Java_VERSION
    Java_INCLUDE_DIRS
    Java_LIBRARIES
    JNI_INCLUDE_DIRS
    JNI_LIBRARIES
    JAVA_AWT_LIBRARY
    JAVA_JVM_LIBRARY
    JAVA_INCLUDE_PATH
    JAVA_INCLUDE_PATH2
    JAVA_AWT_INCLUDE_PATH
    )
endif()


#-----------------------------------------------------------
# Tcl

if ( DEFINED WRAP_TCL)
  set( WRAP_TCL_DEFAULT ${WRAP_TCL} )
elseif ( NOT WRAP_DEFAULT )
  set ( WRAP_TCL_DEFAULT OFF )
else ( )
  find_package ( TCL QUIET )
  if ( TCL_FOUND )
    set ( WRAP_TCL_DEFAULT ${WRAP_DEFAULT} )
  else ( )
    set ( WRAP_TCL_DEFAULT OFF )
  endif ( )
endif ( )

option ( WRAP_TCL "Wrap Tcl" ${WRAP_TCL_DEFAULT} )

if ( WRAP_TCL )
  find_package ( TCL REQUIRED )
  list( APPEND SITK_LANGUAGES_VARS
    TCL_LIBRARY
    TCL_INCLUDE_PATH
    TCL_TCLSH
    TK_LIBRARY
    TK_INCLUDE_PATH
    TK_WISH
    )
endif ( )


#-----------------------------------------------------------
# Ruby

if ( DEFINED WRAP_RUBY )
  set ( WRAP_RUBY_DEFAULT ${WRAP_RUBY} )
elseif ( NOT WRAP_DEFAULT )
  set ( WRAP_RUBY_DEFAULT OFF )
else()
  find_package ( Ruby QUIET )
  if ( RUBY_FOUND )
    set ( WRAP_RUBY_DEFAULT ${WRAP_DEFAULT} )
  else ( )
    set ( WRAP_RUBY_DEFAULT OFF )
  endif ( )
endif ( )

option ( WRAP_RUBY "Wrap Ruby" ${WRAP_RUBY_DEFAULT} )

if ( WRAP_RUBY )
  find_package ( Ruby REQUIRED )
  list( APPEND SITK_LANGUAGES_VARS
    RUBY_EXECUTABLE
    RUBY_INCLUDE_DIRS
    RUBY_LIBRARY
    RUBY_VERSION
    RUBY_FOUND
    RUBY_INCLUDE_PATH
    )
endif()


#-----------------------------------------------------------
#  CSharp

if ( DEFINED WRAP_CSHARP)
  set ( WRAP_CSHARP_DEFAULT ${WRAP_CSHARP} )
elseif ( NOT WRAP_DEFAULT )
  set ( WRAP_CSHARP_DEFAULT OFF )
else ( )
  find_package( CSharp QUIET )
  if ( CSHARP_FOUND AND NOT MINGW )
    set ( WRAP_CSHARP_DEFAULT ${WRAP_DEFAULT} )
  else ()
    set ( WRAP_CSHARP_DEFAULT OFF )
  endif ()
endif ( )

option ( WRAP_CSHARP "Wrap C#" ${WRAP_CSHARP_DEFAULT} )

if ( WRAP_CSHARP )
  find_package( CSharp REQUIRED )
  list( APPEND SITK_LANGUAGES_VARS
    CSHARP_COMPILER
    CSHARP_INTERPRETER
    CSHARP_PLATFORM
    )
endif()


#-----------------------------------------------------------
#  R

if ( DEFINED WRAP_R)
  set ( WRAP_R_DEFAULT ${WRAP_R} )
elseif ( NOT WRAP_DEFAULT )
  set ( WRAP_R_DEFAULT OFF )
else()
  find_package(R QUIET)
  if ( R_FOUND AND NOT WIN32 )
    set ( WRAP_R_DEFAULT ${WRAP_DEFAULT} )
  else( )
    set ( WRAP_R_DEFAULT OFF )
  endif( )
endif()

option ( WRAP_R "Wrap R" ${WRAP_R_DEFAULT} )

if ( WRAP_R )
  find_package(R REQUIRED)
  list( APPEND SITK_LANGUAGES_VARS
    R_INCLUDE_DIR
    R_LIBRARIES
    R_LIBRARY_BASE
    R_COMMAND
    RSCRIPT_EXECUTABLE )
endif()


if( WIN32 )
  mark_as_advanced( WRAP_R )
endif()
