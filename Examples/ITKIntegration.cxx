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
#include "SimpleITK.h"

// ITK includes
#include "itkImage.h"
#include "itkCurvatureFlowImageFilter.h"

// create convenient namespace alias
namespace sitk = itk::simple;

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
  sitk::ImageFileReader reader;
  reader.SetFileName( std::string( argv[1] ) );
  sitk::Image image = reader.Execute();


  //
  // Set up writer
  //
  sitk::ImageFileWriter writer;
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
  const unsigned int                                 Dimension = 2;
  typedef float                                      InternalPixelType;
  typedef itk::Image< InternalPixelType, Dimension > InternalImageType;

  //
  // We must check the the image dimension and the pixel type of the
  // SimpleITK image match the ITK image we will cast to.s
  //
  if ( image.GetDimension() != Dimension )
    {
    std::cerr << "Input image is not a " << Dimension << " dimensional image as expected!" << std::endl;
    return 1;
    }

  //
  // The read sitk::Image could be any pixel type. Cast the image, to
  // float so we know what type we have.
  //
  sitk::CastImageFilter caster;
  caster.SetOutputPixelType( sitk::sitkFloat32 );
  image = caster.Execute( image );

  //
  // Extract the itk image from the SimpleITK image
  //
  InternalImageType::Pointer itkImage =
    dynamic_cast <InternalImageType*>( image.GetITKBase() );

  //
  // Always check the results of dynamic_casts
  //
  if ( itkImage.IsNull() )
    {
    std::cerr << "Unexpected error converting SimpleITK image to ITK image!" << std::endl;
    return 1;
    }

  //
  // Set up the blur filter and attach it to the pipeline.
  //
  typedef itk::CurvatureFlowImageFilter< InternalImageType, InternalImageType >
                                                     BlurFilterType;
  BlurFilterType::Pointer blurFilter = BlurFilterType::New();
  blurFilter->SetInput( itkImage );
  blurFilter->SetNumberOfIterations( 5 );
  blurFilter->SetTimeStep( 0.125 );



  //
  // Execute the  Blur pipeline by calling Update() on the blur filter.
  //
  blurFilter->Update();


  //
  // Return to the simpleITK setting by making a SimpleITK image using the
  // output of the blur filter.
  //
  sitk::Image blurredImage = sitk::Image( blurFilter->GetOutput() );


  //////
  // Now that we have finished the ITK section, we return to the SimpleITK API
  //////


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
    std::cout << "Adding a seed at ";
    for( unsigned int j = 0; j < seed.size(); ++i )
      {
      std::cout << seed[j] << " ";
      }
    std::cout << std::endl;
    }

  sitk::Image outImage = segmentationFilter.Execute(blurredImage);


  //
  // Write out the resulting file
  //
  writer.Execute(outImage);

  return 0;
}
