#!/bin/sh

set -x

export SRC_DIR="${SIMPLEITK_SRC_DIR:-"/tmp/SimpleITK"}"
export BLD_DIR="/tmp/SimpleITK-build"
export OUT_DIR="/work/io"

echo "BUILD_CSHARP: ${BUILD_CSHARP}"
echo "BUILD_JAVA: ${BUILD_JAVA}"

SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG:-v1.1rc1}

# Remove Python 2 and pure Python builds
PYTHON_VERSIONS=${PYTHON_VERSIONS-$(ls /opt/python | sed -e 's/cp2[^ ]\+ \?//g' -e 's/pp3[^ ]\+ \?//g')}

NPROC=$(grep -c processor /proc/cpuinfo)
export MAKEFLAGS="-j ${NPROC}"

# if ExternalData_OBJECT_STORES is not set by the driver script then
# set it here to enable  reuse of downloaded files between python
# builds.
export ExternalData_OBJECT_STORES=${ExternalData_OBJECT_STORES:-/tmp/.ExternalData}
mkdir -p ${ExternalData_OBJECT_STORES}

export PIP_NO_CACHE_DIR=1

export HOME=/tmp

# Create a Python virtual environment for the FetchContent build system.
# This provides jinja2/jsonschema/pyyaml (template code generation) and
# swig (replaces the SuperBuild-compiled SWIG). Use cp312 to match the
# Python version chosen by the SuperBuild's uv-based venv setup.
BUILD_VENV_DIR="/tmp/sitk-build-venv"
/opt/python/cp312-cp312/bin/python -m venv "${BUILD_VENV_DIR}"
"${BUILD_VENV_DIR}/bin/pip" install \
    'jinja2~=3.1' \
    'jsonschema~=4.24' \
    'pyyaml~=6.0' \
    'swig~=4.4.0'
export PATH="${BUILD_VENV_DIR}/bin:${PATH}"
SIMPLEITK_BUILD_PYTHON="${BUILD_VENV_DIR}/bin/python"

build_simpleitk() {

    if [ ! -d ${SRC_DIR} ]; then
        ( git clone https://github.com/SimpleITK/SimpleITK.git ${SRC_DIR} &&
              cd ${SRC_DIR} &&
              git checkout ${SIMPLEITK_GIT_TAG}
        )
    fi

    # Pre-populate the writable ExternalData object store from the source tree.
    # sitkExternalData.cmake appends ${SRC_DIR}/.ExternalData to the search list,
    # but the source is mounted read-only so cmake cannot touch_nocreate the symlink
    # targets there. Copying to the writable store ensures cmake uses it first.
    if [ -d "${SRC_DIR}/.ExternalData" ]; then
        cp -rn "${SRC_DIR}/.ExternalData/." "${ExternalData_OBJECT_STORES}/"
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
        -DSimpleITK_USE_SYSTEM_SWIG:BOOL=ON \
        -DSimpleITK_Python_EXECUTABLE:FILEPATH=${SIMPLEITK_BUILD_PYTHON} \
        -D "CMAKE_CXX_FLAGS:STRING=-fvisibility=hidden -fvisibility-inlines-hidden" \
        -D "CMAKE_C_FLAGS:STRING=-fvisibility=hidden" \
        -DITK_C_OPTIMIZATION_FLAGS:STRING="" \
        -DITK_CXX_OPTIMIZATION_FLAGS:STRING="" \
        ${SIMPLEITK_USE_ELASTIX:+-DSimpleITK_USE_ELASTIX:BOOL=ON} \
        ${SRC_DIR} &&
    make  &&
    find ./ -name \*.o -delete
}

