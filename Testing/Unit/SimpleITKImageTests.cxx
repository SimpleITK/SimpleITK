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
    double size1[3] = {64,65,66};
    sitkTestSetupImage(shortImage, itkShortImage, size1, int16_t, itk::simple::sitkInt16);
    sitkTestSetupImage(floatImage, itkFloatImage, size1, float, itk::simple::sitkFloat32);
    double size2[3] = {100,100,100};
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
  EXPECT_EQ ( "a5104020df8b713235736a5990874c8877aa92ae", hasher.setHashFunction ( itk::simple::ImageHash::SHA1 ).execute ( shortImage ) ) << " SHA1 hash value";
  EXPECT_EQ ( "ddeede13a1e83abc35798f347d59113a", hasher.setHashFunction ( itk::simple::ImageHash::MD5 ).execute ( shortImage ) ) << " MD5 hash value";
}

TEST_F(Image,AddImage) {

  // Add the short and float images (same size)
  itk::simple::AddImage imageAdder;
  itk::simple::Image::Pointer out = imageAdder.execute( shortImage, floatImage );
  
  // Check results
  /*
  typedef itk::Image<float,3> ImageType;
  typedef itk::ImageRegionIterator<ImageType> IteratorType;
  ImageType::Pointer im = out->getITKImage();
  IteratorType it(im, im->GetLargestPossibleRegion());
  it.GoToBegin();
  while (!it.IsAtEnd())
    {
    std::cout << "px = " << it.Get() << std::endl;
    }
  */
  
  
  
  /*
  typedef itk::ImageRegionIterator<itk::simple::SimpleImageBase> OutputIterType;
  OutputIterType it1(out->getITKImage(), out->getITKImage()->GetRequestedRegion());
  int counter = 0;
  while (!it1.IsAtEnd())
    {
    //EXPECT_EQ( (int)it1.Get(), 2*counter );
    ++counter;
    }
  */
}






