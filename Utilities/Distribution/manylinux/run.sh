#!/usr/bin/env bash



if [ -n "$ExternalData_OBJECT_STORES" -a -d "$ExternalData_OBJECT_STORES" ] ; then
    extra_args="-v ${ExternalData_OBJECT_STORES}:/var/io/.ExternalData --env ExternalData_OBJECT_STORES=/var/io/.ExternalData"
fi

# By default use the source SimpleITK directory of this file
if [ -n "${SIMPLEITK_GIT_TAG}" ]; then
    extra_args="$extra_args --env SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG}"
else
    SRC_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
    SRC_DIR="${SRC_DIR}/../../../"
    extra_args="$extra_args --mount type=bind,source=${SRC_DIR},destination=/tmp/SimpleITK,readonly"
fi

ARCHS=${ARCH:-"i686 x86_64"}
for ARCH in ${ARCHS}; do
    docker build --pull=true --rm=true -t simpleitk_manylinux_${ARCH} -f Dockerfile-${ARCH} .

    docker run --rm \
           --user "$(id -u):$(id -g)" \
           ${extra_args} \
           ${PYTHON_VERSIONS:+--env PYTHON_VERSIONS="${PYTHON_VERSIONS}"} \
           -v "$(pwd):/work/io" \
           -t simpleitk_manylinux_${ARCH}

    # use this command to get an interactive prompt to debug behavior
    #docker run --rm -i -t --entrypoint=/bin/bash -u=root $extra_args -v $(pwd):/work/io simpleitk_manylinux_${ARCH}
done
