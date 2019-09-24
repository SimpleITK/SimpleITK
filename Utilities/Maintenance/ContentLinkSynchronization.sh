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

# This script, given an ExternalData object store, checks all ExternalData
# .md5 and .sha512 content links in the ITK source, verifies that hashes
# correspond to the same file, and creates both .md5 and .sha512 hashes if
# they are missing.
#
# If content link verification fails, the script notifies the caller and exits.
# The error should be resolved manually before re-execution.
#
# Once executed, a commit can be created from the result.
#
# This script should be executed prior to releases. After any missing content
# links have been merged, the scripts to archive testing data on the Midas and
# Girder stores should be executed.

die() {
  echo "$@" 1>&2; exit 1
}

if test $# -lt 1 || test "$1" = "-h" || test "$1" = "--help"; then
  die "Usage: $0 <ExternalData_OBJECT_STORES path>"
fi


# Check for a tool to get MD5 sums from.
if type -p md5sum >/dev/null; then
    readonly md5tool="md5sum"
    readonly md5regex="s/ .*//"
elif type -p md5 >/dev/null; then
    readonly md5tool="md5"
    readonly md5regex="s/.*= //"
elif type -p cmake >/dev/null; then
    readonly md5tool="cmake -E md5sum"
    readonly md5regex="s/ .*//"
else
    die "No 'md5sum' or 'md5' tool found."
fi

compute_md5() {
    $md5tool "$1" | sed -e "$md5regex"
}


# Check for a tool to get SHA512 sums from.
if type -p sha512sum >/dev/null; then
    readonly sha512tool="sha512sum"
    readonly sha512regex="s/ .*//"
elif type -p cmake >/dev/null; then
    readonly sha512tool="cmake -E sha512sum"
    readonly sha512regex="s/ .*//"
else
    die "No 'sha512sum' tool found."
fi

compute_sha512 () {
    $sha512tool "$1" | sed -e "$sha512regex"
}

top_level_dir=$(git rev-parse --show-toplevel)
cd "$top_level_dir"

object_store=$1

mkdir -p ${object_store}/{MD5,SHA512}

verify_and_create() {
  algo=$1
  alt_algo=$2

  algo_upper=$(echo $algo | awk '{print toupper($0)}')
  alt_algo_upper=$(echo $alt_algo | awk '{print toupper($0)}')

  find . -name "*.${algo}" -print0 | while read -d ''  -r algo_file; do
    echo "Content link ${algo_file} ..."
    if test -z "${algo_file}"; then
      die "Empty content link!"
      continue
    fi
    algo_hash=$(cat "${algo_file}" | tr -d '[[:space:]]')
    alt_algo_file=${algo_file%\.*}.${alt_algo}
    if test ! -e "${object_store}/${algo_upper}/${algo_hash}"; then
      if test -e "${alt_algo_file}"; then
        alt_algo_hash=$(cat "${alt_algo_file}" | tr -d '[[:space:]]')
        if test -e "${object_store}/${alt_algo_upper}/${alt_algo_hash}"; then
          echo "Found object in ${alt_algo} store, copying to ${algo} store..."
          cp "${object_store}/${alt_algo_upper}/${alt_algo_hash}" "${object_store}/${algo_upper}/${algo_hash}"
        else
          die "Could not find data object in store!"
        fi
      else
        die "Could not find data object in store!"
      fi
    fi
    echo "Verifying    ${algo_file}..."
    object_algo_hash=$(compute_${algo} "${object_store}/${algo_upper}/${algo_hash}" )
    if test "${algo_hash}" != "${object_algo_hash}"; then
      die "${algo}sum for ${object_store}/${algo_upper}/${algo_hash} does not equal hash in ${algo_file}!"
    fi

    object_alt_algo_hash=$(compute_${alt_algo} "${object_store}/${algo_upper}/${algo_hash}" )
    if test -e  "${alt_algo_file}"; then
      echo "Verifying    ${alt_algo_file}..."
      alt_algo_hash=$(cat "${alt_algo_file}" | tr -d '[[:space:]]')
      if test "${alt_algo_hash}" != "${object_alt_algo_hash}"; then
        die "${alt_algo}sum for ${object_store}/${algo_upper}/${algo_hash} does not equal hash in ${alt_algo_file}!"
      fi
    else
      echo "Creating     ${alt_algo_file}..."
      echo "${object_alt_algo_hash}" > "${alt_algo_file}"
      if [ ! -x  "${object_store}/${alt_algo_upper}/${object_alt_algo_hash}" ]; then
        cp "${object_store}/${algo_upper}/${algo_hash}" "${object_store}/${alt_algo_upper}/${object_alt_algo_hash}"
      fi
    fi
  done || exit 1
}

verify_and_create md5 sha512
verify_and_create sha512 md5

echo ""
echo "Verification completed successfully."
echo ""
echo "Commit new content links as necessary."
