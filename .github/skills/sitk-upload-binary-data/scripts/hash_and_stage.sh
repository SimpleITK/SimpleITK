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
#==========================================================================
#
# Hash binary files, copy into .ExternalData/SHA512/, create .sha512
# content links, and remove the originals.  Does NOT create a PR or
# touch any git branches — that is handled separately.
#
# Usage:  hash_and_stage.sh <file1> [<file2> ...]
#
# Must be run from the SimpleITK source root.
#
set -euo pipefail

die() { echo "ERROR: $*" >&2; exit 1; }

# --- preflight -----------------------------------------------------------

[[ $# -ge 1 ]] || die "Usage: $0 <file1> [<file2> ...]"

if command -v sha512sum >/dev/null 2>&1; then
    SHA512CMD=(sha512sum)
elif command -v shasum >/dev/null 2>&1; then
    SHA512CMD=(shasum -a 512)
else
    die "Neither sha512sum (Linux) nor shasum (macOS) found."
fi

SOURCE_ROOT="$(git rev-parse --show-toplevel 2>/dev/null)" \
    || die "Not inside a git repository."

ED_DIR="${SOURCE_ROOT}/.ExternalData"

[[ -d "${ED_DIR}/.git" ]] \
    || die ".ExternalData is not a git clone. Run:\n  Utilities/GitSetup/setup-externaldata"

git -C "${ED_DIR}" remote -v 2>/dev/null | grep -q SimpleITKExternalData \
    || die ".ExternalData is not a clone of SimpleITK/SimpleITKExternalData."

mkdir -p "${ED_DIR}/SHA512"

# --- process files --------------------------------------------------------

MD5_CONFLICTS=()

for FILE in "$@"; do
    [[ -f "${FILE}" ]] || die "File not found: ${FILE}"

    BASENAME="$(basename -- "${FILE}")"
    HASH="$("${SHA512CMD[@]}" -- "${FILE}" | awk '{print $1}')"
    [[ "${HASH}" =~ ^[0-9a-f]{128}$ ]] \
        || die "Unexpected hash output for ${FILE}: '${HASH}'"

    DEST="${ED_DIR}/SHA512/${HASH}"
    if [[ -f "${DEST}" ]]; then
        echo "SKIP  ${BASENAME}: hash already in .ExternalData"
    else
        cp -- "${FILE}" "${DEST}"
        echo "COPY  ${BASENAME} -> .ExternalData/SHA512/${HASH:0:12}..."
    fi

    # content link (128 hex chars + newline)
    echo "${HASH}" > "${FILE}.sha512"
    echo "LINK  ${FILE}.sha512"

    # remove original
    rm -- "${FILE}"
    echo "DEL   ${FILE}"

    # note old .md5 content links
    if [[ -f "${FILE}.md5" ]]; then
        MD5_CONFLICTS+=("${FILE}.md5")
    fi
done

# --- summary --------------------------------------------------------------

echo ""
echo "Content links created.  Next steps:"
echo ""
echo "  git add -- $(printf '%s.sha512 ' "$@")"

if [[ ${#MD5_CONFLICTS[@]} -gt 0 ]]; then
    echo ""
    echo "Remove obsolete MD5 content links:"
    echo ""
    echo "  git rm -- ${MD5_CONFLICTS[*]}"
fi
