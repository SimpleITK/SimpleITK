#
# * This module finds the languages supported by SimpleITK. By default a find package will be performed for each
#   language, and if it is detected wrapping for that language will be enabled (WRAP_<languageName>=ON). This behavior
#   can be overridden by setting "WRAP_DEFAULT" to FALSE. Individual languages can be disabled with the
#   WRAP_<languageName> option. If either WRAP_DEFAULT or WRAP_<languageName> is false then no find_package for the
#   language will be performed, and the language will not be wrapped.
#

include(sitkTargetLinkLibrariesWithDynamicLookup)

sitk_check_dynamic_lookup(MODULE SHARED SITK_UNDEFINED_SYMBOLS_ALLOWED)

option(WRAP_DEFAULT "Enables automatic detection and wrapping for all languages." ON)
mark_as_advanced(WRAP_DEFAULT)

# Arguments: - languageName - name of the language, will check variable `WRAP_<languageName>`
#
# Modified Variables: - _do_find_package - always defined, true if find_pacakge for languages should be run. -
# _find_package_extra_args - may be set to `REQUIRED` or `QUIET` as needed. - WRAP_<languageName>_DEFAULT - may be set
# to `ON` or `OFF` if it can be determined with out a find_package call
#
macro(sitkLanguageShouldDoFindPackage languageName)

  if(DEFINED WRAP_${languageName})
    if(WRAP_${languageName})
      # Variable `WRAP_<languageName>` is defined and TRUE, we need to call  `find_package` with `REQUIRED`
      set(_do_find_package 1)
      set(_find_package_extra_args "REQUIRED")
      set(WRAP_${languageName}_DEFAULT ON)
    else()
      # Variable `WRAP_<languageName>` is defined and FALSE, we do  *NOT* need to call  `find_package` at all to
      # initialize the `WRAP_<languageName>_DEFAULT` variable
      set(WRAP_${languageName}_DEFAULT OFF)
      set(_do_find_package 0)
    endif()
  elseif(WRAP_DEFAULT)
    # The variable `WRAP_<languageName>` is *NOT* defined and WRAP_DEFAULT=ON, so we must "quietly" do a find package to
    # determine the value for `WRAP_<languageName>_DEFAULT` variable
    set(_do_find_package 1)
    set(_find_package_extra_args "QUIET")
  else()
    # The variable `WRAP_<languageName>` is *NOT* defined and explicitly all languages are disabled by WRAP_DEFAULT=OFF,
    # we do *NOT* need to call `find_package` to initialize the `WRAP_<languageName>_DEFAULT` variable.
    set(WRAP_${languageName}_DEFAULT OFF)
    set(_do_find_package 0)
  endif()

endmacro()

#
# Setup the option for each language
#

# -----------------------------------------------------------
# Lua

sitklanguageshoulddofindpackage(LUA)

if(_do_find_package)

  find_package(Lua ${_find_package_extra_args})

  set(WRAP_LUA_DEFAULT ${LUA_FOUND})
endif()

option(WRAP_LUA "Wrap Lua" ${WRAP_LUA_DEFAULT})

if(WRAP_LUA)

  set(LUA_ADDITIONAL_LIBRARIES
      ""
      CACHE STRING "Additional libraries which may be needed for lua such as readline.")
  mark_as_advanced(LUA_ADDITIONAL_LIBRARIES)

  find_package(LuaInterp REQUIRED)
  list(
    APPEND
    SITK_LANGUAGES_VARS
    LUA_EXECUTABLE
    LUA_LIBRARIES
    LUA_INCLUDE_DIR
    LUA_VERSION_STRING
    LUA_MATH_LIBRARY
    LUA_ADDITIONAL_LIBRARIES)
endif()

# -----------------------------------------------------------
# Python

sitklanguageshoulddofindpackage(PYTHON)

if(DEFINED PYTHON_EXECUTABLE AND NOT DEFINED Python_EXECUTABLE)
  message(WARNING "Use Python_EXECUTABLE! Ignoring PYTHON_EXECUTABLE: ${PYTHON_EXECUTABLE}")
endif()

if(_do_find_package)

  set(WRAP_PYTHON_DEFAULT OFF)

  # if we don't need to link against a library, the make the find_package quiet.
  if(SITK_UNDEFINED_SYMBOLS_ALLOWED)
    set(_find_package_extra_args "QUIET")
  endif()

  if(NOT DEFINED Python_FIND_UNVERSIONED_NAMES)
    # Addressed issue with using rename python executables on windows with venv
    # https://github.com/msys2/MINGW-packages/issues/5001
    set(Python_FIND_UNVERSIONED_NAMES "FIRST")
  endif()

  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.19)
    set(_Python_VERSION_REQUIREMENT "3.7.0...<4")
  endif()

  find_package(Python ${_Python_VERSION_REQUIREMENT} ${_find_package_extra_args} COMPONENTS Development.Module
                                                                                            Interpreter)
  if(Python_Interpreter_FOUND AND Python_Development.Module_FOUND)
    set(WRAP_PYTHON_DEFAULT ON)
  endif()
