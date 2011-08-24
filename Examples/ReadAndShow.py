#!/usr/bin/env python

import SimpleITK as sitk
import sys

if len ( sys.argv ) != 2:
    print "Usage: %s inputImage" % ( sys.argv[0] )
    sys.exit ( 1 )

inputImage = sitk.ReadImage( sys.argv[1] )

sitk.Show( inputImage )
