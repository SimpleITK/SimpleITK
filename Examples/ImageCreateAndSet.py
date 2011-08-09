#!/usr/bin/env python

import SimpleITK as sitk

xImg = sitk.Image( 256, 256, sitk.sitkFloat32 )
yImg = sitk.Image( 256, 256, sitk.sitkFloat32 )

for y in range( 0, xImg.GetSize()[1] ):
    for x in range( 0, xImg.GetSize()[0] ):
        xImg.SetPixel( x, y, x )
        yImg[x, y] = y


sigma = 50

xImg = sitk.SubtractConstantFrom( xImg,  xImg.GetSize()[0] / 2 )
yImg = yImg - yImg.GetSize()[1] / 2

gaussianImg = sitk.Exp( -1 * (xImg*xImg + yImg*yImg) / (2.0 * sigma**2) )

# sitk.Show( gaussianImg )
