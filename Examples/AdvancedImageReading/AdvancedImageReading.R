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
# Rscript --vanilla AdvancedImageReading.R
#

library(SimpleITK)

args <- commandArgs( TRUE )

if (length(args) < 1) {
   write('Usage arguments: <image_file_name>', stderr())
   quit(save="no", status=1)
}

# Read image information without reading the bulk data.
file_reader <- ImageFileReader()
file_reader$SetFileName(args[1])
file_reader$ReadImageInformation()
cat('image size:', file_reader$GetSize(), '\n')
cat('image spacing:', file_reader$GetSpacing(), '\n')
# Some files have a rich meta-data dictionary (e.g. DICOM)
for(key in file_reader$GetMetaDataKeys())
{
  cat(paste0(key, ': ', file_reader$GetMetaData(key), '\n'))
}
cat(rep('-',20),'\n', sep='')

# When low on memory, we can incrementally work on sub-images. The following
# subtracts two images (ok, the same image) by reading them as multiple sub-images.

image1_file_name <- args[1]
image2_file_name <- args[1]

parts <- 5 # Number of sub-regions we use

file_reader <- ImageFileReader()
file_reader$SetFileName(image1_file_name)
file_reader$ReadImageInformation()
image_size <- file_reader$GetSize()

result_img <- Image(file_reader$GetSize(), file_reader$GetPixelID(), file_reader$GetNumberOfComponents())
result_img$SetSpacing(file_reader$GetSpacing())
result_img$SetOrigin(file_reader$GetOrigin())
result_img$SetDirection(file_reader$GetDirection())

extract_size <- file_reader$GetSize()
extract_size[-1] <- extract_size[-1]%/%parts
current_index <- rep(0,file_reader$GetDimension())
for(i in 1:parts)
{
  if(i == parts)
  {
    extract_size[-1] <- image_size[-1] - current_index[-1]
  }
  file_reader$SetFileName(image1_file_name)
  file_reader$SetExtractIndex(current_index)
  file_reader$SetExtractSize(extract_size)
  sub_image1 <- file_reader$Execute()

  file_reader$SetFileName(image2_file_name)
  file_reader$SetExtractIndex(current_index)
  file_reader$SetExtractSize(extract_size)
  sub_image2 <- file_reader$Execute()
  result_img <- Paste(result_img, sub_image1 - sub_image2, extract_size, rep(0,file_reader$GetDimension()), current_index)
  current_index[-1] <- current_index[-1] + extract_size[-1]
}

rm(sub_image1, sub_image2)

# Check that our iterative approach is equivalent to reading the whole images.
if(any(as.array(result_img - ReadImage(image1_file_name) + ReadImage(image2_file_name))!=0))
{
  cat('Subtraction error.\n')
  quit(save="no", status=1)
}
quit(save="no", status=0)
