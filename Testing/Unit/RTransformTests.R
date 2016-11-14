## test that the transformation interface works in R.

library(SimpleITK)

translationTest <- function()
{
  fname <- deparse(sys.call(0)[[1]])

  dimension <- 3
  tx <- c(1,2,3)
  translation <- TranslationTransform(dimension, tx)
  offset <- translation$GetOffset()
  if (! (tx[1] == offset[1] && tx[2] == offset[2] && tx[3] == offset[3]))
  {
    cat("failure in", fname, "\n")
    quit(save="no", status=1)
   }
}

translationTest()

quit(save="no", status=0)
