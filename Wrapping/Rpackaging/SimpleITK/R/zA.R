.onLoad <- function(lib,pkg) {
  library.dynam("SimpleITK",pkg,lib)

  defineEnumeration('_itk__simple__PixelIDValueEnum',
                    .values = c(
                      'sitkUnknown' = -1,
                      'sitkUInt8' = RsitkUInt8(),
                      'sitkInt8' = RsitkInt8(),
                      'sitkUInt16' = RsitkUInt16(),
                      'sitkInt16' = RsitkInt16(),
                      'sitkUInt32' = RsitkUInt32(),
                      'sitkInt32' = RsitkInt32(),
                      'sitkUInt64' = RsitkUInt64(),
                      'sitkInt64' = RsitkInt64(),
                      'sitkFloat32' = RsitkFloat32(),
                      'sitkFloat64' = RsitkFloat64(),
                      'sitkComplexFloat32' = RsitkComplexFloat32(),
                      'sitkComplexFloat64' = RsitkComplexFloat64(),
                      'sitkVectorUInt8' = RsitkVectorUInt8(),
                      'sitkVectorInt8' = RsitkVectorInt8(),
                      'sitkVectorUInt16' = RsitkVectorUInt16(),
                      'sitkVectorInt16' = RsitkVectorInt16(),
                      'sitkVectorUInt32' = RsitkVectorUInt32(),
                      'sitkVectorInt32' = RsitkVectorInt32(),
                      'sitkVectorUInt64' = RsitkVectorUInt64(),
                      'sitkVectorInt64' = RsitkVectorInt64(),
                      'sitkVectorFloat32' = RsitkVectorFloat32(),
                      'sitkVectorFloat64' = RsitkVectorFloat64(),
                      'sitkLabelUInt8' = RsitkLabelUInt8(),
                      'sitkLabelUInt16' = RsitkLabelUInt16(),
                      'sitkLabelUInt32' = RsitkLabelUInt32(),
                      'sitkLabelUInt64' = RsitkLabelUInt64()
                      ))

  defineEnumeration('_itk__simple__PixelGetEnum',
                    .values = c(
                      'sitkUnknown' = -1,
                      'Image_GetPixelAsUInt8' = RsitkUInt8(),
                      'Image_GetPixelAsInt8' = RsitkInt8(),
                      'Image_GetPixelAsiUInt16' = RsitkUInt16(),
                      'Image_GetPixelAsInt16' = RsitkInt16(),
                      'Image_GetPixelAsUInt32' = RsitkUInt32(),
                      'Image_GetPixelAsInt32' = RsitkInt32(),
                      'Image_GetPixelAsUInt64' = RsitkUInt64(),
                      'Image_GetPixelAsInt64' = RsitkInt64(),
                      'Image_GetPixelAsFloat' = RsitkFloat32(),
                      'Image_GetPixelAsFloat' = RsitkFloat64()
                      ))

  defineEnumeration('_itk__simple__PixelSetEnum',
                    .values = c(
                      'sitkUnknown' = -1,
                      'Image_SetPixelAsUInt8' = RsitkUInt8(),
                      'Image_SetPixelAsInt8' = RsitkInt8(),
                      'Image_SetPixelAsiUInt16' = RsitkUInt16(),
                      'Image_SetPixelAsInt16' = RsitkInt16(),
                      'Image_SetPixelAsUInt32' = RsitkUInt32(),
                      'Image_SetPixelAsInt32' = RsitkInt32(),
                      'Image_SetPixelAsUInt64' = RsitkUInt64(),
                      'Image_SetPixelAsInt64' = RsitkInt64(),
                      'Image_SetPixelAsFloat' = RsitkFloat32(),
                      'Image_SetPixelAsFloat' = RsitkFloat64()
                      ))

}

                                        # experimental bracket operator for images
setMethod('[', "_p_itk__simple__Image",
          function(x,i, j, k, drop=TRUE) {
                                        # check to see whether this is returning a single number or an image
            m <- sys.call()

            imdim <- Image_GetDimension(x)
            if ((length(m)-2) < imdim)
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
            if (missing(k)) {
              k <- 1:imsize[3]
            } else {
              k <- (1:imsize[3])[k]
            }


            if (any(is.na(c(i,j,k)))) {
              stop("Indexes out of range")
            }
            i <- i - 1
            j <- j - 1
            k <- k - 1
            if ((length(i) == 1) & (length(j) == 1) & (length(k) == 1) ) {
              ## return a single point
              pixtype <- x$GetPixelIDValue()
              afName <- enumFromInteger(pixtype, "_itk__simple__PixelGetEnum")
              aF <- get(afName)
              if (!is.null(aF)) {
                ## need to check whether we are using R or C indexing.
                return(aF(x, c(i, j,k)))
              }
            } else {
              ## construct and return an image
              pixtype <- x$GetPixelIDValue()
              resIm <- SingleBracketOperator(i,j,k,x)
              return(resIm);
            }

          }

          )

setMethod('as.array', "_p_itk__simple__Image",
          function(x, drop=TRUE) {
            sz <- x$GetSize()
            if (.hasSlot(x, "ref")) x = slot(x,"ref")
            ans = .Call("R_swig_ImAsArray", x, FALSE, PACKAGE = "SimpleITK")
            dim(ans) <- sz
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
