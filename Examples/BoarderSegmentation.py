#!/usr/bin/env python

import sys
import SimpleITK as sitk

# verify that we have the correct number of arguments
if ( len( sys.argv ) != 5 ):
    sys.stderr.write( "Usage: prog inputFile outputFile replaceValue upperThreshold\n" )
    exit( 1 )
    
# copy the arguments in to variables
inputFileName = sys.argv[1]
outputFileName = sys.argv[2]
replaceValue = int( sys.argv[3] )
upperThreshold = float( sys.argv[4] )

# Read the file into an sitkImage
image = sitk.ReadImage( inputFileName )

# Threshold the value [0,2), results in values inside the range 1, 0 otherwise
boundary = sitk.BinaryThreshold( image, 0, upperThreshold, 1, 0 )

boundary = sitk.BinaryMorphologicalClosing( boundary, 1 )

# Remove any label pixel not connected to the boarder
boundary = sitk.BinaryGrindPeak( boundary )



boundary = sitk.Cast( boundary, image.GetPixelIDValue() )

# Multiply, the input image by not the boarder.
# This will multiply the image by 0 or 1, where 0 is the
# boarder. Making the board 0
image = image * ~boundary

# add the replace value to the pixel on the board
image = image + ( boundary * replaceValue )

# sitk.Show( image )
