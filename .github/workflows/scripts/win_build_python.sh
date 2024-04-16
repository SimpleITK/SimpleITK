#!/usr/bin/env bash

set -ex

export PATH=/usr/bin:${PATH}

export ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS=2

echo "COREBINARYDIRECTORY: ${COREBINARYDIRECTORY}"
echo "CTEST_SOURCE_DIRECTORY: ${CTEST_SOURCE_DIRECTORY}"

python --version
PYTHON_VERSION=$(python -c 'import sys;print ("{0}{1}".format(sys.version_info[0], sys.version_info[1]))')
Python_EXECUTABLE=$(python -c "import sys; print(sys.executable)")
echo $Python_EXECUTABLE



read -r -d '' CTEST_CACHE << EOM || true
CMAKE_PREFIX_PATH:PATH=${COREBINARYDIRECTORY}
SWIG_EXECUTABLE:FILEPATH=${COREBINARYDIRECTORY}\swigwin\swig.exe
Python_EXECUTABLE:FILEPATH=${Python_EXECUTABLE}
BUILD_TESTING:BOOL=ON
BUILD_EXAMPLES:BOOL=ON
SimpleITK_BUILD_DISTRIBUTE:BOOL=ON
SimpleITK_PYTHON_WHEEL:BOOL=1
EOM


export CTEST_CACHE
export CTEST_BINARY_DIRECTORY="${GITHUB_WORKSPACE}/py${PYTHON_VERSION}"

export CC=cl.exe
export CXX=cl.exe

ctest -D dashboard_source_config_dir="Wrapping/Python" \
      -D "dashboard_track:STRING=Package" \
      -D "CTEST_BUILD_NAME:STRING=${RUNNER_NAME}-${GITHUB_JOB}-py${PYTHON_VERSION}" \
      -D "CTEST_CMAKE_GENERATOR:STRING=Ninja" \
      -S ${CTEST_SOURCE_DIRECTORY}/.github/workflows/github_actions.cmake -VV -j 2

( cd ${CTEST_BINARY_DIRECTORY} && cmake --build "${CTEST_BINARY_DIRECTORY}" --config "${CTEST_CONFIGURATION_TYPE}" --target dist )


mkdir -p "${GITHUB_WORKSPACE}/artifacts"
find ${CTEST_BINARY_DIRECTORY} -name "SimpleITK*.whl" -exec cp -v {} "${GITHUB_WORKSPACE}/artifacts" \;
