#-----------------------------------------------------------------------------
# Get and build itk

# Determine if we need to set to use 64BITS_IDS for windows64
if(CMAKE_CL_64)
  option(
    ITK_USE_64BITS_IDS
    "When ON, ITK will use 64 bits integers to
index pixels. This is needed for managing images larger than 4Gb in
some platforms."
    ON
  )
  mark_as_advanced(ITK_USE_64BITS_IDS)
endif()

option(
  ITK_USE_BUILD_DIR
  "When ON, ITK will not be installed and SimpleITK built against the ITK build
directory."
  OFF
)
mark_as_advanced(ITK_USE_BUILD_DIR)

if(NOT DEFINED ITK_BUILD_DEFAULT_MODULES)
  set(ITK_BUILD_DEFAULT_MODULES ON)
endif()

if(NOT DEFINED Module_ITKReview)
  set(Module_ITKReview ON)
endif()

set(
  _SimpleITK_DEFAULT_MODULES
  "Module_SimpleITKFilters"
  "Module_ITKIOTransformMINC"
  "Module_GenericLabelInterpolator"
  "Module_LabelErodeDilate"
)
foreach(_module ${_SimpleITK_DEFAULT_MODULES})
  if(NOT DEFINED ${_module})
    set(${_module} ON)
  endif()
endforeach()

if(NOT DEFINED ITK_DEFAULT_THREADER)
  set(ITK_DEFAULT_THREADER "Pool")
endif()

get_cmake_property(_varNames VARIABLES)

foreach(_varName ${_varNames})
  if(
    _varName
      MATCHES
      "^ITK_"
    OR
      _varName
        MATCHES
        "^ITKV3"
    OR
      _varName
        MATCHES
        "^ITKV4"
    OR
      _varName
        MATCHES
        "FFTW"
    OR
      _varName
        MATCHES
        "^GDCM_"
    OR
      _varName
        MATCHES
        "^NIFTI_"
    OR
      _varName
        MATCHES
        "^Module_"
    OR
      _varName
        STREQUAL
        "TBB_DIR"
  )
    message(
      STATUS
      "Passing variable \"${_varName}=${${_varName}}\" to ITK external project."
    )
    list(APPEND ITK_VARS ${_varName})
  endif()
endforeach()

list(APPEND ITK_VARS Python_EXECUTABLE)

variablelisttocache( ITK_VARS  ep_itk_cache )
variablelisttoargs( ITK_VARS  ep_itk_args )

set(proj ITK) ## Use ITK convention of calling it ITK

set(
  ITK_GIT_REPOSITORY
  "${git_protocol}://github.com/InsightSoftwareConsortium/ITK.git"
  CACHE STRING
  "URL of ITK Git repository"
)
mark_as_advanced(ITK_GIT_REPOSITORY)
sitk_legacy_naming(ITK_GIT_REPOSITORY ITK_REPOSITORY)

# Using 6.0 alpha tags for SimpleITK 3 development
set(_DEFAULT_ITK_GIT_TAG "v6.0a03")
set(ITK_GIT_TAG "${_DEFAULT_ITK_GIT_TAG}" CACHE STRING "Tag in ITK git repo")
mark_as_advanced(ITK_GIT_TAG)
set(
  ITK_TAG_COMMAND
  GIT_TAG
  "${ITK_GIT_TAG}"
)

set(ITK_USE_GIT_PROTOCOL 0)
if("${git_protocol}" STREQUAL "git")
  set(ITK_USE_GIT_PROTOCOL 1)
endif()

if(${BUILD_SHARED_LIBS})
  set(ITK_BUILD_SHARED_LIBS ON)
else()
  set(ITK_BUILD_SHARED_LIBS OFF)
  list(
    APPEND
    ep_itk_args
    "-DCMAKE_C_VISIBILITY_PRESET:STRING=hidden"
    "-DCMAKE_CXX_VISIBILITY_PRESET:STRING=hidden"
    "-DITK_TEMPLATE_VISIBILITY_DEFAULT:BOOL=OFF"
  )
endif()

if(NOT DEFINED CMAKE_CXX_STANDARD)
  list(APPEND ep_itk_args "-DCMAKE_CXX_STANDARD:STRING=17")
endif()

if(ITK_USE_BUILD_DIR)
  set(
    ITK_INSTALL_COMMAND
    INSTALL_COMMAND
    ${CMAKE_COMMAND}
    -E
    echo
    "Skipping install step."
  )
endif()

if(ITK_GIT_TAG STREQUAL _DEFAULT_ITK_GIT_TAG)
  # While migrated to ITK 6.0 this is disabled
  #list( APPEND ep_itk_args "-DITK_LEGACY_REMOVE:BOOL=ON" )
endif()

file(
  WRITE
  "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt"
  "${ep_itk_cache}\n${ep_common_cache}"
)

ExternalProject_Add(
  ${proj}
  GIT_REPOSITORY ${ITK_GIT_REPOSITORY}
  ${ITK_TAG_COMMAND}
  UPDATE_COMMAND
    "" ${ITK_INSTALL_COMMAND}
  SOURCE_DIR ${proj}
  BINARY_DIR ${proj}-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    --no-warn-unused-cli -C
    "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt"
    ${ep_itk_args} ${ep_common_args} -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
    -DCMAKE_VISIBILITY_INLINES_HIDDEN:BOOL=ON -DBUILD_EXAMPLES:BOOL=OFF
    -DBUILD_TESTING:BOOL=OFF -DBUILD_SHARED_LIBS:BOOL=${ITK_BUILD_SHARED_LIBS}
    -DCMAKE_SKIP_RPATH:BOOL=ON -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DITK_USE_KWSTYLE:BOOL=OFF
    -DITK_USE_GIT_PROTOCOL:BOOL=${ITK_USE_GIT_PROTOCOL}
    -DITK_INSTALL_PACKAGE_DIR=lib/cmake/ITK
  BUILD_COMMAND
    ${BUILD_COMMAND_STRING}
  DEPENDS
    ${${proj}_DEPENDENCIES}
    ${External_Project_USES_TERMINAL}
)

if(ITK_USE_BUILD_DIR)
  ExternalProject_Get_Property(
    ${proj}
    BINARY_DIR
  )

  set(ITK_DIR "${BINARY_DIR}")
else()
  ExternalProject_Get_Property(
    ${proj}
    install_dir
  )
  set(ITK_DIR "${install_dir}/lib/cmake/ITK")
endif()
