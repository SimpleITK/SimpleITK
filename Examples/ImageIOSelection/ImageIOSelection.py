#!/usr/bin/env python
#=========================================================================
#
#  Copyright Insight Software Consortium
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

from __future__ import print_function

import sys
import SimpleITK as sitk


if len(sys.argv)<2:
    print('Wrong number of arguments.', file=sys.stderr)
    print('Usage: ' + __file__ + ' image_file_name', file=sys.stderr)
    sys.exit(1)

# Find out which image IOs are supported
file_reader = sitk.ImageFileReader()
image_ios_tuple = file_reader.GetRegisteredImageIOs()
print("The supported image IOs are: " + str(image_ios_tuple))
print('-'*20)

# Another option is to just print the reader and see which
# IOs are supported
print(file_reader)
print('-'*20)

# Force the use of a specific IO. If the IO doesn't support
# reading the image type it will throw an exception.
file_reader.SetImageIO('PNGImageIO')
file_reader.SetFileName(sys.argv[1])
try:
    image = file_reader.Execute()
    print('Read image: ' + sys.argv[1])
except Exception as err:
    print('Reading failed: ', err)
    sys.exit(1)

sys.exit(0)
