
set(proj ITKExternalITKModule)  ## Use ITK convention of calling it ITK
if(NOT DEFINED ${itkExternalModule}_REPOSITORY)
  set(${proj}_REPOSITORY "${git_protocol}://github.com/SimpleITK/itkSimpleITKFiltersModule.git")
endif()

set(${proj}_TAG_COMMAND GIT_TAG e99b7bed3e241edd5b466ecbdf9342e9b8dc3c6f)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt" "${ep_common_cache}" )

ExternalProject_Add(${proj}
  GIT_REPOSITORY ${${proj}_REPOSITORY}
  ${${proj}_TAG_COMMAND}
  USES_TERMINAL_DOWNLOAD 1
  UPDATE_COMMAND ""
  SOURCE_DIR ${proj}
  BINARY_DIR ${proj}-build
  INSTALL_DIR ITK-prefix
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
  --no-warn-unused-cli
  -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  -D "ITK_DIR:PATH=${CMAKE_CURRENT_BINARY_DIR}/ITK-build"
  -C "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt"
  ${ep_itk_args}
  ${ep_common_args}
  USES_TERMINAL_CONFIGURE 1
  USES_TERMINAL_BUILD 1
  USES_TERMINAL_INSTALL 1
  BUILD_COMMAND ${BUILD_COMMAND_STRING}
  DEPENDS
  ${${proj}_DEPENDENCIES}
  )

