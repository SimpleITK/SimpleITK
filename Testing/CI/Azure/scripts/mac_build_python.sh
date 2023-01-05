#!/usr/bin/env bash

set -ex

export ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS=2

echo "COREBINARYDIRECTORY: ${COREBINARYDIRECTORY}"

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
EOM

export CTEST_CACHE
export CTEST_BINARY_DIRECTORY="${AGENT_BUILDDIRECTORY}/py${PYTHON_VERSION}"

ctest -D dashboard_source_config_dir="Wrapping/Python" \
      -D "dashboard_track:STRING=Package" \
      -D "CTEST_BUILD_NAME:STRING=${AGENT_NAME}-${AGENT_JOBNAME}-py${PYTHON_VERSION}" \
      -S ${BUILD_SOURCESDIRECTORY}/Testing/CI/Azure/azure.cmake -V -j 2 || echo "##vso[task.logissue type=warning]There was a build or testing issue."

cmake --build "${CTEST_BINARY_DIRECTORY}" --target dist &&
    mkdir -p "${BUILD_ARTIFACTSTAGINGDIRECTORY}/python" &&
    find ${CTEST_BINARY_DIRECTORY} -name "SimpleITK*.whl" -exec cp -v {} "${BUILD_ARTIFACTSTAGINGDIRECTORY}/python" \;
