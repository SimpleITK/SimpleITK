#!/usr/bin/env python
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

import hashlib
import argparse
import re
import os

parser = argparse.ArgumentParser(
    description="Given a list of python wheels, generate a list of hyperlinks to GitHub with sha512 fragment identifier"
)
parser.add_argument("--hash", choices=["md5", "sha256", "sha512"], default="sha512")
parser.add_argument("-f", "--format", choices=["gh", "html", "md"], default="html")
parser.add_argument( "-t","--tag", type=str, default=None)
parser.add_argument(
    "files", metavar="python.whl", type=argparse.FileType(mode="rb"), nargs="+"
)


args = parser.parse_args()


for f in args.files:
    try:
        name = os.path.basename(f.name)

        if args.hash == "md5":
            hash_value = hashlib.md5(f.read()).hexdigest()
        elif args.hash == "sha256":
            hash_value = hashlib.sha256(f.read()).hexdigest()
        elif args.hash == "sha512":
            hash_value = hashlib.sha512(f.read()).hexdigest()

        if args.tag:
            tag = args.tag
        else:
            # version="1.1.0"
            version = re.match(
                r"SimpleITK-([0-9]+\.[0-9]+(\.[0-9]+)?(rc[0-9]+)?)", name, re.IGNORECASE
            ).group(1)
            tag = f"v{version}"

        host = "GitHub"
        url = f"https://github.com/SimpleITK/SimpleITK/releases/download/{tag}/{name}#{args.hash}={hash_value}"

        if args.format == "html":
            print(
                f'<li><a href="{url}" title="Click to download {name}">{name} (hosted at {host})</a></li>'
            )
        elif args.format == "md":
            print(f"[{name}]({url})")
        elif args.format == "gh":
            # print the URL in an HTML anchor with no new line to stdout
            print(f"<a href=\"{url}\" ></a>", end="")



    finally:
        f.close()
