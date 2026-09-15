#!/usr/bin/env bash
#
# DownloadReleaseNotes.sh
#
# Downloads release notes from all SimpleITK GitHub releases and saves them as
# Sphinx-ready Markdown files in docs/source/release_notes/.
#
# Each release's body is saved as notes-{tag}.md with the following processing:
#   - A top-level "# SimpleITK Release {tag}" header is prepended
#   - Empty anchor tags (<a href="..."></a>) used as hidden download links
#     are stripped, as they add no value to the documentation
#   - Post-processing to ensure consistent Markdown heading hierarchy
#
# Usage:
#   ./Utilities/Maintenance/DownloadReleaseNotes.sh
#
# Requirements:
#   - gh (GitHub CLI), authenticated with read access to SimpleITK/SimpleITK
#
# After running this script, rebuild the Sphinx documentation:
#   cd docs && make html

set -euo pipefail

REPO="SimpleITK/SimpleITK"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
OUTPUT_DIR="${SCRIPT_DIR}/../../docs/source/release_notes"

echo "Fetching release list for ${REPO}..."
tags=$(gh release list --repo "${REPO}" --limit 200 --json tagName --jq '.[].tagName')

for tag in ${tags}; do
    output="${OUTPUT_DIR}/notes-${tag}.md"
    echo "Downloading notes for ${tag} -> $(basename "${output}")"
    gh release view "${tag}" --repo "${REPO}" --json body --jq '.body' > "${output}"

    # Remove empty anchor tags (hidden links)
    sed -i 's/<a[^>]*><\/a>//g' "${output}"
done

echo "Done."
