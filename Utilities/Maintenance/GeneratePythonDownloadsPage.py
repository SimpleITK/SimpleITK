#!/usr/bin/env python
#=========================================================================
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
#=========================================================================

import hashlib
import argparse
import re
import os

parser = argparse.ArgumentParser( description="Given a list of python wheels, generate a list of hyperlinks to GitHub with sha512 fragment identifier" )
parser.add_argument( '--hash', choices=['md5','sha256', 'sha512'], default='sha512')
parser.add_argument( '-f', '--format', choices=['html','md'], default='html')
parser.add_argument( 'files', metavar="python.whl", type=argparse.FileType(mode='rb'), nargs='+' )


args = parser.parse_args()


for f in args.files:
    name = os.path.basename(f.name)
    #version="1.1.0"
    version = re.match(r'SimpleITK-([0-9]+\.[0-9]+(\.[0-9]+)?(rc[0-9]+)?)', name ).group(1)
    print("version:{0}".format(version))
    if args.hash == "md5":
       hash_value = hashlib.md5(f.read()).hexdigest()
    elif args.hash == "sha256":
       hash_value = hashlib.sha256(f.read()).hexdigest()
    elif args.hash == "sha512":
       hash_value = hashlib.sha512(f.read()).hexdigest()


    tag = "v{0}".format(version)

    #host="SourceForge"
    #url = "https://sourceforge.net/projects/simpleitk/files/SimpleITK/{0}/Python/{1}#{2}={3}".format(version,name,args.hash,hash_value)

    host = "GitHub"
    url = "https://github.com/SimpleITK/SimpleITK/releases/download/{0}/{1}#{2}={3}".format(tag,name,args.hash,hash_value)

    if args.format == 'html':
        print "<li><a href=\"{0}\" title=\"Click to download {1}\">{1} (hosted at {2})</a></li>".format(url,name,host)
    elif args.format == 'md':
        print "[{1}]({0})".format(url,name)

    f.close()
