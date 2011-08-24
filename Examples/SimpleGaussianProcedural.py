#!/usr/bin/env python

import SimpleITK as sitk
import sys

if len ( sys.argv ) < 4:
    print "Usage: %s <input> <sigma> <output>" % ( sys.argv[0] )
    sys.exit ( 1 )


image = sitk.ReadImage( sys.argv[1] )

pixelID = image.GetPixelIDValue()

image  = sitk.SmoothingRecursiveGaussian( image,  float( sys.argv[2] ) )

sitk.WriteImage( sitk.Cast( image, pixelID ), sys.argv[3] )
