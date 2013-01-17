/*=========================================================================
*
*  Copyright Insight Software Consortium
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
#include <stdlib.h>
#include <iostream>

// create convenient namespace alias
namespace sitk = itk::simple;


int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <input> <sigma> <output>\n";
    return 1;
  }


  sitk::Image image = sitk::ReadImage ( std::string ( argv[1] ) );

  sitk::PixelIDValueEnum inputPixelID = image.GetPixelID();

  image = sitk::SmoothingRecursiveGaussian ( image, atof ( argv[2] ) );

  image = sitk::Cast( image, inputPixelID );

  sitk::WriteImage ( image, std::string ( argv[3] ) );

  return 0;
}
