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

if (length(args) < 5) {
    stop("Usage: elx <fixedImage> <movingImage> <parameterFile> <outputImage> <outputParameterFile>")
}

# Instantiate SimpleElastix
elastixImageFilter <- ElastixImageFilter()

# Read input
elastixImageFilter$SetFixedImage(ReadImage(args[1]))
elastixImageFilter$SetMovingImage(ReadImage(args[2]))
elastixImageFilter$SetParameterMap(elastixImageFilter$ReadParameterFile(args[3]))
elastixImageFilter$LogToConsoleOn()

# Run registration
output_image <- elastixImageFilter$Execute()

# Write result image
WriteImage(output_image, args[4])

# Write parameter file. This example only supports one parameter map and one transform parameter map.
elastixImageFilter$WriteParameterFile(elastixImageFilter$GetTransformParameterMap(0L), args[5])
