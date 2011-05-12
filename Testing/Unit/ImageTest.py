import SimpleITK as sitk
import sys

# this test is suppose to test the python interface to the sitk::Image


image = sitk.Image( 10, 10, sitk.sitkInt32 )

image + image
image + 1
1 + image
image - image
image - 1
1 - image
image * image
image * 1
1 * image
image / image
image / 1
1 / image
image & image
image | image
image ^ image
~image

image += image
image -= image
image *= image
image /= image

image = image * 0

image.SetPixel( 0, 0, 1 )
image[ [0,1] ]  = 2
image[ 9,9 ]  = 3

image.GetPixel( 1,1 )
#image.GetPixel( [1,1] )
image[1,1]
image[ [ 1,1 ] ]

if sum(image) != 6:
    print "image sum not 6"
    sys.exit( 1 )

if len( image ) != 100:
    print "len not 100!"
    sys.exit(1)
