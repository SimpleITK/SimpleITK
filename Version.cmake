#
# ONLY MODIFY TO CHANGE VERSION
#
# The number of commits since last this file has changed is used to
# define "dev" and "post", modification of this file will reset that
# version.
#

# Version info

set(SimpleITK_VERSION_MAJOR 1)
set(SimpleITK_VERSION_MINOR 0)
set(SimpleITK_VERSION_PATCH 1)
#set(SimpleITK_VERSION_TWEAK "")


include(sitkSourceVersion)

# pre-release codes are defined based on suffix of most recent tags.

# a[N]+<b[N]+<c[N]+=rc[N]+
if(NOT ${_GIT_VERSION_RC} STREQUAL "" )
  set(SimpleITK_VERSION_RC "${_GIT_VERSION_RC}")
endif()


# The hash is the current git sha1 hash tag of the HEAD.
set(SimpleITK_VERSION_HASH "${_GIT_VERSION_HASH}")

# DEV or POST is set to the number of commits since this file has been
# changed. If the MAJOR.MINOR.[PATCH[.TWEAK]] matches "closest"
# version tag then its consider in the release branch and POST is set
# while DEV is undefined, otherwise we are considered under
# development and DEV is set and POST is undefined.
if(DEFINED _GIT_VERSION_POST)
  set(SimpleITK_VERSION_POST "${_GIT_VERSION_POST}")
elseif(DEFINED _GIT_VERSION_DEV)
  set(SimpleITK_VERSION_DEV "${_GIT_VERSION_DEV}")
endif()

