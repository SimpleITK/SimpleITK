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

if [ -f ${SRC_DIR}/.github/workflows/requirements-build.txt ]; then
   python -m pip install -r ${SRC_DIR}/.github/workflows/requirements-build.txt jinja2~=3.1 jsonschema~=4.24 pyyaml~=6.0 swig~=4.4.0
fi

# Build SimpleITK with FetchContent for ITK
mkdir -p ${BLD_DIR} && \
    cd ${BLD_DIR} && \
    cmake -G Ninja\
          -DBUILD_DOXYGEN=ON\
          -DWRAP_DEFAULT=OFF\
          -DSimpleITK_Python_EXECUTABLE:FILEPATH=${BLD_DIR}/venv/bin/python\
          -DSimpleITK_BUILD_DISTRIBUTE:BOOL=ON\
          ${SRC_DIR} && \
    cmake --build . --target Documentation && \
    cd ${BLD_DIR}/Documentation/ && \
    tar --exclude=\*.md5 --exclude=\*.map -zcvf /SimpleITKDoxygen.tar.gz ./html && \
    tar -zcvf /SimpleITKDoxygenXML.tar.gz ./xml
