#
# This CMake code extracts the information from the git repository,
# and automatically causes a reconfigure if the git HEAD changes. The
# following variable may be defined after execution:
#
# _GIT_VERSION_HASH - the SHA1 hash of the current HEAD
#
# Based on the most recent tag starting with the letter "v" for
# version, which is expected to be of the form
# vN.N[.N[.N][(a|b|c|rc[N])] the following is extracted or undefined:
#
# _GIT_VERSION_MAJOR
# _GIT_VERSION_MINOR
# _GIT_VERSION_PATCH
# _GIT_VERSION_TWEAK
# _GIT_VERSION_RC
#
# If the current project's version ( defiend by
# ${CMAKE_PROJECT_NAME}_VERSION_MAJOR and MINOR and PATCH and TWEAK
# match that of the tag, then it'll be considered that the project is
# in post release mode otherwise it's considered underdevelopment.
#
# Only one of the following variables will be defined.
# _GIT_VERSION_DEV is defined as number of commits
# since the projects Version.cmake file has been modified. While
# _GIT_VERSION_POST is defined as the number of commits since the tag.
#
# If no ".git" directory is found (e.g. building from a source archive),
# version information is instead read from ".git_archival.txt" at the
# project source root, which "git archive" populates via the
# "export-subst" gitattribute when the archive is created. If that file
# was not produced by "git archive" (its placeholders are unexpanded),
# the source version cannot be determined.
#

