#=========================================================================
#
#  Copyright Insight Software Consortium
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
#=========================================================================

from __future__ import print_function

import SimpleITK as sitk

import sys, time, os

if len( sys.argv ) < 3:
    print( "Usage: python " + __file__ + " <input_directory_with_DICOM_series> <output_directory>" )
    sys.exit ( 1 )


# Read the original series. First obtain the series file names using the
# image series reader.
data_directory = sys.argv[1]
series_IDs = sitk.ImageSeriesReader.GetGDCMSeriesIDs(data_directory)
if not series_IDs:
    print("ERROR: given directory \""+data_directory+"\" does not contain a DICOM series.")
    sys.exit(1)
series_file_names = sitk.ImageSeriesReader.GetGDCMSeriesFileNames(data_directory, series_IDs[0])

# Second, to construct a proper volume from the series we must read
# the series with the image series reader.
series_reader = sitk.ImageSeriesReader()
series_reader.SetFileNames(series_file_names)
image3D = series_reader.Execute()

# Lastly, to load the image's DICOM meta-data dictionaries, we read
# each image using an image reader that is set to load all DICOM tags
# (public+private). The resulting images contain their DICOM
# meta-data dictionaries.
image_reader = sitk.ImageFileReader()
image_reader.LoadPrivateTagsOn()
image_list = []
for file_name in series_file_names:
    image_reader.SetFileName(file_name)
    img = image_reader.Execute()
    image_list.append(img)



# Modify the image (blurring)
filtered_image = sitk.DiscreteGaussian(image3D)

# Write the 3D image as a series
# IMPORTANT: There are many DICOM tags that need to be updated when you modify an
#            original image. This is a delicate opration and requires knowlege of
#            the DICOM standard. This example only modifies some. For a more complete
#            list of tags that need to be modified see:
#                           http://gdcm.sourceforge.net/wiki/index.php/Writing_DICOM

writer = sitk.ImageFileWriter()
# Use the study/seriers/frame of reference information given in the meta-data
# dictionary and not the automatically generated information from the file IO
writer.KeepOriginalImageUIDOn()
modification_time = time.strftime("%H%M%S")
modification_date = time.strftime("%Y%m%d")
for i in range(filtered_image.GetDepth()):
    image_slice = filtered_image[:,:,i]
    original_slice = image_list[i]
    # Copy the meta-data except the rescale-intercept, rescale-slope
    for k in original_slice.GetMetaDataKeys():
        if k!="0028|1052" and k!= "0028|1053":
            image_slice.SetMetaData(k, original_slice.GetMetaData(k))
    # Set relevant keys indicating the change, modify or remove private tags as needed
    image_slice.SetMetaData("0008|0031", modification_time)
    image_slice.SetMetaData("0008|0021", modification_date)
    image_slice.SetMetaData("0008|0008", "DERIVED\SECONDARY")
    # Each of the UID components is a number (cannot start with zero) and separated by a '.'
    # We create a unique series ID using the date and time.
    image_slice.SetMetaData("0020|000e", "1.2.826.0.1.3680043.2.1125."+modification_date+".1"+modification_time)
    # Write to the output directory and add the extension dcm if not there, to force writing is in DICOM format.
    writer.SetFileName(os.path.join(sys.argv[2], os.path.basename(series_file_names[i])) + ('' if os.path.splitext(series_file_names[i])[1] == '.dcm' else '.dcm'))
    writer.Execute(image_slice)
sys.exit( 0 )
