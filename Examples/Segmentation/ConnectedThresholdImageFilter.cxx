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
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif


#include "sitkImage.h"
#include "sitkCurvatureFlowImageFilter.h"
#include "sitkConnectedThresholdImageFilter.h"
#include "sitkImageFileReader.h"
#include "sitkImageFileWriter.h"

#include <stdlib.h>
#include <iostream>

namespace sitk = itk::simple;

int main( int argc, char *argv[])
{

  //
  // Check command line parameters
  //
  if( argc < 7 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage outputImage lowerThreshold upperThreshold seedX seedY [seed2X seed2Y ... ]" << std::endl;
    return 1;
    }


  //
  // Read the image
  //

  sitk::ImageFileReader reader;
  reader.SetFileName( std::string( argv[1] ) );
  sitk::Image image = reader.Execute();


  //
  // Blur using CurvatureFlowImageFilter
  //
  sitk::CurvatureFlowImageFilter blurFilter;
  blurFilter.SetNumberOfIterations( 5 );
  blurFilter.SetTimeStep( 0.125 );
  image = blurFilter.Execute( image );


  //
  // Set up ConnectedThresholdImageFilter for segmentation
  //
  sitk::ConnectedThresholdImageFilter segmentationFilter;
  segmentationFilter.SetLower( atof( argv[3] ) );
  segmentationFilter.SetUpper( atof( argv[4] ) );
  segmentationFilter.SetReplaceValue( 255 );

  for (int i = 5; i+1 < argc; i+=2)
    {
    std::vector<unsigned int> seed;
    seed.push_back(atoi(argv[i]));
    seed.push_back(atoi(argv[i+1]));
    segmentationFilter.AddSeed(seed);
    std::cout << "Adding a seed at: ";
    for( unsigned int j = 0; j < seed.size(); ++j )
      {
      std::cout << seed[j] << " ";
      }
    std::cout << std::endl;
    }

  sitk::Image outImage = segmentationFilter.Execute(image);


  //
  // Write out the resulting file
  //
  sitk::ImageFileWriter writer;
  writer.SetFileName( std::string( argv[2] ) );
  writer.Execute(outImage);

  return 0;
}
