#!/usr/bin/env python

import SimpleITK as sitk
import sys

if len ( sys.argv ) < 2:
    print "Usage: N4BiasFieldCorrection inputImage " + \
        "outputImage [shrinkFactor] [maskImage] [numberOfIterations] " +\
        "[numberOfFittingLevels] [outputBiasField]"
    sys.exit ( 1 )




inputImage = sitk.ReadImage( sys.argv[1] )


if len ( sys.argv ) > 4:
    maskImage = sitk.ReadImage( sys.argv[4] )
else:
    maskImage = sitk.OtsuThreshold( inputImage, 0, 1, 200 )

if len ( sys.argv ) > 3:
    inputImage = sitk.Shrink( inputImage, [ int(sys.argv[3]) ] * inputImage.GetDimension() )
    maskImage = sitk.Shrink( maskImage, [ int(sys.argv[3]) ] * inputImage.GetDimension() )

inputImage = sitk.Cast( inputImage, sitk.sitkFloat32 )

corrector = sitk.N4MRIBiasFieldCorrectionImageFilter();

if len ( sys.argv ) > 5:
    corrector.SetMaximumNumberOfIterations( int( sys.argv[5] ) )

if len ( sys.argv ) > 6:
    corrector.SetNumberOfFittingLevels( int( sys.argv[6]  ) )


output = corrector.Execute( inputImage, maskImage )    

sitk.WriteImage( output, sys.argv[2] )
