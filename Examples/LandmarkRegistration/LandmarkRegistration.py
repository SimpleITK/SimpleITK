#!/usr/bin/env python
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

""" A SimpleITK example demonstrating landmark registration. """

import sys
import SimpleITK as sitk

# Black image with a small white square in it.
fixed_image = sitk.Image(100, 100, sitk.sitkUInt8)
fixed_image[11:20, 11:20] = 200

# Black image with a small grey square at a different location.
moving_image = sitk.Image(100, 100, sitk.sitkUInt8)
moving_image[51:60, 51:60] = 69


# Landmarks are 3 corners of the squares.
# 3 (X, Y) pairs are flattened into 1-d lists.
fixed_landmarks = [10, 10, 20, 10, 20, 20]
moving_landmarks = [50, 50, 60, 50, 60, 60]

# Set up the LandmarkBasedTransformInitializerFilter.
landmark_initializer = sitk.LandmarkBasedTransformInitializerFilter()

landmark_initializer.SetFixedLandmarks(fixed_landmarks)
landmark_initializer.SetMovingLandmarks(moving_landmarks)

transform = sitk.Euler2DTransform()

# Compute the transform.
output_transform = landmark_initializer.Execute(transform)

print(output_transform)


# Resample the transformed moving image onto the fixed image.
output_image = sitk.Resample(
    moving_image, fixed_image, transform=output_transform, defaultPixelValue=150
)

# Write the resampled image.
sitk.WriteImage(output_image, "landmark_example.png")


# Write the transform.
if len(sys.argv) > 1:
    out_name = sys.argv[1]
else:
    out_name = "landmark_transform.tfm"

sitk.WriteTransform(output_transform, out_name)
