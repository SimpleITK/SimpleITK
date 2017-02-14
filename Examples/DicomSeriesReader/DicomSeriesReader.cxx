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
#include <iostream>
#include <stdlib.h>


// create convenient namespace alias
namespace sitk = itk::simple;

int main ( int argc, char* argv[] ) {

  if ( argc < 3 ) {
    std::cerr << "Usage: " << argv[0] << " <input_directory> <output_file>\n";
    return 1;
  }

  std::cout << "Reading Dicom directory: " << argv[1] << std::endl;

  // Read the Dicom image series
  sitk::ImageSeriesReader reader;
  const std::vector<std::string> dicom_names = sitk::ImageSeriesReader::GetGDCMSeriesFileNames( argv[1] );
  reader.SetFileNames( dicom_names );

  sitk::Image image = reader.Execute();

  std::vector<unsigned int> size = image.GetSize();
  std::cout << "Image size: " << size[0] << " " << size[1] << " " << size[2] << std::endl;

  std::cout << "Writing " << argv[2] << std::endl;

  sitk::WriteImage( image, argv[2] );

  return 0;
}
