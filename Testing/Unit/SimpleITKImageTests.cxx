#include <gtest/gtest.h>
#include <sitkMacro.h>
#include <sitkImage.h>
#include <sitkImageHashFilter.h>

class Image : public ::testing::Test {
public:
  virtual void SetUp() {
    // Create an image
    for ( int i = 0; i < 3; i++ ) {
      index[i] = 0;
      size[i] = 64+i;
    }
    region.SetSize ( size );
    region.SetIndex ( index );
    itk::Image<int16_t,3>::Pointer im = itk::Image<int16_t,3>::New();
    im->SetRegions ( region );
    im->Allocate();
    itkShortImage = im;
    image = new itk::simple::Image( im.GetPointer() );
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
  ASSERT_TRUE ( image->GetITKImage().IsNotNull() );
  EXPECT_EQ ( image->GetWidth(),
    itkShortImage->GetLargestPossibleRegion().GetSize()[0] ) << " Checking image width";
  EXPECT_EQ ( image->GetHeight(),
    itkShortImage->GetLargestPossibleRegion().GetSize()[1] ) << " Checking image height";
  EXPECT_EQ ( image->GetDepth(),
    itkShortImage->GetLargestPossibleRegion().GetSize()[2] ) << " Checking image depth";
}


TEST_F(Image,Hash) {
  itk::simple::ImageHashFilter hasher;
  EXPECT_EQ ( "08183e1b0c50fd2cf6f070b58e218443fb7d5317",
    hasher.SetHashFunction ( itk::simple::ImageHashFilter::SHA1 ).Execute ( image ) )
    << " SHA1 hash value";
  EXPECT_EQ ( "031c48b3925696af125a807326015c3b",
    hasher.SetHashFunction ( itk::simple::ImageHashFilter::MD5 ).Execute ( image ) )
    << " MD5 hash value";
}






