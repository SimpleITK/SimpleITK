#!/usr/bin/env bash

set -eux
umask 000
groupadd -o -g $_GROUPID $_USER
useradd -m -o -g $_GROUPID $_USER -u $_USERID
unset _GROUPID _USERID
su $_USER $@
