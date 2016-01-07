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
#include <itksys/SystemTools.hxx>

#include "sitkImageCompare.h"

namespace sitk = itk::simple;

void ImageCompare::NormalizeAndSave ( const sitk::Image &input, const std::string &filename )
{
  sitk::Image image = input;

  if (image.GetPixelIDValue() == sitk::sitkLabelUInt8)
    {
    image = sitk::Cast( image, sitk::sitkUInt8);
    }
  else if (image.GetPixelIDValue() == sitk::sitkLabelUInt16)
    {
    image = sitk::Cast( image, sitk::sitkUInt16);
    }
  else if (image.GetPixelIDValue() == sitk::sitkLabelUInt32)
    {
    image = sitk::Cast( image, sitk::sitkUInt32);
    }
  else if (image.GetPixelIDValue() == sitk::sitkLabelUInt64)
    {
    image = sitk::Cast( image, sitk::sitkUInt64);
    }
  else if (image.GetPixelIDValue() == sitk::sitkComplexFloat64
           || image.GetPixelIDValue() == sitk::sitkComplexFloat32)
    {
    image = sitk::ComplexToModulus(image);
    }
  else if (image.GetNumberOfComponentsPerPixel() != 1)
    {
    // just use the magnitude for vector images
    image = sitk::VectorMagnitude(image);
    }

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

  sitk::Image out = sitk::RescaleIntensity( image, 0, 255 );

  out = sitk::Cast ( out, sitk::sitkUInt8 );
  sitk::WriteImage ( out, filename );
}


ImageCompare::ImageCompare()
{
  mTolerance = 0.0;
  mMessage = "";
}

