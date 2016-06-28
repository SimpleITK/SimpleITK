redefineEnumeration <- function(enumerationName, the.function)
{
    current.enum <- get(paste(".__E__", enumerationName, sep = ""))
    the.names <- names(current.enum)
    values <- sapply(the.names, the.function)

    if (any(values== -99))
    {
        warning("Some enumeration names are not recognised\n")
    }
    names(values) <- the.names
    defineEnumeration(enumerationName, values)
}

.onLoad <- function(lib,pkg) {
  library.dynam("SimpleITK",pkg,lib)
  redefineEnumeration('_itk__simple__PixelIDValueEnum', GetPixelIDValueFromString)

  createPixLookup()
}

createPixLookup <- function( where = topenv(parent.frame()))
{
    m <- get(".__E___itk__simple__PixelIDValueEnum")
    # get rid of unknown type - can't access anyway. There will be errors if
    # it happens.
    # Also need to map Float32 to Float and Float64 to Double
    m <- m[m>=0]
    n <- names(m)
    # Turn the names into function names
    ff <- gsub("^sitk(.+)", "Image_GetPixelAs\\1", n)
    ff <- gsub("AsFloat32$", "AsFloat", ff)
    ff <- gsub("AsFloat64$", "AsDouble", ff)
    ff <- gsub("Label", "", ff)
    sitkPixelAccessMap <-  mget(ff, envir=where,
                                ifnotfound=rep(NA,length(ff)))
    ff2 <- gsub("GetPixelAs", "SetPixelAs", ff)
    sitkPixelSetMap <- mget(ff2, envir=where,
                                ifnotfound=rep(NA,length(ff)))

    names(sitkPixelAccessMap) <- n
    names(sitkPixelSetMap) <- n
    assign("sitkPixelAccessMap", sitkPixelAccessMap, envir=where)
    assign("sitkPixelSetMap", sitkPixelSetMap, envir=where)
}

ImportPixVec <- function(VP)
{
    ## some pixel vectors aren't automatically converted to
    ## R vectors, so we'll do it the long way to avoid having to
    ## write new swig fragments dealing with

    ## some pixel vectors work as expected - return them
    if (is.numeric(VP)) return(VP)

    l <- VP$'__len__'()
    res <- rep(NA, l)
    for (idx in 1:l) {
        res[idx] <- VP$'__getitem__'(idx-1)
    }
    return(res)
}

## SetPixel and GetPixel methods. We've provided dummy "extends" methods for these.
## We'll overwite the bindings here
Image_SetPixel = function(self, idx, v)
{
  idx = as.integer(idx);
  ## check that the size of v matches the image pixel type
  if (Image_GetNumberOfComponentsPerPixel(self) != length(v))
  {
      ## It seems that passing incorrect size values doesn't
      ## cause a c++ error, so check here. Swig must
      ## cleverly pass just the first element.
      stop("Error in SetPixel - value does not match image depth")
  }
  PixType <- Image_GetPixelID(self)
  sF <- sitkPixelSetMap[[PixType]]
  if (!is.null(sF)) {
      invisible(sF(self, idx, v))
  } else {
      stop("Error in SetPixel - no accessor function for this pixel type")
  }
}

attr(`Image_SetPixel`, 'returnType') = 'void'
attr(`Image_SetPixel`, "inputTypes") = c('_p_itk__simple__Image', 'integer', 'numeric')
class(`Image_SetPixel`) = c("SWIGFunction", class('Image_SetPixel'))

Image_GetPixel = function(self, idx, .copy = FALSE)
{
  idx = as.integer(idx);
  PixType <- Image_GetPixelID(self)
  aF <- sitkPixelAccessMap[[PixType]]
  if (!is.null(aF)) {
      return(aF(self, idx))
  } else {
      stop("Error in GetPixel - no accessor function for this pixel type")
  }
}

attr(`Image_GetPixel`, 'returnType') = 'numeric'
attr(`Image_GetPixel`, "inputTypes") = c('_p_itk__simple__Image', 'integer')
class(`Image_GetPixel`) = c("SWIGFunction", class('Image_GetPixel'))

