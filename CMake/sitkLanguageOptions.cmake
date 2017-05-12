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

option(WRAP_DEFAULT "The default initial value for wrapping a language when it is detected on the system." ON)
mark_as_advanced(WRAP_DEFAULT)

#
# Macro to set "_QUIET" and "_QUIET_LIBRARY" based on the first
# argument being defined and true, to either REQUIRED or QUIET.
#
macro(set_QUIET var)
  if ( DEFINED  ${var} AND ${var} )
    set( _QUIET "REQUIRED" )
  else()
    set( _QUIET "QUIET" )
  endif()
  if ( SITK_UNDEFINED_SYMBOLS_ALLOWED )
    set( _QUIET_LIBRARY "QUIET" )
  else()
    set( _QUIET_LIBRARY ${_QUIET} )
  endif()
endmacro()

#
# Setup the option for each language
#
set_QUIET( WRAP_LUA )
find_package ( Lua ${_QUIET} )

if ( LUA_FOUND )
  set( WRAP_LUA_DEFAULT ${WRAP_DEFAULT} )
else()
  set( WRAP_LUA_DEFAULT OFF )
endif()

set( LUA_ADDITIONAL_LIBRARIES "" CACHE STRING "Additional libraries which may be needed for lua such as readline.")
mark_as_advanced( LUA_ADDITIONAL_LIBRARIES )

option ( WRAP_LUA "Wrap Lua" ${WRAP_LUA_DEFAULT} )

if ( WRAP_LUA )
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



# If you're not using python or it's the first time, be quiet

set_QUIET( WRAP_PYTHON )
find_package ( PythonInterp ${_QUIET})
if ( PYTHONINTERP_FOUND )
  find_package ( PythonLibs ${PYTHON_VERSION_STRING} EXACT ${_QUIET_LIBRARY} )
else ()
  find_package ( PythonLibs ${_QUIET_LIBRARY} )
endif()

if ( PYTHONLIBS_FOUND AND PYTHONINTERP_FOUND
    AND PYTHON_VERSION_STRING VERSION_LESS 2.7 )
  message( WARNING "Python version less that 2.7: \"${PYTHON_VERSION_STRING}\"." )
endif()

if ( PYTHONLIBS_FOUND AND PYTHONINTERP_FOUND
    AND (PYTHON_VERSION_STRING VERSION_EQUAL PYTHONLIBS_VERSION_STRING) )
  set( WRAP_PYTHON_DEFAULT ${WRAP_DEFAULT} )
else()
  set( WRAP_PYTHON_DEFAULT OFF )
endif()

option( WRAP_PYTHON "Wrap Python" ${WRAP_PYTHON_DEFAULT} )

if ( WRAP_PYTHON )
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



set_QUIET( WRAP_JAVA )
find_package ( Java COMPONENTS Development Runtime ${_QUIET} )
find_package ( JNI ${_QUIET} )
if ( ${JAVA_FOUND} AND ${JNI_FOUND} )
  set( WRAP_JAVA_DEFAULT ${WRAP_DEFAULT} )
else ( ${JAVA_FOUND} AND ${JNI_FOUND} )
  set( WRAP_JAVA_DEFAULT OFF )
endif ( ${JAVA_FOUND} AND ${JNI_FOUND} )

option ( WRAP_JAVA "Wrap Java" ${WRAP_JAVA_DEFAULT} )

if ( WRAP_JAVA )
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


set_QUIET(WRAP_TCL)

find_package ( TCL ${_QUIET} )

if ( ${TCL_FOUND} )
  set ( WRAP_TCL_DEFAULT ${WRAP_DEFAULT} )
else ( ${TCL_FOUND} )
  set ( WRAP_TCL_DEFAULT OFF )
endif ( ${TCL_FOUND} )

option ( WRAP_TCL "Wrap Tcl" ${WRAP_TCL_DEFAULT} )

if ( WRAP_TCL )
  list( APPEND SITK_LANGUAGES_VARS
    TCL_LIBRARY
    TCL_INCLUDE_PATH
    TCL_TCLSH
    TK_LIBRARY
    TK_INCLUDE_PATH
    TK_WISH
    )
endif()


set_QUIET( WRAP_RUBY )

find_package ( Ruby ${_QUIET} )
if ( ${RUBY_FOUND} )
  set ( WRAP_RUBY_DEFAULT ${WRAP_DEFAULT} )
else ( ${RUBY_FOUND} )
  set ( WRAP_RUBY_DEFAULT OFF )
endif ( ${RUBY_FOUND} )

option ( WRAP_RUBY "Wrap Ruby" ${WRAP_RUBY_DEFAULT} )

if ( WRAP_RUBY )
  list( APPEND SITK_LANGUAGES_VARS
    RUBY_EXECUTABLE
    RUBY_INCLUDE_DIRS
    RUBY_LIBRARY
    RUBY_VERSION
    RUBY_FOUND
    RUBY_INCLUDE_PATH
    )
endif()


if (DEFINED  WRAP_CSHARP AND WRAP_CSHARP)
  set(_QUIET "REQUIRED")
else()
  set(_QUIET "QUIET")
endif()

find_package( CSharp ${_QUIET} )
if ( ${CSHARP_FOUND} AND NOT MINGW )
  set ( WRAP_CSHARP_DEFAULT ${WRAP_DEFAULT} )
else ()
  set ( WRAP_CSHARP_DEFAULT OFF )
endif ()

option ( WRAP_CSHARP "Wrap C#" ${WRAP_CSHARP_DEFAULT} )

if ( WRAP_CSHARP )
  list( APPEND SITK_LANGUAGES_VARS
    CSHARP_COMPILER
    CSHARP_INTERPRETER
    CSHARP_PLATFORM
    )
endif()


set_QUIET( WRAP_R )

find_package(R ${_QUIET})
if ( ${R_FOUND} AND NOT WIN32 )
  set ( WRAP_R_DEFAULT ${WRAP_DEFAULT} )
else( )
  set ( WRAP_R_DEFAULT OFF )
endif( )

option ( WRAP_R "Wrap R" ${WRAP_R_DEFAULT} )

if ( WRAP_R )
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

#
# Below here are the 2nd tier languages they are not enabled automatically if detected
#
