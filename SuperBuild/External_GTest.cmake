# Make sure this file is included only once
get_filename_component(CMAKE_CURRENT_LIST_FILENAME ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
if(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED)
  return()
endif()
set(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED 1)

set(proj GTest)

set(GTEST_TARGET_VERSION 1.7.0)
set(GTEST_DOWNLOAD_SOURCE_HASH "2d6ec8ccdf5c46b05ba54a9fd1d130d7")

# follow the standard EP_PREFIX locations
set(GTEST_binary_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj}-build)
set(GTEST_source_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj})
set(GTEST_install_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj})

file(WRITE "${GTEST_binary_dir}/CMakeCacheInit.txt" "${ep_common_cache}" )

set(GTEST_PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/lua.cmake
  ${lua_source_dir}/CMakeLists.txt
)

ExternalProject_Add(${proj}
  URL http://midas3.kitware.com/midas/api/rest?method=midas.bitstream.download&checksum=${GTEST_DOWNLOAD_SOURCE_HASH}&name=swig-${GTEST_TARGET_VERSION}.zip
  URL_MD5 ${GTEST_DOWNLOAD_SOURCE_HASH}
  INSTALL_DIR ${GTEST_install_dir}
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    --no-warn-unused-cli
    -C "${GTEST_binary_dir}/CMakeCacheInit.txt"
    ${ep_common_args}
    -D BUILD_SHARED_LIBS:BOOL=OFF
    -D CMAKE_ARCHIVE_OUTPUT_DIRECTORY:PATH=<BINARY_DIR>/lib
  INSTALL_COMMAND
      ${CMAKE_COMMAND} -E copy_directory <BINARY_DIR>/lib <INSTALL_DIR>/lib
    COMMAND
      ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/include <INSTALL_DIR>/include
)

set(GTEST_ROOT ${GTEST_install_dir})
