#!/usr/bin/env bash

set -ex

export ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS=2

echo "COREBINARYDIRECTORY: ${COREBINARYDIRECTORY}"

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
export CTEST_BINARY_DIRECTORY="${AGENT_BUILDDIRECTORY}/CSharp"

javac -version

ctest -D dashboard_source_config_dir="Wrapping/CSharp" \
      -D "dashboard_track:STRING=Package" \
      -D "CTEST_BUILD_NAME:STRING=${AGENT_NAME}-${AGENT_JOBNAME}-csharp" \
      -S ${BUILD_SOURCESDIRECTORY}/Testing/CI/Azure/azure.cmake -V -j 2  || echo "##vso[task.logissue type=warning]There was a build or testing issue."

cmake --build "${CTEST_BINARY_DIRECTORY}" --target dist


mkdir -p "${BUILD_ARTIFACTSTAGINGDIRECTORY}/csharp"
find "${CTEST_BINARY_DIRECTORY}/dist" -name "SimpleITK*.zip" -exec cp -v {} "${BUILD_ARTIFACTSTAGINGDIRECTORY}/csharp" \;
