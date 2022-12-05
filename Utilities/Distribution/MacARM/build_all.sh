#! /usr/bin/env bash

SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG:-v2.2rc2}

# Look for a git tag as the first command line argument
if [ ! -z $1 ]
then
    SIMPLEITK_GIT_TAG=$1
fi

echo ""
echo "SIMPLEITK_GIT_TAG = ${SIMPLEITK_GIT_TAG}"
echo ""

Build_Root=/tmp
SimpleITK_Source=$Build_Root/SimpleITK
COREBINARYDIRECTORY=$Build_Root/SimpleITK-build


SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

cd $Build_Root

# Get the SimpleITK Source
if [ -d $SimpleITK_Source ]
then
    pushd $SimpleITK_Source
    git pull
    popd
else
    pushd $Build_Root
    git clone https://github.com/SimpleITK/SimpleITK.git
    $SimpleITK_Source=$Build_Root/SimpleITK
fi

if [ ! -z $SIMPLEITK_GIT_TAG ]
then
    pushd $SimpleITK_Source
    git checkout $SIMPLEITK_GIT_TAG
    popd
fi

mkdir -p $COREBINARYDIRECTORY
pushd $COREBINARYDIRECTORY
sh $SCRIPT_DIR/mac_build_core.sh
popd

for version in 3.8 3.9 3.10 3.11
do
    mkdir -p $COREBINARYDIRECTORY/py$version
    pushd $COREBINARYDIRECTORY/py$version
    COREBINARYDIRECTORY=$COREBINARYDIRECTORY sh $SCRIPT_DIR/mac_build_py.sh $version
popd
done
