

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

  set(SWIG_TARGET_VERSION 2.0.10)
  set(SWIG_DOWNLOAD_SOURCE_HASH "6d5e7ad05b4a404e5e85db9befb70c9a")
  set(SWIG_DOWNLOAD_WIN_HASH "cbb7006ecc912f056a2ec7f322fe59fb" )


  if(WIN32)
    # swig.exe available as pre-built binary on Windows:
    ExternalProject_Add(Swig
      URL  http://midas3.kitware.com/midas/api/rest?method=midas.bitstream.download&checksum=${SWIG_DOWNLOAD_WIN_HASH}&aldorithm=md5&name=swigwin-${SWIG_TARGET_VERSION}.tar.gz
      URL_MD5 ${SWIG_DOWNLOAD_WIN_HASH}
      SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${SWIG_TARGET_VERSION}
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ""
      )

    set(SWIG_DIR ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${SWIG_TARGET_VERSION}) # ??
    set(SWIG_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${SWIG_TARGET_VERSION}/swig.exe)
  else()

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
    find_package ( BISON )
    set ( BISON_FLAGS "" CACHE STRING "Flags used by bison" )
    mark_as_advanced ( BISON_FLAGS )


    # follow the standard EP_PREFIX locations
    set ( swig_binary_dir ${CMAKE_CURRENT_BINARY_DIR}/Swig-prefix/src/Swig-build )
    set ( swig_source_dir ${CMAKE_CURRENT_BINARY_DIR}/Swig-prefix/src/Swig )
    set ( swig_install_dir ${CMAKE_CURRENT_BINARY_DIR}/Swig )

    configure_file(
      swig_configure_step.cmake.in
      ${CMAKE_CURRENT_BINARY_DIR}/swig_configure_step.cmake
      @ONLY)
    set ( swig_CONFIGURE_COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/swig_configure_step.cmake )

    ExternalProject_add(Swig
      URL  http://midas3.kitware.com/midas/api/rest?method=midas.bitstream.download&checksum=${SWIG_DOWNLOAD_SOURCE_HASH}&aldorithm=md5&name=swig-${SWIG_TARGET_VERSION}.tar.gz
      URL_MD5 ${SWIG_DOWNLOAD_SOURCE_HASH}
      CONFIGURE_COMMAND ${swig_CONFIGURE_COMMAND}
      DEPENDS "${Swig_DEPENDENCIES}"
      )

    set(SWIG_DIR ${swig_install_dir}/share/swig/${SWIG_TARGET_VERSION})
    set(SWIG_EXECUTABLE ${swig_install_dir}/bin/swig)

    ExternalProject_Add_Step(Swig cpvec
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../Wrapping/std_vector_for_R_swig.i ${SWIG_DIR}/r/std_vector.i
       DEPENDEES install
    )


  endif()
endif(NOT SWIG_DIR)
