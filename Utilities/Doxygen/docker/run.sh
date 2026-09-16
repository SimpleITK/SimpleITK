#!/usr/bin/env bash



SRC_DIR="/work/SimpleITK"
BLD_DIR="/work/SimpleITK-super"

# If the SRC_DIR is not mounted, then this tag will be checked out
SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG:-"release"}

set -xe


if [ ! -d ${SRC_DIR} ]; then
    ( git clone https://github.com/SimpleITK/SimpleITK.git ${SRC_DIR} &&
          cd ${SRC_DIR} &&
          git checkout ${SIMPLEITK_GIT_TAG}
    )
fi

# Create virtual environment and install build requirements
python3 -m venv ${BLD_DIR}/venv && \
    . ${BLD_DIR}/venv/bin/activate && \
    python -m pip install --upgrade pip

# Install the [build-system] requires from pyproject.toml (jinja2, jsonschema, pyyaml, swig, ...)
python -c "import tomllib" 2>/dev/null || python -m pip install --quiet tomli
requires=$(PYPROJECT_FILE=${SRC_DIR}/pyproject.toml python -c "
import os
try:
    import tomllib as toml
except ImportError:
    import tomli as toml
with open(os.environ['PYPROJECT_FILE'], 'rb') as f:
    print('\n'.join(toml.load(f)['build-system']['requires']))
")
python -m pip install $requires

# Build SimpleITK with FetchContent for ITK
mkdir -p ${BLD_DIR} && \
    cd ${BLD_DIR} && \
    cmake -G Ninja\
          -DBUILD_DOXYGEN=ON\
          -DWRAP_DEFAULT=OFF\
          -DSimpleITK_Python_EXECUTABLE:FILEPATH=${BLD_DIR}/venv/bin/python\
          -DSimpleITK_BUILD_DISTRIBUTE:BOOL=ON\
          ${SIMPLEITK_USE_ELASTIX:+-DSimpleITK_USE_ELASTIX:BOOL=ON}\
          ${SRC_DIR} && \
    cmake --build . --target Documentation && \
    cd ${BLD_DIR}/Documentation/ && \
    tar --exclude=\*.md5 --exclude=\*.map -zcvf /SimpleITKDoxygen.tar.gz ./html && \
    tar -zcvf /SimpleITKDoxygenXML.tar.gz ./xml
