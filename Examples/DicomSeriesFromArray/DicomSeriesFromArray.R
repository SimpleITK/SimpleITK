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
# Run with:
#
# Rscript --vanilla DicomSeriesFromArray.R output_directory int
#

library(SimpleITK)

writeSlices <- function(series_tag_values, new_img, out_dir, i) {
    image_slice <- new_img[1:new_img$GetWidth(), 1:new_img$GetHeight(), i]

    # Tags shared by the series.
    lapply(1:nrow(series_tag_values),
      function(tag_index){image_slice$SetMetaData(series_tag_values[tag_index, 1], series_tag_values[tag_index, 2])})

    # Slice specific tags.
    image_slice$SetMetaData("0008|0012", format(Sys.time(), "%H%M%S")) # Instance Creation Date
    image_slice$SetMetaData("0008|0013", format(Sys.time(), "%Y%m%d")) # Instance Creation Time

    # Setting the type to CT preserves the slice location.
    image_slice$SetMetaData("0008|0060", "CT")  # set the type to CT so the thickness is carried over

    # (0020, 0032) image position patient determines the 3D spacing between slices.
    image_slice$SetMetaData("0020|0032", paste(new_img$TransformIndexToPhysicalPoint(c(0,0,i)), collapse='\\')) # Image Position (Patient)
    image_slice$SetMetaData("0020,0013", i-1) # Instance Number

    # Write to the output directory and add the extension dcm, to force writing in DICOM format.
    writer$SetFileName(file.path(out_dir, paste(i-1, '.dcm', sep="")))
    writer$Execute(image_slice)
}


args <- commandArgs( TRUE )
if (length(args) < 2) {
   stop("Two arguments expected - output_directory pixel_type [int, float]")
}

# Create a new series from an array
image_dim = c(5,4,3)

if( args[[2]] == "int" ) {
  new_arr = array(as.integer(runif(60, min=-10, max=10)), dim=image_dim)
} else if( args[[2]] == "float" ) {
    new_arr = array(runif(60, min=-10, max=10), dim=image_dim)
} else {
  stop("Unexpected pixel type, valid values are [int, float].")
}

new_img <- as.image(new_arr)
new_img$SetSpacing(c(2.5,3.5,4.5))

# Write the 3D image as a series
# IMPORTANT: There are many DICOM tags that need to be updated when you modify an
#            original image. This is a delicate opration and requires knowlege of
#            the DICOM standard. This example only modifies some. For a more complete
#            list of tags that need to be modified see:
#                           http://gdcm.sourceforge.net/wiki/index.php/Writing_DICOM
#            If it is critical for your work to generate valid DICOM files,
#            It is recommended to use David Clunie's Dicom3tools to validate the files
#                           (http://www.dclunie.com/dicom3tools.html).

writer <- ImageFileWriter()
# Use the study/series/frame of reference information given in the meta-data
# dictionary and not the automatically generated information from the file IO
writer$KeepOriginalImageUIDOn()

modification_time <- format(Sys.time(), "%H%M%S")
modification_date <- format(Sys.time(), "%Y%m%d")

# Copy some of the tags and add the relevant tags indicating the change.
# For the series instance UID (0020|000e), each of the components is a number, cannot start
# with zero, and separated by a '.' We create a unique series ID using the date and time.
# tags of interest:
direction <- new_img$GetDirection()

series_tag_values <- c("0008|0031",modification_time, # Series Time
                       "0008|0021",modification_date, # Series Date
                       "0008|0008","DERIVED\\SECONDARY", # Image Type
                       "0020|000e", paste("1.2.826.0.1.3680043.2.1125.",modification_date,".1",modification_time, sep=''), # Series Instance UID
                       "0020|0037", paste(direction[[1]], direction[[4]], direction[[7]],# Image Orientation (Patient)
                                          direction[[2]],direction[[5]],direction[[8]], sep='\\'),
                       "0008|103e", "Created-SimpleITK")

if(args[[2]] == "float") {
    # If we want to write floating point values, we need to use the rescale slope, "0028|1053", to select the
    # number of digits we want to keep. We also need to specify additional pixel storage and representation
    # information.
    rescale_slope <- 0.001 #keep three digits after the decimal point
    series_tag_values <- c(series_tag_values,
                           c("0028|1053", paste(rescale_slope), #rescale slope
                             "0028|1052","0",   #rescale intercept
                             "0028|0100", "16", #bits allocated
                             "0028|0101", "16", #bits stored
                             "0028|0102", "15", #high bit
                             "0028|0103", "1")) #pixel representation
}

series_tag_values <- matrix(series_tag_values, nrow=length(series_tag_values)/2, ncol=2, byrow=TRUE) # Series Description

# Write slices to output directory
invisible(lapply(1:(new_img$GetDepth()), function(i){writeSlices(series_tag_values, new_img, args[[1]], i)}))

# Re-read the series
# Read the original series. First obtain the series file names using the
# image series reader.
data_directory <- args[[1]]
series_IDs <- ImageSeriesReader_GetGDCMSeriesIDs(data_directory)
if (length(series_IDs)==0) {
    stop("ERROR: given directory \"", data_directory, "\" does not contain a DICOM series.")
}
series_file_names <- ImageSeriesReader_GetGDCMSeriesFileNames(data_directory, series_IDs[[1]])

series_reader <- ImageSeriesReader()
series_reader$SetFileNames(series_file_names)

# Configure the reader to load all of the DICOM tags (public+private):
# By default tags are not loaded (saves time).
# By default if tags are loaded, the private tags are not loaded.
# We explicitly configure the reader to load tags, including the
# private ones.
series_reader$LoadPrivateTagsOn()
image3D <- series_reader$Execute()
cat(image3D$GetSpacing(),'vs',new_img$GetSpacing(),'\n')
