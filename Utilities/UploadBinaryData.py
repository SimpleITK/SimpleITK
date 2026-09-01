#!/usr/bin/env python3
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

#
# Provide inline script metadata per PEP 723 (https://peps.python.org/pep-0723/)
# /// script
# requires-python = ">=3.9"
# dependencies = [
#   "requests",
# ]
# ///

"""
Upload binary testing data for SimpleITK and related projects to data.kitware.com.

Binary data, e.g. test input images, are not stored in Git because they
would bloat a Git repository's size.

To use the script:

1. Sign up for an account at https://data.kitware.com
2. Place the binary file at the desired location in the Git repository.
3. Run this script, and pass in the binary file(s) as arguments to the script.
4. In test/CMakeLists.txt, use the sitk_add_test macro and reference the file
   path with `DATA` and braces, e.g.: DATA{<Relative/Path/To/Source/Tree/File>}.
5. Re-build SimpleITK, and the testing data will be downloaded into the build tree.

If the Git "girder.api-key" config or GIRDER_API_KEY environment variable
is not set, a prompt will appear for your username and password. The API key
can be created in the data.kitware.com user account web browser interface. The
Git config can be set by running:

    git config girder.api-key YOUR_GIRDER_API_KEY

The script will authenticate to data.kitware.com, upload the file to your
user account's Public folder, and create a *.sha512 CMake ExternalData
content link file. To specify a different folder, use the --folder-id flag.
After the content link has been created, add the *.sha512 file to your
git commit. By default, the binary file is removed from the source tree
following upload; pass --no-remove to keep it in place.

Usage (without explicitly creating a virtual environment or installing
dependencies), run the script using the uv (https://docs.astral.sh/uv/) tool:

    uv run Utilities/UploadBinaryData.py <binary/file/path/in/repo>
"""

import argparse
import base64
import getpass
import hashlib
import os
import subprocess
import sys
from pathlib import Path
from typing import Optional

import requests

API_URL = "https://data.kitware.com/api/v1"


class UploadError(Exception):
    """Raised when a step of the upload process cannot be completed."""


class GirderClient:
    """A minimal client for the subset of the Girder REST API used to upload
    SimpleITK testing data to data.kitware.com."""

    def __init__(self, api_url: str = API_URL):
        self.api_url = api_url
        self.session = requests.Session()

    def authenticate_with_api_key(self, api_key: str) -> Optional[str]:
        """Exchange a Girder API key for a short-lived authentication token."""
        url = f"{self.api_url}/api_key/token?key={api_key}&duration=1"
        try:
            response = self.session.post(
                url,
                headers={"Content-Type": "application/json", "Accept": "application/json"},
            )
            response.raise_for_status()
        except requests.RequestException as e:
            raise UploadError("Could not retrieve token from API key.") from e
        return response.json().get("token")

    def authenticate_with_credentials(self, username: str, password: str) -> Optional[str]:
        """Exchange a username/password for an authentication token."""
        basic_content = base64.b64encode(f"{username}:{password}".encode()).decode()
        url = f"{self.api_url}/user/authentication"
        try:
            response = self.session.get(
                url,
                headers={
                    "Girder-Authorization": f"Basic {basic_content}",
                    "Accept": "*/*",
                },
            )
            response.raise_for_status()
        except requests.RequestException as e:
            raise UploadError("Could not retrieve token from username / password.") from e
        return response.json().get("authToken", {}).get("token")

    def authenticate(self) -> None:
        """Authenticate to data.kitware.com, trying, in order: the
        "girder.api-key" git config value, the GIRDER_API_KEY environment
        variable, and finally an interactive username/password prompt."""
        token = None

        git_api_key = _get_git_config("girder.api-key")
        if git_api_key:
            token = self.authenticate_with_api_key(git_api_key)

        if not token:
            env_api_key = os.environ.get("GIRDER_API_KEY")
            if env_api_key:
                token = self.authenticate_with_api_key(env_api_key)

        if not token:
            print("Please provide your\n\n    https://data.kitware.com\n")
            username = input("username: ")
            password = getpass.getpass("password: ")
            token = self.authenticate_with_credentials(username, password)

        if not token:
            raise UploadError("Could not authenticate to https://data.kitware.com")

        self.session.headers["Girder-Token"] = token

    def get_my_user_id(self) -> str:
        try:
            response = self.session.get(f"{self.api_url}/user/me")
            response.raise_for_status()
        except requests.RequestException as e:
            raise UploadError("Could not get user id.") from e
        return response.json()["_id"]

    def get_public_folder_id(self, user_id: str) -> str:
        try:
            response = self.session.get(
                f"{self.api_url}/folder",
                params={
                    "parentType": "user",
                    "parentId": user_id,
                    "name": "Public",
                    "limit": 3,
                    "sort": "lowerName",
                    "sortdir": 1,
                },
            )
            response.raise_for_status()
        except requests.RequestException as e:
            raise UploadError("Could not get folder id.") from e
        folders = response.json()
        if not folders:
            raise UploadError("Could not find a Public folder for the user.")
        return folders[0]["_id"]

    def create_item(self, folder_id: str, name: str) -> str:
        try:
            response = self.session.post(
                f"{self.api_url}/item",
                params={
                    "folderId": folder_id,
                    "name": name,
                    "description": "SimpleITK testing data uploaded by "
                    "SimpleITK/Utilities/UploadBinaryData.py",
                    "reuseExisting": "true",
                },
            )
            response.raise_for_status()
        except requests.RequestException as e:
            raise UploadError("Could not create item.") from e
        return response.json()["_id"]

    def upload_file(self, item_id: str, name: str, path: Path) -> str:
        try:
            with path.open("rb") as f:
                response = self.session.post(
                    f"{self.api_url}/file",
                    params={
                        "parentType": "item",
                        "parentId": item_id,
                        "name": name,
                        "size": path.stat().st_size,
                    },
                    data=f,
                )
            response.raise_for_status()
        except (requests.RequestException, OSError) as e:
            raise UploadError(f"Could not upload {path}.") from e
        return response.json()["_id"]

    def get_file_sha512(self, file_id: str) -> str:
        try:
            response = self.session.get(
                f"{self.api_url}/file/{file_id}/hashsum_file/sha512",
                headers={"Accept": "text/plain"},
            )
            response.raise_for_status()
        except requests.RequestException as e:
            raise UploadError("Could not get file sha512sum.") from e
        return response.text.strip()


