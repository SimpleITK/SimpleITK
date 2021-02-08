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
#include <iostream>
#include <exception>


// create convenient namespace alias
namespace sitk = itk::simple;

int main ( int argc, char* argv[] )
  {

  if ( argc < 2 )
    {
    std::cerr << "Usage: " << argv[0] << " image_file_name\n";
    return 1;
    }

  // Find out which image IOs are supported
  sitk::ImageFileReader reader;
  std::vector<std::string> image_ios = reader.GetRegisteredImageIOs();
  std::cout << "The supported image IOs are: ";
  std::vector<std::string>::iterator it;
  for (it=image_ios.begin(); it!=image_ios.end(); it++)
    {
    std::cout << (*it) << " ";
    }
  std::cout << std::endl;
  std::cout << "--------------------" << std::endl;

  // Another option is to just print the reader and see which
  // IOs are supported
  std::cout << reader.ToString();
  std::cout << "--------------------" << std::endl;


  // Read the image file
  reader.SetImageIO ( "PNGImageIO" );
  reader.SetFileName ( std::string ( argv[1] ) );

  try
    {
    sitk::Image image = reader.Execute();
    std::cout << "Read image: " << argv[1] << std::endl;
    }
  catch (std::exception& e)
    {
    std::cout << "Read failed: " << e.what() << std::endl;
    }

  return 0;
  }
