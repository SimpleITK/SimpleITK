#!/usr/bin/env bash

ANACONDA_ROOT=${ANACONDA_ROOT:-${HOME}/anaconda}
CONDA_RECIPES=${CONDA_RECIPES:-${HOME}/src/conda-recipes}

(${ANACONDA_ROOT}/bin/conda update conda -y &&
    ${ANACONDA_ROOT}/bin/conda update -n root conda-build -y ) || exit 1

cd ${CONDA_RECIPES} && git fetch origin && git checkout origin/build


( ${ANACONDA_ROOT}/bin/conda build simpleitk &&
    CONDA_PY=34 ${ANACONDA_ROOT}/bin/conda build simpleitk &&
     CONDA_PY=35 ${ANACONDA_ROOT}/bin/conda build simpleitk) || exit 1

find ${ANACONDA_ROOT}/conda-bld -name simpleitk.\*tar.bz2

#${ANACONDA_ROOT}/bin/binstar upload --user simpleitk --channel dev /home/blowekamp/anaconda/conda-bld/linux-32/simpleitk-0.9.0b01-py34_0.tar.bz2
