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


# Run this script to set up development with git.

die() {
  echo 'Failure during SimpleITK Git development setup' 1>&2
  echo '----------------------------------------' 1>&2
  echo '' 1>&2
  echo "$@" 1>&2
  exit 1
}

# Make sure we are inside the repository.
cd "$(echo "$0"|sed 's/[^/]*$//')"/..

if test -d .git/.git; then
  die "The directory '.git/.git' exists, indicating a configuration error.

Please 'rm -rf' this directory."
fi

# Check to make sure we got a new enough git.
git_required_major_version=1
git_required_minor_version=7
git_required_release_version=10
git_required_bugfix_version="" # Use "" if there is no bugfix version.
echo "Checking Git version..."
git_version=$(git --version | awk '{print $3}')
declare -a git_version_arr
git_version_arr=(`echo ${git_version//./ }`)
insufficient_version() {
  if test -z "${git_required_bugfix_version}"; then
    git_required_version="${git_required_major_version}.${git_required_minor_version}.${git_required_release_version}"
  else
    git_required_version="${git_required_major_version}.${git_required_minor_version}.${git_required_release_version}.${git_required_bugfix_version}"
  fi
  die "Insufficient Git version.

Detected version was
  ${git_version}
and the minimum required version is
  ${git_required_version}"
}
if test ${git_version_arr[0]} -lt $git_required_major_version; then
  insufficient_version
elif test ${git_version_arr[0]} -eq $git_required_major_version; then
  if test ${git_version_arr[1]} -lt $git_required_minor_version; then
    insufficient_version
  elif test ${git_version_arr[1]} -eq $git_required_minor_version; then
    if test ${git_version_arr[2]} -lt $git_required_release_version; then
      insufficient_version
    elif test ${git_version_arr[2]} -eq $git_required_release_version; then
      if test -n "${git_required_bugfix_version}" -a \
         -n "${git_version_arr[3]}" -o \
         ${git_version_arr[3]} -lt $git_required_bugfix_version; then
        insufficient_version
      fi
    fi
  fi
fi
echo -e "Git version $git_version is OK.\n"

cd "${BASH_SOURCE%/*}/.." &&
Utilities/GitSetup/setup-user && echo &&
Utilities/GitSetup/setup-hooks && Utilities/DevelopmentSetupScripts/SetupHooks.sh && echo &&
( read -ep "Do you want to setup access itk.org? [y/N]: " access;
    if [ "$access" == "y" ] || [ "$access" == "Y" ]; then
        Utilities/GitSetup/setup-upstream && echo &&
        Utilities/GitSetup/setup-stage && echo &&
        Utilities/GitSetup/setup-ssh ||
        echo 'Failed to setup SSH.  Run this again to retry.'
   fi)  && echo &&
Utilities/GitSetup/tips



cd Utilities/DevelopmentSetupScripts

echo "Setting up useful Git aliases..."
./SetupGitAliases.sh || exit 1
echo

# Disable legacy Gerrit hooks
echo "Disable legacy Gerrit hook..."
git config --unset hooks.GerritId


# Record the version of this setup so Hooks/pre-commit can check it.
SetupForDevelopment_VERSION=3
git config hooks.SetupForDevelopment ${SetupForDevelopment_VERSION}
