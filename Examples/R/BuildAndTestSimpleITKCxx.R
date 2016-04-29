## To install the demo package and run the example, run
## Rscript --vanilla BuildAndTestSimpleITKCxx.R -DSimpleITK_DIR=[path_to_SimpleITK_DIR]
## all additional arguments will be parsed as cmake options
args <- commandArgs( TRUE )
install.packages("SimpleITKCxx",repos=NULL,configure.args=args)
library(methods)
library(SimpleITKCxx)
example("test",echo=FALSE)
