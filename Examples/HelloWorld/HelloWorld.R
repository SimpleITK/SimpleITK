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
#

library(SimpleITK)

# Create an image
pixelType <- 'sitkUInt8'
imageSize <- c( 128, 128 )
image     <- Image( imageSize, pixelType )

# Create a face image
faceSize   <- c( 64, 64)
faceCenter <- c( 64, 64)
face       <- GaussianSource( pixelType, imageSize, faceSize, faceCenter )

# Create eye images
eyeSize    <- c( 5, 5 )
eye2Center <- c( 48, 48 )
eye1Center <- c( 80, 48 )
eye1       <- GaussianSource( pixelType, imageSize, eyeSize, eye1Center, 150 )
eye2       <- GaussianSource( pixelType, imageSize, eyeSize, eye2Center, 150 )

# Apply the eyes to the face
face <- face - eye1 - eye2
face <- BinaryThreshold( face, 200, 255, 255 )

# Create the mouth
mouthRadii  <- c( 30, 20 )
mouthCenter <- c( 64, 76 )
mouth       <- 255 - BinaryThreshold( GaussianSource( pixelType, imageSize, mouthRadii, mouthCenter ),
                                      200, 255, 255 )
# Paste mouth onto the face
mouthSize <- c( 64, 18 )
mouthLoc  <- c( 32, 76 )
face = Paste( face, mouth, mouthSize, mouthLoc, mouthLoc )

# Apply the face to the original image
image <- image + face

# Display the results
if(Sys.getenv("SITK_NOSHOW") == "") {
    Show(image, "Hello World: R", debugOn=TRUE)
}
