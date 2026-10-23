# =========================================================================
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
# =========================================================================

"""Stage GitHub release assets and a portable SHA256SUMS manifest.

Usage: python PrepareReleaseAssets.py DOWNLOAD_DIRECTORY NEW_STAGING_DIRECTORY

Recursively select regular .whl, .zip, and .gz files without following symlinks.
The new staging directory must be outside the download tree. Asset basenames
must begin with an ASCII letter or digit and contain only letters, digits,
periods, underscores, or hyphens. Reject exact duplicate names. Names differing
only by case require a case-sensitive staging filesystem. Upload the entire
staging directory, including SHA256SUMS, as one asset set.
"""

import argparse
import hashlib
import os
from pathlib import Path
import re
import shutil
import stat


def raise_walk_error(error):
    """Do not silently omit files when an artifact directory cannot be read."""
    raise error


def prepare_release_assets(source, destination):
    source = source.resolve()
    destination = destination.absolute()
    if not source.is_dir():
        raise ValueError(f"Source is not a directory: {source}")
    if destination.resolve().is_relative_to(source):
        raise ValueError("The staging directory must be outside the source directory")
    if os.path.lexists(destination):
        raise ValueError(f"Staging destination already exists: {destination}")

    assets = {}
    for directory, _, filenames in os.walk(source, onerror=raise_walk_error):
        for name in filenames:
            if not name.endswith((".whl", ".zip", ".gz")):
                continue
            path = Path(directory) / name
            if not stat.S_ISREG(path.lstat().st_mode):
                continue
            # GitHub may rename special characters; gh also treats '#' as a label.
            if re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9._-]*", name) is None:
                raise ValueError(f"Unsafe release asset filename: {name!r}")
            if name in assets:
                raise ValueError(f"Duplicate release asset basename: {name!r}")
            assets[name] = path

    if not assets:
        raise ValueError(f"No release assets found under {source}")

    # mkdir must succeed before cleanup can own this directory. Never reuse it.
    destination.mkdir()
    try:
        checksums = []
        for name, path in sorted(assets.items()):
            staged = destination / name
            try:
                with path.open("rb") as source_stream, staged.open("xb") as target:
                    shutil.copyfileobj(source_stream, target, length=1024 * 1024)
            except FileExistsError as error:
                raise ValueError(
                    f"Filename collision for {name!r}; use a case-sensitive "
                    "staging filesystem"
                ) from error
            digest = hashlib.sha256()
            with staged.open("rb") as stream:
                for block in iter(lambda: stream.read(1024 * 1024), b""):
                    digest.update(block)
            checksums.append(f"{digest.hexdigest()}  {name}\n")
        # Write the manifest only after every selected file has been copied/read.
        (destination / "SHA256SUMS").write_text(
            "".join(checksums), encoding="ascii", newline="\n"
        )
    except Exception:
        shutil.rmtree(destination, ignore_errors=True)
        raise
    return len(assets)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path, help="Downloaded artifact directory")
    parser.add_argument("destination", type=Path, help="New flat staging directory")
    args = parser.parse_args()
    try:
        count = prepare_release_assets(args.source, args.destination)
    except (OSError, ValueError) as error:
        parser.error(str(error))
    print(f"Staged {count} release assets and SHA256SUMS in {args.destination}")


if __name__ == "__main__":
    main()
