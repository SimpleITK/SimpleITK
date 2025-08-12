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
# Rscript --vanilla ImageRegistrationMethodBSpline3.R fixedImageFilter movingImageFile outputTransformFile

library(SimpleITK)

# Callback invoked each iteration
command_iteration <- function(method, bspline_transform) {
  if (method$GetOptimizerIteration() == 0) {
    # The BSpline is resized before the first optimizer
    # iteration is completed per level. Print the transform object
    # to show the adapted BSpline transform.
    cat(bspline_transform$ToString(), "\n")
  }

  cat(sprintf("%3d = %10.5f\n",
              method$GetOptimizerIteration(),
              method$GetMetricValue()))
}

# Callback invoked before starting a multi-resolution level.
command_multi_iteration <- function(method) {
  if (method$GetCurrentLevel() > 0) {
    cat(sprintf("Optimizer stop condition: %s\n",
                method$GetOptimizerStopConditionDescription()))
    cat(sprintf(" Iteration: %d\n", method$GetOptimizerIteration()))
    cat(sprintf(" Metric value: %f\n", method$GetMetricValue()))
  }

  cat("--------- Resolution Changing ---------\n")
}

args <- commandArgs( TRUE )

if (length(args) < 3) {
    stop("Usage: fixedImageFilter movingImageFile outputTransformFile")
}

fixed <- ReadImage(args[1], 'sitkFloat32')
moving <- ReadImage(args[2], 'sitkFloat32')

transformDomainMeshSize <- rep(2, fixed$GetDimension())
tx <- BSplineTransformInitializer(fixed, transformDomainMeshSize)

cat(sprintf("Initial Number of Parameters: %d\n", tx$GetNumberOfParameters()))

R <- ImageRegistrationMethod()
R$SetMetricAsJointHistogramMutualInformation()

learningRate <- 5.0
numberOfIterations <- 100
convergenceMinimumValue <- 1e-4
convergenceWindowSize <- 5
R$SetOptimizerAsGradientDescentLineSearch(learningRate, numberOfIterations,
                                          convergenceMinimumValue, convergenceWindowSize)

R$SetInterpolator('sitkLinear')

R$SetInitialTransformAsBSpline(tx, inPlace=TRUE, scaleFactors=c(1, 2, 5))
R$SetShrinkFactorsPerLevel(c(4, 2, 1))
R$SetSmoothingSigmasPerLevel(c(4, 2, 1))

R$AddCommand('sitkIterationEvent', function() command_iteration(R, tx))
R$AddCommand('sitkMultiResolutionIterationEvent', function() command_multi_iteration(R))

outTx <- R$Execute(fixed, moving)

cat("-------\n")
cat(tx$ToString(), "\n")
cat(outTx$ToString(), "\n")
cat(sprintf("Optimizer stop condition: %s\n", R$GetOptimizerStopConditionDescription()))
cat(sprintf(" Iteration: %d\n", R$GetOptimizerIteration()))
cat(sprintf(" Metric value: %f\n", R$GetMetricValue()))

WriteTransform(outTx, args[3])

if (Sys.getenv("SITK_NOSHOW") == "") {
  resampler <- ResampleImageFilter()
  resampler$SetReferenceImage(fixed)
  resampler$SetInterpolator('sitkLinear')
  resampler$SetDefaultPixelValue(100)
  resampler$SetTransform(outTx)

  out <- resampler$Execute(moving)
  simg1 <- Cast(RescaleIntensity(fixed), 'sitkUInt8')
  simg2 <- Cast(RescaleIntensity(out), 'sitkUInt8')
  cimg <- Compose(simg1, simg2, simg1 %/% 2.0 + simg2 %/% 2.0)
  Show(cimg, "Image Registration Composition")
}
