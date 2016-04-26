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

## Test the methods introduced via the "extend" mechanism

vectorextractGet <-sapply(castims, function(K)K$GetPixel(c(3,4)-1))
channelextractGet <- sapply(castims, function(K)K[[1]]$GetPixel(c(3,4)-1))

if (any(vectorextractGet[1,] != 2) | any(vectorextractGet[2,] != 3))
{
    cat("Failure in vector extraction using GetPixel\n")
    cat("Pixel type :", targs[(vectorextractGet[1,] != 2) |
                              (vectorextractGet[2,] != 3)], "\n")
    quit(save="no", status=1)
}

## testing reading scalar
if (any(channelextractGet != 2) )
{
    cat("Failure in channel extraction\n")
    cat("Pixel type: ", targs[channelextractGet != 2], "\n")
    quit(save="no", status=1)
}

## Test the SetPixel method - this tests setting vector
## recreate castims so we can write to it
castims <- lapply(targs, function(m)Cast(fr, m))

sapply(castims, function(K)K$SetPixel(c(0,0), c(10,11)))
VecModified <- sapply(castims, function(K)K$GetPixel(c(0,0)))
if (any(VecModified[1,] != 10) | any(VecModified[2,] != 11) )
{
    cat("Failure in SetPixel vector test\n")
    cat("Pixel type: ", targs[(VecModified[1,] != 10) | (VecModified[2,] != 11)], "\n")
    quit(save="no", status=1)
}

## Test the SetPixel method - this tests setting scalar
## recreate castims so we can write to it
castims <- lapply(targs, function(m)Cast(fr, m))

FirstChannel <- lapply(castims, function(K)K[[1]])
sapply(FirstChannel, function(K)K$SetPixel(c(0,0), 12))
channelModified <- sapply(FirstChannel, function(K)K$GetPixel(c(0,0)))
if (any(channelModified != 12) )
{
    cat("Failure in SetPixel scalar test\n")
    cat("Pixel type: ", targs[channelModified != 12], "\n")
    quit(save="no", status=1)
}

## Test label pixels
labtargs <- c("sitkLabelUInt8", "sitkLabelUInt16", "sitkLabelUInt32", "sitkLabelUInt64")
names(labtargs) <- labtargs

labims <- lapply(labtargs, function(tt)Image(c(5,5), tt))

l <- lapply(labims, function(K)K$SetPixel(c(1,2), 7))
labvals <- sapply(labims, function(K)K$GetPixel(c(1,2)))

if (any(labvals != 7))
{
    cat("Failure in SetPixel/GetPixel label test\n")
    print(labvals)
    quit(save="no", status=1)
}
