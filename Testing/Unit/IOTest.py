import SimpleITK as sitk
import sys

# this test is suppose to test the python interface to the IO classs

if len ( sys.argv ) != 2:
    print "Usage: %s outputPath" % ( sys.argv[0] )

outputPath = sys.argv[1]

image = sitk.Image( 10, 10, sitk.sitkInt32 )


try:
    sitk.WriteImage( image, "this.isafilenamewithnoimageio" )
except RuntimeError as e:
    print "Caught expected error"
