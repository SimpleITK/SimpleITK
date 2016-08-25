## Test image slicing operators. They need to conform to rules that are slightly
## different to those for R matrices.
##
## These rules are: spacing needs to be uniform per dimension
## i.e. im[c(1,2,11),] is not accepted
## This means that creating reflected images isn't possible
## with slicing - use slicing + Tile.
## Dropping dimensions is the default, but SimpleITK does not
## support 1D images. The slicing operator will issue a warning if
## this is attempted.
##
## The bracket operator used for slicing now constructs calls to Slice and Extract,
## rather than using special C routines. This means that the operation is multithreaded
## and preserves spacing, origin and direction.
library(SimpleITK)
slicingOperatorUnitSpacingTest<- function()
{
    ## Cropping test - unit spacing
    im <- Image(15,15,"sitkFloat64")
    im$SetSpacing(c(0.3,0.6))
    t <- 0.4
    ct <- cos(t)
    st <- sin(t)
    im$SetDirection(c(ct,-st,st,ct))

    e1 <- im[2:10,3:5]

    ef <- ExtractImageFilter()
    ef$SetSize(c(9,3))
    ef$SetIndex(c(1,2))
    e2 <- ef$Execute(im)

    ## meta-data for slicing operator should match the metadata for the extract
    ## filter which we know to be correct.
    if(!all(e1$GetOrigin() == e2$GetOrigin()))
    {
        cat("slicing operator failed, origins don't match")
        quit(save="no", status=1)
    }
    if(!all(e1$GetSpacing() == e2$GetSpacing()))
    {
        cat("slicing operator failed, spacings don't match")
        quit(save="no", status=1)
    }
    if(!all(e1$GetDirection() == e2$GetDirection()))
    {
        cat("slicing operator failed, directions don't match")
        quit(save="no", status=1)
    }
}


dirToMat <- function(im)
{
    ## produce an R formatted direction matrix
    d1 <- im$GetDirection()
    dim(d1) <- c(2,2)
    d1 <- t(d1)
    return(d1)
}
slicingOperatorNegativeSpacingTest<- function()
{
    ## Cropping test - unit spacing
    im <- Image(15,15,"sitkFloat64")
    im$SetSpacing(c(0.3,0.6))
    t <- 0.4
    ct <- cos(t)
    st <- sin(t)
    im$SetDirection(c(ct,-st,st,ct))

    e1 <- im[2:10,5:3]


    ## meta-data for slicing operator should match the metadata for the extract
    ## filter which we know to be correct.
    if(!all(e1$GetOrigin() == im$TransformIndexToPhysicalPoint(c(1,4))))
    {
        cat("slicing operator failed, origins don't match")
        quit(save="no", status=1)
    }
    d1 <- dirToMat(im)
    d2 <- dirToMat(e1)
    ## reversed the second dimension, so d2[,2] == -d1[,2]
    ## negate the second column and compare to original
    d2[,2] <- -d2[,2]
    if(!all(d1 == d2))
    {
        cat("slicing operator failed, directions incorrect")
        quit(save="no", status=1)
    }
}

slicingPositionChecks <- function()
{
    x<-rep(1:10, rep(12, 10))
    dim(x) <- c(12, 10)
    x[5:9, 6:9] <- 21
    xim <- as.image(x)

    row3 <- as.array(xim[,3,drop=FALSE])
    if (!(all(row3 == 3))) {
        cat("Incorrect pixel values - should be all 3\n")
        quit(save="no", status=1)

    }

    b <- as.array(xim[5:9, 6:9])
    if (!all(b==21)) {
        cat("Failed block extract - voxels should have value 21\n")
        quit(save="no", status=1)
    }
}
slicingOperatorWarningsErrors <- function()
{
    im <- Image(15,15,"sitkFloat64")

    ## this should issue a warning
    msg <- list()
    try(msg <- tools::assertWarning(im[1, 2:3]), silent=TRUE)
    if (length(msg) == 0) {
        cat("Slicing operator should have issued a warning, but did not.\n")
        quit(save="no", status=1)
    }
    ## Turning drop off - no warning
    msg <- list()
    try(msg <- tools::assertCondition(im[1, 2:3, ,drop=FALSE]), silent=TRUE)
    if (length(msg) != 0) {
        cat("Slicing operator issued a warning/error, but should not.\n")
        quit(save="no", status=1)
    }

    ## Irregular spacing - should issue an error
    msg <- list()
    try(msg <- tools::assertError(im[c(1,2, 4), 2:3]), silent=TRUE)
    if (length(msg) == 0) {
        cat("Slicing operator should have issued an error, but did not.\n")
        quit(save="no", status=1)
    }
}

