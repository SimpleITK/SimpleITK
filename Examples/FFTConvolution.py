#!/usr/bin/env python

import SimpleITK as sitk
import sys

if len ( sys.argv ) < 4:
    print "Usage: FFTConvolution <input> <kernel> <output>";
    sys.exit ( 1 )


inputFileName = sys.argv[1]
kernelFileName = sys.argv[2]
outputFileName = sys.argv[3]

### Input Image ###
# read the input image
img = sitk.ReadImage( inputFileName )

# save the type of pixel the input is, so that we can cast the result
# back out to the same type  
pixelID = img.GetPixelIDValue()

# pad the image 
img = sitk.MirrorPad( img, [128] *2, [128]*2 )
size = img.GetSize();

# perform the FFT
fftimg = sitk.FFTRealToComplexConjugate( sitk.Cast( img, sitk.sitkFloat32 ) )


### Kernel Image ###
# Read the kernel image file
kernel = sitk.ReadImage( kernelFileName )

# flip kernel about all axis
kernel = sitk.Flip( kernel, [1]*2 )


# normalize the kernel to sum to ~1
stats = sitk.StatisticsImageFilter();
stats.Execute( kernel )
kernel = sitk.Cast( kernel , sitk.sitkFloat32 ) / stats.GetSum()

padding = [0]*2
padding[0] = (size[0] - kernel.GetSize()[0])/2
padding[1] = (size[1] - kernel.GetSize()[1])/2

# pad the kernel to prevent edge artifacts
kernel = sitk.ConstantPad( kernel, padding, padding, 0.0 )

# perform FFT on kernel
fftkernel = sitk.FFTRealToComplexConjugate( sitk.FFTShift( kernel ) )

### Convolution ###
# Finally perform the convolution in Fourier space by multiplication
img =  sitk.FFTComplexConjugateToReal( fftimg*fftkernel )

# remove the padding
img = sitk.Crop( img, [128]*2, [128]*2 )

### Writing ###
# write the output image the same type as the input
sitk.WriteImage( sitk.Cast( img, pixelID ), outputFileName )
