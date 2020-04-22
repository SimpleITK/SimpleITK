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

// This one header will include all SimpleITK filters and external objects.
#include <SimpleITK.h>
#include <sitkImageOperators.h>

// create convenient namespace alias
namespace sitk = itk::simple;

int main ( int argc, char* argv[] ) {

    sitk::PixelIDValueEnum pixelType = sitk::sitkUInt8;
    std::vector<unsigned int> imageSize ( 2, 128 );

    // Create a black image
    sitk::Image image( imageSize, pixelType );

    // Add a Gaussian blob to the image
    std::vector<double> blobSize ( 2, 64.0 );
    std::vector<double> blobCenter ( 2, 64.0 );
    image = image + sitk::GaussianSource( pixelType, imageSize, blobSize, blobCenter );

    // Write the image as a PNG file
    sitk::WriteImage(image, "blob.png" );

}
