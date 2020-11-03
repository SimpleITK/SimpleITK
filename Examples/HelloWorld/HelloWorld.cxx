/*=========================================================================
*
*  Copyright NumFOCUS
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/

// This one header will include all SimpleITK filters and external
// objects.
#include <SimpleITK.h>
#include <sitkImageOperators.h>
#include <iostream>
#include <stdlib.h>


// create convenient namespace alias
namespace sitk = itk::simple;

int main ( int argc, char* argv[] ) {

  sitk::PixelIDValueEnum pixelType = sitk::sitkUInt8;
  std::vector<unsigned int> imageSize ( 2, 128 );

  // Create an image
  sitk::Image image( imageSize, pixelType );

  // Create a face image
  std::vector<double> faceSize ( 2, 64.0 );
  std::vector<double> faceCenter ( 2, 64.0 );;
  sitk::Image face = sitk::GaussianSource( pixelType, imageSize, faceSize, faceCenter );

  // Create eye images
  std::vector<double> eyeSize ( 2, 5.0 );
  std::vector<double> eye1Center ( 2, 48.0 );
  std::vector<double> eye2Center = { 80.0, 48.0 };
  sitk::Image eye1 = sitk::GaussianSource( pixelType, imageSize, eyeSize, eye1Center, 150 );
  sitk::Image eye2 = sitk::GaussianSource( pixelType, imageSize, eyeSize, eye2Center, 150 );

  // Apply the eyes to the face
  face = face - eye1 - eye2;
  face = sitk::BinaryThreshold( face, 200, 255, 255 );

  // Create the mouth
  std::vector<double> mouthRadii = { 30.0, 20.0 };
  std::vector<double> mouthCenter = { 64.0, 76.0 };
  sitk::Image mouth = 255 - sitk::BinaryThreshold(
                              sitk::GaussianSource(pixelType, imageSize, mouthRadii, mouthCenter),
                              200, 255, 255 );

  // Paste the mouth onto the face
  std::vector<unsigned int> mouthSize = { 64, 18 };
  std::vector<int> mouthLoc = { 32, 76 };
  face = sitk::Paste( face, mouth, mouthSize, mouthLoc, mouthLoc );

  // Apply the face to the original image
  image = image + face;

  // Display the results
  if (getenv("SITK_NOSHOW") == NULL)
    sitk::Show( image, "Hello World: C++", true );

}