slicingSyntaxTrials <- function()
{
    im2 <- Image(15,15,"sitkFloat64")
    im3 <- Image(15,15, 15, "sitkFloat64")

    ## slicing requires all dimensions to be included - these should produce an
    ## error
    msg <- list()
    try(msg <- tools::assertError(im3[1:2, 2:3]), silent=TRUE)
    if (length(msg) == 0) {
        cat("Slicing operator should have issued an error, but did not.\n")
        quit(save="no", status=1)
    }

    msg <- list()
    try(msg <- tools::assertError(im3[1, 2:3,drop=TRUE]), silent=TRUE)
    if (length(msg) == 0) {
        cat("Slicing operator should have issued an error, but did not.\n")
        quit(save="no", status=1)
    }
    ## this should be OK
    msg <- list()
    try(msg <- tools::assertCondition(im3[1:2, 2:3,]), silent=TRUE)
    if (length(msg) != 0) {
        cat("Slicing issued an error/warning, but should not.\n")
        quit(save="no", status=1)
    }
    msg <- list()
    try(msg <- tools::assertCondition(im3[1:2, 2:3,,drop=FALSE]), silent=TRUE)
    if (length(msg) != 0) {
        cat("Slicing issued an error/warning, but should not.\n")
        quit(save="no", status=1)
    }
    ## this should be OK
    msg <- list()
    try(msg <- tools::assertCondition(im3[1:2, ,2:3,]), silent=TRUE)
    if (length(msg) != 0) {
        cat("Slicing issued an error/warning, but should not.\n")
        quit(save="no", status=1)
    }

    ## dropping tests
    j<-im3[,,3,drop=FALSE]
    if (any(j$GetSize() != c(15, 15, 1))) {
        cat("Image slicing error - incorrect dimensions returned\n")
        cat("Expected [15, 15, 1] - got [", j$GetSize(), "]\n")
        quit(save="no", status=1)
    }
    j<-im3[,,3,drop=TRUE]
    if (any(j$GetSize() != c(15, 15))) {
        cat("Image slicing error - incorrect dimensions returned\n")
        cat("Expected [15, 15] - got [", j$GetSize(), "]\n")
        quit(save="no", status=1)
    }
    ## logical indexing, with variables
    xidx <- (1:im3$GetWidth()) > 5
    msg <- list()
    try(msg <- tools::assertCondition(im3[xidx, ,2:3]), silent=TRUE)
    if (length(msg) != 0) {
        cat("Slicing using logical issued an error/warning, but should not.\n")
        quit(save="no", status=1)
    }
}

slicingZeroIndexTrials <- function()
{
    ## various forms of indexes are illegal because we can't support
    ## an "empty" image in the way R supports an "empty" array
    im3 <- Image(15,15, 15, "sitkFloat64")

    ## error caused by calling with c()
    msg <- list()
    try(msg <- tools::assertError(im3[c(), 2:3,]), silent=TRUE)
    if (length(msg) == 0) {
        cat("Slicing operator should have issued an error, but did not.\n")
        quit(save="no", status=1)
    }
    ## check the 3rd dimension, which is handled differently to the first 2
    msg <- list()
    try(msg <- tools::assertError(im3[2:3, 2:3, c()]), silent=TRUE)
    if (length(msg) == 0) {
        cat("Slicing operator should have issued an error, but did not.\n")
        quit(save="no", status=1)
    }
    ## check 0
    msg <- list()
    try(msg <- tools::assertError(im3[2:3, 0, 2:3]), silent=TRUE)
    if (length(msg) == 0) {
        cat("Slicing operator should have issued an error, but did not.\n")
        quit(save="no", status=1)
    }
    msg <- list()
    try(msg <- tools::assertError(im3[2:3, 2:3, 0]), silent=TRUE)
    if (length(msg) == 0) {
        cat("Slicing operator should have issued an error, but did not.\n")
        quit(save="no", status=1)
    }


}
slicingOperatorUnitSpacingTest()
slicingOperatorNegativeSpacingTest()
slicingPositionChecks()
slicingSyntaxTrials()
slicingZeroIndexTrials()