function(_sitk_set_source_version)
  include(sitkGetGitRevisionDescription)

  # File populated by "git archive" via the "export-subst" gitattribute
  # (see .gitattributes and .git_archival.txt) when the source tree was
  # obtained as an archive/tarball (e.g. GitHub's auto-generated source
  # tarballs/zips) instead of a git clone, so no ".git" directory exists.
  set(_GIT_ARCHIVAL_FILE "${PROJECT_SOURCE_DIR}/.git_archival.txt")

  get_git_head_revision(GIT_REFVAR _GIT_VERSION_HASH)

  # Only TRUE when we are in a real git checkout and can run git commands
  # (e.g. git_describe, git_commits_since) directly against it.
  set(_sitk_have_git_repo TRUE)

  # if there is not a git directory we should be in a distributed package,
  # a "git archive" produced tarball, handled via _GIT_ARCHIVAL_FILE below.
  if(_GIT_VERSION_HASH STREQUAL "GITDIR-NOTFOUND")
    set(_sitk_have_git_repo FALSE)
    set(_GIT_TAG "")

    if(EXISTS "${_GIT_ARCHIVAL_FILE}")
      file(STRINGS "${_GIT_ARCHIVAL_FILE}" _sitk_archival_lines)
      foreach(_sitk_archival_line IN LISTS _sitk_archival_lines)
        if(_sitk_archival_line MATCHES "^node: ([a-fA-F0-9]+)$")
          set(_GIT_VERSION_HASH "${CMAKE_MATCH_1}")
        elseif(_sitk_archival_line MATCHES "^describe-name: (.*)$")
          set(_GIT_TAG "${CMAKE_MATCH_1}")
        endif()
      endforeach()
    endif()

    # The "$Format:...$" placeholders are only substituted with real
    # values by "git archive" (via export-subst); if they are still
    # literal, the file was copied without going through "git archive"
    # and is not usable.
    if(_GIT_VERSION_HASH MATCHES "\\$Format:")
      set(_GIT_VERSION_HASH "GITDIR-NOTFOUND")
    endif()
    if(_GIT_TAG MATCHES "\\$Format:")
      set(_GIT_TAG "")
    endif()

    if("${_GIT_TAG}" STREQUAL "")
      # No usable archive info either.
      message(
        WARNING
        "Unable to determine source version!\n
Please use the git repository or an official source distribution.\n"
      )
      set(_GIT_VERSION_DEV "")
      return()
    endif()
  endif()

  if(_GIT_VERSION_HASH MATCHES "[a-fA-F0-9]+")
    string(SUBSTRING "${_GIT_VERSION_HASH}" 0 5 _GIT_VERSION_HASH)
  endif()

  if(_sitk_have_git_repo)
    # Find the closest annotated tag with the v prefix for version.
    # Consider all tags starting with v, to accommodate GitHub Actions way in which annotated tags are clobbered. See
    # actions/checkout#290 for details.
    git_describe(_GIT_TAG "--match=v*" "--tags")

    git_commits_since("${PROJECT_SOURCE_DIR}/Version.cmake" _GIT_VERSION_COUNT)
  endif()

  set(
    VERSION_REGEX
    "^v([0-9]+)\\.([0-9]+)+(\\.([0-9]+))?(\\.([0-9]+))?((a|b|c|rc)[0-9]*)?(-[0-9]+)?"
  )

  string(REGEX MATCH "${VERSION_REGEX}" _out "${_GIT_TAG}")

  if("${_out}" STREQUAL "")
    message(
      WARNING
      "git tag: \"${_GIT_TAG}\" does not match expected version format!"
    )
    return()
  endif()

  set(_GIT_VERSION_MAJOR "${CMAKE_MATCH_1}")
  set(_GIT_VERSION_MINOR "${CMAKE_MATCH_2}")
  if(NOT "${CMAKE_MATCH_4}" STREQUAL "")
    set(_GIT_VERSION_PATCH "${CMAKE_MATCH_4}")
  endif()
  if(NOT "${CMAKE_MATCH_6}" STREQUAL "")
    set(_GIT_VERSION_TWEAK "${CMAKE_MATCH_6}")
  endif()
  if(NOT "${CMAKE_MATCH_7}" STREQUAL "")
    set(_GIT_VERSION_RC "${CMAKE_MATCH_7}") # a,b,rc01 etc
  endif()

  if(NOT "${CMAKE_MATCH_9}" STREQUAL "")
    #trim leading '-'
    string(SUBSTRING "${CMAKE_MATCH_9}" 1 -1 CMAKE_MATCH_9)

    set(_GIT_TAG_COUNT "${CMAKE_MATCH_9}")
  endif()

  set(_GIT_VERSION "${_GIT_VERSION_MAJOR}.${_GIT_VERSION_MINOR}")
  if(DEFINED _GIT_VERSION_PATCH)
    set(_GIT_VERSION "${_GIT_VERSION}.${_GIT_VERSION_PATCH}")
    if(DEFINED _GIT_VERSION_TWEAK)
      set(_GIT_VERSION "${_GIT_VERSION}.${_GIT_VERSION_TWEAK}")
    elseif(DEFINED ${CMAKE_PROJECT_NAME}_VERSION_TWEAK)
      set(_GIT_VERSION "${_GIT_VERSION}.0")
    endif()
  elseif(DEFINED ${CMAKE_PROJECT_NAME}_VERSION_PATCH)
    set(_GIT_VERSION "${_GIT_VERSION}.0")
    if(DEFINED ${CMAKE_PROJECT_NAME}_VERSION_TWEAK)
      set(_GIT_VERSION "${_GIT_VERSION}.0")
    endif()
  endif()

  set(
    _${CMAKE_PROJECT_NAME}_VERSION
    "${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}.${${CMAKE_PROJECT_NAME}_VERSION_MINOR}"
  )
  if(DEFINED ${CMAKE_PROJECT_NAME}_VERSION_PATCH)
    set(
      _${CMAKE_PROJECT_NAME}_VERSION
      "${_${CMAKE_PROJECT_NAME}_VERSION}.${${CMAKE_PROJECT_NAME}_VERSION_PATCH}"
    )
    if(DEFINED ${CMAKE_PROJECT_NAME}_VERSION_TWEAK)
      set(
        _${CMAKE_PROJECT_NAME}_VERSION
        "${_${CMAKE_PROJECT_NAME}_VERSION}.${${CMAKE_PROJECT_NAME}_VERSION_TWEAK}"
      )
    endif()
  endif()

  if(_GIT_VERSION VERSION_EQUAL _${CMAKE_PROJECT_NAME}_VERSION)
    if(_GIT_TAG_COUNT) #ignore if 0
      set(_GIT_VERSION_POST "${_GIT_TAG_COUNT}")
    endif()
  elseif(_sitk_have_git_repo)
    # The first commit after a tag should increase the project version
    # number in Version.cmake and be "dev1"
    math(EXPR _GIT_VERSION_COUNT "${_GIT_VERSION_COUNT}+1")
    set(_GIT_VERSION_DEV "${_GIT_VERSION_COUNT}")
  elseif(_GIT_TAG_COUNT) #ignore if 0
    # No git repository available (e.g. building from a "git archive"
    # tarball) to count commits since Version.cmake was last modified,
    # so fall back to reporting the distance from the nearest tag
    # instead of the exact "dev" count.
    set(_GIT_VERSION_DEV "${_GIT_TAG_COUNT}")
  endif()

  # Propagate variables to parent scope
  set(_GIT_VERSION_HASH "${_GIT_VERSION_HASH}" PARENT_SCOPE)
  set(_GIT_VERSION_MAJOR "${_GIT_VERSION_MAJOR}" PARENT_SCOPE)
  set(_GIT_VERSION_MINOR "${_GIT_VERSION_MINOR}" PARENT_SCOPE)
  set(_GIT_VERSION_PATCH "${_GIT_VERSION_PATCH}" PARENT_SCOPE)
  set(_GIT_VERSION_TWEAK "${_GIT_VERSION_TWEAK}" PARENT_SCOPE)
  set(_GIT_VERSION_RC "${_GIT_VERSION_RC}" PARENT_SCOPE)
  if(DEFINED _GIT_VERSION_POST)
    set(_GIT_VERSION_POST "${_GIT_VERSION_POST}" PARENT_SCOPE)
  endif()
  if(DEFINED _GIT_VERSION_DEV)
    set(_GIT_VERSION_DEV "${_GIT_VERSION_DEV}" PARENT_SCOPE)
  endif()
endfunction()

_sitk_set_source_version()
