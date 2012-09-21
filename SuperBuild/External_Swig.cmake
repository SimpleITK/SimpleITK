set( TARGET_SWIG_VERSION 2.0.8 )
if(NOT SWIG_DIR)
  if(WIN32)
    # swig.exe available as pre-built binary on Windows:
    ExternalProject_Add(Swig
      URL http://prdownloads.sourceforge.net/swig/swigwin-${TARGET_SWIG_VERSION}.zip
      URL_MD5 b33724aaa42a736816d7f095e7d93e4f
      SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${TARGET_SWIG_VERSION}
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ""
      )

    set(SWIG_DIR ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${TARGET_SWIG_VERSION}) # ??
    set(SWIG_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${TARGET_SWIG_VERSION}/swig.exe)
  else()
    #
    #  PCRE (Perl Compatible Regular Expressions)
    #

    # follow the standard EP_PREFIX locations
    set ( pcre_binary_dir ${CMAKE_CURRENT_BINARY_DIR}/PCRE-prefix/src/PCRE-build )
    set ( pcre_source_dir ${CMAKE_CURRENT_BINARY_DIR}/PCRE-prefix/src/PCRE )
    set ( pcre_install_dir ${CMAKE_CURRENT_BINARY_DIR}/PCRE )

    configure_file(
      pcre_configure_step.cmake.in
      ${CMAKE_CURRENT_BINARY_DIR}/pcre_configure_step.cmake
      @ONLY)
    set ( pcre_CONFIGURE_COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/pcre_configure_step.cmake )

    ExternalProject_add(PCRE
      URL http://downloads.sourceforge.net/project/pcre/pcre/8.12/pcre-8.12.tar.gz
      URL_MD5 fa69e4c5d8971544acd71d1f10d59193
      CONFIGURE_COMMAND ${pcre_CONFIGURE_COMMAND}
      )

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
      URL http://prdownloads.sourceforge.net/swig/swig-${TARGET_SWIG_VERSION}.tar.gz
      URL_MD5 69f917e870efc0712c06ab53217b28d1
      CONFIGURE_COMMAND ${swig_CONFIGURE_COMMAND}
      DEPENDS PCRE
      )

    set(SWIG_DIR ${swig_install_dir}/share/swig/${TARGET_SWIG_VERSION})
    set(SWIG_EXECUTABLE ${swig_install_dir}/bin/swig)

    ExternalProject_Add_Step(Swig cpvec
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../Wrapping/std_vector_for_R_swig.i ${SWIG_DIR}/r/std_vector.i
       DEPENDEES install
    )


  endif()
endif(NOT SWIG_DIR)
