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

""" A SimpleITK example demonstrating how to apply a linear Transform and
    a displacement field, loaded from a file, to an image with only a
    single resampling pass. The linear part of the deformation is baked
    directly into the image's metadata via Transform.ApplyToImageMetadata,
    and only the non-linear, residual deformation is resampled, via
    WarpImageFilter. This avoids compounding two separate interpolations
    for what is ultimately one resampling operation. """

import os
import sys

import SimpleITK as sitk

if len(sys.argv) < 5:
    print("Wrong number of arguments.", file=sys.stderr)
    print(
        "Usage: "
        + __file__
        + " <movingImage> <linearTransformFile> <displacementFieldImage> <outputImage>",
        file=sys.stderr,
    )
    sys.exit(1)

moving = sitk.ReadImage(sys.argv[1])
linear_transform = sitk.ReadTransform(sys.argv[2])
displacement_field = sitk.ReadImage(sys.argv[3])

# Remember the image's original grid -- ApplyToImageMetadata only moves
# where the image's content sits in physical space, it does not change
# what output grid we ultimately want the warped result defined on.
original_size = moving.GetSize()
original_origin = moving.GetOrigin()
original_spacing = moving.GetSpacing()
original_direction = moving.GetDirection()

# The linear part of the deformation is baked directly into the image's
# origin, spacing, and direction -- no resampling/interpolation is
# needed for this step.
linear_transform.ApplyToImageMetadata(moving)

# Only the residual, non-linear deformation requires an actual
# resampling pass, performed here in a single interpolation step, back
# onto the image's original grid.
output = sitk.Warp(
    moving,
    displacement_field,
    sitk.sitkLinear,
    original_size,
    original_origin,
    original_spacing,
    original_direction,
)

sitk.WriteImage(output, sys.argv[4])

if "SITK_NOSHOW" not in os.environ:
    sitk.Show(output, "warped moving image")
