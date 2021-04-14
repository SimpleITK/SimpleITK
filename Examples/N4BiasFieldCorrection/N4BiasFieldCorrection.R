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
# Rscript --vanilla N4BiasFieldCorrection.R inputImage, outputImage, shrinkFactor, maskImage, numberOfIterations, numberOfFittingLevels
#

library(SimpleITK)

args <- commandArgs( TRUE )

if (length(args) < 2) {
    stop("At least 2 arguments expected - inputImage, outputImage, [shrinkFactor], ",
         "[maskImage], [numberOfIterations], [numberOfFittingLevels]")
}

inputImage <- ReadImage(args[[1]], 'sitkFloat32')
image <- inputImage

if (length( args ) > 4) {
    maskImage <- ReadImage( args[[4]], 'sitkUint8' )
} else {
    maskImage <- OtsuThreshold( inputImage, 0, 1, 200 )
}

if (length( args ) > 3) {
    image <- Shrink( inputImage, rep(strtoi(args[3]), inputImage$GetDimension()) )
    maskImage <- Shrink( maskImage, rep(strtoi(args[3]), inputImage$GetDimension()) )
}

inputImage <- Cast( inputImage, 'sitkFloat32' )

corrector <- N4BiasFieldCorrectionImageFilter()

numberFittingLevels <- 4

if (length ( args ) > 6) {
    numberFittingLevels <- strtoi( args[[6]] )
}

if (length ( args ) > 5) {
    corrector$SetMaximumNumberOfIterations( rep(strtoi( args[[5]], numberFittingLevels)) )
}

correctedImage <- corrector$Execute( image, maskImage )

logBiasField <- corrector$GetLogBiasFieldAsImage(inputImage)

biasField <- inputImage / Exp( logBiasField )

WriteImage(correctedImage, args[[2]])
