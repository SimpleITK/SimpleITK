#!/usr/bin/env bash

SITK_BUILD_DIR="/dev/shm/SimpleITK/SimpleITK-build"

Doxygen/doxyall.py ${SITK_BUILD_DIR}/Documentation/xml/ ../Wrapping/Python/PythonDocstrings.i
Doxygen/doxyall.py -j ${SITK_BUILD_DIR}/Documentation/xml/ ../Wrapping/Java/JavaDoc.i
