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

import SimpleITK
import sys

if __name__ == '__main__':
  
  #
  # Check Command Line
  #
  if len( sys.argv ) < 7:
    print "Usage: NeighborhoodConnectedImageFilter inputImage outputImage lowerThreshold upperThreshold seedX seedY [seed2X seed2Y ... ]";
    sys.exit( 1 )
  
  
  #
  # Read the image
  #
  reader = SimpleITK.ImageFileReader()
  reader.SetFilename( sys.argv[1] )
  image = reader.Execute();
  
  #
  # Set up the writer
  #
  writer = SimpleITK.ImageFileWriter()
  writer.SetFilename( sys.argv[2] )
  
  #
  # Blur using CurvatureFlowImageFilter
  #
  blurFilter = SimpleITK.CurvatureFlowImageFilter()
  blurFilter.SetNumberOfIterations( 5 )
  blurFilter.SetTimeStep( 0.125 )
  image = blurFilter.Execute( image )
  
  #
  # Set up NeighborhoodConnectedImageFilter for segmentation
  #
  segmentationFilter = SimpleITK.NeighborhoodConnectedImageFilter()
  segmentationFilter.SetLower( float(sys.argv[3]) )
  segmentationFilter.SetUpper( float(sys.argv[4]) )
  segmentationFilter.SetReplaceValue( 255 )
  
  radius = [2,2]
  segmentationFilter.SetRadius( radius )
  
  for i in range( 5, len(sys.argv)-1, 2 ):
    seed = [int(sys.argv[i]), int(sys.argv[i+1])]
    segmentationFilter.AddSeed( seed )
    print "Adding seed at " + str(seed)
  
  # Run the segmentation filter
  image = segmentationFilter.Execute( image )
  
  #
  # Write out the result
  #
  writer.Execute( image )
  
  sys.exit(0)
  
  
  
  
