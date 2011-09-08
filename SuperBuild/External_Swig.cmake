set( TARGET_SWIG_VERSION 2.0.4 )
if(NOT SWIG_DIR)
  if(WIN32)
    # swig.exe available as pre-built binary on Windows:
    ExternalProject_Add(Swig
      URL http://prdownloads.sourceforge.net/swig/swigwin-${TARGET_SWIG_VERSION}.zip
      URL_MD5 4ab8064b1a8894c8577ef9d0fb2523c8
      SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${TARGET_SWIG_VERSION}
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ""
      )

    set(SWIG_DIR ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${TARGET_SWIG_VERSION}) # ??
    set(SWIG_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/swigwin-${TARGET_SWIG_VERSION}/swig.exe)
    set(Swig_DEPEND Swig)
  else()
    # Perl Compatible Regular Expressions
    ExternalProject_add(PCRE
      URL http://downloads.sourceforge.net/project/pcre/pcre/8.12/pcre-8.12.tar.gz
      URL_MD5 fa69e4c5d8971544acd71d1f10d59193
      CONFIGURE_COMMAND ../PCRE/configure --prefix=${CMAKE_INSTALL_PREFIX} --disable-shared
      BUILD_COMMAND ${BUILD_COMMAND_STRING}
      )

    ExternalProject_add(Swig
      URL http://prdownloads.sourceforge.net/swig/swig-${TARGET_SWIG_VERSION}.tar.gz
      URL_MD5  4319c503ee3a13d2a53be9d828c3adc0
      CONFIGURE_COMMAND ../Swig/configure --prefix=${CMAKE_INSTALL_PREFIX}
      --with-pcre-prefix=${CMAKE_INSTALL_PREFIX}
      DEPENDS PCRE
      )

    set(SWIG_DIR ${CMAKE_INSTALL_PREFIX}/share/swig/${TARGET_SWIG_VERSION})
    set(SWIG_EXECUTABLE ${CMAKE_INSTALL_PREFIX}/bin/swig)
    set(Swig_DEPEND Swig)
  endif()
endif(NOT SWIG_DIR)
