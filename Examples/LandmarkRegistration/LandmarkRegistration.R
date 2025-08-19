# =========================================================================
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
# =========================================================================

# A SimpleITK example demonstrating landmark registration.

library(SimpleITK)

args <- commandArgs(TRUE)

# Black image with a small white square in it.
fixedImage <- Image(100, 100, 'sitkUInt8')
# Set pixels in rectangle [11:20, 11:20] to 200
for (x in 11:19) {
  for (y in 11:19) {
    fixedImage$SetPixel(c(x, y), 200)
  }
}

# Black image with a small grey square at a different location.
movingImage <- Image(100, 100, 'sitkUInt8')
# Set pixels in rectangle [51:60, 51:60] to 69
for (x in 51:59) {
  for (y in 51:59) {
    movingImage$SetPixel(c(x, y), 69)
  }
}

# Landmarks are 3 corners of the squares.
# 3 (X, Y) pairs are flattened into 1-d lists.
fixedLandmarks <- c(10, 10, 20, 10, 20, 20)
movingLandmarks <- c(50, 50, 60, 50, 60, 60)

# Set up the LandmarkBasedTransformInitializerFilter.
landmarkInitializer <- LandmarkBasedTransformInitializerFilter()

landmarkInitializer$SetFixedLandmarks(fixedLandmarks)
landmarkInitializer$SetMovingLandmarks(movingLandmarks)

transform <- Euler2DTransform()

# Compute the transform.
outputTransform <- landmarkInitializer$Execute(transform)

cat(outputTransform$ToString())

# Resample the transformed moving image onto the fixed image.
outputImage <- Resample(movingImage, fixedImage, outputTransform, 'sitkLinear', 150)

# Write the resampled image.
WriteImage(outputImage, "landmark_example.png")

# Write the transform.
if (length(args) > 0) {
  outName <- args[1]
} else {
  outName <- "landmark_transform.tfm"
}

WriteTransform(outputTransform, outName)
