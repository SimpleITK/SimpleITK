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

""" A SimpleITK script which verifies the result of the
    ApplyToImageMetadataAndWarp example. The same deformation is applied
    conventionally: the displacement field is cast to double precision and
    used to construct a DisplacementFieldTransform, which is combined with
    the linear transform in a CompositeTransform and applied with a single
    call to Resample. The result is compared to the image produced by the
    example, and the script exits with an error if they differ by more than
    a small tolerance. """

import sys

import SimpleITK as sitk

# The two approaches differ only by the single precision rounding of the
# image metadata and displacement field.
TOLERANCE = 1e-2

if len(sys.argv) < 5:
    print("Wrong number of arguments.", file=sys.stderr)
    print(
        "Usage: "
        + __file__
        + " <movingImage> <linearTransformFile> <displacementFieldImage> <warpedImage>",
        file=sys.stderr,
    )
    sys.exit(1)

moving = sitk.ReadImage(sys.argv[1])
linear_transform = sitk.ReadTransform(sys.argv[2])
displacement_field = sitk.ReadImage(sys.argv[3])
warped = sitk.ReadImage(sys.argv[4])

# DisplacementFieldTransform requires a double precision vector image.
displacement_transform = sitk.DisplacementFieldTransform(
    sitk.Cast(displacement_field, sitk.sitkVectorFloat64)
)

# The last transform in the list is the first applied to the points of the
# output grid: the displacement field, followed by the linear transform.
composite_transform = sitk.CompositeTransform(
    [linear_transform, displacement_transform]
)

expected = sitk.Resample(moving, warped, composite_transform, sitk.sitkLinear, 0.0)

statistics = sitk.StatisticsImageFilter()
statistics.Execute(sitk.AbsoluteValueDifference(warped, expected))
print(
    f"Absolute difference: maximum={statistics.GetMaximum():g}"
    f" mean={statistics.GetMean():g} (tolerance={TOLERANCE:g})"
)

if statistics.GetMaximum() > TOLERANCE:
    print("Results differ more than the tolerance.", file=sys.stderr)
    sys.exit(1)
