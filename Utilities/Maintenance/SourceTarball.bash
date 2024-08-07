#!/usr/bin/env bash
#==========================================================================
#
#   Copyright NumFOCUS
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

usage() {
  die 'USAGE: SourceTarball.bash [(--tgz|--txz|--zip)...] \
        [--verbose] [-v <version>] build_dir [<tag>|<commit>]'
}

info() {
  echo "$@" 1>&2
}

die() {
  echo "$@" 1>&2; exit 1
}

return_pipe_status() {
  echo ${PIPESTATUS[@]} |grep -q -v "[1-9]"
}

find_data_objects() {
  # Find all content links in the tree.
  git ls-tree --full-tree -r "$1" |
  egrep '\.(md5|sha512)$' |
  while read mode type obj path; do
    case "$path" in
      *.md5)  echo MD5/$(git cat-file blob $obj) ;;
      *.sha512) echo SHA512/$(git cat-file blob $obj);;
      *)      die "Unknown ExternalData content link: $path" ;;
    esac
  done | sort | uniq
  return_pipe_status
}

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

compute_MD5() {
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

compute_SHA512 () {
    $sha512tool "$1" | sed -e "$sha512regex"
}


validate () {
    local algo="$1"
    readonly algo
    shift

    local file="$1"
    readonly file
    shift

    local expected="$1"
    readonly expected
    shift

    local actual="$( "compute_$algo" "$file" )"
    readonly actual


    if ! [ "$actual" = "$expected" ]; then
        die "Object $expected is corrupt: $file"
    fi
}

download_object() {
  algo="$1" ; hash="$2" ; path="$3"
  mkdir -p $(dirname "$path") &&
  if curl -Lf "https://simpleitk.org/SimpleITKExternalData/$algo/$hash" --output "$path.tmp$$" 1>&2 ||
     curl -Lf "https://s3.amazonaws.com/simpleitk/public/$algo/$hash" --output "$path.tmp$$" 1>&2 ||
     curl -Lf "https://data.kitware.com:443/api/v1/file/hashsum/$algo/$hash/download" --output "$path.tmp$$" 1>&2; then
    mv "$path.tmp$$" "$path"
  else
    rm -f "$path.tmp$$"
    false
  fi
}

index_data_objects() {
  # Input lines have format <algo>/<hash>
  while IFS=/ read algo hash; do
    # Final path in source tarball
    path=".ExternalData/$algo/$hash"
    # Find the object file on disk
    if test -f "$path"; then
      file="$path" # available in place
    elif test -n "$ExternalData_OBJECT_STORES" -a -f "$ExternalData_OBJECT_STORES/$algo/$hash" ; then
      file=$ExternalData_OBJECT_STORES/$algo/$hash # available from env path
    else
      download_object "$algo" "$hash" "$path" &&
      file="$path"
    fi &&    validate "$algo" "$file" "$hash" &&
    obj=$(git hash-object -t blob -w "$file") &&
    echo "100644 blob $obj	$path" ||
    return
  done |
  git update-index --index-info
  return_pipe_status
}

index_additional_object() {

   file="$1"
   path=$file
   test -n "$2" && path=$2/$(basename $file)

   obj=$(git hash-object -t blob -w "$file") &&
    echo "100644 blob $obj	$path" |
    git update-index --index-info

  return_pipe_status

}


# NOTE: this methods exports the GIT_ALTERNATE_OBJECT_DIRECTORIES variable to effect later processes
index_submodule_objects() {

   SUBMODULE_LIST=$(git submodule foreach --quiet 'echo $(git rev-parse --git-dir)/objects')
   export GIT_ALTERNATE_OBJECT_DIRECTORIES=$SUBMODULE_LIST
   IFS=' '
   git submodule foreach --quiet  'git ls-tree --full-tree -r $sha1 | awk  -v path=$path '"'"'{ print path, $1, $2, $3, path "/" $4 }'"'"'' |
   while read path mode type object file; do
    echo "$mode $type $object	$file" ||
    return
   done  |
   git update-index --index-info
   return_pipe_status
}

load_data_objects() {
  find_data_objects "$@" |
  index_data_objects
  return_pipe_status
}

load_data_files() {
  git ls-tree -r "$1" -- '.ExternalData' |
  git update-index --index-info
  return_pipe_status
}

git_archive_tgz() {
  out="$2.tar.gz" && tmp="$out.tmp$$" &&
  if test -n "$3"; then prefix="$3"; else prefix="$2"; fi &&
  git -c core.autocrlf=false archive $verbose --format=tar --prefix=$prefix/ $1 |
  gzip -9 > "$tmp" &&
  mv "$tmp" "$out" &&
  info "Wrote $out"
}

git_archive_txz() {
  out="$2.tar.xz" && tmp="$out.tmp$$" &&
  if test -n "$3"; then prefix="$3"; else prefix="$2"; fi &&
  git -c core.autocrlf=false archive $verbose --format=tar --prefix=$prefix/ $1 |
  xz -9 > "$tmp" &&
  mv "$tmp" "$out" &&
  info "Wrote $out"
}

git_archive_zip() {
  out="$2.zip" && tmp="$out.tmp$$" &&
  if test -n "$3"; then prefix="$3"; else prefix="$2"; fi &&
  git -c core.autocrlf=true archive $verbose --format=zip --prefix=$prefix/ $1 > "$tmp" &&
  mv "$tmp" "$out" &&
  info "Wrote $out"
}

#-----------------------------------------------------------------------------

formats=
commit=
version=
verbose=
build_dir=

# Parse command line options.
while test $# != 0; do
  case "$1" in
    --tgz) formats="$formats tgz" ;;
    --txz) formats="$formats txz" ;;
    --zip) formats="$formats zip" ;;
    --verbose) verbose=-v ;;
    --) shift; break ;;
    -v) shift; version="$1" ;;
    -*) usage ;;
    *) { test -z "$build_dir" && build_dir="$1"; } ||
       { test -z "$commit" && commit="$1"; } ||
       usage ;;
  esac
  shift
