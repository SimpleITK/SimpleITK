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
# Rscript --vanilla ImageViewing.R
#

library(SimpleITK)

grid_image <- GridSource(outputPixelType="sitkUInt16", size=c(512,512),
                         sigma=c(0.1,0.1), gridSpacing=c(20.0,20.0))

# Procedural interface, using the default image viewer (Fiji/ImageJ) or
# any viewer specified by the SITK_SHOW_COMMAND environment variable.
Show(grid_image, title = "grid using Show function", debugOn = TRUE)

# Object oriented interface:
image_viewer <- ImageViewer()
image_viewer$SetTitle('grid using ImageViewer class')

# Use the default image viewer.
image_viewer$Execute(grid_image)

# Change viewer, and display again.
image_viewer$SetApplication('/Applications/ITK-SNAP.app/Contents/MacOS/ITK-SNAP')
image_viewer$Execute(grid_image)

# Change the viewer command, (use ITK-SNAP's -z option to open the image in zoomed mode)
image_viewer$SetCommand('/Applications/ITK-SNAP.app/Contents/MacOS/ITK-SNAP -z 2')
image_viewer$Execute(grid_image)
