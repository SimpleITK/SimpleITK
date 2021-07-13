#! /usr/bin/env bash

# This script will build the C++ code of SimpleITK
# It should be run in the build directory, e.g. ~/SimpleITK-build

if [ -z "$SimpleITK_Source" ]
then
    echo "No source"
    SimpleITK_Source="/tmp/SimpleITK"
    mkdir -p $SimpleITK_Source
fi
echo $SimpleITK_Source

cmake \
    -D "CMAKE_BUILD_TYPE:STRING=MinSizeRel" \
    -D "CMAKE_OSX_DEPLOYMENT_TARGET=11.0" \
    -D "MAKE_OSX_SYSROOT:PATH=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk" \
    -D "BUILD_EXAMPLES:BOOL=OFF" \
    -D "BUILD_TESTING:BOOL=ON" \
    -D "BUILD_SHARED_LIBS:BOOL=OFF" \
    -D "BUILD_DOCUMENTS:BOOL=OFF" \
    -D "WRAP_DEFAULT:BOOL=OFF" \
    $SimpleITK_Source/SuperBuild

cmake --build . -- -j4
