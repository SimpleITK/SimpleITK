#
# - This module finds the languages supported by SimpleITK, and
#present the option to enable support
#

#
# Currently this will search for Python, Java, TCL, Ruby, C#, R
# Additionally it give the option to wrap LUA.
#


#
# Setup the option for each language
#
if (NOT WRAP_LUA)
  set(_QUIET "QUIET")
endif()
if (CMAKE_VERSION VERSION_LESS "3")
  find_package ( Lua51 ${_QUIET} )
  if ( NOT LUA_FOUND )
    find_package ( Lua50 ${_QUIET} )
  endif()
else()
  find_package ( Lua ${_QUIET} )
endif()
if ( LUA_FOUND )
  set( WRAP_LUA_DEFAULT ON )
else()
  set( WRAP_LUA_DEFAULT OFF )
endif()

option ( WRAP_LUA "Wrap Lua" ${WRAP_LUA_DEFAULT} )

list( APPEND SITK_LANGUAGES_VARS
  LUA_LIBRARIES
  LUA_INCLUDE_DIR
  LUA_VERSION_STRING
  )


find_package ( PythonInterp QUIET)

# If you're not using python or it's the first time, be quiet
if (NOT WRAP_PYTHON)
  set(_QUIET "QUIET")
endif()

find_package ( PythonLibs ${PYTHON_VERSION_STRING} EXACT ${_QUIET} )

if (PYTHON_VERSION_STRING VERSION_LESS 2.6)
  message( WARNING "Python version less that 2.6: \"${PYTHON_VERSION_STRING}\"." )
endif()

if ( PYTHONLIBS_FOUND AND PYTHONINTERP_FOUND
    AND (PYTHON_VERSION_STRING VERSION_EQUAL PYTHONLIBS_VERSION_STRING) )
  set( WRAP_PYTHON_DEFAULT ON )
else()
  set( WRAP_PYTHON_DEFAULT OFF )
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
option( WRAP_PYTHON "Wrap Python" ${WRAP_PYTHON_DEFAULT} )

find_package ( Java COMPONENTS Development Runtime QUIET )
find_package ( JNI QUIET )
if ( ${JAVA_FOUND} AND ${JNI_FOUND} )
  set( WRAP_JAVA_DEFAULT ON )
else ( ${JAVA_FOUND} AND ${JNI_FOUND} )
  set( WRAP_JAVA_DEFAULT OFF )
endif ( ${JAVA_FOUND} AND ${JNI_FOUND} )
list( APPEND SITK_LANGUAGES_VARS
  Java_JAVA_EXECUTABLE
  Java_JAVAC_EXECUTABLE
  Java_JAR_EXECUTABLE
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
option ( WRAP_JAVA "Wrap Java" ${WRAP_JAVA_DEFAULT} )

find_package ( TCL QUIET )
if ( ${TCL_FOUND} )
  set ( WRAP_TCL_DEFAULT ON )
else ( ${TCL_FOUND} )
  set ( WRAP_TCL_DEFAULT OFF )
endif ( ${TCL_FOUND} )
list( APPEND SITK_LANGUAGES_VARS
  TCL_LIBRARY
  TCL_INCLUDE_PATH
  TCL_TCLSH
  TK_LIBRARY
  TK_INCLUDE_PATH
  TK_WISH )
option ( WRAP_TCL "Wrap Tcl" ${WRAP_TCL_DEFAULT} )

find_package ( Ruby QUIET )
if ( ${RUBY_FOUND} )
  set ( WRAP_RUBY_DEFAULT ON )
else ( ${RUBY_FOUND} )
  set ( WRAP_RUBY_DEFAULT OFF )
endif ( ${RUBY_FOUND} )
list( APPEND SITK_LANGUAGES_VARS
  RUBY_EXECUTABLE
  RUBY_INCLUDE_DIRS
  RUBY_LIBRARY
  RUBY_VERSION
  RUBY_FOUND
  RUBY_INCLUDE_PATH )
option ( WRAP_RUBY "Wrap Ruby" ${WRAP_RUBY_DEFAULT} )

find_package( CSharp QUIET )
if ( ${CSHARP_FOUND} AND NOT MINGW )
  set ( WRAP_CSHARP_DEFAULT ON )
else ()
  set ( WRAP_CSHARP_DEFAULT OFF )
endif ()
list( APPEND SITK_LANGUAGES_VARS
  CSHARP_COMPILER
  CSHARP_INTERPRETER
  CSHARP_PLATFORM
)
option ( WRAP_CSHARP "Wrap C#" ${WRAP_CSHARP_DEFAULT} )

find_package(R QUIET)
if ( ${R_FOUND} AND NOT WIN32 )
  set ( WRAP_R_DEFAULT ON )
else( )
  set ( WRAP_R_DEFAULT OFF )
endif( )


list( APPEND SITK_LANGUAGES_VARS
 R_INCLUDE_DIR
 R_LIBRARIES
 R_LIBRARY_BASE
 R_COMMAND
 RSCRIPT_EXECUTABLE )
option ( WRAP_R "Wrap R" ${WRAP_R_DEFAULT} )

if( WIN32 )
  mark_as_advanced( WRAP_R )
endif()

#
# Below here are the 2nd tier languages they are not enabled automatically if detected
#
