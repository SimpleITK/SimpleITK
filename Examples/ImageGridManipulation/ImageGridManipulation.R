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
# Rscript --vanilla ImageGridManipulation.R input-1 input-2
#

library(SimpleITK)

args <- commandArgs( TRUE )

if (length(args) <  2){
   write("Usage arguments: <input-1> <input-2>", stderr())
   quit(save="no", status=1)
}

# Two vector images of same pixel type and dimension expected
reader <- ImageFileReader()
reader$SetFileName(args[[1]])
image_1 <- reader$Execute()
reader$SetFileName(args[[2]])
image_2 <- reader$Execute()

# Join two N-D Vector images to form an (N+1)-D image
join <- JoinSeriesImageFilter()
joined_image <- join$Execute( image_1, image_2 )

# Extract first three channels of joined image (assuming RGB)
select <- VectorIndexSelectionCastImageFilter()
channel1_image <- select$Execute(joined_image, 0, "sitkUInt8")
channel2_image <- select$Execute(joined_image, 1, "sitkUInt8")
channel3_image <- select$Execute(joined_image, 2, "sitkUInt8")

# Recompose image (should be same as joined_image)
compose <- ComposeImageFilter()
composed_image <- compose$Execute(channel1_image, channel2_image, channel3_image)

# Select same subregion using image slicing operator
sliced_image = composed_image[101:400, 101:400, 1]

# Select same subregion using ExtractImageFilter
extract <- ExtractImageFilter()
extract$SetSize( list(300, 300, 0) )
extract$SetIndex( list(100, 100, 0) )
extracted_image <- extract$Execute(composed_image)

# Select same subregion using CropImageFilter (NOTE: CropImageFilter cannot reduce dimensions
# unlike ExtractImageFilter, so cropped_image is a three dimensional image with depth of 1)
crop <- CropImageFilter()
crop$SetLowerBoundaryCropSize( list(100, 100, 0) )
crop$SetUpperBoundaryCropSize( list(composed_image$GetWidth()-400, composed_image$GetHeight()-400, 1) )
cropped_image <- crop$Execute(composed_image)
