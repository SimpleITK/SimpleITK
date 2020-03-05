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
# Rscript --vanilla DemonsRegistration1.R fixedImageFilter movingImageFile outputTransformFile
#

library(SimpleITK)

commandIteration <- function(filter)
{
    msg <- paste("Iteration number ", filter$GetElapsedIterations(),
                 " = ", filter$GetMetric(), "\n" )
    cat(msg)
}

args <- commandArgs( TRUE )

if (length(args) != 3) {
    stop("3 arguments expected - fixedImageFilter, movingImageFile, outputTransformFile")
}

fixed <- ReadImage(args[[1]], 'sitkFloat32')

moving <- ReadImage(args[[2]], 'sitkFloat32')


matcher <- HistogramMatchingImageFilter()
matcher$SetNumberOfHistogramLevels(1024)
matcher$SetNumberOfMatchPoints(7)
matcher$ThresholdAtMeanIntensityOn()
moving <- matcher$Execute(moving, fixed)

# The basic Demons Registration Filter
# Note there is a whole family of Demons Registration algorithms included in SimpleITK
demons <- DemonsRegistrationFilter()
demons$SetNumberOfIterations( 50 )
# Standard deviation for Gaussian smoothing of displacement field
demons$SetStandardDeviations( 1.0 )

demons$AddCommand( 'sitkIterationEvent', function() commandIteration(demons) )

displacementField <- demons$Execute( fixed, moving )

cat("-------\n")
cat("Number Of Iterations: ", demons$GetElapsedIterations(), "\n")
cat("RMS: ", demons$GetRMSChange(), "\n")

outTx <- DisplacementFieldTransform( displacementField )

WriteTransform(outTx, args[[3]])
