#=========================================================================
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
#=========================================================================

library(SimpleITK)

args <- commandArgs( TRUE )

if (length(args) < 2) {
   write("Usage arguments: <input_directory_with_DICOM_series> <output_directory>", stderr())
   quit(save="no", status=1)
}

# Read the original series. First obtain the series file names using the
# image series reader.
data_directory <- args[1]
series_IDs <- ImageSeriesReader_GetGDCMSeriesIDs(data_directory)
if(length(series_IDs)==0) {
    write(paste0("ERROR: given directory \"",data_directory,"\" does not contain a DICOM series."))
    quit(save="no", status=1)
}
series_file_names <- ImageSeriesReader_GetGDCMSeriesFileNames(data_directory, series_IDs[1])

series_reader <- ImageSeriesReader()
series_reader$SetFileNames(series_file_names)

# Configure the reader to load all of the DICOM tags (public+private):
# By default tags are not loaded (saves time).
# By default if tags are loaded, the private tags are not loaded.
# We explicitly configure the reader to load tags, including the
# private ones.
series_reader$MetaDataDictionaryArrayUpdateOn()
series_reader$LoadPrivateTagsOn()
image3D <- series_reader$Execute()

# Modify the image (blurring)
filtered_image <- DiscreteGaussian(image3D)

# Write the 3D image as a series
# IMPORTANT: There are many DICOM tags that need to be updated when you modify an
#            original image. This is a delicate opration and requires knowlege of
#            the DICOM standard. This example only modifies some. For a more complete
#            list of tags that need to be modified see:
#                           http://gdcm.sourceforge.net/wiki/index.php/Writing_DICOM

writer <- ImageFileWriter()
# Use the study/series/frame of reference information given in the meta-data
# dictionary and not the automatically generated information from the file IO
writer$KeepOriginalImageUIDOn()

# Copy relevant tags from the original meta-data dictionary (private tags are also
# accessible).
tags_to_copy <- c("0010|0010", # Patient Name
                "0010|0020", # Patient ID
                "0010|0030", # Patient Birth Date
                "0020|000D", # Study Instance UID, for machine consumption
                "0020|0010", # Study ID, for human consumption
                "0008|0020", # Study Date
                "0008|0030", # Study Time
                "0008|0050", # Accession Number
                "0008|0060"  # Modality
)

modification_time <- format(Sys.time(), "%H%M%S")
modification_date <- format(Sys.time(), "%Y%m%d")

# Copy some of the tags and add the relevant tags indicating the change.
# When attempting to copy we are not ensured that the tags exist, in which case
# we get a NULL as an entry in the list returned by lapply, these are removed
# by the Filter.
# For the series instance UID (0020|000e), each of the components is a number, cannot start
# with zero, and separated by a '.' We create a unique series ID using the date and time.
# tags of interest:
direction <- filtered_image$GetDirection()
series_tag_values <- c(Filter(Negate(is.null),
                             lapply(tags_to_copy,
                             function(k) {
                               if(series_reader$HasMetaDataKey(0,k)) {
                                 list(k, series_reader$GetMetaData(0,k))
                                }
                             })),
                        list(list("0008|0031",modification_time), # Series Time
                             list("0008|0021",modification_date), # Series Date
                             list("0008|0008","DERIVED\\SECONDARY"), # Image Type
                             list("0020|000e", paste0("1.2.826.0.1.3680043.2.1125.",modification_date,".1",modification_time)), # Series Instance UID
                             list("0020|0037", paste(c(direction[1], direction[4], direction[7],
                                                       direction[2],direction[5],direction[8]), collapse="\\")), # Image Orientation (Patient)
                             list("0008|103e", paste0(series_reader$GetMetaData(0,"0008|103e"), " Processed-SimpleITK")))) # Series Description

for(i in 1:filtered_image$GetDepth()) {
  image_slice <- filtered_image[,,i]
  # Tags shared by the series.
  invisible(lapply(series_tag_values,
                   function(tag_value) {image_slice$SetMetaData(tag_value[1], tag_value[2])}))
  # Slice specific tags.
  image_slice$SetMetaData("0008|0012", format(Sys.time(), "%Y%m%d")) # Instance Creation Date
  image_slice$SetMetaData("0008|0013", format(Sys.time(), "%H%M%S")) # Instance Creation Time
  image_slice$SetMetaData("0020|0032", paste(filtered_image$TransformIndexToPhysicalPoint(c(0,0,i-1)), collapse="\\")) # Image Position (Patient)
  image_slice$SetMetaData("0020|0013", as.character(i)) # Instance Number

  # Write to the output directory and add the extension dcm, to force writing in DICOM format.
  writer$SetFileName(file.path(args[[2]], sprintf("%d.dcm",i)))
  writer$Execute(image_slice)
}

quit(save="no", status=0)
