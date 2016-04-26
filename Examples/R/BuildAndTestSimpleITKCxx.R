if (!require(Rcpp))
    install.packages("Rcpp",repos="https://cran.rstudio.com/")

install.packages("SimpleITKCxx",repos=NULL)
library(SimpleITKCxx)
example("test")
