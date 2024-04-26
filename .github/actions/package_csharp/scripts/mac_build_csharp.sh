#!/usr/bin/env bash

set -ex

export ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS=2

echo "COREBINARYDIRECTORY: ${COREBINARYDIRECTORY}"
echo "CTEST_SOURCE_DIRECTORY: ${CTEST_SOURCE_DIRECTORY}"

read -r -d '' CTEST_CACHE << EOM || true
CMAKE_PREFIX_PATH:PATH=${COREBINARYDIRECTORY}
CMAKE_CXX_VISIBILITY_PRESET:STRING=hidden
CMAKE_VISIBILITY_INLINES_HIDDEN:BOOL=ON
CMAKE_OSX_DEPLOYMENT_TARGET=10.9
SWIG_EXECUTABLE:FILEPATH=${COREBINARYDIRECTORY}/Swig/bin/swig
BUILD_EXAMPLES:BOOL=ON
BUILD_TESTING:BOOL=ON
SimpleITK_BUILD_DISTRIBUTE:BOOL=ON
SimpleITK_BUILD_STRIP:BOOL=1
EOM

export CTEST_CACHE
export CTEST_BINARY_DIRECTORY="${GITHUB_WORKSPACE}/CSharp"

ctest -D dashboard_source_config_dir="Wrapping/CSharp" \
      -D "dashboard_track:STRING=Package" \
      -D "CTEST_BUILD_NAME:STRING=${RUNNER_NAME}-${GITHUB_JOB}-csharp" \
      -D CSHARP_INTERPRETER:FILEPATH=$(which mono) \
      -S "${CTEST_SOURCE_DIRECTORY}/.github/workflows/github_actions.cmake" -VV -j 2 || \
       echo "::warning file=mac_build_csharp.sh:: There was a build or testing issue with csharp."

cmake --build "${CTEST_BINARY_DIRECTORY}" --target dist


mkdir -p "${GITHUB_WORKSPACE}/artifacts"
find "${CTEST_BINARY_DIRECTORY}/dist" -name "SimpleITK*.zip" -exec cp -v {} "${GITHUB_WORKSPACE}/artifacts" \;
echo "==== CMakeCache.txt ===="
cat ${GITHUB_WORKSPACE}/CSharp/CMakeCache.txt
