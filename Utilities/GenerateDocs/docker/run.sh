#!/bin/sh

#
# Genrates a SimpleITK Doxygen tarball for a tag
#
# Example usage: $ SIMPLEITK_GIT_TAG=v1.2.0 run.sh
#
# This script build build a docker image, then run the SimpleITK build step inorder to generate the Doxygen. By mounting the current directory onto the container a Doxygen tar-ball will be produced.


if [ -n "$ExternalData_OBJECT_STORES" -a -d "$ExternalData_OBJECT_STORES" ] ; then
    extra_args="-v ${ExternalData_OBJECT_STORES}:/var/io/.ExternalData -e ExternalData_OBJECT_STORES=/var/io/.ExternalData"
fi

if [ ! -z "${SIMPLEITK_GIT_TAG}" ] ; then
    extra_args="${extra_args} -e SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG}"
fi


echo " extra_args: "  ${extra_args}

DOCKER_TAG=simpleitk_doxygen

SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG:-v1.2.0}

docker build --pull=true --rm=true -t ${DOCKER_TAG} -f Dockerfile .

docker run --rm -t -e SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG} -e _USER=$(id -un)  -e _USERID=$(id -u)  -e_GROUPID=$(id -g) $extra_args -v $(pwd):/work/io  ${DOCKER_TAG}
