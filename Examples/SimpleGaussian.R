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
# Run with:
#
# Rscript --vanilla SimpleGaussian.R  input sigma output
#

library(SimpleITK)

args <- commandArgs( TRUE )

myreader <- ImageFileReader()
myreader <- ImageFileReader_SetFileName( myreader, args[[1]] )
myimage <- ImageFileReader_Execute( myreader )

pixeltype <- Image_GetPixelIDValue( myimage )

myfilter <- SmoothingRecursiveGaussianImageFilter()
myfilter <- SmoothingRecursiveGaussianImageFilter_SetSigma( myfilter, as.real(args[2]) )
smoothedimage <- SmoothingRecursiveGaussianImageFilter_Execute( myfilter, myimage )

mycaster <- CastImageFilter()
mycaster <- CastImageFilter_SetOutputPixelType( mycaster, pixeltype )
castedimage <- CastImageFilter_Execute( mycaster, soothedimage )

mywriter <- ImageFileWriter()
mywriter <- ImageFileWriter_SetFileName( mywriter, args[[3]] )
mywriter <- ImageFileWriter_Execute( mywriter, castedimage )

