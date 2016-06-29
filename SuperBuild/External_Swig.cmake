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
    set(SWIG_GIT_TAG "rel-3.0.10" CACHE STRING "Tag in swig git repo")
    mark_as_advanced(SWIG_GIT_REPO)
    mark_as_advanced(SWIG_GIT_TAG)
  endif()

  set(SWIG_TARGET_VERSION "3.0.10" )
  set(SWIG_DOWNLOAD_SOURCE_HASH "bb4ab8047159469add7d00910e203124")
  set(SWIG_DOWNLOAD_WIN_HASH "f229724fe856aa78df6128ecfefe6e0a")

  if(WIN32)
    # binary SWIG for windows
    #------------------------------------------------------------------------------


    set(swig_source_dir ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${SWIG_TARGET_VERSION})

    # swig.exe available as pre-built binary on Windows:
    ExternalProject_Add(Swig
      URL https://midas3.kitware.com/midas/api/rest?method=midas.bitstream.download&checksum=${SWIG_DOWNLOAD_WIN_HASH}&name=swigwin-${SWIG_TARGET_VERSION}.zip
      URL_MD5 ${SWIG_DOWNLOAD_WIN_HASH}
      SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${SWIG_TARGET_VERSION}
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ""
      )

    set(SWIG_DIR ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${SWIG_TARGET_VERSION}) # path specified as source in ep
    set(SWIG_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${SWIG_TARGET_VERSION}/swig.exe)

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
      set(SWIG_DOWNLOAD_STEP
        URL "https://midas3.kitware.com/midas/api/rest?method=midas.bitstream.download&checksum=${SWIG_DOWNLOAD_SOURCE_HASH}&name=swig-${SWIG_TARGET_VERSION}.tar.gz"
        URL_MD5 "${SWIG_DOWNLOAD_SOURCE_HASH}"
        )
    endif()

    ExternalProject_add(Swig
      ${SWIG_DOWNLOAD_STEP}
      CONFIGURE_COMMAND ${swig_CONFIGURE_COMMAND}
      DEPENDS "${Swig_DEPENDENCIES}"
      )

    set(SWIG_DIR ${swig_install_dir}/share/swig/${SWIG_TARGET_VERSION})
    set(SWIG_EXECUTABLE ${swig_install_dir}/bin/swig)

  endif()
endif(NOT SWIG_DIR)
