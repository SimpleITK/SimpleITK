#include <gtest/gtest.h>
#include <SimpleITK.h>
#include <SimpleITKMacro.h>

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

  itk::simple::Image::Pointer image;
  itk::simple::SimpleImageBase::Pointer itkShortImage;
  itk::simple::SimpleImageBase::IndexType index;
  itk::simple::SimpleImageBase::SizeType size;
  itk::simple::SimpleImageBase::RegionType region;
};


TEST_F(Image,Create) {
  ASSERT_TRUE ( image->getITKImage().IsNotNull() );
  EXPECT_EQ ( image->getWidth(), itkShortImage->GetLargestPossibleRegion().GetSize()[0] ) << " Checking image width";
  EXPECT_EQ ( image->getHeight(), itkShortImage->GetLargestPossibleRegion().GetSize()[1] ) << " Checking image height";
  EXPECT_EQ ( image->getDepth(), itkShortImage->GetLargestPossibleRegion().GetSize()[2] ) << " Checking image depth";
}


TEST_F(Image,Hash) {
  itk::simple::ImageHash hasher;
  EXPECT_EQ ( "08183e1b0c50fd2cf6f070b58e218443fb7d5317", hasher.setHashFunction ( itk::simple::ImageHash::SHA1 ).execute ( image ) ) << " SHA1 hash value";
  EXPECT_EQ ( "031c48b3925696af125a807326015c3b", hasher.setHashFunction ( itk::simple::ImageHash::MD5 ).execute ( image ) ) << " MD5 hash value";
}
