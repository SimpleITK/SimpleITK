
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
#


# Make sure find package macros are included
include( FindPackageHandleStandardArgs )

SET(TEMP_CMAKE_FIND_APPBUNDLE ${CMAKE_FIND_APPBUNDLE})
SET(CMAKE_FIND_APPBUNDLE "NEVER")
FIND_PROGRAM(R_COMMAND R DOC "R executable.")
IF (R_COMMAND)
  EXECUTE_PROCESS(WORKING_DIRECTORY . COMMAND ${R_COMMAND} RHOME OUTPUT_VARIABLE R_BASE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
  SET(R_HOME ${R_BASE_DIR} CACHE PATH "R home directory obtained from R RHOME")
  mark_as_advanced( R_HOME )
ENDIF (R_COMMAND)
FIND_PROGRAM(RSCRIPT_EXECUTABLE Rscript DOC "Rscript executable.")

SET(CMAKE_FIND_APPBUNDLE ${TEMP_CMAKE_FIND_APPBUNDLE})

FIND_PATH(R_INCLUDE_DIR R.h PATHS /usr/local/lib /usr/local/lib64 PATH_SUFFIXES R/include DOC "Path to file R.h")
FIND_LIBRARY(R_LIBRARY_BASE R PATHS ${R_BASE_DIR} PATH_SUFFIXES /lib DOC "R library (example libR.a, libR.dylib, etc.).")

SET(R_LIBRARIES ${R_LIBRARY_BASE})
mark_as_advanced( R_LIBRARIES R_INCLUDE_DIR R_COMMAND R_LIBRARY_BASE )

FIND_PACKAGE_HANDLE_STANDARD_ARGS(R DEFAULT_MSG R_LIBRARIES R_INCLUDE_DIR R_COMMAND R_LIBRARY_BASE )
