#!/usr/bin/env bash
set -eux

# this script is indented to be included in the docker image and run a container

OUT_DIR=/work/io
SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG:-v1.1rc1}

git clone https://github.com/SimpleITK/SimpleITK.git && ( cd SimpleITK && git checkout ${SIMPLEITK_GIT_TAG} )

mkdir bld && cd bld

cmake \
    -G Ninja \
    -DBUILD_DOXYGEN:BOOL=ON \
    -DBUILD_EXAMPLES:BOOL=OFF \
    -DWRAP_DEFAULT:BOOL=OFF \
    ../SimpleITK/SuperBuild

ninja SimpleITK-doc

cd SimpleITK-build/Documentation/
tar -zcvf ${OUT_DIR}/simpleitk_doxygen_html_${SIMPLEITK_GIT_TAG}.tar.gz html
