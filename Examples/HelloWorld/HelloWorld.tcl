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


# Create an image
set pixelType $sitkUInt16
set imageSize { 128 128 }
Image img   $imageSize $pixelType

# Create a face
set faceSize   { 64 64 }
set faceCenter { 64 64 }
set face       [ GaussianSource $pixelType $imageSize $faceSize $faceCenter ]

# Create eye images
set eyeSize    { 5 5 }
set eye1Center { 48 48 }
set eye2Center { 80 48 }
set eye1       [ GaussianSource $pixelType $imageSize $eyeSize $eye1Center 150 ]
set eye2       [ GaussianSource $pixelType $imageSize $eyeSize $eye2Center 150 ]

# Apply the eyes to the face
set face [ Subtract $face $eye1 ]
set face [ Subtract $face $eye2 ]
set face [ BinaryThreshold $face 200 255 255 ]

# Create the mouth
set mouthRadii  { 30 20 }
set mouthCenter { 64 76 }
set mouth [ GaussianSource $pixelType $imageSize $mouthRadii $mouthCenter ]
set mouth [ Subtract 255 [ BinaryThreshold $mouth 200 255 255 ] ]

# Paste the mouth onto the face
set mouthSize { 64 18 }
set mouthLoc  { 32 76 }
set face [ Paste $face $mouth $mouthSize $mouthLoc $mouthLoc ]

# Apply the face to the original image
set img $face

# Display the results
if { ![info exists ::env(SITK_NOSHOW)] } {
    Show $img "Hello World: TCL" 1
}
