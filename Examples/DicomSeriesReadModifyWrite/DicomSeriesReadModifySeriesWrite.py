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
import time
import os

if len(sys.argv) < 3:
    print("Usage: python " + __file__ +
          " <input_directory_with_DICOM_series> <output_directory>")
    sys.exit(1)

# Read the original series. First obtain the series file names using the
# image series reader.
data_directory = sys.argv[1]
series_IDs = sitk.ImageSeriesReader.GetGDCMSeriesIDs(data_directory)
if not series_IDs:
    print("ERROR: given directory \"" + data_directory +
          "\" does not contain a DICOM series.")
    sys.exit(1)
series_file_names = sitk.ImageSeriesReader.GetGDCMSeriesFileNames(
    data_directory, series_IDs[0])

series_reader = sitk.ImageSeriesReader()
series_reader.SetFileNames(series_file_names)

# Configure the reader to load all of the DICOM tags (public+private):
# By default tags are not loaded (saves time).
# By default if tags are loaded, the private tags are not loaded.
# We explicitly configure the reader to load tags, including the
# private ones.
series_reader.MetaDataDictionaryArrayUpdateOn()
series_reader.LoadPrivateTagsOn()
image3D = series_reader.Execute()

# Modify the image (blurring)
filtered_image = sitk.DiscreteGaussian(image3D)

# Write the 3D image as a series
# IMPORTANT: There are many DICOM tags that need to be updated when you modify
#            an original image. This is a delicate opration and requires
#            knowledge of the DICOM standard. This example only modifies some.
#            For a more complete list of tags that need to be modified see:
#                http://gdcm.sourceforge.net/wiki/index.php/Writing_DICOM

writer = sitk.ImageFileWriter()
# Use the study/series/frame of reference information given in the meta-data
# dictionary and not the automatically generated information from the file IO
writer.KeepOriginalImageUIDOn()

# Copy relevant tags from the original meta-data dictionary (private tags are
# also accessible).
tags_to_copy = ["0010|0010",  # Patient Name
                "0010|0020",  # Patient ID
                "0010|0030",  # Patient Birth Date
                "0020|000D",  # Study Instance UID, for machine consumption
                "0020|0010",  # Study ID, for human consumption
                "0008|0020",  # Study Date
                "0008|0030",  # Study Time
                "0008|0050",  # Accession Number
                "0008|0060"  # Modality
                ]

modification_time = time.strftime("%H%M%S")
modification_date = time.strftime("%Y%m%d")

# Copy some of the tags and add the relevant tags indicating the change.
# For the series instance UID (0020|000e), each of the components is a number,
# cannot start with zero, and separated by a '.' We create a unique series ID
# using the date and time.
# Tags of interest:
direction = filtered_image.GetDirection()
series_tag_values = [
                        (k, series_reader.GetMetaData(0, k))
                        for k in tags_to_copy
                        if series_reader.HasMetaDataKey(0, k)] + \
                    [("0008|0031", modification_time),  # Series Time
                     ("0008|0021", modification_date),  # Series Date
                     ("0008|0008", "DERIVED\\SECONDARY"),  # Image Type
                     ("0020|000e", "1.2.826.0.1.3680043.2.1125." +
                      modification_date + ".1" + modification_time),
                     # Series Instance UID
                     ("0020|0037",
                      '\\'.join(map(str, (direction[0], direction[3],
                                          direction[6],
                                          # Image Orientation (Patient)
                                          direction[1], direction[4],
                                          direction[7])))),
                     ("0008|103e",
                      series_reader.GetMetaData(0, "0008|103e")
                      + " Processed-SimpleITK")]  # Series Description

for i in range(filtered_image.GetDepth()):
    image_slice = filtered_image[:, :, i]
    # Tags shared by the series.
    for tag, value in series_tag_values:
        image_slice.SetMetaData(tag, value)
    # Slice specific tags.
    #   Instance Creation Date
    image_slice.SetMetaData("0008|0012", time.strftime("%Y%m%d"))
    #   Instance Creation Time
    image_slice.SetMetaData("0008|0013", time.strftime("%H%M%S"))
    #   Image Position (Patient)
    image_slice.SetMetaData("0020|0032", '\\'.join(
        map(str, filtered_image.TransformIndexToPhysicalPoint((0, 0, i)))))
    #   Instace Number
    image_slice.SetMetaData("0020|0013", str(i))

    # Write to the output directory and add the extension dcm, to force writing
    # in DICOM format.
    writer.SetFileName(os.path.join(sys.argv[2], str(i) + '.dcm'))
    writer.Execute(image_slice)
sys.exit(0)
