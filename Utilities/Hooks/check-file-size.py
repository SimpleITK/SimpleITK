#!/usr/bin/env python3
# ==========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          https://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
# ==========================================================================
#
# Reject staged files larger than a configurable size limit.
#
# The local default limit is set with the git config keys
# "hooks.MaxObjectKiB" (in KiB) or "hooks.max-size" (in bytes). Either can be
# overridden for specific paths or patterns via the "hooks.MaxObjectKiB" or
# "hooks-max-size" attributes in a git attributes file -- see
# "git help attributes" for the attribute file format.
#
# Adapted from the check_size logic formerly in Utilities/Hooks/kw-pre-commit.

import subprocess
import sys

DEFAULT_MAX_KIB = 1024


def die(message):
    print("pre-commit hook failure", file=sys.stderr)
    print("-----------------------", file=sys.stderr)
    print(message, file=sys.stderr)
    sys.exit(1)


def git_config_int(key, default):
    result = subprocess.run(["git", "config", "--get", key], capture_output=True, text=True)
    value = result.stdout.strip()
    return int(value) if value else default


def check_attr(attr, path):
    result = subprocess.run(
        ["git", "check-attr", attr, "--", path],
        capture_output=True,
        text=True,
        check=True,
    )
    prefix = f"{path}: {attr}: "
    line = result.stdout.strip()
    return line[len(prefix) :] if line.startswith(prefix) else "unspecified"


def staged_blob(path):
    """Return (mode, object_id) for a path staged in the index, or None if
    the path is not currently staged (e.g. deleted)."""
    result = subprocess.run(
        ["git", "ls-files", "-s", "--", path],
        capture_output=True,
        text=True,
        check=True,
    )
    line = result.stdout.strip()
    if not line:
        return None
    fields = line.split()
    return fields[0], fields[1]


def blob_size(object_id):
    result = subprocess.run(
        ["git", "cat-file", "-s", object_id],
        capture_output=True,
        text=True,
        check=True,
    )
    return int(result.stdout.strip())


def max_bytes_for(path, default_max_kib, default_max_bytes):
    """Resolve the size limit, in bytes, for path (None means unlimited)."""
    max_kib_attr = check_attr("hooks.MaxObjectKiB", path)
    if max_kib_attr not in ("unset", "set", "unspecified"):
        try:
            int(max_kib_attr)
        except ValueError:
            die(f'The path \'{path}\' has invalid attribute "hooks.MaxObjectKiB={max_kib_attr}".')

    max_bytes_attr = check_attr("hooks-max-size", path)
    if max_bytes_attr == "unset":
        return None
    if max_bytes_attr == "set":
        return default_max_bytes
    if max_bytes_attr == "unspecified":
        if max_kib_attr == "unset":
            return None
        if max_kib_attr == "set":
            return default_max_kib * 1024
        if max_kib_attr == "unspecified":
            return default_max_bytes
        return int(max_kib_attr) * 1024
    try:
        return int(max_bytes_attr)
    except ValueError:
        die(f'The path \'{path}\' has invalid attribute "hooks-max-size={max_bytes_attr}".')


def main():
    paths = sys.argv[1:]
    if not paths:
        return 0

    default_max_kib = git_config_int("hooks.MaxObjectKiB", DEFAULT_MAX_KIB)
    default_max_bytes = git_config_int("hooks.max-size", default_max_kib * 1024)

    errors = []
    for path in paths:
        staged = staged_blob(path)
        if staged is None:
            continue
        mode, object_id = staged
        if mode == "160000":  # Nested repository reference -- no blob to size.
            continue

        max_bytes = max_bytes_for(path, default_max_kib, default_max_bytes)
        if max_bytes is None or max_bytes <= 0:
            continue

        size = blob_size(object_id)
        if size > max_bytes:
            errors.append(f"The path '{path}' has size {size} bytes, greater than allowed {max_bytes} bytes.")

    if errors:
        die(
            "At least one file is staged for commit with size larger than its limit.\n"
            "We prefer to keep large files out of the main source tree, especially\n"
            "binary files that do not compress well.  This hook disallows large files\n"
            'by default but can be configured.  A limit for specific files or patterns\n'
            'may be set in ".gitattributes" with the "hooks-max-size" attribute.\n'
            "For example, the line\n\n"
            "  *.c              hooks-max-size=1500000\n\n"
            'sets a limit of 1500000 bytes for C source files.  See "git help attributes"\n'
            "for details on the .gitattributes format.  If no attribute has been set\n"
            "for a given file then its size is limited by the local default.  Run\n\n"
            "  git config hooks.max-size <bytes>\n\n"
            "to set the local default limit (0 to disable).\n\n" + "\n".join(errors)
        )
    return 0


if __name__ == "__main__":
    sys.exit(main())
