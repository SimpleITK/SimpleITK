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
# Rscript --vanilla ImageRegistrationMethodExhaustive.R fixedImageFilter movingImageFile outputTransformFile
#

# This script demonstrates the use of the Exhaustive optimizer in the
# ImageRegistrationMethod to estimate a good initial rotation position.

# Because gradient descent base optimization can get stuck in local
# minima, a good initial transform is critical for reasonable
# results. Search a reasonable space on a grid with brute force may be a
# reliable way to get a starting location for further optimization.

# The initial translation and center of rotation for the transform is
# initialized based on the first principle moments of the intensities of
# the image. Then in either 2D or 3D a Euler transform is used to
# exhaustively search a grid of the rotation space at a certain step
# size. The resulting transform is a reasonable guess where to start
# further registration.

library(SimpleITK)

commandIteration <- function(method)
{
    if (method$GetOptimizerIteration()==0) {
        cat("Scales:", method$GetOptimizerScales(), "\n")
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

fixed <- ReadImage(args[[1]], 'sitkFloat32')
moving <- ReadImage(args[[2]], 'sitkFloat32')

R <- ImageRegistrationMethod()
R$SetMetricAsMattesMutualInformation(numberOfHistogramBins = 50)

sample_per_axis <- 12
if (fixed$GetDimension() == 2) {
    tx <- Euler2DTransform()
    # Set the number of samples (radius) in each dimension, with a
    # default step size of 1.0
    R$SetOptimizerAsExhaustive(c(sample_per_axis%/%2,0,0))
    # Utilize the scale to set the step size for each dimension
    R$SetOptimizerScales(c(2.0*pi/sample_per_axis,1.0,1.0))
} else if (fixed.GetDimension() == 3) {
    tx <- Euler3DTransform()
    R$SetOptimizerAsExhaustive(c(sample_per_axis%/%2,sample_per_axis%/%2,sample_per_axis%/%4,0,0,0))
    R$SetOptimizerScales(c(2.0*pi/sample_per_axis,2.0*pi/sample_per_axis,2.0*pi/sample_per_axis,1.0,1.0,1.0))
}

# Initialize the transform with a translation and the center of
# rotation from the moments of intensity.
tx <- CenteredTransformInitializer(fixed, moving, tx)
R$SetInitialTransform(tx)
R$SetInterpolator('sitkLinear')
R$AddCommand( 'sitkIterationEvent', function() commandIteration(R) )

outTx <- R$Execute(fixed, moving)

cat("-------\n")
outTx
cat("Optimizer stop condition:", R$GetOptimizerStopConditionDescription(), '\n')
cat("Iteration:", R$GetOptimizerIteration(), '\n')
cat("Metric value:", R$GetMetricValue(), '\n')

WriteTransform(outTx, args[[3]])
