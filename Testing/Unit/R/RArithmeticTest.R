## simple arithmetic tests for R. We are ensuring that operator overloading
## works and that the results are the same as for R arithmetic. We also
## use the image/array conversion routines
##
## do everything using floating point, to avoid dealing with 8bit precision

library(SimpleITK)

testimA <- ReadImage(system.file("extdata/cthead1-Float.mha", package="SimpleITK"))
testimB <- ReadImage(system.file("extdata/cthead1-Float.mha", package="SimpleITK"))

# need to cast to signed types to compare with R arithmetic
testimInt <- ReadImage(system.file("extdata/cthead1.png", package="SimpleITK"))
testimInt <- Cast(testimInt, 'sitkInt16')

testArrayA <- as.array(testimA)
testArrayB <- as.array(testimB)

compareImArray <- function(im, Arr)
  {
    imA <- as.array(im)
    if (any(is.nan(imA) != is.nan(Arr))) {
      return(FALSE)
    }
    Arr[is.nan(Arr)] <- 0
    imA[is.nan(imA)] <- 0
    return(all(imA == Arr))
  }
compareBinImArray <- function(im, Arr)
  {
    imA <- as.array(im) > 0
    if (any(is.nan(imA) != is.nan(Arr))) {
      return(FALSE)
    }
    Arr[is.nan(Arr)] <- 0
    imA[is.nan(imA)] <- 0
    return(all(imA == Arr))
  }
compareImArrayTol <- function(im, Arr, tol=1e-06)
  {
    # first check the NaNs - should match
    imA <- as.array(im)
    if (any(is.nan(imA) != is.nan(Arr))) {
      return(FALSE)
    }
    if (any(is.infinite(imA) != is.infinite(Arr))) {
      return(FALSE)
    }
    # reset NaN
    Arr[is.nan(Arr)] <- 0
    imA[is.nan(imA)] <- 0
    # reset inf
    Arr[is.infinite(Arr)] <- 0
    imA[is.infinite(imA)] <- 0

    return(all(abs(imA - Arr)< tol) )
  }

plusTest <- function()
  {
    fname <- deparse(sys.call(0)[[1]])

    Im <- testimA + testimB
    A <- testArrayA + testArrayB

    if (!compareImArray(Im, A)) {
      cat("failure in", fname, "\n")
      quit(save="no", status=1)
    }

    ImC <- testimA + 101
    AC <- testArrayA + 101
    if (!compareImArray(ImC, AC)) {
      cat("failure in", fname, "\n")
      quit(save="no", status=1)
    }
    ImC <- 101 + testimA
    AC <- 101 + testArrayA
    if (!compareImArray(ImC, AC)) {
      cat("failure in", fname, "\n")
      quit(save="no", status=1)
    }

  }

minusTest <- function()
  {
    fname <- deparse(sys.call(0)[[1]])

    Im <- testimA - testimB
    A <- testArrayA - testArrayB

    if (!compareImArray(Im, A)) {
      cat("failure in", fname, "\n")
      quit(save="no", status=1)
    }
    ImC <- testimA - 101
    AC <- testArrayA - 101
    if (!compareImArray(ImC, AC)) {
      cat("failure in", fname, "\n")
      quit(save="no", status=1)
    }
    ImC <- 101 - testimA
    AC <- 101 - testArrayA
    if (!compareImArray(ImC, AC)) {
      cat("failure in", fname, "\n")
      quit(save="no", status=1)
    }  }

multTest <- function()
  {
    fname <- deparse(sys.call(0)[[1]])

    Im <- testimA * testimB
    A <- testArrayA * testArrayB

    if (!compareImArray(Im, A)) {
      cat("failure in", fname, "\n")
      quit(save="no", status=1)
    }
    ImC <- testimA * 101
    AC <- testArrayA * 101
    if (!compareImArray(ImC, AC)) {
      cat("failure in", fname, "\n")
      quit(save="no", status=1)
    }
    ImC <- 101 * testimA
    AC <- 101 * testArrayA
    if (!compareImArray(ImC, AC)) {
      cat("failure in", fname, "\n")
      quit(save="no", status=1)
    }
  }
divTest <- function()
  {
    fname <- deparse(sys.call(0)[[1]])
    ## need to avoid 0/0. Also there is a difference in precision.
    ## image is floating point, array is double precision, so we need
    ## to include a tolerance
    Im <- testimA / (testimB + 1)
    A <- testArrayA / (testArrayB+1)

    if (!compareImArrayTol(Im, A)) {
      cat("A failure in", fname, "\n")
      quit(save="no", status=1)
    }
    ImC <- testimA / 101
    AC <- testArrayA / 101
    if (!compareImArrayTol(ImC, AC)) {
      cat("B failure in", fname, "\n")
      quit(save="no", status=1)
    }
    # sitk doesn't return infs
    ImC <- 101/(testimA+1)
    AC <- 101/(testArrayA+1)
    if (!compareImArrayTol(ImC, AC, tol=1e-05)) {
      cat("C failure in", fname, "\n")
      quit(save="no", status=1)
    }
  }
