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

  float testImages( const itk::simple::Image& testImage,
                    const itk::simple::Image& baselineImage,
                    bool retportErrors,
                    const std::string &baselineImageFilename );


  // Return the message from the previous image comparison.
  std::string getMessage() { return mMessage; }
  void setTolerance ( double t ) { mTolerance = t; }
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
    } catch (std::exception &e) {                                       \
      std::cerr << "Unexpected error while writing image:" << e.what() << std::endl; \
    } catch (...) {                                                     \
      std::cerr << "Unknow Error while writing image for measurement" << std::endl; \
    }                                                                   \
                                                                        \
    itk::simple::Image timage = image;                                  \
    if (timage.GetPixelIDValue() == itk::simple::sitkLabelUInt8) \
      {                                                                 \
      timage = itk::simple::Cast( timage, itk::simple::sitkUInt8); \
      }                                                                 \
    else if (timage.GetPixelIDValue() == itk::simple::sitkLabelUInt16) \
      {                                                                 \
      timage = itk::simple::Cast( timage, itk::simple::sitkUInt16); \
      }                                                                 \
    else if (timage.GetPixelIDValue() == itk::simple::sitkLabelUInt32) \
      {                                                                 \
      timage = itk::simple::Cast( timage, itk::simple::sitkUInt32); \
      }                                                                 \
    else if (timage.GetPixelIDValue() == itk::simple::sitkLabelUInt64) \
      {                                                                 \
      timage = itk::simple::Cast( timage, itk::simple::sitkUInt64); \
      }                                                                 \
    itk::simple::WriteImage ( timage, dataFinder.GetOutputFile ( actualHashValue + ".nrrd" ) ); \
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
