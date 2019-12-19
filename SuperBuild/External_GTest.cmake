# Make sure this file is included only once
get_filename_component(CMAKE_CURRENT_LIST_FILENAME ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
if(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED)
  return()
endif()
set(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED 1)

set(proj GTest)

set(GTEST_GIT_REPOSITORY "${git_protocol}://github.com/google/googletest.git" CACHE  STRING "Google Test repository")
mark_as_advanced(GTEST_GIT_REPOSITORY)

set(GTEST_GIT_TAG "release-1.10.0" CACHE STRING "Tag or hash for GTtest git repo")
mark_as_advanced(GTEST_GIT_TAG)
set(GTEST_TAG_COMMAND GIT_TAG "${GTEST_GIT_TAG}")

# follow the standard EP_PREFIX locations
set(GTEST_source_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj})

ExternalProject_Add(${proj}
  GIT_REPOSITORY ${GTEST_GIT_REPOSITORY}
  ${GTEST_TAG_COMMAND}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
  ${External_Project_USES_TERMINAL}
)

sitkSourceDownloadDependency(${proj})

set(GTEST_ROOT ${GTEST_source_dir})