float ImageCompare::testImages( const itk::simple::Image& testImage,
                                const itk::simple::Image& baselineImage,
                                bool reportErrors,
                                const std::string &baselineImageFilename)
{

  const std::string OutputDir = dataFinder.GetOutputDirectory();

  const std::string shortFilename = itksys::SystemTools::GetFilenameName( baselineImageFilename );

    // verify they have the same size
  if ( baselineImage.GetHeight() != testImage.GetHeight()
       || baselineImage.GetWidth() != testImage.GetWidth()
       || baselineImage.GetDepth() != testImage.GetDepth() )
    {
    mMessage = "ImageCompare: Image dimensions are different";
    return -1;
    }


    // Compute image difference squared
    sitk::Image diffSquared( 0, 0, itk::simple::sitkUInt8 );
    try
      {

      if ( baselineImage.GetPixelID() == sitk::sitkComplexFloat32 ||
           baselineImage.GetPixelID() == sitk::sitkComplexFloat64 )
        {

        const sitk::Image diff =  sitk::Subtract( testImage, baselineImage );
        // for complex number we multiply the image by it's complex
        // conjugate, this will produce only a real value result
        const sitk::Image conj = sitk::RealAndImaginaryToComplex( sitk::ComplexToReal( diff ),
                                                                  sitk::Multiply( sitk::ComplexToImaginary( diff ), -1.0 ) );
        diffSquared = sitk::ComplexToReal( sitk::Multiply( diff, conj ) );
        }
      else if ( baselineImage.GetNumberOfComponentsPerPixel() > 1 )
        {
        const sitk::Image diff =  sitk::Subtract( sitk::Cast( testImage, sitk::sitkVectorFloat32 ), sitk::Cast( baselineImage, sitk::sitkVectorFloat32 ) );

        // for vector image just do a sum of the components
        diffSquared  = sitk::Pow( sitk::VectorIndexSelectionCast( diff, 0 ), 2.0 );
        for ( unsigned int i = 1; i < diff.GetNumberOfComponentsPerPixel(); ++i )
          {
          const sitk::Image temp = sitk::Pow( sitk::VectorIndexSelectionCast( diff, i ), 2.0 );
          diffSquared = sitk::Add( temp, diffSquared );
          }

        diffSquared = sitk::Divide( diffSquared, diff.GetNumberOfComponentsPerPixel() );
        }
      else
        {
        sitk::Image diff =  sitk::Subtract( sitk::Cast( testImage, sitk::sitkFloat32 ), sitk::Cast( baselineImage, sitk::sitkFloat32 ) );
        diffSquared = sitk::Multiply( diff, diff );
        }

      }
    catch ( std::exception& e )
      {
      mMessage = "ImageCompare: Failed to subtract image " + baselineImageFilename + " because: " + e.what();
      return -1;
      }



    sitk::StatisticsImageFilter stats;
    stats.Execute ( diffSquared );
    const double rms = std::sqrt ( stats.GetMean() );

    if ( !reportErrors )
      {
      // The measurement errors should be reported for both success and errors
      // to facilitate setting tight tolerances of tests.
      std::cout << "<DartMeasurement name=\"RMSeDifference " << shortFilename <<  "\" type=\"numeric/float\">" << rms << "</DartMeasurement>" << std::endl;
      }
    else
      {
      std::ostringstream msg;
      msg << "ImageCompare: image Root Mean Square (RMS) difference was " << rms << " which exceeds the tolerance of " << mTolerance;
      msg << "\n";
      mMessage = msg.str();

      std::cout << "<DartMeasurement name=\"RMSeDifference\" type=\"numeric/float\">" << rms << "</DartMeasurement>" << std::endl;
      std::cout << "<DartMeasurement name=\"Tolerance\" type=\"numeric/float\">" << mTolerance << "</DartMeasurement>" << std::endl;

      std::string volumeName = OutputDir + "/" + shortFilename + ".nrrd";
      sitk::ImageFileWriter().SetFileName ( volumeName ).Execute ( testImage );

      // Save pngs
      std::string ExpectedImageFilename = OutputDir + "/" + shortFilename + "_Expected.png";
      std::string ActualImageFilename = OutputDir + "/" + shortFilename + "_Actual.png";
      std::string DifferenceImageFilename = OutputDir + "/" + shortFilename + "_Difference.png";

      try
        {
        NormalizeAndSave ( baselineImage, ExpectedImageFilename );
        NormalizeAndSave ( testImage, ActualImageFilename );
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


      }

    return (rms > fabs ( mTolerance )) ? rms  : 0.0;
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


  // Extract the center slice of our test image
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

  const std::string baselineFileName = dataFinder.GetFile( "Baseline/" + name + extension );



  if ( !itksys::SystemTools::FileExists ( baselineFileName.c_str(), true ) )
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

  // Generate all possible baseline filenames
  std::vector<std::string> baselineFileNames;

  {
  int x = 0;

  baselineFileNames.push_back(baselineFileName);


  while ( ++x )
    {
    std::ostringstream filename_stream;
    filename_stream <<  "Baseline/" << name  << "." << x << extension;

    std::string filename = dataFinder.GetFile( filename_stream.str() );

    if (!itksys::SystemTools::FileExists ( filename, true ) )
      {
      break;
      }
    baselineFileNames.push_back(filename);
    }

  }

  std::vector<std::string>::const_iterator iterName;

  std::string bestBaselineName =  *baselineFileNames.begin();
  float bestRMS = std::numeric_limits<float>::max();

  for ( iterName = baselineFileNames.begin(); iterName != baselineFileNames.end(); ++iterName )
    {

    sitk::Image baseline( 0, 0, sitk::sitkUInt8 );

    try
      {
      baseline = sitk::ImageFileReader().SetFileName (*iterName ).Execute();
      }
    catch ( std::exception& e )
      {
      mMessage = "ImageCompare: Failed to load image " +*iterName + " because: " + e.what();
      return false;
      }

    float RMS = testImages( centerSlice, baseline, false,  *iterName);

    if ( RMS >= 0.0 && RMS < bestRMS )
      {
      bestBaselineName = *iterName;
      bestRMS = RMS;
      }

    }


  if ( bestRMS > fabs ( mTolerance ) )
    {
    sitk::Image baseline =  sitk::ImageFileReader().SetFileName (bestBaselineName ).Execute();
    testImages( centerSlice, baseline, true, bestBaselineName );
    return false;
    }
  else
    {
    return true;
    }

}
