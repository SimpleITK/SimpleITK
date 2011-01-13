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
#include "sitkNeighborhoodConnectedImageFilter.h"
#include "sitkImageFileReader.h"
#include "sitkImageFileWriter.h"


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
  itk::simple::Image::Pointer image;

  itk::simple::ImageFileReader reader;
  reader.SetFilename( std::string( argv[1] ) );
  image = reader.Execute();


  //
  // Set up writer
  //
  itk::simple::ImageFileWriter writer;
  writer.SetFilename( std::string( argv[2] ) );


  //
  // Blur using CurvatureFlowImageFilter
  //
  itk::simple::CurvatureFlowImageFilter blurFilter;
  blurFilter.SetNumberOfIterations( 5 );
  blurFilter.SetTimeStep( 0.125 );
  image = blurFilter.Execute( image );
  

  //
  // Set up NeighborhoodConnectedImageFilter for segmentation
  //
  itk::simple::NeighborhoodConnectedImageFilter segmentationFilter;
  segmentationFilter.SetLower( atof( argv[3] ) );
  segmentationFilter.SetUpper( atof( argv[4] ) );
  segmentationFilter.SetReplaceValue( 255 );

  std::vector< unsigned int > radius;
  radius.push_back( 2 );
  radius.push_back( 2 );
  segmentationFilter.SetRadius( radius );

  for (int i = 5; i+1 < argc; i+=2)
    {
    std::vector<size_t> seed;
    seed.push_back(atoi(argv[i]));
    seed.push_back(atoi(argv[i+1]));
    segmentationFilter.AddSeed(seed);
    std::cout << "Adding a seed at ";
    printStdVector(seed, std::cout);
    std::cout << std::endl;
    }

  itk::simple::Image::Pointer outImage = segmentationFilter.Execute(image);


  //
  // Write out the resulting file
  //
  writer.Execute(outImage);

  return 0;
}
