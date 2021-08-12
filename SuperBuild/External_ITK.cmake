
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

if(NOT DEFINED Module_SimpleITKFilters)
  set(Module_SimpleITKFilters ON)
endif()

if (NOT DEFINED Module_ITKIOTransformMINC)
  set(Module_ITKIOTransformMINC ON)
endif()

if (NOT DEFINED ITK_DEFAULT_THREADER)
  set( ITK_DEFAULT_THREADER "Platform")
endif()

get_cmake_property( _varNames VARIABLES )

foreach (_varName ${_varNames})
  if(_varName MATCHES "^ITK_"
      OR _varName MATCHES "^ITKV3"
      OR _varName MATCHES "^ITKV4"
      OR _varName MATCHES "FFTW"
      OR _varName MATCHES "^GDCM_"
      OR _varName MATCHES "^Module_"
      OR _varName STREQUAL "TBB_DIR")
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


set(ITK_GIT_REPOSITORY "${git_protocol}://github.com/InsightSoftwareConsortium/ITK.git" CACHE STRING "URL of ITK Git repository")
mark_as_advanced(ITK_GIT_REPOSITORY)
sitk_legacy_naming(ITK_GIT_REPOSITORY ITK_REPOSITORY)

set(_DEFAULT_ITK_GIT_TAG "v5.2.1")
set(ITK_GIT_TAG "${_DEFAULT_ITK_GIT_TAG}" CACHE STRING "Tag in ITK git repo")
mark_as_advanced(ITK_GIT_TAG)
set(ITK_TAG_COMMAND GIT_TAG "${ITK_GIT_TAG}")

set(ITK_USE_GIT_PROTOCOL 0)
if("${git_protocol}" STREQUAL "git")
  set(ITK_USE_GIT_PROTOCOL 1)
endif()


if( ${BUILD_SHARED_LIBS} )
  set( ITK_BUILD_SHARED_LIBS ON )
else()
  set( ITK_BUILD_SHARED_LIBS OFF )
  list( APPEND ep_itk_args
    "-DCMAKE_C_VISIBILITY_PRESET:STRING=hidden"
    "-DCMAKE_CXX_VISIBILITY_PRESET:STRING=hidden"
    "-DITK_TEMPLATE_VISIBILITY_DEFAULT:BOOL=OFF" )
endif()


if( ITK_GIT_TAG STREQUAL _DEFAULT_ITK_GIT_TAG )
  # Unable to use ITK_LEGACY_REMOVE due to change in the enum types.
  # list( APPEND ep_itk_args "-DITK_LEGACY_REMOVE:BOOL=ON" )
endif()

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt" "${ep_itk_cache}\n${ep_common_cache}" )

ExternalProject_Add(${proj}
  GIT_REPOSITORY ${ITK_GIT_REPOSITORY}
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
  -DITK_USE_KWSTYLE:BOOL=OFF
  -DITK_USE_GIT_PROTOCOL:BOOL=${ITK_USE_GIT_PROTOCOL}
  -DITK_INSTALL_PACKAGE_DIR=lib/cmake/ITK
  BUILD_COMMAND ${BUILD_COMMAND_STRING}
  DEPENDS
    ${ITK_DEPENDENCIES}
  ${External_Project_USES_TERMINAL}
  )


ExternalProject_Get_Property(${proj} install_dir)
set(ITK_DIR "${install_dir}/lib/cmake/ITK")
