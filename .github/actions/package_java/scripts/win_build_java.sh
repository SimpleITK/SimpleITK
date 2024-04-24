#!/usr/bin/env bash

set -ex

export PATH=/usr/bin:${PATH}

export ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS=2

echo "COREBINARYDIRECTORY: ${COREBINARYDIRECTORY}"
echo "CTEST_SOURCE_DIRECTORY: ${CTEST_SOURCE_DIRECTORY}"

read -r -d '' CTEST_CACHE << EOM || true
CMAKE_PREFIX_PATH:PATH=${COREBINARYDIRECTORY}
SWIG_EXECUTABLE:FILEPATH=${COREBINARYDIRECTORY}\swigwin\swig.exe
BUILD_TESTING:BOOL=ON
BUILD_EXAMPLES:BOOL=ON
SimpleITK_BUILD_DISTRIBUTE:BOOL=ON
CSHARP_PLATFORM:STRING=${CSHARP_PLATFORM}
EOM


export CTEST_CACHE
export CTEST_BINARY_DIRECTORY="${GITHUB_WORKSPACE}/Java"

export CC=cl.exe
export CXX=cl.exe


ctest -D dashboard_source_config_dir="Wrapping/Java" \
      -D "dashboard_track:STRING=Package" \
      -D "CTEST_BUILD_NAME:STRING=${RUNNER_NAME}-${GITHUB_JOB}-java" \
      -D "CTEST_CMAKE_GENERATOR:STRING=Ninja" \
      -S "${CTEST_SOURCE_DIRECTORY}/.github/workflows/github_actions.cmake" -VV -j 2 || \
      echo "::warning file=win_build_csharp.sh:: There was a build or testing issue with Java."

( cd ${CTEST_BINARY_DIRECTORY} && cmake --build "${CTEST_BINARY_DIRECTORY}" --config "${CTEST_CONFIGURATION_TYPE}" --target dist -v )



mkdir -p "${GITHUB_WORKSPACE}/artifacts"
find ${CTEST_BINARY_DIRECTORY}/dist -name "SimpleITK*.zip" -exec cp -v {} "${GITHUB_WORKSPACE}/artifacts" \;
