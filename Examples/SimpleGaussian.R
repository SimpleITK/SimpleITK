library(SimpleITK)

myreader <- ImageFileReader()
myreader <- ImageFileReader_SetFilename( myreader, "STAPLE1.png")
myimage <- ImageFileReader_Execute( myreader )

myfilter <- RecursiveGaussianImageFilter()
myfilter <- RecursiveGaussianImageFilter_SetSigma( myfilter, 2.0 )
smoothedimage <- RecursiveGaussianImageFilter_Execute( myfilter, myimage )

mywriter <- ImageFileWriter()
mywriter <- ImageFileWriter_SetFilename( mywriter, "smoothedSTAPLE1.mhd" )
mywriter <- ImageFileWriter_Execute( mywriter, smoothedimage )

