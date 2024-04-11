#!/usr/bin/env bash

set -ex

export ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS=2

echo "COREBINARYDIRECTORY: ${COREBINARYDIRECTORY}"
echo "CTEST_BINARY_DIRECTORY: ${CTEST_BINARY_DIRECTORY}"
echo "CTEST_SOURCE_DIRECTORY: ${CTEST_SOURCE_DIRECTORY}"

which python
python --version
PYTHON_VERSION=$(python -c 'import sys;print ("{0}{1}".format(sys.version_info[0], sys.version_info[1]))')

read -r -d '' CTEST_CACHE << EOM || true
CMAKE_PREFIX_PATH:PATH=${COREBINARYDIRECTORY}
CMAKE_CXX_VISIBILITY_PRESET:STRING=hidden
CMAKE_VISIBILITY_INLINES_HIDDEN:BOOL=ON
CMAKE_OSX_DEPLOYMENT_TARGET=10.9
SWIG_EXECUTABLE:FILEPATH=${COREBINARYDIRECTORY}/Swig/bin/swig
BUILD_EXAMPLES:BOOL=ON
BUILD_TESTING:BOOL=ON
SimpleITK_PYTHON_PLAT_NAME:STRING=macosx-10.9-x86_64
SimpleITK_BUILD_DISTRIBUTE:BOOL=ON
SimpleITK_PYTHON_WHEEL:BOOL=1
SimpleITK_BUILD_STRIP:BOOL=1
Python_EXECUTABLE:FILEPATH=$(which python)
EOM

export CTEST_CACHE
export CTEST_BINARY_DIRECTORY="${GITHUB_WORKSPACE}/py${PYTHON_VERSION}"

ctest -D dashboard_source_config_dir="Wrapping/Python" \
      -D "dashboard_track:STRING=Package" \
      -D "CTEST_BUILD_NAME:STRING=${RUNNER_NAME}-${GITHUB_JOB}-py${PYTHON_VERSION}" \
      -S ${CTEST_SOURCE_DIRECTORY}/.github/workflows/github_actions.cmake -VV -j 2

cmake --build "${CTEST_BINARY_DIRECTORY}" --target dist


mkdir -p "${GITHUB_WORKSPACE}/artifacts"
find ${CTEST_BINARY_DIRECTORY} -name "SimpleITK*.whl" -exec cp -v {} "${GITHUB_WORKSPACE}/artifacts" \;
