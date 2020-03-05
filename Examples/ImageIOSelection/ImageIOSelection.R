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
# Rscript --vanilla IOSelection.R
#

library(SimpleITK)

args <- commandArgs( TRUE )

if (length(args) < 1) {
   write('Usage arguments: <image_file_name>', stderr())
   quit(save="no", status=1)
}

# Find out which image IOs are supported
file_reader <- ImageFileReader()
image_ios <- file_reader$GetRegisteredImageIOs()
cat('The supported image IOs are: ', image_ios, '\n')
cat(rep('-',20),'\n', sep='')

# Another option is to just print the reader and see which
# IOs are supported
print(file_reader)
cat(rep('-',20),'\n', sep='')

# Force the use of a specific IO.
file_reader$SetImageIO('PNGImageIO')
file_reader$SetFileName(args[1])

# If the IO doesn't support reading the image type it
# will throw an exception.
image <- tryCatch(file_reader$Execute(),
                  warning = function(err) {
                      message(err)
                      quit(save="no", status=1)
                  }
                  )
cat('Read image:',args[1],'\n')
quit(save="no", status=0)
