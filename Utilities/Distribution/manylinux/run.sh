#!/bin/sh

if [ -n "$ExternalData_OBJECT_STORES" -a -d "$ExternalData_OBJECT_STORES" ] ; then
    extra_args="-v ${ExternalData_OBJECT_STORES}:/var/io/.ExternalData -e ExternalData_OBJECT_STORES=/var/io/.ExternalData"
fi

if [ ! -z "${SIMPLEITK_GIT_TAG}" ] ; then
    extra_args="${extra_args} -e SIMPLEITK_GIT_TAG=${SIMPLEITK_GIT_TAG}"
fi

# example versions: "cp27-cp27m cp27-cp27mu cp36-cp36m"
if [ ! -z "${PYTHON_VERSIONS}" ] ; then
    extra_args="${extra_args} -e PYTHON_VERSIONS=${PYTHON_VERSIONS}"
fi

for ARCH in i686 x86_64; do
    docker build --pull=true  --rm=true -t simpleitk_manylinux_${ARCH} -f Dockerfile-${ARCH} .

    docker run --storage-opt size=150G --rm -e _USER=$(id -un)  -e _USERID=$(id -u)  -e_GROUPID=$(id -g) $extra_args -v $(pwd):/work/io -t simpleitk_manylinux_${ARCH}

    # use this command to get an interactive prompt to debug behavior
    #docker run --rm -i -t --entrypoint=/bin/bash -u=root $extra_args -v $(pwd):/var/io simpleitk_manylinux_${ARCH}
done
