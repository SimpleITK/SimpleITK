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
# Rscript --vanilla DicomConvert.R root_of_data_directory output_file_extension --w new_image_width --od output_directory
#

library(SimpleITK)
library(argparser)

convert_image <- function(input_file_name, output_file_name, new_width = NA)
{
  image_file_reader = ImageFileReader()
  # only read DICOM images
  image_file_reader$SetImageIO('GDCMImageIO')
  image_file_reader$SetFileName(input_file_name)
  try(image_file_reader$ReadImageInformation(), silent = TRUE)
  image_size <- image_file_reader$GetSize()
  #if this isn't a DICOM image return FALSE
  if(length(image_size) == 0) {
    return(FALSE)
  }
  if(length(image_size) == 3 & image_size[3] == 1) {
    image_size[3] <- 0
    image_file_reader$SetExtractSize(image_size)
  }
  image <- NULL
  try(image <- image_file_reader$Execute(), silent = TRUE)
  if(is.null(image))
  {
    return(FALSE)
  }
  if(!is.na(new_width))
  {
    original_size <- image$GetSize()
    original_spacing <- image$GetSpacing()
    new_spacing <- c((original_size[1]-1)*original_spacing[1]/(new_width-1),
                    (original_size[1]-1)*original_spacing[1]/(new_width-1))
    new_size <- c(new_width, as.integer((original_size[2]-1)*original_spacing[2]/new_spacing[2]))
    image <- Resample(image, new_size, Transform(), 'sitkLinear',
                      image$GetOrigin(), new_spacing, image$GetDirection(),0,
                      image$GetPixelID())
  }
  # If a single channel image, rescale to [0,255]. Also modify the intensity values based
  # on the photomertic interpretation. If MONOCHROME2 (minimum should be displayed as black) we
  # don't need to do anything, if image has MONOCRHOME1 (minimum should be displayed as white) we flip
  # the intensities. This is a constraint imposed by ITK which always assumes MONOCHROME2.
  if(image$GetNumberOfComponentsPerPixel() == 1)
  {
    image <- RescaleIntensity(image, 0, 255)
    if(trimws(image_file_reader$GetMetaData('0028|0004')) == 'MONOCHROME1')
    {
      image <-  InvertIntensity(image, maximum=255)
    }
    image <- Cast(image, 'sitkUInt8')
  }
  WriteImage(image, output_file_name)
  return(TRUE)
 }

parser<-arg_parser('Convert and resize DICOM files to common image types.')
parser<-add_argument(parser, 'root_of_data_directory', help='Path to the topmost directory containing data.')
parser<-add_argument(parser, 'output_file_extension', help='Image file extension, this determines output file type (e.g. png) .')
parser<-add_argument(parser, '--w', help='Width of converted images.')
parser<-add_argument(parser, '--od', help='Output directory.')
argv<-parse_args(parser)

input_file_names <- list.files(argv$root_of_data_directory, recursive=TRUE, full.names=TRUE)
if(!is.na(argv$od)) {
  # if all output files are written to the same directory we need them to have a unique name, so use an index.
  file_names <- lapply(seq_len(length(input_file_names)), function(new_file_name) return(file.path(argv$od, toString(new_file_name))))
} else {
  file_names <- input_file_names
}
#append the file extension to the output file names
output_file_names <- lapply(file_names, function(file_name) return(paste0(file_name,'.',argv$output_file_extension)))
res <- mapply(convert_image, input_file_names, output_file_names, new_width=as.integer(argv$w), SIMPLIFY=FALSE)
df <- data.frame(input_file_name = unlist(input_file_names[unlist(res)]),
                output_file_name = unlist(output_file_names[unlist(res)]))
dir_name <- if(!is.na(argv$od)) argv$od else getwd()
write.csv(df,file.path(dir_name, 'file_names.csv'), row.names=FALSE)
