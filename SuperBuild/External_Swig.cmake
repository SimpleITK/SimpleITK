# Make sure this file is included only once
get_filename_component(CMAKE_CURRENT_LIST_FILENAME ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
if(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED)
  return()
endif()
set(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED 1)

# Sanity checks
if(DEFINED Swig_DIR AND NOT EXISTS ${Swig_DIR})
  message(FATAL_ERROR "Swig_DIR variable is defined but corresponds to non-existing directory")
endif()

if(NOT SWIG_DIR)

  if (NOT MSVC)
    option(USE_SWIG_FROM_GIT "Use a version of swig pulled from the git repo. This will require automake tools and does not work under windows." OFF )

    mark_as_advanced(USE_SWIG_FROM_GIT)
  endif()

  if( USE_SWIG_FROM_GIT )
    set(SWIG_GIT_REPOSITORY "${git_protocol}://github.com/swig/swig.git" CACHE STRING "URL of swig git repo")
    set(SWIG_GIT_TAG "rel-3.0.11" CACHE STRING "Tag in swig git repo")
    mark_as_advanced(SWIG_GIT_REPO)
    mark_as_advanced(SWIG_GIT_TAG)
  endif()

  set(SWIG_TARGET_VERSION "3.0.11" )
  set(SWIG_DOWNLOAD_SOURCE_HASH "13732eb0f1ab2123d180db8425c1edea")
  set(SWIGWIN_DOWNLOAD_HASH "5cc57e3658f62b7f648bec7eed91a4f0" )

  if(WIN32)
    # binary SWIG for windows
    #------------------------------------------------------------------------------

    sitkSourceDownload(SWIGWIN_URL "swigwin-${SWIG_TARGET_VERSION}.zip"  ${SWIGWIN_DOWNLOAD_HASH})

    set(swig_source_dir "${CMAKE_CURRENT_BINARY_DIR}/swigwin")

    # swig.exe available as pre-built binary on Windows:
    ExternalProject_Add(Swig
      URL "${SWIGWIN_URL}"
      URL_MD5 ${SWIG_DOWNLOAD_WIN_HASH}
      SOURCE_DIR ${swig_source_dir}
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ""
      ${External_Project_USES_TERMINAL}
      )
    add_dependencies(Swig  "SuperBuildSimpleITKSource")

    set(SWIG_DIR "${swig_source_dir}") # path specified as source in ep
    set(SWIG_EXECUTABLE ${SWIG_DIR}/swig.exe)

  else()
    # compiled SWIG for others
    #------------------------------------------------------------------------------

    # Set dependency list
    set(Swig_DEPENDENCIES "PCRE")

    #
    #  PCRE (Perl Compatible Regular Expressions)
    #
    include(External_PCRE)


    #
    # SWIG
    #

    # swig uses bison find it by cmake and pass it down
    if(USE_SWIG_FROM_GIT)
      set(BISON_REQUIRED "REQUIRED")
    endif()
    find_package(BISON ${BISON_REQUIRED})
    set(BISON_FLAGS "-y" CACHE STRING "Flags used by bison")
    mark_as_advanced(BISON_FLAGS)


    # follow the standard EP_PREFIX locations
    set(swig_binary_dir ${CMAKE_CURRENT_BINARY_DIR}/Swig-prefix/src/Swig-build)
    set(swig_source_dir ${CMAKE_CURRENT_BINARY_DIR}/Swig-prefix/src/Swig)
    set(swig_install_dir ${CMAKE_CURRENT_BINARY_DIR}/Swig)

    # configure step
    configure_file(
      swig_configure_step.cmake.in
      ${CMAKE_CURRENT_BINARY_DIR}/swig_configure_step.cmake
      @ONLY)
    set(swig_CONFIGURE_COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/swig_configure_step.cmake)

    if(USE_SWIG_FROM_GIT)
      set(SWIG_DOWNLOAD_STEP
        GIT_REPOSITORY "${SWIG_GIT_REPOSITORY}"
        GIT_TAG "${SWIG_GIT_TAG}"
        )
    else()
      sitkSourceDownload(SWIG_URL "swig-${SWIG_TARGET_VERSION}.tar.gz" ${SWIG_DOWNLOAD_SOURCE_HASH})
      set(SWIG_DOWNLOAD_STEP
        URL "${SWIG_URL}"
        URL_MD5 "${SWIG_DOWNLOAD_SOURCE_HASH}"
        )
    endif()

    ExternalProject_add(Swig
      ${SWIG_DOWNLOAD_STEP}
      CONFIGURE_COMMAND ${swig_CONFIGURE_COMMAND}
      DEPENDS "${Swig_DEPENDENCIES}"
      ${External_Project_USES_TERMINAL}
      )

    if(NOT USE_SWIG_FROM_GIT)
      sitkSourceDownloadDependency(Swig)
    endif()

    set(SWIG_DIR ${swig_install_dir}/share/swig/${SWIG_TARGET_VERSION})
    set(SWIG_EXECUTABLE ${swig_install_dir}/bin/swig)

  endif()
endif(NOT SWIG_DIR)
