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
# Run with:
#
# Rscript --vanilla DicomImagePrintTags.R input_file
#

library(SimpleITK)

args <- commandArgs( TRUE )

if (length(args) <  1) {
   write("Usage arguments: <input_file>", stderr())
   quit(1)
}

inputImage <- ReadImage(args[[1]])

keys <- inputImage$GetMetaDataKeys()

for ( k in keys)
{
 print(sprintf("(%s) = \"%s\"", k, inputImage$GetMetaData(k)))
}
