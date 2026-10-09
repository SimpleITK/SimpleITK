#-----------------------------------------------------------------------------
# Shared Elastix Git repository and tag options (SimpleITK naming)
# This file centralizes the Elastix repository and tag CMake cache variables
# to avoid duplication between FetchContent and ExternalProject driven builds.

set(_elastix_repo "${SimpleITK_GIT_PROTOCOL}://github.com/SuperElastix/elastix")

set(
  ELASTIX_GIT_REPOSITORY
  "${_elastix_repo}"
  CACHE STRING
  "URL of Elastix Git repository"
)
mark_as_advanced(ELASTIX_GIT_REPOSITORY)

set(_DEFAULT_ELASTIX_GIT_TAG "0a244f63683af84728310101d1ab49002962698d") # Sep 24, 2026
set(
  ELASTIX_GIT_TAG
  "${_DEFAULT_ELASTIX_GIT_TAG}"
  CACHE STRING
  "Tag in Elastix git repo"
)
mark_as_advanced(ELASTIX_GIT_TAG)
