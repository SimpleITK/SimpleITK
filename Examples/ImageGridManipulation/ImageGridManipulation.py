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

from __future__ import print_function

import SimpleITK as sitk
import sys

if len(sys.argv) < 3:
    print("Usage: " + sys.argv[0] + " <input-1> <input-2>")
    sys.exit(1)

# Two vector images of same pixel type and dimension expected
image_1 = sitk.ReadImage(sys.argv[1])
image_2 = sitk.ReadImage(sys.argv[2])

# Join two N-D Vector images to form an (N+1)-D image
join = sitk.JoinSeriesImageFilter()
joined_image = join.Execute(image_1, image_2)

# Extract first three channels of joined image (assuming RGB)
select = sitk.VectorIndexSelectionCastImageFilter()
channel1_image = select.Execute(joined_image, 0, sitk.sitkUInt8)
channel2_image = select.Execute(joined_image, 1, sitk.sitkUInt8)
channel3_image = select.Execute(joined_image, 2, sitk.sitkUInt8)

# Recompose image (should be same as joined_image)
compose = sitk.ComposeImageFilter()
composed_image = compose.Execute(channel1_image, channel2_image,
                                 channel3_image)

# Select same subregion using image slicing operator
sliced_image = composed_image[100:400, 100:400, 0]

# Select same subregion using ExtractImageFilter
extract = sitk.ExtractImageFilter()
extract.SetSize([300, 300, 0])
extract.SetIndex([100, 100, 0])
extracted_image = extract.Execute(composed_image)

# Select same sub-region using CropImageFilter (NOTE: CropImageFilter cannot
# reduce dimensions unlike ExtractImageFilter, so cropped_image is a three
# dimensional image with depth of 1)
crop = sitk.CropImageFilter()
crop.SetLowerBoundaryCropSize([100, 100, 0])
crop.SetUpperBoundaryCropSize([composed_image.GetWidth() - 400,
                               composed_image.GetHeight() - 400, 1])
cropped_image = crop.Execute(composed_image)
