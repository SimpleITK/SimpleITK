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
# Rscript --vanilla ImageRegistrationMethod2.R fixedImageFilter movingImageFile outputTransformFile
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

if (length(args) != 3) {
    stop("3 arguments expected - fixedImageFilter, movingImageFile, outputTransformFile")
}

pixelType <- 'sitkFloat32'

fixed <- ReadImage(args[[1]], pixelType)
fixed <- Normalize(fixed)
fixed <- DiscreteGaussian(fixed, 2.0)


moving <- ReadImage(args[[2]], pixelType)
moving <- Normalize(moving)
moving <- DiscreteGaussian(moving, 2.0)

R <- ImageRegistrationMethod()

R$SetMetricAsJointHistogramMutualInformation()

R$SetOptimizerAsGradientDescentLineSearch(learningRate=1.0,
                                          numberOfIterations=200,
                                          convergenceMinimumValue=1e-5,
                                          convergenceWindowSize=5)

R$SetInitialTransform(TranslationTransform(fixed$GetDimension()))

R$SetInterpolator('sitkLinear')

R$AddCommand('sitkIterationEvent', function() commandIteration(R))

outTx <- R$Execute(fixed, moving)

cat("-------\n")
outTx
cat("Optimizer stop condition:", R$GetOptimizerStopConditionDescription(), '\n')
cat("Iteration:", R$GetOptimizerIteration(), '\n')
cat("Metric value:", R$GetMetricValue(), '\n')

WriteTransform(outTx, args[[3]])
