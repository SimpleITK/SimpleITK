#ifndef __ImageCompare_h
#define __ImageCompare_h
#include <SimpleITKTestHarness.h>
#include <sitkImage.h>

class ImageCompare {
public:
  typedef ImageCompare Self;
  ImageCompare();

  // Compare the image to the named baseline image slice by slice, display the difference in the center slice
  // If the baseline does not exist, fail, and write a baseline image in the output directory
  bool compare ( const itk::simple::Image& image, std::string testGroup, std::string tag );

  // Return the message from the previous image comparison.
  std::string getMessage() { return mMessage; }
  Self& setTolerance ( double t ) { mTolerance = t; return *this; }
  double getTolerance() { return mTolerance; }

  static void NormalizeAndSave ( const itk::simple::Image &image, const std::string &filename );
protected:
  std::string mMessage;
  double mTolerance;
};

#define IMAGECOMPARE( x, tag )                  \
  { \
ImageCompare imageCompare;  \
 EXPECT_TRUE( imageCompare.compare( x, "", tag ) ) << imageCompare.getMessage(); \
 }
#define IMAGECOMPAREWITHTOLERANCE( x, tag, tolerance )        \
  { \
  ImageCompare imageCompare;  \
  imageCompare.setTolerance(tolerance); \
  EXPECT_TRUE( imageCompare.compare( x, "", tag ) ) << imageCompare.getMessage(); \
  }

#define IMAGECOMPAREWITHHASH( hash, hashType, image, message )        \
  { \
  std::string actualHashValue = itk::simple::Hash( image, itk::simple::HashImageFilter::hashType ); \
  EXPECT_EQ ( hash, actualHashValue  ) << message;                      \
  if ( hash != actualHashValue )                                        \
    {                                                                   \
    std::string TestImageFilename = dataFinder.GetOutputFile ( actualHashValue + ".png"); \
    try {                                                               \
      ImageCompare::NormalizeAndSave( image, TestImageFilename );       \
                                                                        \
      std::cout << "<DartMeasurementFile name=\"TestImage\" type=\"image/png\">"; \
      std::cout << TestImageFilename << "</DartMeasurementFile>" << std::endl; \
    } catch (... ) {                                                    \
      std::cerr << "Unknow Error while writing image for measurement" << std::endl; \
    }                                                                   \
                                                                        \
    itk::simple::WriteImage ( image, dataFinder.GetOutputFile ( actualHashValue + ".nrrd" ) ); \
    std::cout << "Saved actual image as " << dataFinder.GetOutputFile ( actualHashValue + ".nrrd" ) << std::endl; \
    }                                                                   \
  }

#define IMAGECOMPARE_WITH_TESTCASE( x, testCase, tag )  \
  { \
ImageCompare imageCompare;  \
 EXPECT_TRUE( imageCompare.compare( x, testCase, tag ) ) << imageCompare.getMessage(); \
 }
#define IMAGECOMPAREWITHTOLERANCE_WITH_TESTCASE( x, testCase, tag, tolerance ) \
  { \
  ImageCompare imageCompare;  \
  imageCompare.setTolerance(tolerance); \
  EXPECT_TRUE( imageCompare.compare( x, testCase, tag ) ) << imageCompare.getMessage(); \
  }


#endif
