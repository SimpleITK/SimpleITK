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


import SimpleITK
import sys

if len ( sys.argv ) < 4:
    print "Usage: MathematicalMorphology <input> <operation> <output>";
    print "operation: 0=binary erode, 1=binary dilate, 2=grayscale erode, 3=grayscale dilate";
    sys.exit ( 1 )

reader = SimpleITK.ImageFileReader()
reader.SetFileName ( sys.argv[1] )
image = reader.Execute();

print image.ToString()

morphoMath = SimpleITK.MathematicalMorphologyImageFilter()
morphoMath.SetOperation ( int ( sys.argv[2] ) )
image = morphoMath.Execute ( image );

print image.ToString()

writer = SimpleITK.ImageFileWriter()
writer.SetFileName ( sys.argv[3] )
writer.Execute ( image );

