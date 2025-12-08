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
# sitkPythonVersion.cmake
#
# Constructs a PEP 440 compliant version string from SimpleITK version variables.
#

function(sitk_get_pep440_version output_var)
  #
  # Uses configured CMake version variables to construct a PEP 440 compliant version string.
  #
  # Arguments:
  #   output_var - Name of the variable to store the result
  #
  # Returns:
  #   A PEP 440 compliant version string in the specified output variable
  #
  # PEP 440 format: N.N[.N]+[{a|b|c|rc}N][.postN][.devN][+localversion]
  #

  set(_version "${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR}")

  if(
    DEFINED
      SimpleITK_VERSION_PATCH
    AND
      NOT
        "${SimpleITK_VERSION_PATCH}"
          STREQUAL
          ""
  )
    string(APPEND _version ".${SimpleITK_VERSION_PATCH}")

    if(
      DEFINED
        SimpleITK_VERSION_TWEAK
      AND
        NOT
          "${SimpleITK_VERSION_TWEAK}"
            STREQUAL
            ""
    )
      string(APPEND _version ".${SimpleITK_VERSION_TWEAK}")
    endif()
  endif()

  # Pre-release version (alpha, beta, release candidate)
  if(DEFINED SimpleITK_VERSION_RC AND NOT "${SimpleITK_VERSION_RC}" STREQUAL "")
    string(APPEND _version "${SimpleITK_VERSION_RC}")
  endif()

  # Post-release or development version
  if(
    DEFINED
      SimpleITK_VERSION_POST
    AND
      NOT
        "${SimpleITK_VERSION_POST}"
          STREQUAL
          ""
  )
    string(APPEND _version ".post${SimpleITK_VERSION_POST}")
  elseif(
    DEFINED
      SimpleITK_VERSION_DEV
    AND
      NOT
        "${SimpleITK_VERSION_DEV}"
          STREQUAL
          ""
  )
    string(APPEND _version ".dev${SimpleITK_VERSION_DEV}")
  endif()

  # Local Version Identifier (git hash)
  # Only add if hash is defined and we're not building for distribution
  if(
    DEFINED
      SimpleITK_VERSION_HASH
    AND
      NOT
        "${SimpleITK_VERSION_HASH}"
          STREQUAL
          ""
  )
    if(NOT SimpleITK_BUILD_DISTRIBUTE)
      string(APPEND _version "+g${SimpleITK_VERSION_HASH}")
    endif()
  endif()

  set(${output_var} "${_version}" PARENT_SCOPE)
endfunction()
