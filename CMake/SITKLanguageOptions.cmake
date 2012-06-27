#
# - This module finds the languages supported by SimpleITK, and
#present the option to enable support
#

#
# Currently this will search for Python, Java, TCL, Ruby, C#, R
# Additionally it give the option to wrap LUA.
#


# for wrapping to wrok correctly fPIC is needed on certain system.
macro(check_PIC_flag Language)
  string( TOUPPER ${Language} LANGUAGE )
  if ( UNIX AND NOT APPLE AND WRAP_${LANGUAGE} )
    if ( NOT ${CMAKE_CXX_FLAGS} MATCHES "-fPIC")
      message ( FATAL_ERROR "${Language} wrapping requires CMAKE_CXX_FLAGS (or equivalent) to include -fPIC and ITK built with this flag." )
    endif()
  endif()
endmacro()


#
# Setup the option for each language
#
option ( WRAP_LUA "Wrap Lua" ON )

find_package ( PythonInterp 2.6 QUIET)
find_package ( PythonLibs 2.6 QUIET )
if ( ${PYTHONLIBS_FOUND} AND ${PYTHONINTERP_FOUND} )
  set( WRAP_PYTHON_DEFAULT ON )
else ( ${PYTHONLIBS_FOUND} AND ${PYTHONINTERP_FOUND} )
  set( WRAP_PYTHON_DEFAULT OFF )
endif ( ${PYTHONLIBS_FOUND} AND ${PYTHONINTERP_FOUND} )
list( APPEND SITK_LANGUAGES_VARS
  PYTHON_DEBUG_LIBRARY
  PYTHON_EXECUTABLE
  PYTHON_LIBRARY
  PYTHON_INCLUDE_DIR
#  PYTHON_INCLUDE_PATH ( depricated )
   )
option( WRAP_PYTHON "Wrap Python" ${WRAP_PYTHON_DEFAULT} )
check_PIC_flag ( Python )

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
check_PIC_flag ( Java )

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
check_PIC_flag ( Ruby )
list( APPEND SITK_LANGUAGES_VARS
  RUBY_EXECUTABLE
  RUBY_INCLUDE_DIRS
  RUBY_LIBRARY
  RUBY_VERSION
  RUBY_FOUND
  RUBY_INCLUDE_PATH )
option ( WRAP_RUBY "Wrap Ruby" ${WRAP_RUBY_DEFAULT} )
check_PIC_flag ( Ruby )

find_package( CSharp QUIET )
if ( ${CSHARP_FOUND} )
  set ( WRAP_CSHARP_DEFAULT ON )
else ( ${CSHARP_FOUND} )
  set ( WRAP_CSHARP_DEFAULT OFF )
endif ( ${CSHARP_FOUND} )
list( APPEND SITK_LANGUAGES_VARS
  CSHARP_COMPILER
  CSHARP_INTERPRETER
  CSHARP_PLATFORM
)
option ( WRAP_CSHARP "Wrap C#" ${WRAP_CSHARP_DEFAULT} )

#
# Below here are the 2nd tier languages they are not enabled automatically if detected
#

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
