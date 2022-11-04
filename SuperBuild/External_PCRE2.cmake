
# Make sure this file is included only once
get_filename_component(CMAKE_CURRENT_LIST_FILENAME ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
if(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED)
  return()
endif()
set(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED 1)

# Sanity checks
if(DEFINED PCRE2_DIR AND NOT EXISTS ${PCRE2_DIR})
  message(FATAL_ERROR "PCRE2_DIR variable is defined but corresponds to non-existing directory")
endif()

# Set dependency list
set(PCRE2_DEPENDENCIES "")

if(NOT PCRE2_DIR)
  #
  #  PCRE2 (Perl Compatible Regular Expressions)
  #

  set(PCRE2_TARGET_VERSION 10.40)
  sitkSourceDownload(PCRE2_URL "pcre2-${PCRE2_TARGET_VERSION}.tar.gz")


  # follow the standard EP_PREFIX locations
  set(pcre2_binary_dir ${CMAKE_CURRENT_BINARY_DIR}/PCRE2-prefix/src/PCRE2-build)
  set(pcre2_source_dir ${CMAKE_CURRENT_BINARY_DIR}/PCRE2-prefix/src/PCRE2)
  set(pcre2_install_dir ${CMAKE_CURRENT_BINARY_DIR}/PCRE2)

  if ( APPLE AND CMAKE_OSX_SYSROOT )
    set(REQUIRED_C_FLAGS "-isysroot ${CMAKE_OSX_SYSROOT}")
    set(REQUIRED_CXX_FLAGS "-isysroot ${CMAKE_OSX_SYSROOT}")
  endif()

  configure_file(
    pcre2_configure_step.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/pcre2_configure_step.cmake
    @ONLY)

  set ( pcre2_CONFIGURE_COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/pcre2_configure_step.cmake )

  ExternalProject_add(PCRE2
    URL "${PCRE2_URL}"
    URL_HASH "${PCRE2_URL_HASH}"
    CONFIGURE_COMMAND ${pcre2_CONFIGURE_COMMAND}
    DEPENDS "${PCRE2_DEPENDENCIES}"
    ${External_Project_USE_ARCHIVE_TIMESTAMP}
    )

  sitkSourceDownloadDependency(PCRE2)

endif(NOT PCRE2_DIR)
