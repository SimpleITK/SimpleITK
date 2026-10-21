#!/bin/sh

set -x

export SRC_DIR="${SIMPLEITK_SRC_DIR:-"/tmp/SimpleITK"}"
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

export HOME=/tmp

build_simpleitk() {

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
        ${SIMPLEITK_USE_ELASTIX:+-DSimpleITK_USE_ELASTIX:BOOL=ON} \
        ${SRC_DIR}/SuperBuild &&
    make  &&
    find ./ -name \*.o -delete
}

build_simpleitk_python() {

    Python_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    Python_INCLUDE_DIR="$( find -L /opt/python/${PYTHON}/include/ -name Python.h -exec dirname {} \; )"

    echo ""
    echo "Python_EXECUTABLE:${Python_EXECUTABLE}"

    BLD_PY_DIR="${BLD_DIR}-${PYTHON}${ABI_SUFFIX:-}"
    rm -rf  ${BLD_PY_DIR} &&
    mkdir -p ${BLD_PY_DIR} &&
    cd ${BLD_PY_DIR} &&
    cmake \
        -D "CMAKE_CXX_FLAGS:STRING=-fvisibility=hidden -fvisibility-inlines-hidden ${CXXFLAGS}" \
        -D "CMAKE_C_FLAGS:STRING=-fvisibility=hidden ${CFLAGS}" \
        -DCMAKE_MODULE_PATH:PATH=${SRC_DIR} \
        -DCMAKE_PREFIX_PATH:PATH=${BLD_DIR} \
        -DCMAKE_BUILD_TYPE:STRING=Release \
        -DSWIG_EXECUTABLE:FILEPATH=${BLD_DIR}/Swig/bin/swig \
        -DSWIG_DIR:PATH=${BLD_DIR}/Swig/ \
        -DSimpleITK_PYTHON_USE_LIMITED_API:BOOL=${USE_LIMITED_API:-OFF} \
        -DSimpleITK_PYTHON_USE_ABI3T:BOOL=${USE_ABI3T:-OFF} \
        -DSimpleITK_BUILD_DISTRIBUTE:BOOL=ON \
        -DSimpleITK_BUILD_STRIP:BOOL=ON \
        -DSimpleITK_PYTHON_WHEEL:BOOL=ON \
        -DSimpleITK_Python_EXECUTABLE:FILEPATH=${SimpleITK_Python_EXECUTABLE} \
        -DPython_EXECUTABLE:FILEPATH=${Python_EXECUTABLE} \
        -DPython_INCLUDE_DIR:PATH=${Python_INCLUDE_DIR} \
        ${SRC_DIR}/Wrapping/Python &&
    make &&
    make dist

}

build_simpleitk || exit 1

SimpleITK_Python_EXECUTABLE="${BLD_DIR}/venv/bin/python"

if [[ ! -z ${BUILD_CSHARP:+x} && "${BUILD_CSHARP}" -ne 0 ]]; then
    mkdir ${BLD_DIR}-csharp &&
        cd ${BLD_DIR}-csharp &&
        cmake  \
            -D "CMAKE_CXX_FLAGS:STRING=-fvisibility=hidden -fvisibility-inlines-hidden ${CXXFLAGS}" \
            -D "CMAKE_C_FLAGS:STRING=-fvisibility=hidden ${CFLAGS}" \
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
            -D "CMAKE_CXX_FLAGS:STRING=-fvisibility=hidden -fvisibility-inlines-hidden ${CXXFLAGS}" \
            -D "CMAKE_C_FLAGS:STRING=-fvisibility=hidden ${CFLAGS}" \
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
    # Build the classic abi3 wheel using the minimum supported Stable ABI
    # version (Python 3.11). A single abi3 wheel built this way works on
    # all supported GIL-enabled Python versions from 3.11 upward, so we
    # only need to build it once (matches the mac/Windows packaging path).
    #
    # Build the abi3t wheel separately, using the free-threaded Python
    # 3.15t interpreter. This requires both SimpleITK_PYTHON_USE_LIMITED_API
    # and SimpleITK_PYTHON_USE_ABI3T so scikit-build-core's "cp315.cp315t"
    # py-api override applies, producing a wheel with the combined
    # abi3.abi3t tag that covers both GIL-enabled and free-threaded
    # Python 3.15+.

    USE_LIMITED_API=ON

    # Build abi3 with the minimum supported Python 3.11
    PYTHON=cp311-cp311
    ABI_SUFFIX=-abi3
    Python_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    if [[ -x "${Python_EXECUTABLE}" ]]; then
        PLATFORM=$(${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_platform())")
        build_simpleitk_python &&
           ( auditwheel repair $(find ${BLD_DIR}-${PYTHON}${ABI_SUFFIX}/ -name *.whl) -w ${OUT_DIR}/wheelhouse/;
             ctest -j ${NPROC} -LE UNSTABLE | tee ${OUT_DIR}/ctest_${PLATFORM}_${PYTHON}${ABI_SUFFIX}.log &&
             rm -rf ${BLD_DIR}-${PYTHON}${ABI_SUFFIX} )
    fi

    # Build abi3t with free-threaded Python 3.15t
    PYTHON=cp315-cp315t
    USE_ABI3T=ON
    ABI_SUFFIX=-abi3t
    Python_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    if [[ -x "${Python_EXECUTABLE}" ]]; then
        PLATFORM=$(${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_platform())")
        build_simpleitk_python &&
           ( auditwheel repair $(find ${BLD_DIR}-${PYTHON}${ABI_SUFFIX}/ -name *.whl) -w ${OUT_DIR}/wheelhouse/;
             ctest -j ${NPROC} -LE UNSTABLE | tee ${OUT_DIR}/ctest_${PLATFORM}_${PYTHON}${ABI_SUFFIX}.log &&
             rm -rf ${BLD_DIR}-${PYTHON}${ABI_SUFFIX} )
    fi

    unset USE_LIMITED_API USE_ABI3T ABI_SUFFIX
fi



for PYTHON in ${PYTHON_VERSIONS}; do
    # Skip abi3/abi3t versions as they are handled separately in the BUILD_PYTHON_LIMITED_API block
    case "${PYTHON}" in
        cp311-cp311|cp315-cp315t)
            echo "Skipping ${PYTHON} (handled in BUILD_PYTHON_LIMITED_API block)"
            continue
            ;;
    esac

    Python_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    if [[ -x "${Python_EXECUTABLE}" ]]; then
        PLATFORM=$(${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_platform())")
        build_simpleitk_python &&
            ( auditwheel repair $(find ${BLD_DIR}-${PYTHON}/ -name *.whl) -w ${OUT_DIR}/wheelhouse/;
              ctest -j ${NPROC} -LE UNSTABLE | tee ${OUT_DIR}/ctest_${PLATFORM}_${PYTHON}.log &&
              rm -rf ${BLD_DIR}-${PYTHON} )
    fi
done
