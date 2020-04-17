#!/usr/bin/env bash



SRC_DIR="/work/SimpleITK"
BLD_DIR="/work/SimpleITK-super"

# If the SRC_DIR is not mounted, then this tag will be checked out
SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG:-"master"}

set -xe


if [ ! -d ${SRC_DIR} ]; then
    ( git clone https://github.com/SimpleITK/SimpleITK.git ${SRC_DIR} &&
          cd ${SRC_DIR} &&
          git checkout ${SIMPLEITK_GIT_TAG}
    )
fi

mkdir -p ${BLD_DIR} && \
    cd ${BLD_DIR} && \
    cmake -G Ninja\
          -DBUILD_DOXYGEN=ON\
          -DWRAP_DEFAULT=OFF\
          -DSimpleITK_BUILD_DISTRIBUTE:BOOL=ON\
          ${SRC_DIR}/SuperBuild/ && \
    cmake --build . --target SimpleITK-doc && \
    cd ${BLD_DIR}/SimpleITK-build/Documentation/ && \
    tar --exclude=\*.md5 --exclude=\*.map -zcvf /SimpleITKDoxygen.tar.gz ./html
