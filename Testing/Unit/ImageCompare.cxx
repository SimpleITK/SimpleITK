#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkImageHashFilter.h>
#include <sitkSubtractImageFilter.h>
#include <sitkStatisticsImageFilter.h>
#include <sitkExtractImageFilter.h>

#include "ImageCompare.h"
#include "itkExceptionObject.h"
ImageCompare::ImageCompare() {
  mTolerance = 0.0;
  mMessage = "";
}

bool ImageCompare::compare ( itk::simple::Image::Pointer image, std::string inTestCase, std::string inTag ) {
  itk::simple::Image::Pointer slice;
  std::string testCase = inTestCase;
  std::string tag = inTag;
  std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
  
  if ( testCase == "" ) {
    testCase = ::testing::UnitTest::GetInstance()->current_test_info()->test_case_name();
  }

  std::cout << "Starting image compare on " << testCase << "_" << testName << "_" << tag << std::endl;
  if ( image.IsNull() ) {
    mMessage = "ImageCompare: image is null";
    return false;
  }
  // Does the baseline exist?
  std::string extension = ".nrrd";
  std::string OutputDir = dataFinder.GetOutputDirectory();
  
  std::string name = testCase
    .append( "_" )                                                        
    .append(testName)
    .append("_")
    .append ( tag );

  // Extract the center slice of our image
  slice = image;
  if ( image->GetDimension() == 3 )
    {
    size_t centerSlice = (int)( image->GetDepth() / 2.0 );
    slice = itk::simple::ExtractImageFilter().Execute ( image, centerSlice );
    }

  std::string baselineFilename = dataFinder.GetSourceDirectory() + "/Testing/Data/Baseline/" + name + extension;
  
  if ( !itksys::SystemTools::FileExists ( baselineFilename.c_str() ) ) {
    // Baseline does not exist, write out what we've been given
    std::string newBaselineDir = OutputDir + "/Newbaseline/";
    itksys::SystemTools::MakeDirectory ( newBaselineDir.c_str() );
    std::cout << "Making directory " << newBaselineDir << std::endl;
    std::string newBaseline = newBaselineDir + name + extension;
    itk::simple::ImageFileWriter().SetFilename ( newBaseline ).Execute ( slice );
    mMessage = "Baseline does not exist, wrote " + newBaseline + "\ncp " + newBaseline + " " + baselineFilename;
    return false;
  }

  itk::simple::Image::Pointer baseline;
  std::cout << "Loading baseline " << baselineFilename << std::endl;

  try {
    baseline = itk::simple::ImageFileReader().SetFilename ( baselineFilename ).Execute();
  } catch ( itk::ExceptionObject& e ) { 
    mMessage = "ImageCompare: Failed to load image " + baselineFilename + " because: " + e.what();
    return false;
  }

  // Do the diff
  itk::simple::ImageHashFilter hasher;
  if ( hasher.Execute ( baseline ) == hasher.Execute ( slice ) ) {
    // Nothing else to do
    return true;
  }
    
  if ( baseline->GetHeight() != slice->GetHeight() 
       || baseline->GetWidth() != slice->GetWidth() 
       || baseline->GetDepth() != slice->GetDepth() ) {
    mMessage = "ImageCompare: Image dimensions are different";
    return false;
  }

  // Get the center slices
  itk::simple::Image::Pointer diff = itk::simple::SubtractImageFilter().Execute ( slice, baseline );
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
    itk::simple::ImageFileWriter().SetFilename ( volumeName ).Execute ( slice );

    return false;
  }

  return true;
}
