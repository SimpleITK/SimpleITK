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


# If you're not using python or it's the first time, be quiet
if (DEFINED  WRAP_PYTHON AND WRAP_PYTHON)
  set(_QUIET "REQUIRED")
else()
  set(_QUIET "QUIET")
endif()

find_package ( PythonInterp ${_QUIET})

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
check_PIC_flag ( Python )


if (DEFINED  WRAP_JAVA AND WRAP_JAVA)
  set(_QUIET "REQUIRED")
else()
  set(_QUIET "QUIET")
endif()

find_package ( Java COMPONENTS Development Runtime ${_QUIET} )
find_package ( JNI ${_QUIET} )
if ( ${JAVA_FOUND} AND ${JNI_FOUND} )
  set( WRAP_JAVA_DEFAULT ON )
else ( ${JAVA_FOUND} AND ${JNI_FOUND} )
  set( WRAP_JAVA_DEFAULT OFF )
endif ( ${JAVA_FOUND} AND ${JNI_FOUND} )

option ( WRAP_JAVA "Wrap Java" ${WRAP_JAVA_DEFAULT} )
check_PIC_flag ( Java )

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


if (DEFINED  WRAP_TCL AND WRAP_TCL)
  set(_QUIET "REQUIRED")
else()
  set(_QUIET "QUIET")
endif()

find_package ( TCL ${_QUIET} )
if ( ${TCL_FOUND} )
  set ( WRAP_TCL_DEFAULT ON )
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


find_package ( Ruby QUIET )
if ( ${RUBY_FOUND} )
  set ( WRAP_RUBY_DEFAULT ON )
else ( ${RUBY_FOUND} )
  set ( WRAP_RUBY_DEFAULT OFF )
endif ( ${RUBY_FOUND} )

option ( WRAP_RUBY "Wrap Ruby" ${WRAP_RUBY_DEFAULT} )
check_PIC_flag ( Ruby )

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
  set ( WRAP_CSHARP_DEFAULT ON )
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


if (DEFINED  WRAP_R AND WRAP_R)
  set(_QUIET "REQUIRED")
else()
  set(_QUIET "QUIET")
endif()

find_package(R ${_QUIET})
if ( ${R_FOUND} AND NOT WIN32 )
  set ( WRAP_R_DEFAULT ON )
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