build_simpleitk_python() {

    Python_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    Python_INCLUDE_DIR="$( find -L /opt/python/${PYTHON}/include/ -name Python.h -exec dirname {} \; )"

    echo ""
    echo "Python_EXECUTABLE:${Python_EXECUTABLE}"

    BLD_PY_DIR="${BLD_DIR}-${PYTHON}${USE_LIMITED_API:+-abi3}"
    rm -rf  ${BLD_PY_DIR} &&
    mkdir -p ${BLD_PY_DIR} &&
    cd ${BLD_PY_DIR} &&
    cmake \
        -D "CMAKE_CXX_FLAGS:STRING=-fvisibility=hidden -fvisibility-inlines-hidden ${CXXFLAGS}" \
        -D "CMAKE_C_FLAGS:STRING=-fvisibility=hidden ${CFLAGS}" \
        -DCMAKE_MODULE_PATH:PATH=${SRC_DIR} \
        -DCMAKE_PREFIX_PATH:PATH=${BLD_DIR} \
        -DITK_DIR:PATH=${BLD_DIR}/_deps/itk-build \
        ${SIMPLEITK_USE_ELASTIX:+-DElastix_DIR:PATH=${BLD_DIR}/_deps/elastix-build} \
        -DCMAKE_BUILD_TYPE:STRING=Release \
        -DBUILD_EXAMPLES:BOOL=OFF \
        -DSimpleITK_PYTHON_USE_LIMITED_API:BOOL=${USE_LIMITED_API:-OFF} \
        -DSimpleITK_BUILD_DISTRIBUTE:BOOL=ON \
        -DSimpleITK_BUILD_STRIP:BOOL=ON \
        -DSimpleITK_PYTHON_WHEEL:BOOL=ON \
        -DSimpleITK_Python_EXECUTABLE:FILEPATH=${SIMPLEITK_BUILD_PYTHON} \
        -DPython_EXECUTABLE:FILEPATH=${Python_EXECUTABLE} \
        -DPython_INCLUDE_DIR:PATH=${Python_INCLUDE_DIR} \
        ${SRC_DIR}/Wrapping/Python &&
    make &&
    make dist

}

build_simpleitk || exit 1

if [[ ! -z ${BUILD_CSHARP:+x} && "${BUILD_CSHARP}" -ne 0 ]]; then
    mkdir ${BLD_DIR}-csharp &&
        cd ${BLD_DIR}-csharp &&
        cmake  \
            -D "CMAKE_CXX_FLAGS:STRING=-fvisibility=hidden -fvisibility-inlines-hidden ${CXXFLAGS}" \
            -D "CMAKE_C_FLAGS:STRING=-fvisibility=hidden ${CFLAGS}" \
            -DCMAKE_MODULE_PATH:PATH=${SRC_DIR} \
            -DCMAKE_PREFIX_PATH:PATH=${BLD_DIR} \
            -DITK_DIR:PATH=${BLD_DIR}/_deps/itk-build \
            ${SIMPLEITK_USE_ELASTIX:+-DElastix_DIR:PATH=${BLD_DIR}/_deps/elastix-build} \
            -DCMAKE_BUILD_TYPE:STRING=Release \
            -DBUILD_EXAMPLES:BOOL=OFF \
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
            -DITK_DIR:PATH=${BLD_DIR}/_deps/itk-build \
            ${SIMPLEITK_USE_ELASTIX:+-DElastix_DIR:PATH=${BLD_DIR}/_deps/elastix-build} \
            -DCMAKE_BUILD_TYPE:STRING=Release \
            -DBUILD_EXAMPLES:BOOL=OFF \
            -DSimpleITK_JAVA_ARCH:STRING="linux_$(arch)" \
            -DSimpleITK_BUILD_STRIP:BOOL=ON \
            ${SRC_DIR}/Wrapping/Java &&
        cmake --build "${BLD_DIR}-java" --target dist &&
        find "${BLD_DIR}-java/dist" -name "SimpleITK*.zip" -exec cp -v {} "${OUT_DIR}" \;
fi

if [[ ! -z ${BUILD_PYTHON_LIMITED_API:+x} && "${BUILD_PYTHON_LIMITED_API}" -ne 0 ]]; then
    USE_LIMITED_API=ON
    PYTHON=cp311-cp311
    Python_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    PLATFORM=$(${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_platform())")
    build_simpleitk_python &&
       ( auditwheel repair $(find ${BLD_DIR}-${PYTHON}${USE_LIMITED_API:+-abi3}/ -name *.whl) -w ${OUT_DIR}/wheelhouse/;
         ctest -j ${NPROC} -LE UNSTABLE | tee ${OUT_DIR}/ctest_${PLATFORM}_${PYTHON}${USE_LIMITED_API:+-abi3}.log &&
         rm -rf ${BLD_DIR}-${PYTHON}${USE_LIMITED_API:+-abi3} )
    unset USE_LIMITED_API
fi



for PYTHON in ${PYTHON_VERSIONS}; do
    Python_EXECUTABLE=/opt/python/${PYTHON}/bin/python
    PLATFORM=$(${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_platform())")
    build_simpleitk_python &&
        ( auditwheel repair $(find ${BLD_DIR}-${PYTHON}/ -name *.whl) -w ${OUT_DIR}/wheelhouse/;
          ctest -j ${NPROC} -LE UNSTABLE | tee ${OUT_DIR}/ctest_${PLATFORM}_${PYTHON}.log &&
          rm -rf ${BLD_DIR}-${PYTHON} )
done
