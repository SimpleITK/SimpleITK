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

