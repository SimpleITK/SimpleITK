# Run with:
#
# Rscript --vanilla SimpleGaussian.R  input sigma output
#

library(SimpleITK)

args <- commandArgs( TRUE )

myreader <- ImageFileReader()
myreader <- ImageFileReader_SetFilename( myreader, args[[1]] )
myimage <- ImageFileReader_Execute( myreader )

myfilter <- RecursiveGaussianImageFilter()
myfilter <- RecursiveGaussianImageFilter_SetSigma( myfilter, as.real(args[2]) )
smoothedimage <- RecursiveGaussianImageFilter_Execute( myfilter, myimage )

mywriter <- ImageFileWriter()
mywriter <- ImageFileWriter_SetFilename( mywriter, args[[3]] )
mywriter <- ImageFileWriter_Execute( mywriter, smoothedimage )

