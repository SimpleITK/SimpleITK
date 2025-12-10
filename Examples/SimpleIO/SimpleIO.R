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
# Rscript --vanilla SimpleIO  input output
#

# These examples are used in the I/O documentation page. The IO.rst file
# pulls the code examples based their line numbers in this file. So any
# change in the line numbers of the code below will break the I/O page.


example1 <- function(inputImageFileName, outputImageFileName) {
  library(SimpleITK)

  #START_OO_IMAGE_READER_WRITER_EXAMPLE
  reader <- ImageFileReader()
  reader$SetImageIO("PNGImageIO")
  reader$SetFileName(inputImageFileName)
  image <- reader$Execute()

  writer <- ImageFileWriter()
  writer$SetFileName(outputImageFileName)
  writer$Execute(image)
  #END_OO_IMAGE_READER_WRITER_EXAMPLE
}

example2 <- function(inputImageFileName, outputImageFileName) {
  library(SimpleITK)

  #START_PROCEDURAL_IMAGE_READER_WRITER_EXAMPLE
  image <- ReadImage(inputImageFileName)
  WriteImage(image, outputImageFileName)
  #END_PROCEDURAL_IMAGE_READER_WRITER_EXAMPLE
}

example3 <- function() {
  library(SimpleITK)

  #START_PROCEDURAL_TRANSFORM_READER_WRITER_EXAMPLE
  basic_transform <- Euler2DTransform()
  basic_transform$SetTranslation(c(2,3))

  file_name <- 'euler2D_r.tfm'
  WriteTransform(basic_transform, file_name)
  read_result = ReadTransform(file_name)

  stopifnot(read_result$GetName() != basic_transform$GetName())
  #END_PROCEDURAL_TRANSFORM_READER_WRITER_EXAMPLE
}

args <- commandArgs( TRUE )

example1(args[[1]], args[[2]])
example2(args[[1]], args[[2]])
example3()
