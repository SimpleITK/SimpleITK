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

// SimpleITK includes
#include "sitkImage.h"
#include "sitkConnectedThresholdImageFilter.h"
#include "sitkImageFileReader.h"
#include "sitkImageFileWriter.h"

// ITK includes
#include "itkImage.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkCastImageFilter.h"

/**
 * This example shows how ITK and SimpleITK can be used together to work
 * on the same data. We use the same example application as the one presented
 * in the Segmentation/ConnectedThresholdImageFilter.cxx example, but we
 * replace the SimpleITK version of CurvatureFlowImageFilter with the
 * corresponding ITK version. While not terribly useful in this situation since
 * CurvatureFlowImageFilter is already available in SimpleITK this demonstrates
 * how ITK filters that have not been converted for SimpleITK can still be used
 * in a SimpleITK context
 */
int main( int argc, char *argv[])
{

  //
  // Check command line parameters
  //
  if( argc < 7 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage outputImage lowerThreshold upperThreshold "
      "seedX seedY [seed2X seed2Y ... ]" << std::endl;
    return 1;
    }


  //
  // Read the image
  //
  itk::simple::Image::Pointer image;

  itk::simple::ImageFileReader reader;
  reader.SetFileName( std::string( argv[1] ) );
  image = reader.Execute();


  //
  // Set up writer
  //
  itk::simple::ImageFileWriter writer;
  writer.SetFileName( std::string( argv[2] ) );


  //////
  // Blur using CurvatureFlowImageFilter
  //
  // Here we demonstrate the use of the ITK version of CurvatureFlowImageFilter
  // instead of the SimpleITK version.
  //////

  //
  // First, define the typedefs that correspond to the types of the input
  // image. This requires foreknowlege of the data type of the input image.
  //
  typedef unsigned char                           InputPixelType;
  const unsigned int                              Dimension = 2;
  typedef itk::Image< InputPixelType, Dimension > InputImageType;


  //
  // Define the typedefs for the ITK blur filter and the cast filters used to
  // cast between the different pixel types.
  //
  typedef float                                      InternalPixelType;
  typedef itk::Image< InternalPixelType, Dimension > InternalImageType;
  typedef itk::CastImageFilter< InputImageType, InternalImageType>
                                                     CastFilterType;
  typedef itk::CurvatureFlowImageFilter< InternalImageType, InternalImageType >
                                                     BlurFilterType;


  //
  // Extract the itk image from the SimpleITK image
  //
  InputImageType::Pointer itkImage =
    dynamic_cast <InputImageType*>( image->GetImageBase().GetPointer() );


  //
  // Set up the cast filter.
  //
  CastFilterType::Pointer castFilter = CastFilterType::New();
  castFilter->SetInput( itkImage );


  //
  // Set up the blur filter and attach it to the pipeline.
  //
  BlurFilterType::Pointer blurFilter = BlurFilterType::New();
  blurFilter->SetInput( castFilter->GetOutput() );
  blurFilter->SetNumberOfIterations( 5 );
  blurFilter->SetTimeStep( 0.125 );


  //
  // Execute the Cast -> Blur pipeline by calling Update() on the blur filter.
  //
  blurFilter->Update();


  //
  // Return to the simpleITK setting by making a SimpleITK image using the
  // output of the blur filter.
  //
  image = new itk::simple::Image( blurFilter->GetOutput() );


  //////
  // Now that we have finished the ITK section, we return to the SimpleITK API
  //////


  //
  // Set up ConnectedThresholdImageFilter for segmentation
  //
  itk::simple::ConnectedThresholdImageFilter segmentationFilter;
  segmentationFilter.SetLower( atof( argv[3] ) );
  segmentationFilter.SetUpper( atof( argv[4] ) );
  segmentationFilter.SetReplaceValue( 255 );

  for (int i = 5; i+1 < argc; i+=2)
    {
    std::vector<unsigned int> seed;
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
