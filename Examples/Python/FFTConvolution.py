#!/usr/bin/env python
#=========================================================================
#
#  Copyright Insight Software Consortium
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#=========================================================================

from __future__ import print_function
from __future__ import division

import SimpleITK as sitk
import sys
import os
import math

if len ( sys.argv ) < 4:
    print( "Usage: FFTConvolution <input> <kernel> <output>" )
    sys.exit ( 1 )


inputFileName = sys.argv[1]
kernelFileName = sys.argv[2]
outputFileName = sys.argv[3]

### Input Image ###
# read the input image
img = sitk.ReadImage( inputFileName )

# save the type of pixel the input is, so that we can cast the result
# back out to the same type  
pixelID = img.GetPixelID()

# pad the image 
img = sitk.MirrorPad( img, [128] *2, [128]*2 )
size = img.GetSize();

# perform the FFT
fftimg = sitk.ForwardFFT( sitk.Cast( img, sitk.sitkFloat32 ) )


### Kernel Image ###
# Read the kernel image file
kernel = sitk.ReadImage( kernelFileName )

# flip kernel about all axis
kernel = sitk.Flip( kernel, [True]*2 )


# normalize the kernel to sum to ~1
stats = sitk.StatisticsImageFilter();
stats.Execute( kernel )
kernel = sitk.Cast( kernel / stats.GetSum(), sitk.sitkFloat32 )

upadding = [0]*2
upadding[0] = int( math.floor( (size[0] - kernel.GetSize()[0])/2.0 ) )
upadding[1] = int( math.floor( (size[1] - kernel.GetSize()[1])/2.0 ) )

lpadding = [0]*2
lpadding[0] = int( math.ceil( (size[0] - kernel.GetSize()[0])/2.0 ) )
lpadding[1] = int( math.ceil( (size[1] - kernel.GetSize()[1])/2.0 ) )

# pad the kernel to prevent edge artifacts
kernel = sitk.ConstantPad( kernel, upadding, lpadding, 0.0 )

# perform FFT on kernel
fftkernel = sitk.ForwardFFT( sitk.FFTShift( kernel ) )

# meta-data must match for multiplication
fftkernel.SetSpacing( fftimg.GetSpacing() )
fftkernel.SetOrigin( fftimg.GetOrigin() )
fftkernel.SetDirection( fftimg.GetDirection() )


### Convolution ###
# Finally perform the convolution in Fourier space by multiplication
img =  sitk.InverseFFT( fftimg*fftkernel )

# remove the padding
img = sitk.Crop( img, [128]*2, [128]*2 )

### Writing ###
# write the output image the same type as the input
sitk.WriteImage( sitk.Cast( img, pixelID ), outputFileName )



if ( not "SITK_NOSHOW" in os.environ ):
    sitk.Show( sitk.ReadImage( inputFileName ), "original" )
    sitk.Show( sitk.ReadImage( kernelFileName ), "kernel" )
    sitk.Show( sitk.Cast( img, pixelID ), "FFT_Convolution" )
