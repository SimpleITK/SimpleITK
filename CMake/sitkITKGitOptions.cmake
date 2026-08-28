#-----------------------------------------------------------------------------
# Shared ITK Git repository and tag options (SimpleITK naming)
# This file centralizes the ITK repository and tag CMake cache variables
# to avoid duplication between FetchContent and ExternalProject driven builds.

set(
  _itk_repo
  "${SimpleITK_GIT_PROTOCOL}://github.com/InsightSoftwareConsortium/ITK.git"
)

set(ITK_GIT_REPOSITORY "${_itk_repo}" CACHE STRING "URL of ITK Git repository")
mark_as_advanced(ITK_GIT_REPOSITORY)

if(COMMAND sitk_legacy_naming)
  sitk_legacy_naming(ITK_GIT_REPOSITORY ITK_REPOSITORY)
endif()

set(_DEFAULT_ITK_GIT_TAG "841f4b66d37804907cef5758d80bde19aa08d104") # main on 2026-07-10, includes ITK#6580 fix for FastApproximateRankImageFilter
set(ITK_GIT_TAG "${_DEFAULT_ITK_GIT_TAG}" CACHE STRING "Tag in ITK git repo")
mark_as_advanced(ITK_GIT_TAG)

set(
  ITK_TAG_COMMAND
  GIT_TAG
  "${ITK_GIT_TAG}"
)