powTest <- function()
  {
    fname <- deparse(sys.call(0)[[1]])
    ## There is a difference in precision.
    ## image is floating point, array is double precision, so we need
    ## to include a tolerance
    p <- array(data=0.9, dim=dim(testArrayA))
    ip <- testimA * 0 + 0.9
    Im <- testimA ^ ip
    A <- testArrayA ^ p

    if (!compareImArrayTol(Im, A, tol=5e-05)) {
      cat("A failure in", fname, "\n")
      quit(save="no", status=1)
    }
    ImC <- testimA ^ 0.9
    AC <- testArrayA ^ 0.9
    if (!compareImArrayTol(ImC, AC, tol=5e-05)) {
      cat("B failure in", fname, "\n")
      quit(save="no", status=1)
    }
    # there isn't a SimpleITK function for this
    #ImC <- 3.1^testimA
    #AC <- 3.1^testArrayA
    #if (!compareImArrayTol(ImC, AC)) {
    #  cat("failure in", fname, "\n")
    #  #quit(save="no", status=1)
    #}
  }
modTest <- function()
  {
    fname <- deparse(sys.call(0)[[1]])
    ## needs to use integer dividend and integer images. No support
    ## for float in underlying sitk filter
    ImC <- testimInt %% 3
    AC <- as.array(testimInt) %% 3
    if (!compareImArray(ImC, AC)) {
      cat("failure in", fname, "\n")
      quit(save="no", status=1)
    }
  }

mathTest <- function()
  {
    # this will produce NaNs - need to compare them
    mnames <- c('cos', 'sin', 'tan', 'acos', 'asin', 'atan', 'abs', 'exp', 'sqrt',
                 'log', 'log10')
    for (n in mnames) {
      Im <- eval(parse(text=paste(n, "(testimA/256)")))
      A <- eval(parse(text=paste(n, "(testArrayA/256)")))
      print(n)
      if (!compareImArrayTol(Im, A, 1e-05))
        {
          cat("failure in mathGroup", n, "\n")
          quit(save="no", status=1)
        }
    }

  }

logicTest <- function()
  {
    bin1 <- testimInt > 100
    bin2 <- testimInt > 120
    bA1 <- as.array(bin1)
    bA2 <- as.array(bin2)

    r1 <- bin1 & bin2
    r2 <- bA1 & bA2
    if (!compareBinImArray(r1, r2))
      {
        cat("failure in &\n")
        quit(save="no", status=1)
      }

    r1 <- bin1 | bin2
    r2 <- bA1 | bA2
    if (!compareBinImArray(r1, r2))
      {
        cat("failure in |\n")
        quit(save="no", status=1)
      }
    r1 <- xor(bin1, bin2)
    r2 <- xor(bA1, bA2)
    if (!compareBinImArray(r1, r2))
      {
        cat("failure in xor\n")
        quit(save="no", status=1)
      }

    r1 <- !bin1
    r2 <- !bA1
    if (!compareBinImArray(r1, r2))
      {
        cat("failure in !\n")
        quit(save="no", status=1)
      }
  }

compareTest <- function()
  {
    i0 <- testimInt
    i1 <- 113
    i2 <- i0 + 1

    a0 <- as.array(testimInt)
    a1 <- 113
    a2 <- a0 + 1

    r1 <- i0 == i1
    r2 <- a0 == a1

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in ==\n")
        quit(save="no", status=1)
      }

    r1 <- i0 != i1
    r2 <- a0 != a1

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in !=\n")
        quit(save="no", status=1)
      }

    r1 <- i0 <= i1
    r2 <- a0 <= a1

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in <=\n")
        quit(save="no", status=1)
      }

    r1 <- i0 >= i1
    r2 <- a0 >= a1

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in <=\n")
        quit(save="no", status=1)
      }
    r1 <- i0 < i1
    r2 <- a0 < a1

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in <\n")
        quit(save="no", status=1)
      }

    r1 <- i0 > i1
    r2 <- a0 > a1

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in >\n")
        quit(save="no", status=1)
      }
###################################
    r1 <- i1 == i0
    r2 <- a1 == a0

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in ==\n")
        quit(save="no", status=1)
      }

    r1 <- i1 != i0
    r2 <- a1 != a0

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in !=\n")
        quit(save="no", status=1)
      }

    r1 <- i1 <= i0
    r2 <- a1 <= a0

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in <=\n")
        quit(save="no", status=1)
      }

    r1 <- i1 >= i0
    r2 <- a1 >= a0

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in >=\n")
        quit(save="no", status=1)
      }
    r1 <- i1 < i0
    r2 <- a1 < a0

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in <\n")
        quit(save="no", status=1)
      }

    r1 <- i1 > i0
    r2 <- a1 > a0

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in >\n")
        quit(save="no", status=1)
      }
    ## will need to be extended to support image comparison ops.
###################################
    r1 <- i0 == i2
    r2 <- a0 == a2

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in ==\n")
        quit(save="no", status=1)
      }

    r1 <- i0 != i2
    r2 <- a0 != a2

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in !=\n")
        quit(save="no", status=1)
      }

    r1 <- i0 <= i2
    r2 <- a0 <= a2

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in <=\n")
        quit(save="no", status=1)
      }

    r1 <- i0 >= i2
    r2 <- a0 >= a2

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in >=\n")
        quit(save="no", status=1)
      }
    r1 <- i0 < i2
    r2 <- a0 < a2

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in <\n")
        quit(save="no", status=1)
      }

    r1 <- i0 > i2
    r2 <- a0 > a2

    if (!compareBinImArray(r1, r2))
      {
        cat("failure in >\n")
        quit(save="no", status=1)
      }

  }

plusTest()
minusTest()
multTest()
divTest()
powTest()
modTest()
mathTest()
logicTest()
compareTest()

quit(save="no", status=0)
