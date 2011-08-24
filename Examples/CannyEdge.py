#!/usr/bin/env python

import SimpleITK as sitk
import sys

if len ( sys.argv ) < 2:
    print "Usage: %s <input>" % ( sys.argv[0] )
    sys.exit ( 1 )


image = sitk.Cast( sitk.ReadImage( sys.argv[1] ), sitk.sitkFloat32 ) 

edges = sitk.CannyEdgeDetection( image, 100, 300, [4]*3 )

stats = sitk.StatisticsImageFilter()
stats.Execute( image )

# sitk.Show( sitk.Maximum( image, edges*stats.GetMaximum()*.5) )

