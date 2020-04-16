parseSWIGNamespaceFile <- function(nspace) {
  ## SWIG attemtpts to generate a package namespace file, but it is
  ## very wrong, at least for simpleITK. However it does contain a useful
  ## list of names that we can work with.
  ##
  ## Everything in SimpleITK is done with S4 classes. However the user never
  ## needs to create them by hand, everything is done by constructor functions,
  ## $ method and delete. We thus want to export functions ending in ImageFilter,
  ## the same names without ImageFilter, the associated $ and delete methods
  ## then perhaps some operator stuff by hand.

  ## parse the text file using the R parser, as the swig generated namespace is
  ## basically like function calls
  cde <- parse(nspace)
  ## Turn this into lists with useful structure
  cde <- lapply(cde, as.list)
  fnames <- lapply(cde, "[[", 1)
  fargs <- lapply(cde, function(X) {
    X <- sapply(X[-1], as.character)
    X
  })
  names(fargs) <- fnames

  ## We're interested in the export list, which includes all the image filters
  ## get all names starting with delete_ and ending in ImageFilter
  allclasses <- grep("^delete_.+", fargs$export, value=TRUE)
  classnames <- gsub("^delete_(.+)$", "\\1", allclasses)
  imagefilterfunctions <- gsub("^(.+)ImageFilter$", "\\1", classnames)
  classnamesreduced <- grep("^(.+)ImageFilter$", classnames, value=TRUE, invert=TRUE)
  otherfilterfunctions <- gsub("^(.+)Filter$", "\\1", classnamesreduced)
  thefunctions <- c(imagefilterfunctions, otherfilterfunctions)
  # confirm that there is a procedural version by matching against the original export list
  # only imagefilters have procedural versions
  realfunction <- thefunctions %in% fargs$export
  thefunctions <- thefunctions[realfunction]

  ## Special functions, like ReadImage, don't have associated new_ methods
  ## However, very difficult to filter the method names. e.g

  return(list(filters=classnames[!duplicated(classnames)], functions=thefunctions[!duplicated(thefunctions)]))
}

writeSITKNamespace <- function(objlist) {
  ll <- paste0('"', c(objlist$filters, objlist$functions), '"')
  llh <- paste0(head(ll, -1), ",")
  ll <- c("export(", llh, tail(ll, 1), ")")
  return(ll)
}

handExports <- function() {
  f <- c('import(methods)',
         'importFrom("utils", "head", "tail")',
         'useDynLib(SimpleITK)',
         'exportClasses("_p_itk__simple__Image")',
         'export("as.image")',
         'export("ReadImage", "ReadTransform", "WriteImage", "WriteTransform",
  "GaborSource", "GridSource", "GaussianSource", "PhysicalPointSource",
  "GetPixelIDValueAsString", "GetPixelIDValueFromString", "Show")',
         'export("ImageSeriesReader_GetGDCMSeriesFileNames","ImageSeriesReader_GetGDCMSeriesIDs")',
         'exportMethods("$", "print", "show", "as.array")')

  f
}

manualexclusions <- c("DoubleDoubleMap", "RCommand", "VectorBool", "VectorDouble", "VectorFloat",
                      "VectorInt16", "VectorInt32", "VectorInt64",
                      "VectorInt8", "VectorOfImage", "VectorString",
                      "VectorUInt16", "VectorUInt32", "VectorUInt64",
                      "VectorUInt8", "VectorUIntList", "ProcessObject",
                      "ImageFilter", "ImageReaderBase")


newNAMESPACE <- function(oldnamespace, targetnamespace) {
  byhand <- handExports()
  swigstuff <- parseSWIGNamespaceFile(oldnamespace)
  swigstuff$filters <- setdiff(swigstuff$filters, manualexclusions)
  auto <- writeSITKNamespace(swigstuff)
  writeLines(c(byhand, auto), targetnamespace)
}

args <- commandArgs( TRUE )
src <- args[[1]]
dest <- args[[2]]

newNAMESPACE(src, dest)
q(save="no")
