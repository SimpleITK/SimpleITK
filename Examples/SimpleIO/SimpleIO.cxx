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
#include <assert.h>


void example1(std::string inputImageFileName, std::string outputImageFileName)
  {
  itk::simple::ImageFileReader reader;
  reader.SetImageIO("PNGImageIO");
  reader.SetFileName(inputImageFileName);

  itk::simple::Image image;
  image = reader.Execute();

  itk::simple::ImageFileWriter writer;
  writer.SetFileName(outputImageFileName);
  writer.Execute(image);
  }

void example2(std::string inputImageFileName, std::string outputImageFileName)
  {
  itk::simple::Image image;
  image = itk::simple::ReadImage(inputImageFileName, itk::simple::sitkUnknown, "PNGImageIO");

  itk::simple::WriteImage(image, outputImageFileName);
  }

void example3()
  {
  itk::simple::Euler2DTransform basic_transform;
  basic_transform.SetTranslation(std::vector<double> {2.0, 3.0});

  itk::simple::WriteTransform(basic_transform, "euler2D.tfm");
  itk::simple::Transform read_result = itk::simple::ReadTransform("euler2D.tfm");

  assert(basic_transform == read_result);
  }
namespace sitk = itk::simple;


int main ( int argc, char* argv[] ) {

  if ( argc < 3 ) {
    std::cerr << "Usage: " << argv[0] << " <input> <output>\n";
    return 1;
  }

  std::cout << "Running first I/O example\n";
  example1(argv[1], argv[2]);

  std::cout << "Running second I/O example\n";
  example2(argv[1], argv[2]);

  std::cout << "Running transform I/O example\n";
  example3();

  return 0;
}
