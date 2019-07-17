# Make sure this file is included only once
get_filename_component(CMAKE_CURRENT_LIST_FILENAME ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
if(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED)
  return()
endif()
set(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED 1)

set(proj virtualenv)

set(${proj}_TARGET_VERSION 15.1.0)

# based on the standard EP_PREFIX locations, but since we don't build
# or install, then standards install directory is also the source
set(${proj}_binary_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj}-build)
set(${proj}_source_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj})
set(${proj}_install_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj})

sitkSourceDownload(${proj}_URL "virtualenv-${${proj}_TARGET_VERSION}.tar.gz")

ExternalProject_Add(${proj}
  URL "${${proj}_URL}"
  URL_HASH "${${proj}_URL_HASH}"
  SOURCE_DIR ${${proj}_source_dir}
  BINARY_DIR ${${proj}_binary_dir}
  INSTALL_DIR ${${proj}_install_dir}
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  ${External_Project_USES_TERMINAL}
)

sitkSourceDownloadDependency(${proj})


set(${proj}_ROOT ${${proj}_source_dir})
set(PYTHON_VIRTUALENV_SCRIPT ${${proj}_source_dir}/virtualenv.py)
