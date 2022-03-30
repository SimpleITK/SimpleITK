#!/bin/sh

set -x

export SRC_DIR="/tmp/SimpleITK"
export BLD_DIR="/tmp/SimpleITK-build"
export OUT_DIR="/work/io"

SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG:-v1.1rc1}

# Remove Python 2 and pure Python builds
PYTHON_VERSIONS=${PYTHON_VERSIONS:-$(ls /opt/python | sed -e 's/cp2[^ ]\+ \?//g' -e 's/pp3[^ ]\+ \?//g')}

NPROC=$(grep -c processor /proc/cpuinfo)
export MAKEFLAGS="-j ${NPROC}"

# if ExternalData_OBJECT_STORES is not set by the driver script then
# set it here to enable  reuse of downloaded files between python
# builds.
export ExternalData_OBJECT_STORES=${ExternalData_OBJECT_STORES:-/tmp/.ExternalData}
mkdir -p ${ExternalData_OBJECT_STORES}


export PYTHONUSERBASE=${PYTHONUSERBASE:-/tmp/.pylocal}
mkdir -p ${PYTHONUSERBASE}
export PATH=${PATH}:/tmp/.pylocal/bin

function build_simpleitk {


    if [ ! -d ${SRC_DIR} ]; then
        ( git clone https://github.com/SimpleITK/SimpleITK.git ${SRC_DIR} &&
              cd ${SRC_DIR} &&
              git checkout ${SIMPLEITK_GIT_TAG}
        )
    fi

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
        -DITK_GIT_REPOSITORY:STRING="https://github.com/InsightSoftwareConsortium/ITK.git" \
        -DITK_C_OPTIMIZATION_FLAGS:STRING="" \
        -DITK_CXX_OPTIMIZATION_FLAGS:STRING="" \
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
        ${SRC_DIR}/Wrapping/Python &&
    make &&
    make dist

}

build_simpleitk || exit 1



for PYTHON in ${PYTHON_VERSIONS}; do
    PYTHON_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    PLATFORM=$(${PYTHON_EXECUTABLE} -c "import distutils.util; print(distutils.util.get_platform())")
    build_simpleitk_python &&
        ( auditwheel repair $(find ${BLD_DIR}-${PYTHON}/ -name SimpleITK*.whl) -w ${OUT_DIR}/wheelhouse/;
          ctest -j ${NPROC} -LE UNSTABLE | tee ${OUT_DIR}/ctest_${PLATFORM}_${PYTHON}.log &&
          rm -rf ${BLD_DIR}-${PYTHON} )
done
