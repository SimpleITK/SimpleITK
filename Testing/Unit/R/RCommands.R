## Test the AddCommand method and command classes

library(SimpleITK)

options(warn=2)


commandFromFunctionTest <- function()
{
    img <- Image(64, 64, 'sitkFloat32')

    castFilter <- CastImageFilter()

    output_text <- ""
    commandFunction <- function()
    {
        output_text <<- paste(output_text, 'start', sep='')
    }

    castFilter$AddCommand('sitkStartEvent', commandFunction)

    output <- castFilter$Execute(img)
    cat(paste('output_text: "', output_text, '"\n', sep=''))

    # test that output_text is 'start'

     if(output_text != 'start')
     {
         stop("commandFromFunctionTest failed, expected 'start' got \"", output_text, '"')
     }
}


commandFromLambda <- function()
{
    img <- Image(64, 64, 'sitkFloat32')

    castFilter <- CastImageFilter()

    output_text <- ''
    castFilter$AddCommand('sitkStartEvent', function() output_text <<- paste(output_text, 'start', sep=''))

    output <- castFilter$Execute(img)

    if(output_text != 'start')
    {
        stop("commandFromLambda failed, expected 'start' got \"", output_text, '"')
    }
}


commandFromLambdaWithClosure <- function()
{
    img <- Image(64, 64, 'sitkFloat32')

    output_text = ''

    commandWithArguments <- function(filter)
    {
        output_text <<- paste(output_text, filter$GetName(), sep='')
    }



    castFilter <- CastImageFilter()

    castFilter$AddCommand('sitkEndEvent', function() commandWithArguments(castFilter))

    output = castFilter$Execute(img)
    if(output_text != 'CastImageFilter')
    {
        stop("commandFromLambdaWithClosure failed, expected 'CastImageFilter' got \"", output_text, '"')
    }
}


commandFromFunctionTest()
commandFromLambda()
commandFromLambdaWithClosure()
