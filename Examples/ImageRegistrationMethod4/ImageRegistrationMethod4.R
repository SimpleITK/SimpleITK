#=========================================================================
#
#  Copyright NumFOCUS
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#=========================================================================
# Run with:
#
# Rscript --vanilla ImageRegistrationMethod4.R fixedImageFilter movingImageFile outputTransformFile numberOfBins samplingPercentage
#

library(SimpleITK)

commandIteration <- function(method)
{
    msg <- paste(method$GetOptimizerIteration(), "=",
                 method$GetMetricValue(), ":",
                 method$GetOptimizerPosition(), "\n" )
    cat(msg)
}

args <- commandArgs( TRUE )

if (length(args) < 3) {
    stop("3, 4, or 5 arguments expected - fixedImageFilter, movingImageFile, outputTransformFile [numberOfBins] [samplingPercentage]")
}

fixed <- ReadImage(args[[1]], 'sitkFloat32')
moving <- ReadImage(args[[2]], 'sitkFloat32')

numberOfBins <- 24
samplingPercentage <- 0.10

if (length(args) > 4) {
    numberOfBins <- strtoi(args[[4]])
}
if (length(args) > 5) {
    samplingPercentage <- as.numeric(args[[5]])
}

R <- ImageRegistrationMethod()
R$SetMetricAsMattesMutualInformation(numberOfBins)
R$SetMetricSamplingPercentage(samplingPercentage)
R$SetMetricSamplingStrategy('RANDOM')
R$SetOptimizerAsRegularStepGradientDescent(1.0,.001,200)
R$SetInitialTransform(TranslationTransform(fixed$GetDimension()))
R$SetInterpolator('sitkLinear')

R$AddCommand( 'sitkIterationEvent', function() commandIteration(R) )

outTx <- R$Execute(fixed, moving)

cat("-------\n")
outTx
cat("Optimizer stop condition:", R$GetOptimizerStopConditionDescription(), '\n')
cat("Iteration:", R$GetOptimizerIteration(), '\n')
cat("Metric value:", R$GetMetricValue(), '\n')

WriteTransform(outTx, args[[3]])
