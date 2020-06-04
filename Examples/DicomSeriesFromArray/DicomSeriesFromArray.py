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

import SimpleITK as sitk

import sys
import time
import os
import numpy as np

pixel_dtypes = {"int16": np.int16,
                "float64": np.float64}


def writeSlices(series_tag_values, new_img, out_dir, i):
    image_slice = new_img[:, :, i]

    # Tags shared by the series.
    list(map(lambda tag_value: image_slice.SetMetaData(tag_value[0],
                                                       tag_value[1]),
             series_tag_values))

    # Slice specific tags.
    #   Instance Creation Date
    image_slice.SetMetaData("0008|0012", time.strftime("%Y%m%d"))
    #   Instance Creation Time
    image_slice.SetMetaData("0008|0013", time.strftime("%H%M%S"))

    # Setting the type to CT so that the slice location is preserved and
    # the thickness is carried over.
    image_slice.SetMetaData("0008|0060", "CT")

    # (0020, 0032) image position patient determines the 3D spacing between
    # slices.
    #   Image Position (Patient)
    image_slice.SetMetaData("0020|0032", '\\'.join(
        map(str, new_img.TransformIndexToPhysicalPoint((0, 0, i)))))
    #   Instance Number
    image_slice.SetMetaData("0020,0013", str(i))

    # Write to the output directory and add the extension dcm, to force
    # writing in DICOM format.
    writer.SetFileName(os.path.join(out_dir, str(i) + '.dcm'))
    writer.Execute(image_slice)


if len(sys.argv) < 3:
    print("Usage: python " + __file__ + " <output_directory> [" + ", "
          .join(pixel_dtypes) + "]")
    sys.exit(1)

# Create a new series from a numpy array
try:
    pixel_dtype = pixel_dtypes[sys.argv[2]]
except KeyError:
    pixel_dtype = pixel_dtypes["int16"]

new_arr = np.random.uniform(-10, 10, size=(3, 4, 5)).astype(pixel_dtype)
new_img = sitk.GetImageFromArray(new_arr)
new_img.SetSpacing([2.5, 3.5, 4.5])

# Write the 3D image as a series
# IMPORTANT: There are many DICOM tags that need to be updated when you modify
#            an original image. This is a delicate opration and requires
#            knowledge of the DICOM standard. This example only modifies some.
#            For a more complete list of tags that need to be modified see:
#                  http://gdcm.sourceforge.net/wiki/index.php/Writing_DICOM
#            If it is critical for your work to generate valid DICOM files,
#            It is recommended to use David Clunie's Dicom3tools to validate
#            the files:
#                  http://www.dclunie.com/dicom3tools.html

writer = sitk.ImageFileWriter()
# Use the study/series/frame of reference information given in the meta-data
# dictionary and not the automatically generated information from the file IO
writer.KeepOriginalImageUIDOn()

modification_time = time.strftime("%H%M%S")
modification_date = time.strftime("%Y%m%d")

# Copy some of the tags and add the relevant tags indicating the change.
# For the series instance UID (0020|000e), each of the components is a number,
# cannot start with zero, and separated by a '.' We create a unique series ID
# using the date and time. Tags of interest:
direction = new_img.GetDirection()
series_tag_values = [
    ("0008|0031", modification_time),  # Series Time
    ("0008|0021", modification_date),  # Series Date
    ("0008|0008", "DERIVED\\SECONDARY"),  # Image Type
    ("0020|000e", "1.2.826.0.1.3680043.2.1125."
     + modification_date + ".1" + modification_time),  # Series Instance UID
    ("0020|0037", '\\'.join(map(str, (direction[0], direction[3], direction[6],
                                      direction[1], direction[4],
                                      direction[7])))),  # Image Orientation
    # (Patient)
    ("0008|103e", "Created-SimpleITK")  # Series Description
]

if pixel_dtype == np.float64:
    # If we want to write floating point values, we need to use the rescale
    # slope, "0028|1053", to select the number of digits we want to keep. We
    # also need to specify additional pixel storage and representation
    # information.
    rescale_slope = 0.001  # keep three digits after the decimal point
    series_tag_values = series_tag_values + [
        ('0028|1053', str(rescale_slope)),  # rescale slope
        ('0028|1052', '0'),  # rescale intercept
        ('0028|0100', '16'),  # bits allocated
        ('0028|0101', '16'),  # bits stored
        ('0028|0102', '15'),  # high bit
        ('0028|0103', '1')]  # pixel representation

# Write slices to output directory
list(map(lambda i: writeSlices(series_tag_values, new_img, sys.argv[1], i),
         range(new_img.GetDepth())))

# Re-read the series
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
series_reader.LoadPrivateTagsOn()
image3D = series_reader.Execute()
print(image3D.GetSpacing(), 'vs', new_img.GetSpacing())
sys.exit(0)
