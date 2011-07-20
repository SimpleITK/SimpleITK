#include <SimpleITK.h>
#include <memory>

#include "ImageCompare.h"
#include "itkExceptionObject.h"

static void NormalizeAndSave ( itk::simple::Image image, std::string filename ) {
  itk::simple::StatisticsImageFilter stats;
  stats.Execute ( image );
  itk::simple::Image out = itk::simple::IntensityWindowing ( image, stats.GetMinimum(), stats.GetMaximum(), 0, 255 );
  out = itk::simple::Cast ( out, itk::simple::sitkUInt8 );
  itk::simple::WriteImage ( out, filename );
}




ImageCompare::ImageCompare() {
  mTolerance = 0.0;
  mMessage = "";
}

bool ImageCompare::compare ( const itk::simple::Image& image, std::string inTestCase, std::string inTag ) {
  itk::simple::Image centerSlice( 0, 0, itk::simple::sitkUInt8 );
  std::string testCase = inTestCase;
  std::string tag = inTag;
  std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

  if ( testCase == "" ) {
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

    centerSlice = itk::simple::RegionOfInterest( image, sz, idx );
    } else {
    centerSlice = itk::simple::Cast ( image, image.GetPixelIDValue() );
  }

  std::string baselineFileName = dataFinder.GetSourceDirectory() + "/Testing/Data/Baseline/" + name + extension;

  if ( !itksys::SystemTools::FileExists ( baselineFileName.c_str() ) ) {
    // Baseline does not exist, write out what we've been given
    std::string newBaselineDir = OutputDir + "/Newbaseline/";
    itksys::SystemTools::MakeDirectory ( newBaselineDir.c_str() );
    std::cout << "Making directory " << newBaselineDir << std::endl;
    std::string newBaseline = newBaselineDir + name + extension;
    itk::simple::ImageFileWriter().SetFileName ( newBaseline ).Execute ( centerSlice );
    mMessage = "Baseline does not exist, wrote " + newBaseline + "\ncp " + newBaseline + " " + baselineFileName;
    return false;
  }

  itk::simple::Image baseline( 0, 0, itk::simple::sitkUInt8 );
  std::cout << "Loading baseline " << baselineFileName << std::endl;

  try {
    baseline = itk::simple::ImageFileReader().SetFileName ( baselineFileName ).Execute();
  } catch ( itk::ExceptionObject& e ) {
    mMessage = "ImageCompare: Failed to load image " + baselineFileName + " because: " + e.what();
    return false;
  }

  // Do the diff
  itk::simple::HashImageFilter hasher;
  if ( hasher.Execute ( baseline ) == hasher.Execute ( centerSlice ) ) {
    // Nothing else to do
    return true;
  }


  if ( baseline.GetHeight() != centerSlice.GetHeight()
       || baseline.GetWidth() != centerSlice.GetWidth()
       || baseline.GetDepth() != centerSlice.GetDepth() ) {

    mMessage = "ImageCompare: Image dimensions are different";
    return false;
  }

  // Get the center slices
  itk::simple::Image diff( 0, 0, itk::simple::sitkUInt8 );
  try
    {
      diff = itk::simple::SubtractImageFilter().Execute ( centerSlice, baseline );
    }
  catch ( itk::ExceptionObject& e )
    {
    mMessage = "ImageCompare: Failed to subtract image " + baselineFileName + " because: " + e.what();
    return false;
    }
  itk::simple::StatisticsImageFilter stats;
  stats.Execute ( diff );
  double dValue = sqrt ( stats.GetMean() );

  if ( fabs ( dValue ) > fabs ( mTolerance ) ) {
    std::ostringstream msg;
    msg << "ImageCompare: image Root Mean Square (RMS) difference was " << dValue << " which exceeds the tolerance of " << mTolerance;
    msg << "\n";
    mMessage = msg.str();

    std::cout << "<DartMeasurement name=\"RMSeDifference\" type=\"numeric/float\">" << dValue << "</DartMeasurement>" << std::endl;
    std::cout << "<DartMeasurement name=\"Tolerance\" type=\"numeric/float\">" << mTolerance << "</DartMeasurement>" << std::endl;

    std::string volumeName = OutputDir + "/" + name + ".nrrd";
    itk::simple::ImageFileWriter().SetFileName ( volumeName ).Execute ( centerSlice );

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
