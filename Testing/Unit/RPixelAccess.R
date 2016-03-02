## tests of image pixel access.
## helps to check whether the rtype entries for std:vector in R.i are OK.
library(SimpleITK)

## generate a test image with 2 components.
pp <- PhysicalPointImageSource()
x <- Image(c(25,25), 'sitkUInt8')
pp$SetReferenceImage(x)
fr <- pp$Execute()

## first component has rows with equal value, starting from 0.
## second component has columns with equal value, stating from 0.
# cast to lots of different types
targs <- c("sitkVectorUInt8", "sitkVectorInt8", "sitkVectorUInt16",
           "sitkVectorInt16", "sitkVectorUInt32", "sitkVectorInt32",
           "sitkVectorUInt64", "sitkVectorInt64", "sitkVectorFloat32",
           "sitkVectorFloat64")
names(targs) <- targs
castims <- lapply(targs, function(m)Cast(fr, m))
res<-list()
pixvals <- list()

vectorextract <- sapply(castims, function(K)K[3,4])
channelextract <- sapply(castims, function(K)K[[1]][3,4])

if (any(vectorextract[1,] != 2) | any(vectorextract[2,] != 3))
{
    cat("Failure in vector extraction\n")
    cat("Pixel type :", targs[(vectorextract[1,] != 2) |
                              (vectorextract[2,] != 3)], "\n")
    quit(save="no", status=1)
}

if (any(channelextract != 2) )
{
    cat("Failure in channel extraction\n")
    cat("Pixel type: ", targs[channelextract != 2], "\n")
    quit(save="no", status=1)
}
