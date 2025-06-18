#!/bin/sh

set -x

export SRC_DIR="/tmp/SimpleITK"
export BLD_DIR="/tmp/SimpleITK-build"
export OUT_DIR="/work/io"

echo "BUILD_CSHARP: ${BUILD_CSHARP}"
echo "BUILD_JAVA: ${BUILD_JAVA}"

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

export PIP_NO_CACHE_DIR=1

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

    PYTHON_EXECUTABLE=/usr/local/bin/python3.12

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
        -DPython_EXECUTABLE:FILEPATH=${PYTHON_EXECUTABLE} \
        ${SRC_DIR}/SuperBuild &&
    make  &&
    find ./ -name \*.o -delete
}

function build_simpleitk_python {

    PYTHON_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    PYTHON_INCLUDE_DIR="$( find -L /opt/python/${PYTHON}/include/ -name Python.h -exec dirname {} \; )"

    echo ""
    echo "PYTHON_EXECUTABLE:${PYTHON_EXECUTABLE}"

    BLD_PY_DIR="${BLD_DIR}-${PYTHON}${USE_LIMITED_API:+-abi3}"
    rm -rf  ${BLD_PY_DIR} &&
    mkdir -p ${BLD_PY_DIR} &&
    cd ${BLD_PY_DIR} &&
    cmake \
        -D "CMAKE_CXX_FLAGS:STRING=-fvisibility=hidden -fvisibility-inlines-hidden ${CFLAGS}" \
        -D "CMAKE_C_FLAGS:STRING=-fvisibility=hidden ${CXXFLAGS}" \
        -DCMAKE_MODULE_PATH:PATH=${SRC_DIR} \
        -DCMAKE_PREFIX_PATH:PATH=${BLD_DIR} \
        -DCMAKE_BUILD_TYPE:STRING=Release \
        -DSWIG_EXECUTABLE:FILEPATH=${BLD_DIR}/Swig/bin/swig \
        -DSWIG_DIR:PATH=${BLD_DIR}/Swig/ \
        -DSimpleITK_PYTHON_USE_LIMITED_API:BOOL=${USE_LIMITED_API:-OFF} \
        -DSimpleITK_BUILD_DISTRIBUTE:BOOL=ON \
        -DSimpleITK_BUILD_STRIP:BOOL=ON \
        -DSimpleITK_PYTHON_WHEEL:BOOL=ON \
        -DSimpleITK_PYTHON_EGG:BOOL=OFF \
        -DPython_EXECUTABLE:FILEPATH=${PYTHON_EXECUTABLE} \
        -DPython_INCLUDE_DIR:PATH=${PYTHON_INCLUDE_DIR} \
        ${SRC_DIR}/Wrapping/Python &&
    make &&
    make dist

}

build_simpleitk || exit 1


if [[ ! -z ${BUILD_CSHARP:+x} && "${BUILD_CSHARP}" -ne 0 ]]; then
    mkdir ${BLD_DIR}-csharp &&
        cd ${BLD_DIR}-csharp &&
        cmake  \
            -D "CMAKE_CXX_FLAGS:STRING=-fvisibility=hidden -fvisibility-inlines-hidden ${CFLAGS}" \
            -D "CMAKE_C_FLAGS:STRING=-fvisibility=hidden ${CXXFLAGS}" \
            -DCMAKE_MODULE_PATH:PATH=${SRC_DIR} \
            -DCMAKE_PREFIX_PATH:PATH=${BLD_DIR} \
            -DCMAKE_BUILD_TYPE:STRING=Release \
            -DSWIG_EXECUTABLE:FILEPATH=${BLD_DIR}/Swig/bin/swig \
            -DSWIG_DIR:PATH=${BLD_DIR}/Swig/ \
            -DSimpleITK_CSHARP_ARCH:STRING="linux_$(arch)" \
            -DSimpleITK_BUILD_STRIP:BOOL=ON \
            ${SRC_DIR}/Wrapping/CSharp &&
        cmake --build "${BLD_DIR}-csharp" --target dist &&
        find "${BLD_DIR}-csharp/dist" -name "SimpleITK*.zip" -exec cp -v {} "${OUT_DIR}" \;
fi

if [[ ! -z ${BUILD_JAVA:+x} && "${BUILD_JAVA}" -ne 0 ]]; then
    mkdir ${BLD_DIR}-java &&
        cd ${BLD_DIR}-java &&
        cmake  \
            -D "CMAKE_CXX_FLAGS:STRING=-fvisibility=hidden -fvisibility-inlines-hidden ${CFLAGS}" \
            -D "CMAKE_C_FLAGS:STRING=-fvisibility=hidden ${CXXFLAGS}" \
            -DCMAKE_MODULE_PATH:PATH=${SRC_DIR} \
            -DCMAKE_PREFIX_PATH:PATH=${BLD_DIR} \
            -DCMAKE_BUILD_TYPE:STRING=Release \
            -DSWIG_EXECUTABLE:FILEPATH=${BLD_DIR}/Swig/bin/swig \
            -DSWIG_DIR:PATH=${BLD_DIR}/Swig/ \
            -DSimpleITK_JAVA_ARCH:STRING="linux_$(arch)" \
            -DSimpleITK_BUILD_STRIP:BOOL=ON \
            ${SRC_DIR}/Wrapping/Java &&
        cmake --build "${BLD_DIR}-java" --target dist &&
        find "${BLD_DIR}-java/dist" -name "SimpleITK*.zip" -exec cp -v {} "${OUT_DIR}" \;
fi

if [[ ! -z ${BUILD_PYTHON_LIMITED_API:+x} && "${BUILD_PYTHON_LIMITED_API}" -ne 0 ]]; then
    USE_LIMITED_API=ON
    PYTHON=cp311-cp311
    PYTHON_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    PLATFORM=$(${PYTHON_EXECUTABLE} -c "import distutils.util; print(distutils.util.get_platform())")
    build_simpleitk_python &&
       ( auditwheel repair $(find ${BLD_DIR}-${PYTHON}${USE_LIMITED_API:+-abi3}/ -name *.whl) -w ${OUT_DIR}/wheelhouse/;
         ctest -j ${NPROC} -LE UNSTABLE | tee ${OUT_DIR}/ctest_${PLATFORM}_${PYTHON}${USE_LIMITED_API:+-abi3}.log &&
         rm -rf ${BLD_DIR}-${PYTHON}${USE_LIMITED_API:+-abi3} )
    unset USE_LIMITED_API
fi



for PYTHON in ${PYTHON_VERSIONS}; do
    PYTHON_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    PLATFORM=$(${PYTHON_EXECUTABLE} -c "import distutils.util; print(distutils.util.get_platform())")
    build_simpleitk_python &&
        ( auditwheel repair $(find ${BLD_DIR}-${PYTHON}/ -name *.whl) -w ${OUT_DIR}/wheelhouse/;
          ctest -j ${NPROC} -LE UNSTABLE | tee ${OUT_DIR}/ctest_${PLATFORM}_${PYTHON}.log &&
          rm -rf ${BLD_DIR}-${PYTHON} )
done
