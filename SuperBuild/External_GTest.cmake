# Make sure this file is included only once
get_filename_component(CMAKE_CURRENT_LIST_FILENAME ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
if(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED)
  return()
endif()
set(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED 1)

set(proj GTest)

set(GTEST_TARGET_VERSION 1.8.0)
set(GTEST_DOWNLOAD_SOURCE_HASH "16877098823401d1bf2ed7891d7dce36")

# follow the standard EP_PREFIX locations
set(GTEST_source_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj})

sitkSourceDownload(GTEST_URL "googletest-release-${GTEST_TARGET_VERSION}.tar.gz" ${GTEST_DOWNLOAD_SOURCE_HASH})

ExternalProject_Add(${proj}
  URL "${GTEST_URL}"
  URL_MD5 ${GTEST_DOWNLOAD_SOURCE_HASH}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
  ${External_Project_USES_TERMINAL}
)

sitkSourceDownloadDependency(${proj})

set(GTEST_ROOT ${GTEST_source_dir}/googletest)