done
test $# = 0 || usage
test -n "$commit" || commit=HEAD
test -n "$formats" || formats=tgz

test -n "$build_dir" ||
  die "Missing required build_dir argument."

test -e "${build_dir}/SimpleITKConfig.cmake" ||
  die "invalid build directory."


if ! git rev-parse --verify -q "$commit" >/dev/null ; then
  die "'$commit' is not a valid commit"
fi
if test -z "$version"; then
  desc=$(git describe "--match=v*" "--tags" $commit) &&
  if test "${desc:0:1}" != "v"; then
    die "'git describe $commit' is '$desc'; use -v <version>"
  fi &&
  version=${desc#v} &&
  echo "$commit is version $version"
fi

# Create temporary git index to construct source tree
export GIT_INDEX_FILE="$(pwd)/tmp-$$-index" &&
trap "rm -f '$GIT_INDEX_FILE'" EXIT &&


result=0 &&


info "Loading source tree from $commit..." &&
rm -f "$GIT_INDEX_FILE" &&
git read-tree -m -i $commit &&
git rm -rf -q --cached '.ExternalData' &&
index_additional_object "${build_dir}/sitkSourceVersionVars.cmake" "CMake" &&


tree=$(git write-tree) &&
info "Generating source archive(s)..." &&
for fmt in $formats; do
  git_archive_$fmt $tree "SimpleITK-$version" || result=1
done &&

info "Loading data for $commit..." &&
rm -f "$GIT_INDEX_FILE" &&
load_data_objects $commit &&
load_data_files $commit &&
tree=$(git write-tree) &&


info "Generating data archive(s)..." &&
for fmt in $formats; do
  git_archive_$fmt $tree "SimpleITKData-$version" "SimpleITK-$version" || result=1
done &&
exit $result
