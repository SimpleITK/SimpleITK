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

compositeAddTransformTest <- function()
{
  fname <- deparse(sys.call(0)[[1]])

  dimension <- 2

  tx1 <- c(1,2)
  translation1 <- TranslationTransform(dimension, tx1)

  tx2 <- c(3,4)
  translation2 <- TranslationTransform(dimension, tx2)

  composite_transform <- Transform(translation1)
  dummy <- composite_transform$AddTransform(translation2)
  if (!is.null(dummy))
  {
    cat("failure in", fname, "\n")
    quit(save="no", status=1)
   }
}

translationTest()
compositeAddTransformTest()
quit(save="no", status=0)