def _get_git_config(key: str) -> Optional[str]:
    try:
        result = subprocess.run(
            ["git", "config", "--get", key], capture_output=True, text=True
        )
    except FileNotFoundError:
        return None
    return result.stdout.strip() if result.returncode == 0 else None


def _local_sha512(path: Path) -> str:
    digest = hashlib.sha512()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def upload_binary_file(client: GirderClient, binary_file: Path, folder_id: str) -> str:
    """Upload a single binary file to the given Girder folder, verifying that
    the server-computed sha512 hash matches the local file. Returns the
    verified sha512 hash of the file."""
    if not binary_file.is_file():
        raise UploadError(f"{binary_file} does not exist or is not a regular file.")

    item_name = binary_file.name
    item_id = client.create_item(folder_id, item_name)

    print(f"Uploading {item_name}...")
    file_id = client.upload_file(item_id, item_name, binary_file)

    remote_sha512 = client.get_file_sha512(file_id)
    try:
        local_sha512 = _local_sha512(binary_file)
    except OSError as e:
        raise UploadError(f"Could not read {binary_file} to verify its hash.") from e
    if local_sha512 != remote_sha512:
        raise UploadError("Local file hash does not match uploaded file hash.")

    return remote_sha512


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Upload binary testing data for SimpleITK and related "
        "projects to data.kitware.com.",
        epilog=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument(
        "-f",
        "--folder-id",
        default=None,
        help="Girder folder id to upload to. Defaults to the user's Public folder.",
    )
    parser.add_argument(
        "--remove",
        action=argparse.BooleanOptionalAction,
        default=True,
        help="Remove the local binary file(s) after a successful upload. "
        "Use --no-remove to keep them.",
    )
    parser.add_argument(
        "binary_files",
        nargs="+",
        type=Path,
        help="Path(s), in the repository, to the binary file(s) to upload.",
    )
    args = parser.parse_args()

    client = GirderClient()
    try:
        client.authenticate()

        folder_id = args.folder_id
        if not folder_id:
            user_id = client.get_my_user_id()
            folder_id = client.get_public_folder_id(user_id)

        generated_content_links = []
        md5_content_link_conflicts = []
        for binary_file in args.binary_files:
            md5_content_link = binary_file.with_name(binary_file.name + ".md5")
            if md5_content_link.exists():
                md5_content_link_conflicts.append(md5_content_link)

            sha512 = upload_binary_file(client, binary_file, folder_id)

            sha512_content_link = binary_file.with_name(binary_file.name + ".sha512")
            try:
                sha512_content_link.write_text(sha512 + "\n")
            except OSError as e:
                raise UploadError(f"Could not write {sha512_content_link}.") from e
            generated_content_links.append(sha512_content_link)

            if args.remove:
                try:
                    binary_file.unlink()
                except OSError as e:
                    raise UploadError(f"Could not remove {binary_file}.") from e
    except UploadError as e:
        print(str(e), file=sys.stderr)
        return 1

    print("\nTesting data upload complete.\n\nNow run:\n")
    print("  git add --", " ".join(str(p) for p in generated_content_links), "\n")
    if md5_content_link_conflicts:
        print("and:\n")
        print("  git rm --", " ".join(str(p) for p in md5_content_link_conflicts))
    return 0


if __name__ == "__main__":
    sys.exit(main())