## experimental bracket operator for images
setMethod('[',
          signature=c(x="_p_itk__simple__Image", i="ANY", j="ANY"),
          function(x,i, j, ..., drop=TRUE) {
              m <- sys.call()
              args = as.list(m[-c(1L, 2L)])
              numIndices = length(args) - !is.null(args$drop)
              imdim <- Image_GetDimension(x)
              if (numIndices < imdim)
              {
                  stop("Image has more dimensions")
              }
              imsize <- rep(1, 5)
              imsize[1:imdim] <- Image_GetSize(x)
              if (missing(i)) {
                  i <- 1:imsize[1]
              } else {
                  i <- (1:imsize[1])[i]
              }
              if (missing(j)) {
                  j <- 1:imsize[2]
              } else {
                  j <- (1:imsize[2])[j]
              }
              if (numIndices >= 3) {
                  k <- args[[3]]
                  if (missing(k)) {
                      k <- 1:imsize[3]
                  } else {
                      k <- (1:imsize[3])[eval.parent(k)]
                  }
              } else {
                  k <- 1
              }
              if (numIndices >=4) {
                  l <- args[[4]]
                  if (missing(l)) {
                      l <- 1:imsize[4]
                  } else {
                      l <- (1:imsize[4])[eval.parent(l)]
                  }
              } else {
                  l <- 1
              }
              if (any(is.na(c(i,j,k, l)))) {
                  stop("Indexes out of range")
              }
              i <- i - 1
              j <- j - 1
              k <- k - 1
              lenI <- length(i)
              lenJ <- length(j)
              lenK <- length(k)
              lenL <- length(l)

              ll <- c(lenI, lenJ, lenK, lenL)
              ## check for 0, c() indexes and flag an error
              if (any(ll==0) ) {
                  stop("Illegal 0 or empty index in image slicing\n")
              }
             ## check to see whether this is returning a single number or an image
            if (all(ll == 1)) {
              ## return a single point
              pixtype <- x$GetPixelID()
              aF <- sitkPixelAccessMap[[pixtype]]
              if (!is.null(aF)) {
                ## need to check whether we are using R or C indexing.
                return(ImportPixVec(aF(x, c(i, j,k, l))))
              }
            } else {
              ## create call to SliceImageFilter
              ## Check index spacing is uniform
              dx <- diff(i)
              if (!(all(dx==dx[1]))) {
                  stop("X spacing is not uniform\n")
              }
              dy <- diff(j)
              if (!all(dy==dy[1])) {
                  stop("Y spacing is not uniform\n")
              }
              dz <- diff(k)
              if (!all(dz==dz[1])) {
                  stop("Z spacing is not uniform\n")
              }
              dt <- diff(l)
              if (!all(dt==dt[1])) {
                  stop("T spacing is not uniform\n")
              }
              start <- c(i[1], j[1], k[1], l[1])
              step <- c(dx[1], dy[1], dz[1], dt[1])
              ## deal with single row/column
              step[is.na(step)] <- 1
              finish <- c(i[lenI], j[lenJ], k[lenK], l[lenK]) + step
              resIm <- Slice(x, start, finish, step)
              ## Drop dimensions
              sz <- Image_GetSize(resIm)
              if (drop & any(sz==1)) {
                  sz[sz==1] <- 0
                  if (sum(sz != 0) > 1) {
                      resIm <- Extract(resIm, sz)
                  } else {
                      warning("Cannot return 1D image - returning image with some dimensions=1")
                  }
              }
              return(resIm);
            }

          }

          )

setMethod('[[', "_p_itk__simple__Image",
          function(x, i, j, ...) {
              return(VectorIndexSelectionCast(x, i-1)) 
          }
          )

setMethod('as.array', "_p_itk__simple__Image",
          function(x, drop=TRUE) {
            sz <- x$GetSize()
            components <- x$GetNumberOfComponentsPerPixel()
            if (components > 1) sz <- c(components, sz)
            if (.hasSlot(x, "ref")) x = slot(x,"ref")
            ans = .Call("R_swig_ImAsArray", x, FALSE, PACKAGE = "SimpleITK")
            dim(ans) <- sz
            if (components > 1) {
                ## vector images have planes stored next to each other.
                ## place in separate planes for sensible display
                perm <- c(2:length(sz), 1)
                ans <- aperm(ans, perm)
            }
            if (drop)
              return(drop(ans))
            return(ans)

            }
          )

as.image <- function(arr, spacing=rep(1, length(dim(arr))),
                     origin=rep(0,length(dim(arr))))
  {
    size <- dim(arr)
    return(ArrayAsIm(arr, size, spacing,origin))
  }
