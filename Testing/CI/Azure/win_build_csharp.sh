#!/usr/bin/env bash

set -ex

export PATH=/usr/bin:${PATH}

export ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS=2

read -r -d '' CTEST_CACHE << EOM || true
CMAKE_PREFIX_PATH:PATH=${COREBINARYDIRECTORY}
SWIG_EXECUTABLE:FILEPATH=${COREBINARYDIRECTORY}\swigwin\swig.exe
BUILD_TESTING:BOOL=ON
BUILD_EXAMPLES:BOOL=ON
SimpleITK_BUILD_DISTRIBUTE:BOOL=ON
Java_JAR_EXECUTABLE:FILEPATH=jar.exe
CSHARP_PLATFORM:STRING=${CSHARP_PLATFORM}
EOM


export CTEST_CACHE
export CTEST_BINARY_DIRECTORY="${AGENT_BUILDDIRECTORY}/csharp"

export CC=cl.exe
export CXX=cl.exe


ctest -D dashboard_source_config_dir="Wrapping/CSharp" \
      -D "dashboard_track:STRING=Package" \
      -D "CTEST_BUILD_NAME:STRING=${AGENT_NAME}-${AGENT_JOBNAME}-csharp" \
      -D "CTEST_CMAKE_GENERATOR:STRING=Ninja" \
      -S ${BUILD_SOURCESDIRECTORY}/Testing/CI/Azure/azure.cmake -V || echo "##vso[task.logissue type=warning]There was a build or testing issue."

( cd ${CTEST_BINARY_DIRECTORY} && cmake --build "${CTEST_BINARY_DIRECTORY}" --config "${CTEST_CONFIGURATION_TYPE}" --target dist -v )


mkdir -p "${BUILD_ARTIFACTSTAGINGDIRECTORY}/csharp"
find ${CTEST_BINARY_DIRECTORY}/dist -name "SimpleITK*.zip" -exec cp -v {} "${BUILD_ARTIFACTSTAGINGDIRECTORY}/csharp" \;
