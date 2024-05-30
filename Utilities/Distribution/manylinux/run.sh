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


# a function to check if a variable is set then append it to the extra_args
function check_var_append_to_extra_args {
  if [ -n "$1" ]; then
    echo "Forwarding $1 to docker container"
    extra_args="$extra_args --env '$1'"
  fi
}

# a bash array of variables to check and append to extra_args
check_vars=( "BUILD_CSHARP" "BUILD_JAVA" "PYTHON_VERSIONS" "BUILD_PYTHON_LIMITED_API")
for var in "${check_vars[@]}"; do
    check_var_append_to_extra_args $var
done

echo "extra_args: ${extra_args}"


for DF in ${DOCKERFILE}; do
    image_name="simpleitk_manylinux_$(echo "${DF}" | tr '[:upper:]' '[:lower:]')"
    docker build --pull=true --rm=true -t ${image_name} -f ${DF} .

    docker run -i --rm \
           --user "$(id -u):$(id -g)" \
           ${extra_args} \
           -v "$(pwd):/work/io" \
           -t ${image_name}

    # use this command to get an interactive prompt to debug behavior
    #docker run --rm -i -t --entrypoint=/bin/bash -u=root $extra_args -v $(pwd):/work/io simpleitk_manylinux_${DF}
done
