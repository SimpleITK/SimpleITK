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
#include "SimpleITK.h"
#include <stdlib.h>
#include <iostream>


// create convenient namespace alias
namespace sitk = itk::simple;


/** This example shows hour to import abuffer from an array into a
* simpleITK Image, perform some manipulation, then get access to that
* buffer again. This technique is useful for integrating into external
* applications.
*/
int main( int , char *[] )
{

  // construct and initialize an image buffer, this buffer could have
  // just as well come from the rest of an application we are trying
  // to integrate simpleITK with.
  uint8_t *in = new uint8_t[100*100*100];
  for ( unsigned int i = 0; i < 100*100*100; ++i )
    {
    in[i] = i%255;
    }

  // Configure a filter to import the buffer
  sitk::ImportImageFilter importer;
  importer.SetSpacing( std::vector<double>( 3, .33 ) );
  importer.SetOrigin( std::vector<double>( 3, .123 ) );
  importer.SetSize( std::vector<unsigned int>( 3, 100 ) );
  importer.SetBufferAsUInt8( in );

  // actaully convert the buffer to a simpleITK image
  sitk::Image img = importer.Execute();


  sitk::Show( img );
  // at this point img, contains the same buffer as in

  // use some useful filters in ITK
  img = sitk::GrayscaleErode( img , 3 );

  sitk::Show( img );

  // The output type of the morpholgy will be the same pixel type as
  // the input. But we place the assert to clarify and verify out
  // logic.
  assert( img.GetPixelID() == sitk::sitkUInt8 );

  // The method which matches the actual pixel type of the image must
  // be called.
  uint8_t *out = img.GetBufferAsUInt8();

  for ( unsigned int i = 0; i < 10; ++i)
    {
    std::cout << int(out[i]) << " ";
    }
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
