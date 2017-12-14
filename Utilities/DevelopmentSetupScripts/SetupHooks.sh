#!/usr/bin/env bash
#==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================*/


# Run this script to set up the git hooks for committing changes to SimpleITK.
# For more information, see:
#   https://www.itk.org/Wiki/Git/Hooks

egrep-q() {
  egrep "$@" >/dev/null 2>/dev/null
}

die() {
	echo 'failure during hook setup' 1>&2
	echo '-------------------------' 1>&2
	echo '' 1>&2
	echo "$@" 1>&2
	exit 1
}

# Disable the 'hooks' branch submodule check.
# We have a check that blocks addition of submodules.
git config hooks.submodule false

# We don't have as must style setup as ITK, but we may...
# Set up KWStyle hook.
git config hooks.KWStyle.conf "Utilities/KWStyle/SITK.kws.xml.in"
git config hooks.KWStyle.overwriteRulesConf "Utilities/KWStyle/SITKOverwrite.txt"


echo "Setting up JSON validation with python..."
PYTHON_EXECUTABLE=$(which python) || die "No python found for hooks."
git config hooks.python ${PYTHON_EXECUTABLE}
git config hooks.ValidateJSON true
