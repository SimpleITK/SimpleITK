#include <gtest/gtest.h>
#include <SimpleITK.h>
#include <SimpleITKMacro.h>
#include "itkImageRegionIterator.h"

#define sitkTestSetupImage(simpleImageName, itkImageName, sizeArr, itkType, simpleType) \
  { \
  itk::simple::SimpleImageBase::IndexType index; \
  itk::simple::SimpleImageBase::SizeType size; \
  itk::simple::SimpleImageBase::RegionType region; \
  typedef itk::Image<itkType,3> ImageType; \
  typedef itk::ImageRegionIterator<ImageType> IteratorType; \
  for ( int i = 0; i < 3; i++ )  \
    { \
    index[i] = 0; \
    size[i] = sizeArr[i]; \
    } \
  region.SetSize ( size ); \
  region.SetIndex ( index ); \
  itk::Image<itkType,3>::Pointer i = itk::Image<itkType,3>::New(); \
  i->SetRegions ( region ); \
  i->Allocate(); \
  IteratorType it(i, i->GetRequestedRegion()); \
  it.GoToBegin(); \
  int counter = 0; \
  while(!it.IsAtEnd())  \
    { \
    it.Set(counter); \
    ++counter; \
    ++it; \
    } \
  itkImageName = i; \
  simpleImageName = new itk::simple::Image ( itkImageName, simpleType ); \
  }

class Image : public ::testing::Test {
public:
  virtual void SetUp() {
    // Create test images
    double size1[3] = {12,11,10};
    sitkTestSetupImage(shortImage, itkShortImage, size1, int16_t, itk::simple::sitkInt16);
    sitkTestSetupImage(floatImage, itkFloatImage, size1, float, itk::simple::sitkFloat32);
    double size2[3] = {30,30,30};
    sitkTestSetupImage(differentSizedImage, itkDifferentSizedImage, size2, int16_t, itk::simple::sitkInt16);
  }
  
  typedef itk::Image<int16_t,3> ShortImageType;
  itk::simple::Image::Pointer shortImage;
  ShortImageType::Pointer itkShortImage;
  
  typedef itk::Image<float,3> FloatImageType;
  itk::simple::Image::Pointer floatImage;
  FloatImageType::Pointer itkFloatImage;
  
  itk::simple::Image::Pointer differentSizedImage;
  ShortImageType::Pointer itkDifferentSizedImage;
};


TEST_F(Image,Create) {
  ASSERT_TRUE ( shortImage->getITKImage().IsNotNull() );
  EXPECT_EQ ( shortImage->getWidth(), itkShortImage->GetLargestPossibleRegion().GetSize()[0] ) << " Checking image width";
  EXPECT_EQ ( shortImage->getHeight(), itkShortImage->GetLargestPossibleRegion().GetSize()[1] ) << " Checking image height";
  EXPECT_EQ ( shortImage->getDepth(), itkShortImage->GetLargestPossibleRegion().GetSize()[2] ) << " Checking image depth";
}


TEST_F(Image,Hash) {
  itk::simple::ImageHash hasher;
  EXPECT_EQ ( "d160ca5e5687e4a6d7b2289c41dadc19287b209f", hasher.setHashFunction ( itk::simple::ImageHash::SHA1 ).execute ( shortImage ) ) << " SHA1 hash value";
  EXPECT_EQ ( "52e81e6129f3fac5ec17200b48c0248e", hasher.setHashFunction ( itk::simple::ImageHash::MD5 ).execute ( shortImage ) ) << " MD5 hash value";
}

TEST_F(Image,AddImage) {

  // Add the short and float images (same size)
  itk::simple::AddImage imageAdder;
  itk::simple::Image::Pointer out = imageAdder.execute( shortImage, floatImage );
  
  // Make sure addition was done correctly
  int counter = 0;
  sitkForEachPixelR( out, px, 
    ASSERT_TRUE( 2*counter == (int)px );
    ++counter;
  );
  
  
  // Try adding different sized images
  sitkForEachPixelW(differentSizedImage, px, 
    px = 1;
  )
  itk::simple::Image::Pointer out2 = imageAdder.execute( shortImage, differentSizedImage );
  counter = 0;
  sitkForEachPixelR( out2, px, 
    ASSERT_TRUE( counter+1 == (int)px );
    ++counter;
  );
}






