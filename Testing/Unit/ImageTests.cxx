#include <SimpleITK.h>
#include <SimpleITKTestHarness.h>

class Image : public ::testing::Test {
public:
  virtual void SetUp() {
    itk::simple::SimpleImageBase::IndexType index;
    itk::simple::SimpleImageBase::SizeType size;
    itk::simple::SimpleImageBase::RegionType region;
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
    im->FillBuffer ( 0 );
    itkShortImage = im;
    shortImage = new itk::simple::Image( im.GetPointer() );

    itk::Image<float,3>::Pointer fim = itk::Image<float,3>::New();
    fim->SetRegions ( region );
    fim->Allocate();
    im->FillBuffer ( 0.0 );
    itkFloatImage = fim;
    floatImage = new itk::simple::Image( fim.GetPointer() );

  }

  itk::simple::Image::Pointer image;
  itk::simple::SimpleImageBase::Pointer itkShortImage;
  itk::simple::SimpleImageBase::IndexType index;
  itk::simple::SimpleImageBase::SizeType size;
  itk::simple::SimpleImageBase::RegionType region;

  typedef itk::Image<int16_t,3> ShortImageType;
  itk::simple::Image::Pointer shortImage;

  typedef itk::Image<float,3> FloatImageType;
  itk::simple::Image::Pointer floatImage;
  FloatImageType::Pointer itkFloatImage;

  itk::simple::Image::Pointer differentSizedImage;
  ShortImageType::Pointer itkDifferentSizedImage;
};


TEST_F(Image,Create) {
  ASSERT_TRUE ( shortImage->GetImageBase().IsNotNull() );
  EXPECT_EQ ( shortImage->GetWidth(), itkShortImage->GetLargestPossibleRegion().GetSize()[0] ) << " Checking image width";
  EXPECT_EQ ( shortImage->GetHeight(), itkShortImage->GetLargestPossibleRegion().GetSize()[1] ) << " Checking image height";
  EXPECT_EQ ( shortImage->GetDepth(), itkShortImage->GetLargestPossibleRegion().GetSize()[2] ) << " Checking image depth";
}


TEST_F(Image,Hash) {
  itk::simple::ImageHashFilter hasher;
  EXPECT_EQ ( "08183e1b0c50fd2cf6f070b58e218443fb7d5317",
    hasher.SetHashFunction ( itk::simple::ImageHashFilter::SHA1 ).Execute ( shortImage ) )
    << " SHA1 hash value";
  EXPECT_EQ ( "031c48b3925696af125a807326015c3b",
    hasher.SetHashFunction ( itk::simple::ImageHashFilter::MD5 ).Execute ( floatImage ) )
    << " MD5 hash value";
}
