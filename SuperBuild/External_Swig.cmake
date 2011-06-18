if(NOT SWIG_DIR)

# Perl Compatible Regular Expressions
ExternalProject_add(PCRE
  URL http://downloads.sourceforge.net/project/pcre/pcre/8.12/pcre-8.12.tar.gz
  URL_MD5 fa69e4c5d8971544acd71d1f10d59193
  CONFIGURE_COMMAND ../PCRE/configure --prefix=${CMAKE_INSTALL_PREFIX}
  BUILD_COMMAND ${BUILD_COMMAND_STRING}
  )

ExternalProject_add(Swig
  URL http://prdownloads.sourceforge.net/swig/swig-2.0.1.tar.gz
  URL_MD5 df4465a62ccc5f0120fee0890ea1a31f
  CONFIGURE_COMMAND ../Swig/configure --prefix=${CMAKE_INSTALL_PREFIX}
#  --without-pcre
  --with-pcre-prefix=${CMAKE_INSTALL_PREFIX}
  DEPENDS PCRE
  )
set(SWIG_DIR ${CMAKE_INSTALL_PREFIX}/share/swig/2.0.1)
set(SWIG_EXECUTABLE ${CMAKE_INSTALL_PREFIX}/bin/swig)
set(Swig_DEPEND Swig)

endif(NOT SWIG_DIR)
