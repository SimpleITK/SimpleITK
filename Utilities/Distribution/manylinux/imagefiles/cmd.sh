#!/bin/sh

set -x

export SRC_DIR="/tmp/SimpleITK"
export BLD_DIR="/tmp/SimpleITK-build"
export OUT_DIR="/work/io"

SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG:-v1.0rc3}

PYTHON_VERSIONS=${PYTHON_VERSIONS:-$(ls /opt/python | sed -e 's/cp2[0-6][^ ]\+ \?//g')}

NPROC=$(grep -c processor /proc/cpuinfo)
export MAKEFLAGS="-j ${NPROC}"


function build_simpleitk {

    echo "SIMPLEITK_GIT_TAG: ${SIMPLEITK_GIT_TAG}"

    git clone https://github.com/SimpleITK/SimpleITK.git ${SRC_DIR} &&
    (cd ${SRC_DIR}  && git checkout ${SIMPLEITK_GIT_TAG}  ) &&
    rm -rf ${BLD_DIR} &&
    mkdir -p ${BLD_DIR} && cd ${BLD_DIR} &&
    cmake \
        -DSimpleITK_BUILD_DISTRIBUTE:BOOL=ON \
        -DSimpleITK_BUILD_STRIP:BOOL=ON \
        -DCMAKE_BUILD_TYPE:STRING=Release \
        -DBUILD_TESTING:BOOL=ON \
        -DBUILD_EXAMPLES:BOOL=OFF \
        -DBUILD_SHARED_LIBS:BOOL=OFF \
        -DWRAP_DEFAULT:BOOL=OFF \
        -DITK_REPOSITORY:STRING="https://github.com/InsightSoftwareConsortium/ITK.git" \
        ${SRC_DIR}/SuperBuild &&
    make  &&
    find ./ -name \*.o -delete
}




function build_simpleitk_python {

    PYTHON_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    PYTHON_INCLUDE_DIR="$( find -L /opt/python/${PYTHON}/include/ -name Python.h -exec dirname {} \; )"

    echo ""
    echo "PYTHON_EXECUTABLE:${PYTHON_EXECUTABLE}"
    echo "PYTHON_INCLUDE_DIR:${PYTHON_INCLUDE_DIR}"
    echo "PYTHON_LIBRARY:${PYTHON_LIBRARY}"

    rm -rf ${BLD_DIR}-${PYTHON} &&
    mkdir -p ${BLD_DIR}-${PYTHON} &&
    cd ${BLD_DIR}-${PYTHON} &&
    cmake \
        -D "CMAKE_CXX_FLAGS:STRING=-fvisibility=hidden -fvisibility-inlines-hidden ${CFLAGS}" \
        -D "CMAKE_C_FLAGS:STRING=-fvisibility=hidden ${CXXFLAGS}" \
        -DCMAKE_MODULE_PATH:PATH=${SRC_DIR} \
        -DCMAKE_PREFIX_PATH:PATH=${BLD_DIR} \
        -DCMAKE_BUILD_TYPE:STRING=Release \
        -DSWIG_EXECUTABLE:FILEPATH=${BLD_DIR}/Swig/bin/swig \
        -DSWIG_DIR:PATH=${BLD_DIR}/Swig/ \
        -DSimpleITK_BUILD_DISTRIBUTE:BOOL=ON \
        -DSimpleITK_BUILD_STRIP:BOOL=ON \
        -DSimpleITK_PYTHON_WHEEL:BOOL=ON \
        -DSimpleITK_PYTHON_EGG:BOOL=OFF \
        -DPYTHON_EXECUTABLE:FILEPATH=${PYTHON_EXECUTABLE} \
        -DPYTHON_INCLUDE_DIR:PATH=${PYTHON_INCLUDE_DIR} \
        -DPYTHON_VIRTUALENV_SCRIPT:FILEPATH=${BLD_DIR}/virtualenv/virtualenv.py \
        ${SRC_DIR}/Wrapping/Python &&
    make &&
    make dist

}

build_simpleitk || exit 1


for PYTHON in ${PYTHON_VERSIONS}; do
    build_simpleitk_python &&
    ctest -j ${NPROC} &&
    auditwheel repair $(find ${BLD_DIR}-${PYTHON}/ -name SimpleITK*.whl) -w ${OUT_DIR}/wheelhouse/
done
