#!/usr/bin/env bash

set -x

if [ -n "$ExternalData_OBJECT_STORES" -a -d "$ExternalData_OBJECT_STORES" ] ; then
    extra_args="-v ${ExternalData_OBJECT_STORES}:/var/io/.ExternalData --env ExternalData_OBJECT_STORES=/var/io/.ExternalData"
fi

# By default use the source SimpleITK directory of this file
if [ -n "${SIMPLEITK_GIT_TAG}" ]; then
    extra_args="$extra_args --env SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG}"
else
    SRC_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &&  git rev-parse --show-toplevel )"
    extra_args="$extra_args --mount type=bind,source=${SRC_DIR},destination=/tmp/SimpleITK,readonly"
fi

proc=`uname -p`
if [ "$proc" == "x86_64" ] ; then
    DOCKERFILE=${DOCKERFILE:="Dockerfile-2014-x86_64 Dockerfile-2010-x86_64"}
elif [ "$proc" == "aarch64" ] ; then
    DOCKERFILE=${DOCKERFILE:="Dockerfile-2014-aarch64"}
fi

echo "\nDOCKERFILE"
echo $DOCKERFILE

for DF in ${DOCKERFILE}; do
    image_name="simpleitk_manylinux_$(echo "${DF}" | tr '[:upper:]' '[:lower:]')"
    docker build --pull=true --rm=true -t ${image_name} -f ${DF} .

    docker run -i --rm \
           --user "$(id -u):$(id -g)" \
           ${extra_args} \
           ${PYTHON_VERSIONS:+--env PYTHON_VERSIONS="${PYTHON_VERSIONS}"} \
           -v "$(pwd):/work/io" \
           -t ${image_name}

    # use this command to get an interactive prompt to debug behavior
    #docker run --rm -i -t --entrypoint=/bin/bash -u=root $extra_args -v $(pwd):/work/io simpleitk_manylinux_${DF}
done
