#!/usr/bin/env bash

TAG=${TAG:-"master"}
set -xe
if [ ! -d SimpleITK ]; then
    git clone https://github.com/SimpleITK/SimpleITK.git &&
        (cd SimpleITK && git checkout ${TAG})
fi

mkdir SimpleITK-build && \
    cd SimpleITK-build && \
    cmake -G Ninja\
          -DBUILD_DOXYGEN=ON\
          -DWRAP_DEFAULT=OFF\
          -DSimpleITK_BUILD_DISTRIBUTE:BOOL=ON\
          ../SimpleITK/SuperBuild/ && \
    cmake --build . --target SimpleITK-doc && \
    cd SimpleITK-build/Documentation/ && \
    tar --exclude=\*.md5 -zcvf /SimpleITKDoxygen.tar.gz ./html
