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

library(SimpleITK)

args <- commandArgs(TRUE)

if (length(args) < 3) {
    stop("Usage: tfx <inputImage> <parameterFile> <outputImage>")
}

# Instantiate transformix
transformixImageFilter <- TransformixImageFilter()
transformixImageFilter$LogToConsoleOn()

# Read input
transformixImageFilter$SetMovingImage(ReadImage(args[1]))
transformixImageFilter$SetTransformParameterMap(transformixImageFilter$ReadParameterFile(args[2]))

# Run warp
resampled_image <- transformixImageFilter$Execute()

# Write result image
WriteImage(resampled_image, args[3])
