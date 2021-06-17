library(SimpleITK)
# Test exceptions when an incorrect method name is used

raiseAnException <- function() {
  anonymous_transform_type <- Transform(TranslationTransform(2,c(1.0,0.0)))
  try(anonymous_transform_type$GetOffset())
  message("Exception caught, test passed")
  quit(save="no", status=0)
  return(TRUE)
}

raiseAnException()
# something else went wrong if we get this far
quit(save="no", status=1)
