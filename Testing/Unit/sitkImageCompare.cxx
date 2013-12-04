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
#include <SimpleITK.h>
#include <memory>

#include "sitkImageCompare.h"

namespace sitk = itk::simple;

void ImageCompare::NormalizeAndSave ( const sitk::Image &input, const std::string &filename )
{
  sitk::Image image = input;

  // Extract the center slice of our image
  if ( input.GetDimension() == 3 )
    {
    std::vector<int> idx( 3, 0 );
    std::vector<unsigned int> sz = input.GetSize();

    // set to just the center slice
    idx[2] = (int)( input.GetDepth() / 2 );
    sz[2] = 0;
    image = sitk::Extract( input, sz, idx );
    }

  sitk::StatisticsImageFilter stats;
  stats.Execute ( image );
  sitk::Image out = sitk::IntensityWindowing ( image, stats.GetMinimum(), stats.GetMaximum(), 0, 255 );
  out = sitk::Cast ( out, sitk::sitkUInt8 );
  sitk::WriteImage ( out, filename );
}


ImageCompare::ImageCompare()
{
  mTolerance = 0.0;
  mMessage = "";
}

bool ImageCompare::compare ( const sitk::Image& image, std::string inTestCase, std::string inTag )
{
  sitk::Image centerSlice( 0, 0, sitk::sitkUInt8 );
  std::string testCase = inTestCase;
  std::string tag = inTag;
  std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

  if ( testCase == "" )
    {
    testCase = ::testing::UnitTest::GetInstance()->current_test_info()->test_case_name();
    }

  std::cout << "Starting image compare on " << testCase << "_" << testName << "_" << tag << std::endl;
  // Does the baseline exist?
  std::string extension = ".nrrd";
  std::string OutputDir = dataFinder.GetOutputDirectory();

  std::string name = testCase
    .append( "_" )
    .append(testName);

  if ( tag != "" )
    {
    name.append("_").append ( tag );
    }

  // Extract the center slice of our image
  if ( image.GetDimension() == 3 )
    {
    std::vector<int> idx( 3, 0 );
    std::vector<unsigned int> sz = image.GetSize();

    // set to just the center slice
    idx[2] = (int)( image.GetDepth() / 2 );
    sz[2] = 1;
    centerSlice = sitk::RegionOfInterest( image, sz, idx );
    }
  else
    {
    centerSlice = image;
    }

  std::string baselineFileName = dataFinder.GetFile( "Baseline/" + name + extension );

  if ( !itksys::SystemTools::FileExists ( baselineFileName.c_str() ) )
    {
    // Baseline does not exist, write out what we've been given
    std::string newBaselineDir = OutputDir + "/Newbaseline/";
    itksys::SystemTools::MakeDirectory ( newBaselineDir.c_str() );
    std::cout << "Making directory " << newBaselineDir << std::endl;
    std::string newBaseline = newBaselineDir + name + extension;
    sitk::ImageFileWriter().SetFileName ( newBaseline ).Execute ( centerSlice );
    mMessage = "Baseline does not exist, wrote " + newBaseline + "\ncp " + newBaseline + " " + baselineFileName;
    return false;
    }

  sitk::Image baseline( 0, 0, sitk::sitkUInt8 );
  std::cout << "Loading baseline " << baselineFileName << std::endl;

  try
    {
    baseline = sitk::ImageFileReader().SetFileName ( baselineFileName ).Execute();
    }
  catch ( std::exception& e )
    {
    mMessage = "ImageCompare: Failed to load image " + baselineFileName + " because: " + e.what();
    return false;
    }

  // verify they have the same size
  if ( baseline.GetHeight() != centerSlice.GetHeight()
       || baseline.GetWidth() != centerSlice.GetWidth()
       || baseline.GetDepth() != centerSlice.GetDepth() )
    {
    mMessage = "ImageCompare: Image dimensions are different";
    return false;
    }

  // Get the center slices
  sitk::Image diffSquared( 0, 0, itk::simple::sitkUInt8 );
  try
    {

    if ( baseline.GetPixelID() == sitk::sitkComplexFloat32 ||
         baseline.GetPixelID() == sitk::sitkComplexFloat64 )
      {

      sitk::Image diff =  sitk::Subtract( centerSlice, baseline );
      // for complex number we multiply the image by it's complex
      // conjugate, this will produce only a real value result
      sitk::Image conj = sitk::RealAndImaginaryToComplex( sitk::ComplexToReal( diff ),
                                                          sitk::Multiply( sitk::ComplexToImaginary( diff ), -1.0 ) );
      diffSquared = sitk::ComplexToReal( sitk::Multiply( diff, conj ) );
      }
    else if ( baseline.GetNumberOfComponentsPerPixel() > 1 )
      {
      sitk::Image diff =  sitk::Subtract( sitk::Cast( centerSlice, sitk::sitkVectorFloat32 ), sitk::Cast( baseline, sitk::sitkVectorFloat32 ) );

      // for vector image just do a sum of the components
      diffSquared  = sitk::Pow( sitk::VectorIndexSelectionCast( diff, 0 ), 2.0 );
      for ( unsigned int i = 1; i < diff.GetNumberOfComponentsPerPixel(); ++i )
        {
        sitk::Image temp = sitk::Pow( sitk::VectorIndexSelectionCast( diff, i ), 2.0 );
        diffSquared = sitk::Add( temp, diffSquared );
        }

      diffSquared = sitk::Divide( diffSquared, diff.GetNumberOfComponentsPerPixel() );
      }
    else
      {
      sitk::Image diff =  sitk::Subtract( sitk::Cast( centerSlice, sitk::sitkFloat32 ), sitk::Cast( baseline, sitk::sitkFloat32 ) );
      diffSquared = sitk::Multiply( diff, diff );
      }

    }
  catch ( std::exception& e )
    {
    mMessage = "ImageCompare: Failed to subtract image " + baselineFileName + " because: " + e.what();
    return false;
    }


  sitk::StatisticsImageFilter stats;
  stats.Execute ( diffSquared );
  double rms = std::sqrt ( stats.GetMean() );

  if ( rms > fabs ( mTolerance ) )
    {
    std::ostringstream msg;
    msg << "ImageCompare: image Root Mean Square (RMS) difference was " << rms << " which exceeds the tolerance of " << mTolerance;
    msg << "\n";
    mMessage = msg.str();

    std::cout << "<DartMeasurement name=\"RMSeDifference\" type=\"numeric/float\">" << rms << "</DartMeasurement>" << std::endl;
    std::cout << "<DartMeasurement name=\"Tolerance\" type=\"numeric/float\">" << mTolerance << "</DartMeasurement>" << std::endl;

    std::string volumeName = OutputDir + "/" + name + ".nrrd";
    sitk::ImageFileWriter().SetFileName ( volumeName ).Execute ( centerSlice );

    // Save pngs
    std::string ExpectedImageFilename = OutputDir + "/" + name + "_Expected.png";
    std::string ActualImageFilename = OutputDir + "/" + name + "_Actual.png";
    std::string DifferenceImageFilename = OutputDir + "/" + name + "_Difference.png";

    try
      {
      NormalizeAndSave ( baseline, ExpectedImageFilename );
      NormalizeAndSave ( centerSlice, ActualImageFilename );
      NormalizeAndSave ( sitk::Sqrt(diffSquared), DifferenceImageFilename );

      // Let ctest know about it
      std::cout << "<DartMeasurementFile name=\"ExpectedImage\" type=\"image/png\">";
      std::cout << ExpectedImageFilename << "</DartMeasurementFile>" << std::endl;
      std::cout << "<DartMeasurementFile name=\"ActualImage\" type=\"image/png\">";
      std::cout << ActualImageFilename << "</DartMeasurementFile>" << std::endl;
      std::cout << "<DartMeasurementFile name=\"DifferenceImage\" type=\"image/png\">";
      std::cout << DifferenceImageFilename << "</DartMeasurementFile>" << std::endl;

      }
    catch( std::exception &e )
      {
      std::cerr << "Exception encountered while trying to normalize and save images for dashboard!" << std::endl;
      std::cerr << e.what() << std::endl;
      }
    catch(...)
      {
      std::cerr << "Unexpected error while trying to normalize and save images for dashboard!" << std::endl;
      }


    return false;
  }

  return true;
}
