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
# Rscript --vanilla ImageRegistrationMethodDisplacement1.R fixedImageFilter movingImageFile outputTransformFile
#

library(SimpleITK)

commandIteration <- function(method)
{
    if (method$GetOptimizerIteration()==0) {
        cat("\tLevel:", method$GetCurrentLevel(),
            "\n\tScales:", method$GetOptimizerScales(), "\n")
    }
    msg <- paste("#", method$GetOptimizerIteration(),
                 "\n\tMetric Value: ", method$GetMetricValue(),
                 "\n\tLearning Rate: ", method$GetOptimizerLearningRate(),
                 '\n', sep="")
    cat(msg)
}

commandMultiIteration <- function(method)
{
    msg <- paste("\tStop Condition: ", method$GetOptimizerStopConditionDescription(),
                 "\n============= Resolution Change =============\n", sep="")
    cat(msg)
}

args <- commandArgs( TRUE )

if (length(args) != 3) {
    stop("3 arguments expected - fixedImageFilter, movingImageFile, outputTransformFile")
}

fixed <- ReadImage(args[[1]], 'sitkFloat32')
moving <- ReadImage(args[[2]], 'sitkFloat32')

initialTx <- CenteredTransformInitializer(fixed, moving, AffineTransform(fixed$GetDimension()))

R <- ImageRegistrationMethod()

R$SetShrinkFactorsPerLevel(c(3,2,1))
R$SetSmoothingSigmasPerLevel(c(2,1,1))

R$SetMetricAsJointHistogramMutualInformation(20)
R$MetricUseFixedImageGradientFilterOff()

R$SetOptimizerAsGradientDescent(learningRate=1.0,
                                numberOfIterations=100,
                                convergenceMinimumValue=1e-6,
                                convergenceWindowSize=10,
                                estimateLearningRate = 'EachIteration')
R$SetOptimizerScalesFromPhysicalShift()

R$SetInitialTransform(initialTx)

R$SetInterpolator('sitkLinear')

R$AddCommand( 'sitkIterationEvent', function() commandIteration(R) )
R$AddCommand( 'sitkMultiResolutionIterationEvent', function() commandMultiIteration(R) )

outTx1 <- R$Execute(fixed, moving)

cat("-------\n")
outTx1
cat("Optimizer stop condition:", R$GetOptimizerStopConditionDescription(), '\n')
cat("Iteration:", R$GetOptimizerIteration(), '\n')
cat("Metric value:", R$GetMetricValue(), '\n')


displacementField <- Image(fixed$GetSize(), 'sitkVectorFloat64')
displacementField$CopyInformation(fixed)
displacementTx <- DisplacementFieldTransform(displacementField)
rm(displacementField)
displacementTx$SetSmoothingGaussianOnUpdate(varianceForUpdateField=0.0,
                                            varianceForTotalField=1.5)

R$SetMovingInitialTransform(outTx1)
R$SetInitialTransform(displacementTx, inPlace=TRUE)

R$SetMetricAsANTSNeighborhoodCorrelation(4)
R$MetricUseFixedImageGradientFilterOff()

R$SetShrinkFactorsPerLevel(c(3,2,1))
R$SetSmoothingSigmasPerLevel(c(2,1,1))

R$SetOptimizerScalesFromPhysicalShift()
R$SetOptimizerAsGradientDescent(learningRate=1,
                                numberOfIterations=300,
                                convergenceMinimumValue=1e-6,
                                convergenceWindowSize=10,
                                estimateLearningRate = 'EachIteration')

R$Execute(fixed, moving)



cat("-------\n")
displacementTx
cat("Optimizer stop condition:", R$GetOptimizerStopConditionDescription(), '\n')
cat("Iteration:", R$GetOptimizerIteration(), '\n')
cat("Metric value:", R$GetMetricValue(), '\n')

outTx <- CompositeTransform(outTx1$GetDimension())
outTx$AddTransform(outTx1)
outTx$AddTransform(displacementTx)

WriteTransform(outTx,  args[[3]])
