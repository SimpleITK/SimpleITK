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

""" A SimpleITK example demonstrating various image grid manipulation
    techniques. """

import sys
import SimpleITK as sitk

if len(sys.argv) < 3:
    print("Usage: " + sys.argv[0] + " <input-1> <input-2>")
    sys.exit(1)

image_1 = sitk.ReadImage(sys.argv[1])
image_2 = sitk.ReadImage(sys.argv[2])

# Join two N-D Vector images to form an (N+1)-D image
join = sitk.JoinSeriesImageFilter()
joined_image = join.Execute(image_1, image_2)

# Extract first three channels of joined image (assuming RGB)
select = sitk.VectorIndexSelectionCastImageFilter()
select.SetOutputPixelType(sitk.sitkUInt8)

select.SetIndex(0)
channel1_image = select.Execute(joined_image)
select.SetIndex(1)
channel2_image = select.Execute(joined_image)
select.SetIndex(2)
channel3_image = select.Execute(joined_image)

# Recompose image (should be same as joined_image)
compose = sitk.ComposeImageFilter()
composed_image = compose.Execute(channel1_image, channel2_image, channel3_image)

# Select same subregion using image slicing operator
sliced_image = composed_image[10:40, 10:40, 0]

# Select same subregion using ExtractImageFilter
extract = sitk.ExtractImageFilter()
extract.SetSize([30, 30, 0])
extract.SetIndex([10, 10, 0])
extracted_image = extract.Execute(composed_image)

# Select same sub-region using CropImageFilter (NOTE: CropImageFilter cannot
# reduce dimensions unlike ExtractImageFilter, so cropped_image is a three
# dimensional image with depth of 1)
crop = sitk.CropImageFilter()
crop.SetLowerBoundaryCropSize([10, 10, 0])
crop.SetUpperBoundaryCropSize(
    [composed_image.GetWidth() - 40, composed_image.GetHeight() - 40, 1]
)
cropped_image = crop.Execute(composed_image)

# Print image information to demonstrate variable usage
print(f"Sliced image size: {sliced_image.GetWidth()}x{sliced_image.GetHeight()}x{sliced_image.GetDepth()}")
print(f"Extracted image size: {extracted_image.GetWidth()}x{extracted_image.GetHeight()}x{extracted_image.GetDepth()}")
print(f"Cropped image size: {cropped_image.GetWidth()}x{cropped_image.GetHeight()}x{cropped_image.GetDepth()}")
