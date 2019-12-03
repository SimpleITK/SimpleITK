#!/bin/sh

if [ -n "$ExternalData_OBJECT_STORES" -a -d "$ExternalData_OBJECT_STORES" ] ; then
    extra_args="-v ${ExternalData_OBJECT_STORES}:/var/io/.ExternalData --env ExternalData_OBJECT_STORES=/var/io/.ExternalData"
fi

ARCHS=${ARCH:-"i686 x86_64"}

for ARCH in ${ARCHS}; do
    docker build --pull=true --rm=true -t simpleitk_manylinux_${ARCH} -f Dockerfile-${ARCH} .

    docker run --rm \
           --env _USER=$(id -un) \
           --env "_USERID=$(id -u)" \
           --env "_GROUPID=$(id -g)" \
           ${extra_args} \
           ${SIMPLEITK_GIT_TAG:+--env SIMPLEITK_GIT_TAG="${SIMPLEITK_GIT_TAG}"} \
           ${PYTHON_VERSIONS:+--env PYTHON_VERSIONS="${PYTHON_VERSIONS}"} \
           -v "$(pwd):/work/io" \
           -t simpleitk_manylinux_${ARCH}

    # use this command to get an interactive prompt to debug behavior
    #docker run --rm -i -t --entrypoint=/bin/bash -u=root $extra_args -v $(pwd):/work/io simpleitk_manylinux_${ARCH}
done
