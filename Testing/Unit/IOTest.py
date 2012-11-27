#==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================*/
from __future__ import print_function

import SimpleITK as sitk
import sys

# this test is suppose to test the python interface to the IO classs

if len ( sys.argv ) != 2:
    print( "Usage: %s outputPath" % ( sys.argv[0] ) )

outputPath = sys.argv[1]

image = sitk.Image( 10, 10, sitk.sitkInt32 )


try:
    sitk.WriteImage( image, "this.isafilenamewithnoimageio" )
except RuntimeError as e:
    print( "Caught expected error" )
