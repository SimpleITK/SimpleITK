#! /usr/bin/env bash


# This script is hard coded to point to the installed location
# of the Python.org package distrbution of Python 3.8 or 3.9.

# Default to 3.8
PY_MAJOR=3
PY_MINOR=8
PY_VERSION=3.8

if [ $1 == "3.9" ]
then
    PY_MAJOR=3
    PY_MINOR=9
    PY_VERSION=3.9
fi

PY_DIR=/Library/Frameworks/Python.framework/Versions/${PY_VERSION}
echo $PY_DIR

if [ -z "$SimpleITK_Source" ]
then
    echo "No source"
    SimpleITK_Source="/tmp/SimpleITK"
fi
echo $SimpleITK_Source

if [ -z "$COREBINARYDIRECTORY" ]
then
    COREBINARYDIRECTORY="/tmp/SimpleITK-build/"
fi

echo "COREBINARYDIRECTORY: ${COREBINARYDIRECTORY}"

cmake \
    -D "CMAKE_PREFIX_PATH:PATH=${COREBINARYDIRECTORY}" \
    -D "ITK_DIR:PATH=${COREBINARYDIRECTORY}/ITK-prefix/lib/cmake/ITK" \
    -D "CMAKE_CXX_VISIBILITY_PRESET:STRING=hidden" \
    -D "CMAKE_VISIBILITY_INLINES_HIDDEN:BOOL=ON" \
    -D "CMAKE_OSX_DEPLOYMENT_TARGET=11.0" \
    -D "SWIG_EXECUTABLE:FILEPATH=${COREBINARYDIRECTORY}/Swig/bin/swig" \
    -D "BUILD_EXAMPLES:BOOL=ON" \
    -D "BUILD_TESTING:BOOL=ON" \
    -D "PYTHON_EXECUTABLE:FILEPATH=${PY_DIR}/bin/python${PY_MAJOR}" \
    -D "PYTHON_INCLUDE_DIR:PATH=${PY_DIR}/include/python${PY_VERSION}" \
    -D "PYTHON_LIBRARY:FILEPATH=${PY_DIR}/libpython${PY_VERSION}.dylib" \
    -D "SimpleITK_PYTHON_PLAT_NAME:STRING=macosx-11.0-arm64" \
    -D "SimpleITK_BUILD_DISTRIBUTE:BOOL=ON" \
    -D "SimpleITK_PYTHON_WHEEL:BOOL=1" \
    -D "SimpleITK_BUILD_STRIP:BOOL=1" \
    $SimpleITK_Source/Wrapping/Python

cmake --build .
cmake --build . --target dist
