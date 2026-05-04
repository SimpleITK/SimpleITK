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

# Make sure find package macros are included
include(FindPackageHandleStandardArgs)

set(_R_WINDOWS_HINTS)
if(WIN32)
  list(
    APPEND
    _R_WINDOWS_HINTS
    "[HKEY_CURRENT_USER\\Software\\R-core\\R;InstallPath]/bin/x64"
  )
  list(
    APPEND
    _R_WINDOWS_HINTS
    "[HKEY_LOCAL_MACHINE\\Software\\R-core\\R;InstallPath]/bin/x64"
  )
  list(
    APPEND
    _R_WINDOWS_HINTS
    "[HKEY_CURRENT_USER\\Software\\R-core\\R;InstallPath]/bin"
  )
  list(
    APPEND
    _R_WINDOWS_HINTS
    "[HKEY_LOCAL_MACHINE\\Software\\R-core\\R;InstallPath]/bin"
  )
endif()

set(TEMP_CMAKE_FIND_APPBUNDLE ${CMAKE_FIND_APPBUNDLE})
set(CMAKE_FIND_APPBUNDLE "NEVER")
find_program(R_COMMAND R HINTS ${_R_WINDOWS_HINTS} DOC "R executable.")
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
endif(R_COMMAND)

find_program(
  RSCRIPT_EXECUTABLE
  Rscript
  HINTS
    ${R_HOME}
    ${_R_WINDOWS_HINTS}
  DOC "Rscript executable."
)

set(CMAKE_FIND_APPBUNDLE ${TEMP_CMAKE_FIND_APPBUNDLE})

# R.h gets installed in all sorts of places -
# ubuntu: /usr/share/R/include, RHEL/Fedora: /usr/include/R/R.h
find_path(
  R_INCLUDE_DIR
  R.h
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
if(WIN32)
  list(
    APPEND
    _R_LIBRARY_PATH_SUFFIXES
    bin
    bin/x64
  )
endif()

if(MINGW)
  # On Windows with a MinGW/Rtools toolchain, R does not install a static import
  # library (libR.a or R.lib). Instead the R runtime is provided as R.dll located
  # in R's bin/x64/ directory.  MinGW's linker (ld) can link directly against a
  # .dll file: it reads the DLL's export table and synthesises the import stubs
  # automatically, so no separate .dll.a import library is required.
  #
  # The resulting SimpleITK R package .dll will have a dynamic dependency on
  # R.dll, which is resolved at load time when R executes `useDynLib(SimpleITK)`
  # (i.e. when the user calls `library(SimpleITK)`).  This mirrors how libR.so is
  # used on Linux — the package shared library is loaded into the live R process
  # and the R API symbols are resolved from R's own address space.
  #
  # We temporarily add .dll to CMAKE_FIND_LIBRARY_SUFFIXES so that find_library()
  # will locate R.dll, then restore the original suffixes immediately afterwards.
  list(APPEND CMAKE_FIND_LIBRARY_SUFFIXES .dll)

  list(
    APPEND
    _R_LIBRARY_PATH_SUFFIXES
    /bin
    /bin/x64
  )
endif()

find_library(
  R_LIBRARY_BASE
  R
  PATHS
    ${R_HOME}
  PATH_SUFFIXES
    ${_R_LIBRARY_PATH_SUFFIXES}
  DOC "R library (example libR.a, libR.dylib, R.dll, etc.)."
)

if(MINGW)
  list(POP_BACK CMAKE_FIND_LIBRARY_SUFFIXES)
endif()

set(R_LIBRARIES ${R_LIBRARY_BASE})
mark_as_advanced(
  RSCRIPT_EXECUTABLE
  R_LIBRARIES
  R_INCLUDE_DIR
  R_COMMAND
  R_LIBRARY_BASE
)

set(
  _REQUIRED_R_VARIABLES
  R_INCLUDE_DIR
  R_COMMAND
)

if(NOT LINUX)
  # On Linux the libR.so is sometimes not available; on all other platforms
  # a link error results if the library is not found.
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
