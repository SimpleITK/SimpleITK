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
  bool compare ( itk::simple::Image::Pointer image, std::string testGroup, std::string tag );

  // Return the message from the previous image comparison.
  std::string getMessage() { return mMessage; }
  Self& setTolerance ( double t ) { mTolerance = t; return *this; }
  double getTolerance() { return mTolerance; }
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
