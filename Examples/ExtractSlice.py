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
import sys
import os

if len ( sys.argv ) != 4:
    print( "Usage: %s inputImage sliceNumber outputImage" % ( sys.argv[0] ) )
    sys.exit ( 1 )

zslice = int( sys.argv[2] )

inputImage = sitk.ReadImage( str(sys.argv[1]) )

size = list( inputImage.GetSize() )
size[2] = 0

index = [ 0, 0, zslice  ]

Extractor = sitk.ExtractImageFilter()
Extractor.SetSize( size )
Extractor.SetIndex( index )

sitk.WriteImage( Extractor.Execute( inputImage ), str(sys.argv[3]) )


if ( not "SITK_NOSHOW" in os.environ ):
    sitk.Show( Extractor.Execute( inputImage ) )