endif()

option(WRAP_PYTHON "Wrap Python" ${WRAP_PYTHON_DEFAULT})

if(WRAP_PYTHON)

  list(
    APPEND
    SITK_LANGUAGES_VARS
    Python_ROOT_DIR
    Python_EXECUTABLE
    Python_LIBRARY
    Python_INCLUDE_DIR
    Python_LIBRARY_DEBUG
    Python_LIBRARY_RELEASE)
  # Support CMake < 3.24 by explicitly passing _Python_VERSION variables to workaround issue fixed in
  # kitware/cmake@ece3bedbf (FindPython: fix error on multiple queries with different COMPONENTS) See
  # https://gitlab.kitware.com/cmake/cmake/-/merge_requests/7410 for more details
  if(CMAKE_VERSION VERSION_LESS "3.24")
    list(
      APPEND
      SITK_LANGUAGES_VARS
      _Python_VERSION
      _Python_VERSION_MAJOR
      _Python_VERSION_MINOR
      _Python_VERSION_PATCH
      _Python_VERSION_TWEAK)
  endif()
endif()

# -----------------------------------------------------------
# Java

sitklanguageshoulddofindpackage(JAVA)

if(_do_find_package)

  find_package(Java COMPONENTS Development Runtime ${_find_package_extra_args})
  find_package(JNI ${_find_package_extra_args})

  if(JAVA_FOUND AND JNI_FOUND)
    set(WRAP_JAVA_DEFAULT ON)
  else(${JAVA_FOUND} AND JNI_FOUND)
    set(WRAP_JAVA_DEFAULT OFF)
  endif()
endif()

option(WRAP_JAVA "Wrap Java" ${WRAP_JAVA_DEFAULT})

if(WRAP_JAVA)
  list(
    APPEND
    SITK_LANGUAGES_VARS
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
    JAVA_AWT_INCLUDE_PATH)
endif()

# -----------------------------------------------------------
# Tcl

sitklanguageshoulddofindpackage(WRAP_TCL)

if(_do_find_package)

  find_package(TCL ${_find_package_extra_args})

  set(WRAP_TCL_DEFAULT ${TCL_FOUND})
endif()

option(WRAP_TCL "Wrap Tcl" ${WRAP_TCL_DEFAULT})

if(WRAP_TCL)
  list(
    APPEND
    SITK_LANGUAGES_VARS
    TCL_LIBRARY
    TCL_INCLUDE_PATH
    TCL_TCLSH
    TK_LIBRARY
    TK_INCLUDE_PATH
    TK_WISH)
endif()

# -----------------------------------------------------------
# Ruby

sitklanguageshoulddofindpackage(RUBY)

if(_do_find_package)

  find_package(Ruby ${_find_package_extra_args})

  # CMake 3.15 switch to the conforming "Ruby" prefix, while supporting the legacy "RUBY"
  if(Ruby_FOUND)
    set(WRAP_RUBY_DEFAULT ${WRAP_DEFAULT})
  else()
    set(WRAP_RUBY_DEFAULT OFF)
  endif()
endif()

option(WRAP_RUBY "Wrap Ruby" ${WRAP_RUBY_DEFAULT})

if(WRAP_RUBY)
  list(
    APPEND
    SITK_LANGUAGES_VARS
    Ruby_EXECUTABLE
    Ruby_INCLUDE_DIRS
    Ruby_LIBRARIES)
endif()

# -----------------------------------------------------------
# CSharp

sitklanguageshoulddofindpackage(CSHARP)

if(_do_find_package)

  find_package(CSharp ${_find_package_extra_args})

  if(CSHARP_FOUND AND NOT MINGW)
    set(WRAP_CSHARP_DEFAULT ON)
  else()
    set(WRAP_CSHARP_DEFAULT OFF)
  endif()
endif()

option(WRAP_CSHARP "Wrap C#" ${WRAP_CSHARP_DEFAULT})

if(WRAP_CSHARP)
  list(
    APPEND
    SITK_LANGUAGES_VARS
    CSHARP_COMPILER
    CSHARP_INTERPRETER
    CSHARP_PLATFORM)
endif()

# -----------------------------------------------------------
# R

sitklanguageshoulddofindpackage(R)

if(_do_find_package)

  find_package(R ${_find_package_extra_args})

  if(R_FOUND AND NOT WIN32)
    set(WRAP_R_DEFAULT ON)
  else()
    set(WRAP_R_DEFAULT OFF)
  endif()
endif()

option(WRAP_R "Wrap R" ${WRAP_R_DEFAULT})

if(WRAP_R)
  if(R_VERSION_STRING VERSION_LESS 3.3)
    message(WARNING "R version less than 3.3: \"${R_VERSION_STRING}\".")
  endif()
  list(
    APPEND
    SITK_LANGUAGES_VARS
    R_INCLUDE_DIR
    R_LIBRARIES
    R_LIBRARY_BASE
    R_COMMAND
    RSCRIPT_EXECUTABLE)
endif()

if(WIN32)
  mark_as_advanced(WRAP_R)
endif()
