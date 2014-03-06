'''=========================================================================
'
'  Copyright Insight Software Consortium
'
'  Licensed under the Apache License, Version 2.0 (the "License");
'  you may not use this file except in compliance with the License.
'  You may obtain a copy of the License at
'
'         http://www.apache.org/licenses/LICENSE-2.0.txt
'
'  Unless required by applicable law or agreed to in writing, software
'  distributed under the License is distributed on an "AS IS" BASIS,
'  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
'  See the License for the specific language governing permissions and
'  limitations under the License.
'
'========================================================================='''

from __future__ import print_function

import SimpleITK as sitk
import sys
import os

#
# Check Command Line
#
if len( sys.argv ) < 7:
  print("Usage: ConnectedThresholdImageFilter inputImage outputImage lowerThreshold upperThreshold seedX seedY [seed2X seed2Y ... ]");
  sys.exit( 1 )


#
# Read the image
#
reader = sitk.ImageFileReader()
reader.SetFileName( sys.argv[1] )
image = reader.Execute();

#
# Blur using CurvatureFlowImageFilter
#
blurFilter = sitk.CurvatureFlowImageFilter()
blurFilter.SetNumberOfIterations( 5 )
blurFilter.SetTimeStep( 0.125 )
image = blurFilter.Execute( image )

#
# Set up ConnectedThresholdImageFilter for segmentation
#
segmentationFilter = sitk.ConnectedThresholdImageFilter()
segmentationFilter.SetLower( float(sys.argv[3]) )
segmentationFilter.SetUpper( float(sys.argv[4]) )
segmentationFilter.SetReplaceValue( 255 )

for i in range( 5, len(sys.argv)-1, 2 ):
  seed = [ int(sys.argv[i]), int(sys.argv[i+1]) ]
  segmentationFilter.AddSeed( seed )
  print( "Adding seed at: ", seed, " with intensity: ", image.GetPixel(*seed) )

# Run the segmentation filter
image = segmentationFilter.Execute( image )
image[seed] = 255

#
# Write out the result
#
writer = sitk.ImageFileWriter()
writer.SetFileName( sys.argv[2] )
writer.Execute( image )


if ( not "SITK_NOSHOW" in os.environ ):
  sitk.Show( image, "ConntectedThreshold" )

