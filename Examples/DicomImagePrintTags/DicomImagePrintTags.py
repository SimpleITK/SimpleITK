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

""" A SimpleITK example demonstrating how to print a DICOM image's tags. """

import sys
import SimpleITK as sitk

def main(args):
    """ A SimpleITK script that prints a DICOM image's tags. """
    if len(args) < 2:
        print("Usage: DicomImagePrintTags <input_file>")
        sys.exit(1)

    reader = sitk.ImageFileReader()

    reader.SetFileName(args[1])
    reader.LoadPrivateTagsOn()

    reader.ReadImageInformation()

    for k in reader.GetMetaDataKeys():
        v = reader.GetMetaData(k)
        print(f'({k}) = = "{v}"')

    print(f"Image Size: {reader.GetSize()}")
    print(f"Image PixelType: {sitk.GetPixelIDValueAsString(reader.GetPixelID())}")


if __name__ == "__main__":
    main(sys.argv)
