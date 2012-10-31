## Arithmetic/Maths/
setMethod('+', signature(e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) Add(e1, e2)
          )

setMethod('+', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) Add(e1, e2)
          )

setMethod('+', signature(e1="numeric", e2="_p_itk__simple__Image"),
          function(e1, e2) Add(e2, e1)
          )

setMethod('-', signature(e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) Subtract(e1, e2)
          )

setMethod('-', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) Subtract(e1, e2)
          )

setMethod('-', signature(e1="numeric", e2="_p_itk__simple__Image"),
          function(e1, e2) Subtract(e1, e2)
          )

setMethod('*', signature(e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) Multiply(e1, e2)
          )

setMethod('*', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) Multiply(e1, e2)
          )
setMethod('*', signature(e1="numeric", e2="_p_itk__simple__Image"),
          function(e1, e2) Multiply(e1, e2)
          )

setMethod('/', signature(e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) Divide(e1, e2)
          )

setMethod('/', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) Divide(e1, e2)
          )

setMethod('/', signature(e1="numeric", e2="_p_itk__simple__Image"),
          function(e1, e2) Divide(e1, e2)
          )

setMethod('^', signature(e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) Pow(e1, e2)
          )

setMethod('^', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) Pow(e1, e2)
          )

setMethod('^', signature(e1="numeric", e2="_p_itk__simple__Image"),
          function(e1, e2) Pow(e1, e2)
          )

setMethod('%%', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) Modulus(e1, e2)
          )

setMethod('%/%', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) stop("No integer division op for images")
          )

## Math group - names are consistent, so we can do this programatically

for (nm in c('cos', 'sin', 'tan', 'acos', 'asin', 'atan', 'abs', 'exp', 'sqrt',
            'log', 'log10'))
{
  Inm <- nm
  substr(Inm , 1, 1) <- toupper(substr(Inm , 1, 1))
  ftext <- paste("function(x)", Inm, "(x)", sep="")
  setMethod(nm, signature(x="_p_itk__simple__Image"),
            eval(parse(text=ftext))
            )

}

## Logic
setMethod('&', signature(e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) And(e1, e2)
          )
setMethod('|', signature(e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) Or(e1, e2)
          )
setMethod("xor", signature(x="_p_itk__simple__Image", y="_p_itk__simple__Image"),
          function(x, y) Xor(x, y)
         )

setMethod('!', signature(x="_p_itk__simple__Image"),
          function(x) Not(x)
          )
# compare
# Nothing in sITK yet for image == image, image == const. Could construct
# some from filter combinations - e.g. image == , >= , <=, <, > const can be
# binary threshold
# this isn't ideal and should be replaced ASAP. It is incorrect
# for pixel types with negatives. It gives a flavour though
# can be corrected by looking up the min and max pixel values
setMethod('==', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) {
            BinaryThreshold(e1, e2, e2, 1, 0)
          }
          )
setMethod('==', signature( e1="numeric", e2="_p_itk__simple__Image"),
          function(e1, e2) {
            BinaryThreshold(e2, e1, e1, 1, 0)
          }
          )
setMethod('==', signature( e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) {
            stop("Not implemented")
            #(e1 - e2) == 0
          }
          )

setMethod('<=', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) {
            # can we look up pixel traits?
            BinaryThreshold(e1, 0, e2, 1, 0)
          }
          )
setMethod('<=', signature(e1="numeric", e2="_p_itk__simple__Image"),
          function(e1, e2) {
            # can we look up pixel traits?
            BinaryThreshold(e2, e1, 255, 1, 0)
          }
          )
setMethod('<=', signature(e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) {
            stop("Not implemented")
          }
          )

setMethod('>=', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) {
            # can we look up pixel traits?
            BinaryThreshold(e1, e2, 255, 1, 0)
          }
          )
setMethod('>=', signature(e1="numeric", e2="_p_itk__simple__Image"),
          function(e1, e2) {
            BinaryThreshold(e2, 0, e1, 1, 0)
          }
          )
setMethod('>=', signature(e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) {
            stop("Not implemented")
          }
          )

setMethod('<', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) {
            BinaryThreshold(e1, e2, 255, 0, 1)
          }
          )
setMethod('<', signature(e1="numeric", e2="_p_itk__simple__Image"),
          function(e1, e2) {
            BinaryThreshold(e2, 0, e1, 0, 1)
          }
          )
setMethod('<', signature(e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) {
            stop("Not implemented")
          }
          )
setMethod('>', signature(e1="_p_itk__simple__Image", e2="numeric"),
          function(e1, e2) {
            BinaryThreshold(e1, 0, e2, 0, 1)
          }
          )
setMethod('>', signature(e1="numeric", e2="_p_itk__simple__Image"),
          function(e1, e2) {
            BinaryThreshold(e2, e1, 255, 0, 1)
          }
          )

setMethod('>', signature(e1="_p_itk__simple__Image", e2="_p_itk__simple__Image"),
          function(e1, e2) {
            stop("Not implemented")
          }
          )
