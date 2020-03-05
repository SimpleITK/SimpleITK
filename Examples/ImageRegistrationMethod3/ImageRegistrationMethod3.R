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
# Rscript --vanilla ImageRegistrationMethod3.R fixedImageFilter movingImageFile outputTransformFile
#

library(SimpleITK)

commandIteration <- function(method)
{
    if (method$GetOptimizerIteration()==0) {
        cat("Estimated Scales:", method$GetOptimizerScales())
    }
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

fixed <- ReadImage(args[[1]], 'sitkFloat32')

moving <- ReadImage(args[[2]], 'sitkFloat32')

R <- ImageRegistrationMethod()

R$SetMetricAsCorrelation()

R$SetOptimizerAsRegularStepGradientDescent(learningRate=2.0,
                                           minStep=1e-4,
                                           numberOfIterations=500,
                                           relaxationFactor=0.5,
                                           gradientMagnitudeTolerance=1e-8 )
R$SetOptimizerScalesFromIndexShift()

tx <- CenteredTransformInitializer(fixed, moving, Similarity2DTransform())
R$SetInitialTransform(tx)

R$SetInterpolator('sitkLinear')

R$AddCommand( 'sitkIterationEvent', function() commandIteration(R) )

outTx <- R$Execute(fixed, moving)

cat("-------\n")
outTx
cat("Optimizer stop condition:", R$GetOptimizerStopConditionDescription(), '\n')
cat("Iteration:", R$GetOptimizerIteration(), '\n')
cat("Metric value:", R$GetMetricValue(), '\n')


WriteTransform(outTx,  args[[3]])
