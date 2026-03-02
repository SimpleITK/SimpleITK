#
# - This module locates an installed R distribution.
#
# Defines the following:
#
# R_INCLUDE_DIR      - Path to R include directory
# R_LIBRARIES        - Path to R library
# R_LIBRARY_BASE     -
# R_COMMAND          - Path to R command
# RSCRIPT_EXECUTABLE - Path to Rscript command
# R_VERSION_STRING   - R version obtained from R_COMMAND and R.version variable
# R_CPPFLAGS         - C preprocessor flags from R CMD config --cppflags
# R_LDFLAGS          - Linker flags from R CMD config --ldflags

# Make sure find package macros are included
include(FindPackageHandleStandardArgs)

set(TEMP_CMAKE_FIND_APPBUNDLE ${CMAKE_FIND_APPBUNDLE})
set(CMAKE_FIND_APPBUNDLE "NEVER")
find_program(R_COMMAND R DOC "R executable.")
if(R_COMMAND)
  execute_process(
    WORKING_DIRECTORY .
    COMMAND
      ${R_COMMAND} RHOME
    OUTPUT_VARIABLE R_BASE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  set(R_HOME ${R_BASE_DIR} CACHE PATH "R home directory obtained from R RHOME")
  mark_as_advanced(R_HOME)
  execute_process(
    WORKING_DIRECTORY .
    COMMAND
      ${R_COMMAND} --slave -e
      "cat(paste0(R.version[c('major', 'minor')], collapse='.'))"
    OUTPUT_VARIABLE R_VERSION_STRING
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  # Query R for include directory using R.home('include')
  execute_process(
    WORKING_DIRECTORY .
    COMMAND
      ${R_COMMAND} --slave --vanilla -e "cat(R.home('include'))"
    OUTPUT_VARIABLE R_INCLUDE_DIR_FROM_R
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  # Query R for library directory
  execute_process(
    WORKING_DIRECTORY .
    COMMAND
      ${R_COMMAND} --slave --vanilla -e "cat(R.home('lib'))"
    OUTPUT_VARIABLE R_LIB_DIR_FROM_R
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  # Query R CMD config for compiler flags
  execute_process(
    WORKING_DIRECTORY .
    COMMAND
      ${R_COMMAND} CMD config --cppflags
    OUTPUT_VARIABLE R_CPPFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )

  # Query R CMD config for linker flags
  execute_process(
    WORKING_DIRECTORY .
    COMMAND
      ${R_COMMAND} CMD config --ldflags
    OUTPUT_VARIABLE R_LDFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
endif(R_COMMAND)

find_program(RSCRIPT_EXECUTABLE Rscript DOC "Rscript executable.")

set(CMAKE_FIND_APPBUNDLE ${TEMP_CMAKE_FIND_APPBUNDLE})

# R.h gets installed in all sorts of places -
# ubuntu: /usr/share/R/include, RHEL/Fedora: /usr/include/R/R.h
# Prioritize the path obtained from R itself
find_path(
  R_INCLUDE_DIR
  R.h
  HINTS
    ${R_INCLUDE_DIR_FROM_R}
  PATHS
    /usr/local/lib
    /usr/local/lib64
    /usr/share
    /usr/include
    ${R_BASE_DIR}
  PATH_SUFFIXES
    include
    R
    R/include
  DOC "Path to file R.h"
)
find_library(
  R_LIBRARY_BASE
  R
  HINTS
    ${R_LIB_DIR_FROM_R}
  PATHS
    ${R_BASE_DIR}
  PATH_SUFFIXES
    /lib
  DOC "R library (example libR.a, libR.dylib, etc.)."
)

set(R_LIBRARIES ${R_LIBRARY_BASE})
mark_as_advanced(
  RSCRIPT_EXECUTABLE
  R_LIBRARIES
  R_INCLUDE_DIR
  R_COMMAND
  R_LIBRARY_BASE
  R_CPPFLAGS
  R_LDFLAGS
  R_INCLUDE_DIR_FROM_R
  R_LIB_DIR_FROM_R
)

set(
  _REQUIRED_R_VARIABLES
  R_INCLUDE_DIR
  R_COMMAND
)

if(APPLE)
  # On linux platform some times the libR.so is not available, however
  # on apple a link error results if the library is linked.
  list(
    APPEND
    _REQUIRED_R_VARIABLES
    R_LIBRARIES
    R_LIBRARY_BASE
  )
endif()

find_package_handle_standard_args(
  R
  REQUIRED_VARS
    ${_REQUIRED_R_VARIABLES}
  VERSION_VAR R_VERSION_STRING
)
