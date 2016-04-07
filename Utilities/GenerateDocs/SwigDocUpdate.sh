#!/usr/bin/env bash


# Updates Swig .i documentation files from SimpleITK's Doxygen XML.
#
# To generate the input to this script, the SimpleITK Doxygen must be built.
#
# Configuration for directories need to be manually done in the
# config_vars.sh file. The ITK Doxygen XML will automatically be
# downloaded if needed.
#
# Usage: SWigDocUpdate.sh
#

die() {
    echo "$@" 1>&2
    exit 1
}

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Load configuration variable from file
. ${DIR}/config_vars.sh || die 'Unable to find local \"config_vars.sh\" configuration file.'


[ -e ${SITK_BUILD_DIR}/Documentation/xml/sitkImage_8h.xml ] ||
   die "Uable to find SimpleITK Doxygen XML! SimpleITK Doxygen needs to be generated with the Documentation target!"

${PYTHON_EXECUTABLE} doxyall.py ${SITK_BUILD_DIR}/Documentation/xml/ ${SIMPLEITK}/Wrapping/Python/PythonDocstrings.i
${PYTHON_EXECUTABLE} doxyall.py -j ${SITK_BUILD_DIR}/Documentation/xml/ ${SIMPLEITK}/Wrapping/Java/JavaDoc.i

if [ ! -d ${SIMPLEITK}/Wrapping/R/Packaging/SimpleITK/man/ ] ; then
    mkdir -p ${SIMPLEITK}/Wrapping/R/Packaging/SimpleITK/man/
fi
${PYTHON_EXECUTABLE} doxyall.py -r ${SITK_BUILD_DIR}/Documentation/xml/ ${SIMPLEITK}/Wrapping/R/Packaging/SimpleITK/man/
