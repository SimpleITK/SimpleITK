#!/usr/bin/env python

import SimpleITK as sitk
import sys

if len ( sys.argv ) != 4:
    print "Usage: %s inputImage sliceNumber outputImage" % ( sys.argv[0] )
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
