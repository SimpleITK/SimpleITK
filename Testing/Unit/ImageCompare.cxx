#include <SimpleITK.h>
#include <memory>

#include "ImageCompare.h"
#include "itkExceptionObject.h"

namespace sitk = itk::simple;

static void NormalizeAndSave ( sitk::Image image, std::string filename )
{
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
    .append(testName)
    .append("_")
    .append ( tag );

  // Extract the center slice of our image
  if ( image.GetDimension() == 3 )
    {
    std::vector<int> idx( 3, 0 );
    std::vector<unsigned int> sz = image.GetSize();

    // set to just the center slice
    idx[2] = (int)( image.GetDepth() / 2.0 );
    sz[2] = 1;

    centerSlice = sitk::RegionOfInterest( image, sz, idx );
    }
  else
    {
    centerSlice = image;
    }

  std::string baselineFileName = dataFinder.GetSourceDirectory() + "/Testing/Data/Baseline/" + name + extension;

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
  catch ( itk::ExceptionObject& e )
    {
    mMessage = "ImageCompare: Failed to load image " + baselineFileName + " because: " + e.what();
    return false;
    }

  // check that the images aren't identical
  sitk::HashImageFilter hasher;
  if ( hasher.Execute ( baseline ) == hasher.Execute ( centerSlice ) )
    {
    // Nothing else to do
    return true;
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
  sitk::Image diff( 0, 0, itk::simple::sitkUInt8 );
  try
    {
      diff = sitk::SubtractImageFilter().Execute ( centerSlice, baseline );
    }
  catch ( itk::ExceptionObject& e )
    {
    mMessage = "ImageCompare: Failed to subtract image " + baselineFileName + " because: " + e.what();
    return false;
    }
  sitk::StatisticsImageFilter stats;
  stats.Execute ( diff );
  double dValue = sqrt ( stats.GetMean() );

  if ( fabs ( dValue ) > fabs ( mTolerance ) )
    {
    std::ostringstream msg;
    msg << "ImageCompare: image Root Mean Square (RMS) difference was " << dValue << " which exceeds the tolerance of " << mTolerance;
    msg << "\n";
    mMessage = msg.str();

    std::cout << "<DartMeasurement name=\"RMSeDifference\" type=\"numeric/float\">" << dValue << "</DartMeasurement>" << std::endl;
    std::cout << "<DartMeasurement name=\"Tolerance\" type=\"numeric/float\">" << mTolerance << "</DartMeasurement>" << std::endl;

    std::string volumeName = OutputDir + "/" + name + ".nrrd";
    sitk::ImageFileWriter().SetFileName ( volumeName ).Execute ( centerSlice );

    // Save pngs
    std::string ExpectedImageFilename = OutputDir + "/" + name + "_Expected.png";
    std::string ActualImageFilename = OutputDir + "/" + name + "_Actual.png";
    std::string DifferenceImageFilename = OutputDir + "/" + name + "_Difference.png";

    NormalizeAndSave ( baseline, ExpectedImageFilename );
    NormalizeAndSave ( centerSlice, ActualImageFilename );
    NormalizeAndSave ( diff, DifferenceImageFilename );

    // Let ctest know about it
    std::cout << "<DartMeasurementFile name=\"ExpectedImage\" type=\"image/png\">";
    std::cout << ExpectedImageFilename << "</DartMeasurementFile>" << std::endl;
    std::cout << "<DartMeasurementFile name=\"ActualImage\" type=\"image/png\">";
    std::cout << ActualImageFilename << "</DartMeasurementFile>" << std::endl;
    std::cout << "<DartMeasurementFile name=\"DifferenceImage\" type=\"image/png\">";
    std::cout << DifferenceImageFilename << "</DartMeasurementFile>" << std::endl;

    return false;
  }

  return true;
}
