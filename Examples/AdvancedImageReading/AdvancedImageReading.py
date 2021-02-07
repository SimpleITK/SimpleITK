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

import sys

import SimpleITK as sitk
import numpy as np

if len(sys.argv) < 2:
    print('Wrong number of arguments.', file=sys.stderr)
    print('Usage: ' + __file__ + ' image_file_name', file=sys.stderr)
    sys.exit(1)

# Read image information without reading the bulk data.
file_reader = sitk.ImageFileReader()
file_reader.SetFileName(sys.argv[1])
file_reader.ReadImageInformation()
print(f'image size: {file_reader.GetSize()}\nimage spacing: {file_reader.GetSpacing()}')
# Some files have a rich meta-data dictionary (e.g. DICOM)
for key in file_reader.GetMetaDataKeys():
    print(key + ': ' + file_reader.GetMetaData(key))
print('-' * 20)

# When low on memory, we can incrementally work on sub-images. The following
# subtracts two images (ok, the same image) by reading them as multiple'
# sub-images.

image1_file_name = sys.argv[1]
image2_file_name = sys.argv[1]

parts = 5  # Number of sub-regions we use

file_reader = sitk.ImageFileReader()
file_reader.SetFileName(image1_file_name)
file_reader.ReadImageInformation()
image_size = file_reader.GetSize()

result_img = sitk.Image(file_reader.GetSize(), file_reader.GetPixelID(),
                        file_reader.GetNumberOfComponents())
result_img.SetSpacing(file_reader.GetSpacing())
result_img.SetOrigin(file_reader.GetOrigin())
result_img.SetDirection(file_reader.GetDirection())

extract_size = list(file_reader.GetSize())
extract_size[-1] = extract_size[-1] // parts
current_index = [0] * file_reader.GetDimension()
for i in range(parts):
    if i == (parts - 1):
        extract_size[-1] = image_size[-1] - current_index[-1]
    file_reader.SetFileName(image1_file_name)
    file_reader.SetExtractIndex(current_index)
    file_reader.SetExtractSize(extract_size)
    sub_image1 = file_reader.Execute()

    file_reader.SetFileName(image2_file_name)
    file_reader.SetExtractIndex(current_index)
    file_reader.SetExtractSize(extract_size)
    sub_image2 = file_reader.Execute()
    idx = [slice(None,None)]*file_reader.GetDimension()
    idx[-1] = current_index[-1]
    result_img[idx] =  sub_image1 - sub_image2
    current_index[-1] += extract_size[-1]
del sub_image1
del sub_image2

# Check that our iterative approach is equivalent to reading the whole images.
if np.any(sitk.GetArrayViewFromImage(result_img
                                     - sitk.ReadImage(image1_file_name)
                                     + sitk.ReadImage(image2_file_name))):
    print('Subtraction error.')
    sys.exit(1)
sys.exit(0)
