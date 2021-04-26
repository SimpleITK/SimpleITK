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
# Rscript --vanilla ImageRegistrationOptimizerWeights.R <fixedImageFile> <movingImageFile> <outputTransformFile>
#


library(SimpleITK)

args <- commandArgs( TRUE )

if (length(args) != 3) {
    stop("Expected arguments: <fixedImageFile> <movingImageFile> <outputTransformFile>")
}

fixed_image = ReadImage(args[[1]], "sitkFloat32")
moving_image = ReadImage(args[[2]], "sitkFloat32")

# initialization
transform <- CenteredTransformInitializer(fixed_image,
                                          moving_image,
                                          Euler3DTransform(),
                                          "GEOMETRY")
# registration
registration_method <- ImageRegistrationMethod()
registration_method$SetMetricAsCorrelation()
registration_method$SetMetricSamplingStrategy("NONE")
registration_method$SetInterpolator("sitkLinear")
registration_method$SetOptimizerAsGradientDescent(learningRate=1.0,
                                                  numberOfIterations=300,
                                                  convergenceMinimumValue=1e-6,
                                                  convergenceWindowSize=10)
registration_method$SetOptimizerScalesFromPhysicalShift()
registration_method$SetInitialTransform(transform, inPlace=TRUE)
registration_method$SetOptimizerWeights(c(0,0,1,1,1,1))
output_sink_tx<-registration_method$Execute(fixed_image, moving_image)

cat("-------\n")
cat("Final transform parameters: ", transform$GetParameters(), "\n")
cat("Optimizer stop condition: ", registration_method$GetOptimizerStopConditionDescription(), "\n")
cat("Iteration: ", registration_method$GetOptimizerIteration(), "\n")
cat("Metric value:", registration_method$GetMetricValue(), "\n")

WriteTransform(transform, args[[3]])
