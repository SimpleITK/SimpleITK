
#-----------------------------------------------------------------------------
# Get and build itk

get_cmake_property( _varNames VARIABLES )

foreach (_varName ${_varNames})
  if(_varName MATCHES "^ITK_" OR _varName MATCHES "FFTW")
    message( STATUS "Passing variable \"${_varName}=${${_varName}}\" to ITK external project.")
    list(APPEND ITK_VARS ${_varName})
  endif()
endforeach()

list(APPEND ITK_VARS
  PYTHON_EXECUTABLE
  PYTHON_INCLUDE_DIR
  PYTHON_LIBRARY
  PYTHON_DEBUG_LIBRARY
  )

VariableListToCache( ITK_VARS  ep_itk_cache )
VariableListToArgs( ITK_VARS  ep_itk_args )


set(proj ITK)  ## Use ITK convention of calling it ITK
set(ITK_REPOSITORY git://itk.org/ITK.git)

# NOTE: it is very important to update the ITK_DIR path with the
set(ITK_TAG_COMMAND GIT_TAG v4.3.1
 )

if( ${ITK_WRAPPING} OR ${BUILD_SHARED_LIBS} )
  set( ITK_BUILD_SHARED_LIBS ON )
else()
  set( ITK_BUILD_SHARED_LIBS OFF )
endif()


file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt" "${ep_itk_cache}\n${ep_common_cache}" )

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
  ${ep_itk_args}
  ${ep_common_args}
  -DBUILD_EXAMPLES:BOOL=OFF
  -DBUILD_TESTING:BOOL=OFF
  -DBUILD_SHARED_LIBS:BOOL=${ITK_BUILD_SHARED_LIBS}
  -DCMAKE_SKIP_RPATH:BOOL=ON
  -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  -DITK_LEGACY_REMOVE:BOOL=ON
  -DITK_BUILD_ALL_MODULES:BOOL=ON
  -DITK_USE_REVIEW:BOOL=ON
  -DITK_WRAP_float:BOOL=ON
  -DITK_WRAP_unsigned_char:BOOL=ON
  -DITK_WRAP_signed_short:BOOL=ON
  -DITK_WRAP_unsigned_short:BOOL=ON
  -DITK_WRAP_complex_float:BOOL=ON
  -DITK_WRAP_vector_float:BOOL=ON
  -DITK_WRAP_covariant_vector_float:BOOL=ON
  -DITK_WRAP_rgb_signed_short:BOOL=ON
  -DITK_WRAP_rgb_unsigned_char:BOOL=ON
  -DITK_WRAP_rgb_unsigned_short:BOOL=ON
  -DITK_WRAP_PYTHON:BOOL=${ITK_WRAPPING}
  # Required as to not install into system
  -DINSTALL_WRAP_ITK_COMPATIBILITY:BOOL=OFF
  # Swig
  -DSWIG_DIR:PATH=${SWIG_DIR}
  -DSWIG_EXECUTABLE:PATH=${SWIG_EXECUTABLE}
  BUILD_COMMAND ${BUILD_COMMAND_STRING}
  DEPENDS
  ${ITK_DEPENDENCIES}
  )


ExternalProject_Get_Property(ITK install_dir)
set(ITK_DIR "${install_dir}/lib/cmake/ITK-4.3" )
set(WrapITK_DIR "${install_dir}/lib/cmake/ITK-4.3/WrapITK")
