## tests of image pixel access.
## helps to check whether the rtype entries for std:vector in R.i are OK.
library(SimpleITK)

imsize <- 64
img1 = Image(imsize, imsize, "sitkFloat32")
img2 = Image(imsize, imsize, "sitkFloat32")

arglist <- list(img1, img2, img1)

h<-Tile(arglist, c(length(arglist),1))
sz <- h$GetSize()

if (any(sz != c(imsize*length(arglist), imsize)))
{
    cat("Failure in tiling with image list arguments\n")
    quit(save="no", status=1)
}
