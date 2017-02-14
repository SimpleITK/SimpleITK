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

import SimpleITK as sitk
import sys, os

if len ( sys.argv ) < 2:
    print( "Usage: DicomImagePrintTags <input_file>" )
    sys.exit ( 1 )

reader = sitk.ImageFileReader()

reader.SetFileName( sys.argv[1] )
reader.LoadPrivateTagsOn();

inputImage = reader.Execute()

for k in inputImage.GetMetaDataKeys():
    v = inputImage.GetMetaData(k)
    print("({0}) = = \"{1}\"".format(k,v))
