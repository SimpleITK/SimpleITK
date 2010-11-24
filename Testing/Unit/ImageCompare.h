#ifndef __ImageCompare_h
#define __ImageCompare_h
#include "SimpleITKTestHarness.h"
#include "SimpleITK.h"

class ImageCompare {
public:
  typedef ImageCompare Self;
  ImageCompare();

  // Compare the image to the named baseline image slice by slice, display the difference in the center slice
  // If the baseline does not exist, fail, and write a baseline image in the output directory
  bool compare ( itk::simple::Image::Pointer image, std::string name );

  // Return the message from the previous image comparison.
  std::string getMessage() { return mMessage; }
  Self& setTolerance ( double t ) { mTolerance = t; return *this; }
  double getTolerance() { return mTolerance; }
protected:
  std::string mMessage;
  double mTolerance;
};

#define IMAGECOMPARE( x, str )                  \
  { \
ImageCompare imageCompare;  \
 EXPECT_TRUE( imageCompare.compare( x, str ) ) << imageCompare.getMessage(); \
 }
#define IMAGECOMPAREWITHTOLERANCE( x, str, tolerance )        \
  { \
  ImageCompare imageCompare;  \
  imageCompare.setTolerance(tolerance); \
  EXPECT_TRUE( imageCompare.compare( x, str ) ) << imageCompare.getMessage(); \
  }


#endif
