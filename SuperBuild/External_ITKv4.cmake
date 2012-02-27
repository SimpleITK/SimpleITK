
#-----------------------------------------------------------------------------
# Get and build itk

set(ITK_LANGUAGES_VARS
      PYTHON_EXECUTABLE
      PYTHON_INCLUDE_DIR
      )

VariableListToCache( ITK_LANGUAGES_VARS  ep_languages_cache )
VariableListToArgs( ITK_LANGUAGES_VARS  ep_languages_args )


set(proj ITK)  ## Use ITK convention of calling it ITK
set(ITK_REPOSITORY git://itk.org/ITK.git)
set(ITK_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/ITK-4.1)
set(ITK_TAG_COMMAND GIT_TAG v4.1rc01 ) # Tue Jan 31 nightly-master
set(WrapITK_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/ITK-4.0/WrapITK)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt" "${ep_languages_cache}\n${ep_common_cache}" )

ExternalProject_Add(${proj}
  GIT_REPOSITORY ${ITK_REPOSITORY}
  ${ITK_TAG_COMMAND}
  UPDATE_COMMAND ""
  SOURCE_DIR ${proj}
  BINARY_DIR ${proj}-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
  --no-warn-unused-cli
  -C "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt"
  ${ep_common_args}
  ${ep_languages_args}
  -DBUILD_EXAMPLES:BOOL=OFF
  -DBUILD_TESTING:BOOL=OFF
  -DBUILD_SHARED_LIBS:BOOL=${ITK_WRAPPING}
  -DCMAKE_SKIP_RPATH:BOOL=ON
  -DITK_LEGACY_REMOVE:BOOL=ON
  -DITK_BUILD_ALL_MODULES:BOOL=ON
  -DITK_USE_REVIEW:BOOL=ON
  -DUSE_WRAP_ITK:BOOL=${ITK_WRAPPING}
  -DINSTALL_WRAP_ITK_COMPATIBILITY:BOOL=OFF
  -DWRAP_float:BOOL=ON
  -DWRAP_unsigned_char:BOOL=ON
  -DWRAP_signed_short:BOOL=ON
  -DWRAP_unsigned_short:BOOL=ON
  -DWRAP_complex_float:BOOL=ON
  -DWRAP_vector_float:BOOL=ON
  -DWRAP_covariant_vector_float:BOOL=ON
  -DWRAP_rgb_signed_short:BOOL=ON
  -DWRAP_rgb_unsigned_char:BOOL=ON
  -DWRAP_rgb_unsigned_short:BOOL=ON
  -DWRAP_ITK_TCL:BOOL=OFF
  -DWRAP_ITK_JAVA:BOOL=OFF
  -DWRAP_ITK_PYTHON:BOOL=ON
  ${ITK_PYTHON_ARGS}
  ${FFTW_FLAGS}
  BUILD_COMMAND ${BUILD_COMMAND_STRING}
  DEPENDS
  ${ITK_DEPENDENCIES}
  )
