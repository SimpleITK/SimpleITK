#' this a first test whether it is possible to call SimpleITK via Rcpp
#'
#' this a first test whether it is possible to call SimpleITK via Rcpp. It simply shows how to change the origin of a sitk::Image using SimpleITK's C++ interface.
#' @param image image of class
#' @param origin vector of length image$GetDimension()
#' @return returns the image dimension
#' @examples
#' require(SimpleITK)
#' img <- Image(10,10,10,"sitkInt8")
#' img <-test(img,1:3)
#' chk <- stopifnot(all.equal(img$GetOrigin(),1:3))
#' if (is.null(chk)) cat("\n  ***** test passed without an error *****\n\n")
#' @useDynLib SimpleITKCxx
#' @import SimpleITK
#' @export 
test <- function(image,origin=NULL) {
    if (!inherits(image,"_p_itk__simple__Image"))
        stop("image must be a SimpleITK image")
    imdim <- image$GetDimension()
    if (is.null(origin))
        origin <- rep(0,imdim)
    if (length(origin) != imdim)
        stop(paste("origin must be of length",imdim))
    storage.mode(origin) = "numeric"
    ref <- .Call("mytest",image@ref,origin)
    image@ref <- ref
    return(image)
}
