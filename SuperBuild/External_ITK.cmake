
#-----------------------------------------------------------------------------
# Get and build itk

# Determine if we need to set to use 64BITS_IDS for windows64
if(CMAKE_CL_64)
  option(ITK_USE_64BITS_IDS "When ON, ITK will use 64 bits integers to
index pixels. This is needed for managing images larger than 4Gb in
some platforms."
    ON)
  mark_as_advanced(ITK_USE_64BITS_IDS)
endif()

if(NOT DEFINED ITK_BUILD_DEFAULT_MODULES)
  set(ITK_BUILD_DEFAULT_MODULES ON)
endif()

if(NOT DEFINED Module_ITKReview)
  set(Module_ITKReview ON)
endif()


get_cmake_property( _varNames VARIABLES )

foreach (_varName ${_varNames})
  if(_varName MATCHES "^ITK_"
      OR _varName MATCHES "^ITKV3"
      OR _varName MATCHES "FFTW"
      OR _varName MATCHES "^Module_ITK")
    message( STATUS "Passing variable \"${_varName}=${${_varName}}\" to ITK external project.")
    list(APPEND ITK_VARS ${_varName})
  endif()
endforeach()

list(APPEND ITK_VARS
  PYTHON_EXECUTABLE
  )

VariableListToCache( ITK_VARS  ep_itk_cache )
VariableListToArgs( ITK_VARS  ep_itk_args )


set(proj ITK)  ## Use ITK convention of calling it ITK
if(NOT DEFINED ITK_REPOSITORY)
  set(ITK_REPOSITORY "${git_protocol}://itk.org/ITK.git")
endif()

set(ITK_USE_GIT_PROTOCOL 0)
if("${git_protocol}" STREQUAL "git")
  set(ITK_USE_GIT_PROTOCOL 1)
endif()

# NOTE: it is very important to update the ITK_DIR path with the ITK version
set(ITK_TAG_COMMAND GIT_TAG v4.11.1) # v4.11.1 tag

if( ${BUILD_SHARED_LIBS} )
  set( ITK_BUILD_SHARED_LIBS ON )
else()
  set( ITK_BUILD_SHARED_LIBS OFF )
  list( APPEND ep_itk_args
    "-DCMAKE_C_VISIBILITY_PRESET:STRING=hidden"
    "-DCMAKE_CXX_VISIBILITY_PRESET:STRING=hidden"
    "-DITK_TEMPLATE_VISIBILITY_DEFAULT:BOOL=OFF" )
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
  -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
  -DCMAKE_VISIBILITY_INLINES_HIDDEN:BOOL=ON
  -DBUILD_EXAMPLES:BOOL=OFF
  -DBUILD_TESTING:BOOL=OFF
  -DBUILD_SHARED_LIBS:BOOL=${ITK_BUILD_SHARED_LIBS}
  -DCMAKE_SKIP_RPATH:BOOL=ON
  -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  -DITK_LEGACY_REMOVE:BOOL=ON
  -DITK_USE_KWSTYLE:BOOL=OFF
  -DITK_USE_GIT_PROTOCOL:BOOL=${ITK_USE_GIT_PROTOCOL}
  BUILD_COMMAND ${BUILD_COMMAND_STRING}
  DEPENDS
    ${ITK_DEPENDENCIES}
  ${External_Project_USES_TERMINAL}
  )


ExternalProject_Get_Property(ITK install_dir)
set(ITK_DIR "${install_dir}/lib/cmake/ITK-4.11" )
