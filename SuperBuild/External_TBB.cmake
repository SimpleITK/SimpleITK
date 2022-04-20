# Make sure this file is included only once
get_filename_component(CMAKE_CURRENT_LIST_FILENAME ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
if(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED)
  return()
endif()
set(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED 1)


set(proj TBB)


ExternalProject_add(${proj}
  URL https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.3.0.tar.gz
  URL_HASH SHA256=8f616561603695bbb83871875d2c6051ea28f8187dbe59299961369904d1d49e
  SOURCE_DIR ${proj}
  BINARY_DIR ${proj}-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    -DTBB_TEST:BOOL=OFF
    -DCMAKE_BUILD_TYPE:STRING=Release
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/../oneTBB-prefix
    ${ep_common_args}
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DCMAKE_BUILD_TYPE:STRING=Release
  BUILD_BYPRODUCTS "${TBB_DIR}/TBBConfig.cmake"
  ${External_Project_USES_TERMINAL}
  )

ExternalProject_Get_Property(${proj} install_dir)
set(TBB_DIR "${install_dir}/lib/cmake/TBB")
