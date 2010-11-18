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
    im->FillBuffer ( 100 );
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
  EXPECT_EQ ( "645b71695b94923c868e16b943d8acf8f6788617", hasher.SetHashFunction ( itk::simple::ImageHashFilter::SHA1 ).Execute ( shortImage ) ) << " SHA1 hash value";
  EXPECT_EQ ( "d4ca27c766665f7422027ab1b977b2ef", hasher.SetHashFunction ( itk::simple::ImageHashFilter::MD5 ).Execute ( shortImage ) ) << " MD5 hash value";

  EXPECT_EQ ( "3b6bfcb1922bf8b29b171062ad722c82f8aa3f50", hasher.SetHashFunction ( itk::simple::ImageHashFilter::SHA1 ).Execute ( floatImage ) ) << " SHA1 hash value";
  EXPECT_EQ ( "e5eba8af943d7911220c9f2fb9b5b9c8", hasher.SetHashFunction ( itk::simple::ImageHashFilter::MD5 ).Execute ( floatImage ) ) << " MD5 hash value";
}
