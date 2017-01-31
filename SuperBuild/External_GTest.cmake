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
set(GTEST_binary_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj}-build)
set(GTEST_source_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj})
set(GTEST_install_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj})

sitkSourceDownload(GTEST_URL "googletest-release-${GTEST_TARGET_VERSION}.tar.gz" ${GTEST_DOWNLOAD_SOURCE_HASH})

file(WRITE "${GTEST_binary_dir}/CMakeCacheInit.txt" "${ep_common_cache}" )

set(${proj}_ARCHIVE_OUTPUT_DIRECTORY "<BINARY_DIR>/lib")
if (CMAKE_GENERATOR MATCHES "Visual Studio")
  set(${proj}_ARCHIVE_OUTPUT_DIRECTORY "<BINARY_DIR>/lib/$<CONFIG>")
endif()

set(ep_extra_args)
if(MSVC_VERSION EQUAL 1700)
  # Tuples are limited by _VARIADIC_MAX in VS11. The variadic
  # templates are not deep enough by default. We are not currently
  # using the GTest features which require tuple, so just disable them
  # and hope that upstream premanetly addresses the problem, with out
  # required more CMake core for compiler issues.
  set(ep_extra_args ${ep_extra_args} -D CMAKE_CXX_FLAGS=-DGTEST_HAS_TR1_TUPLE=0 ${CMAKE_CXX_FLAGS})
endif()

if(MSVC)
  set(ep_extra_args ${ep_extra_args} -D gtest_force_shared_crt:BOOL=ON)
endif()


ExternalProject_Add(${proj}
  URL "${GTEST_URL}"
  URL_MD5 ${GTEST_DOWNLOAD_SOURCE_HASH}
  INSTALL_DIR ${GTEST_install_dir}
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    --no-warn-unused-cli
    -C "${GTEST_binary_dir}/CMakeCacheInit.txt"
    ${ep_common_args}
    ${ep_extra_args}
    -DBUILD_GMOCK:BOOL=OFF
    -DBUILD_GTEST:BOOL=ON
    -DBUILD_SHARED_LIBS:BOOL=OFF
    -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY:PATH=<BINARY_DIR>/lib
    -Dgtest_disable_pthreads:BOOL=ON
  INSTALL_COMMAND
      ${CMAKE_COMMAND} -E copy_directory ${${proj}_ARCHIVE_OUTPUT_DIRECTORY} <INSTALL_DIR>/lib
    COMMAND
      ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/googletest/include <INSTALL_DIR>/include
  ${External_Project_USES_TERMINAL}
)

sitkSourceDownloadDependency(${proj})

set(GTEST_ROOT ${GTEST_install_dir})
