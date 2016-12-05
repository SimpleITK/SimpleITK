
# Make sure this file is included only once
get_filename_component(CMAKE_CURRENT_LIST_FILENAME ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
if(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED)
  return()
endif()
set(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED 1)

# Sanity checks
if(DEFINED PCRE_DIR AND NOT EXISTS ${PCRE_DIR})
  message(FATAL_ERROR "PCRE_DIR variable is defined but corresponds to non-existing directory")
endif()

# Set dependency list
set(PCRE_DEPENDENCIES "")

if(NOT PCRE_DIR)
  #
  #  PCRE (Perl Compatible Regular Expressions)
  #

  set(PCRE_TARGET_VERSION 8.37)
  set(PCRE_DOWNLOAD_SOURCE_HASH "6e0cc6d1bdac7a4308151f9b3571b86e")
  sitkSourceDownload(PCRE_URL "pcre-${PCRE_TARGET_VERSION}.tar.gz" ${PCRE_DOWNLOAD_SOURCE_HASH})


  # follow the standard EP_PREFIX locations
  set(pcre_binary_dir ${CMAKE_CURRENT_BINARY_DIR}/PCRE-prefix/src/PCRE-build)
  set(pcre_source_dir ${CMAKE_CURRENT_BINARY_DIR}/PCRE-prefix/src/PCRE)
  set(pcre_install_dir ${CMAKE_CURRENT_BINARY_DIR}/PCRE)

  configure_file(
    pcre_configure_step.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/pcre_configure_step.cmake
    @ONLY)

  set ( pcre_CONFIGURE_COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/pcre_configure_step.cmake )

  ExternalProject_add(PCRE
    URL "${PCRE_URL}"
    URL_MD5 "${PCRE_DOWNLOAD_SOURCE_HASH}"
    CONFIGURE_COMMAND ${pcre_CONFIGURE_COMMAND}
    DEPENDS "${PCRE_DEPENDENCIES}"
    ${External_Project_USES_TERMINAL}
    )

  sitkSourceDownloadDependency(PCRE)

endif(NOT PCRE_DIR)
