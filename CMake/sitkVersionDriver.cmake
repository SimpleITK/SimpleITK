# ========================================================================
#
#  Copyright NumFOCUS
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
# ========================================================================
#
# sitkVersionDriver.cmake
#
# Standalone "cmake -P" driver that reproduces the version-computation
# portion of a real SimpleITK CMake configure (Version.cmake ->
# sitkSourceVersion.cmake -> sitkPythonVersion.cmake) without running a
# full project() configure. Used by CMake/sitk_version_provider.py (a
# scikit-build-core dynamic-metadata provider) so that the wheel's
# PKG-INFO "Version:" field is identical to SimpleITK.__version__.
#
# Usage:
#   cmake -DSITK_SOURCE_DIR=<repo-root> \
#         -DSITK_VERSION_OUTPUT_FILE=<path-to-write-result> \
#         -P CMake/sitkVersionDriver.cmake
#
# SITK_SOURCE_DIR defaults to the parent of this file's directory.
# The computed PEP 440 version string is written, with no trailing
# newline, to SITK_VERSION_OUTPUT_FILE.
#

cmake_minimum_required(VERSION 3.26.1)

if(NOT DEFINED SITK_SOURCE_DIR)
  get_filename_component(
    SITK_SOURCE_DIR
    "${CMAKE_CURRENT_LIST_DIR}/.."
    ABSOLUTE
  )
endif()

if(NOT DEFINED SITK_VERSION_OUTPUT_FILE)
  message(
    FATAL_ERROR
    "SITK_VERSION_OUTPUT_FILE must be set (-D) to the path to write the result to."
  )
endif()

if(NOT EXISTS "${SITK_SOURCE_DIR}/Version.cmake")
  message(
    FATAL_ERROR
    "SITK_SOURCE_DIR (\"${SITK_SOURCE_DIR}\") does not look like the SimpleITK source tree: Version.cmake not found."
  )
endif()

# Fake just enough of a project() configure's context for
# Version.cmake / sitkSourceVersion.cmake / sitkGetGitRevisionDescription.cmake
# / sitkPythonVersion.cmake to run standalone and produce output
# identical to a real configure; none of these modules reads any other
# project()-provided variable.
set(CMAKE_PROJECT_NAME "SimpleITK")
set(PROJECT_SOURCE_DIR "${SITK_SOURCE_DIR}")

# Writable scratch directory standing in for PROJECT_BINARY_DIR; only
# used by sitkGetGitRevisionDescription.cmake to stage a copy of
# .git/HEAD so a real build reconfigures on commit changes -- moot
# here, but it must be a writable path.
get_filename_component(
  _sitk_version_scratch_dir
  "${SITK_VERSION_OUTPUT_FILE}"
  DIRECTORY
)
if(_sitk_version_scratch_dir STREQUAL "")
  set(_sitk_version_scratch_dir "${CMAKE_CURRENT_BINARY_DIR}")
endif()
set(PROJECT_BINARY_DIR "${_sitk_version_scratch_dir}/sitk-version-scratch")

list(PREPEND CMAKE_MODULE_PATH "${SITK_SOURCE_DIR}/CMake")

# Version.cmake sets SimpleITK_VERSION_MAJOR/MINOR/PATCH and
# include()s sitkSourceVersion (resolved via CMAKE_MODULE_PATH above),
# which sets the _GIT_VERSION_* variables sitkPythonVersion reads.
include("${SITK_SOURCE_DIR}/Version.cmake")

include(sitkPythonVersion)
sitk_get_pep440_version(SITK_PYTHON_VERSION)

file(WRITE "${SITK_VERSION_OUTPUT_FILE}" "${SITK_PYTHON_VERSION}")
