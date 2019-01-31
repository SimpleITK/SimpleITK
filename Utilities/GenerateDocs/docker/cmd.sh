#!/usr/bin/env bash
set -eux

# this script is indented to be included in the docker image and run a container

OUT_DIR=/work/io
SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG:-v1.1rc1}
SIMPLEITK_GIT_REPO=${SIMPLEITK_GIT_REPO:-https://github.com/SimpleITK/SimpleITK.git}

git clone  ${SIMPLEITK_GIT_REPO} && ( cd SimpleITK && git checkout ${SIMPLEITK_GIT_TAG} )

here=$(pwd)

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

cd ${here}

if [ ! -e bld/SimpleITK-build/Documentation/xml/sitkImage_8h.xml ]
then
    echo "SimpleITK documentation target hasn't been built"
    exit 1
fi


rm -f ${here}/SimpleITK/Wrapping/R/Packaging/SimpleITK/man/*.Rd

cd ${here}/SimpleITK/Utilities/GenerateDocs/
cp /work/bin/config_vars.sh .
./SwigDocUpdate.sh

cp ${here}/SimpleITK/Wrapping/Python/PythonDocstrings.i ${OUT_DIR}/
cp ${here}/SimpleITK/Wrapping/Java/JavaDoc.i ${OUT_DIR}

cd ${here}/SimpleITK/Wrapping/R/Packaging/SimpleITK/man
tar -zcvf ${OUT_DIR}/sitkRdfiles_${SIMPLEITK_GIT_TAG}.tar.gz *.Rd
