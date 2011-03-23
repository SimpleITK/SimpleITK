#include <SimpleITKTestHarness.h>
#include <memory>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>
#include <sitkPixelContainer.h>

#include "itkImage.h"
#include "itkVectorImage.h"
#include <stdint.h>

using  itk::simple::InstantiatedPixelIDTypeList;

class PixelContainer : public ::testing::Test {
public:
  virtual void SetUp() {
    itk::ImageBase<3>::IndexType index;
    itk::ImageBase<3>::SizeType size;
    itk::ImageBase<3>::RegionType region;
    // Create an image
    for ( int i = 0; i < 3; i++ ) {
      index[i] = 0;
      size[i] = 64+i;
    }
    region.SetSize ( size );
    region.SetIndex ( index );
    itkShortImage = ShortImageType::New();
    itkShortImage->SetRegions ( region );
    itkShortImage->Allocate();
    itkShortImage->FillBuffer ( 100 );
    itkShortImageBase = itkShortImage;
    shortImage.reset ( new itk::simple::Image( itkShortImage.GetPointer() ) );

    shortPixelContainer.reset ( shortImage->GetPixelContainer() );

    shortBuffer = shortPixelContainer->GetBufferAsInt16();

    itkFloatImage = FloatImageType::New();
    itkFloatImage->SetRegions ( region );
    itkFloatImage->Allocate();
    itkFloatImage->FillBuffer ( 0.0 );
    itkFloatImageBase = itkFloatImage;
    floatImage.reset ( new itk::simple::Image( itkFloatImage.GetPointer() ) );

    floatPixelContainer.reset ( floatImage->GetPixelContainer() );

    floatBuffer = floatPixelContainer->GetBufferAsFloat();

    itkFloatVectorImage = FloatVectorImageType::New();
    floatVectorImage.reset ( new itk::simple::Image( itkFloatVectorImage.GetPointer() ) );

    itkFloatVector2DImage = FloatVector2DImageType::New();
    floatVector2DImage.reset ( new itk::simple::Image( itkFloatVector2DImage ) );

  }

  std::auto_ptr<itk::simple::Image> image;
  itk::ImageBase<3>::Pointer itkShortImageBase;
  itk::ImageBase<3>::IndexType index;
  itk::ImageBase<3>::SizeType size;
  itk::ImageBase<3>::RegionType region;

  typedef itk::Image<short,3> ShortImageType;
  ShortImageType::Pointer itkShortImage;
  std::auto_ptr<itk::simple::Image> shortImage;
  std::auto_ptr<itk::simple::PixelContainer> shortPixelContainer;
  int16_t * shortBuffer;

  itk::ImageBase<3>::Pointer itkFloatImageBase;
  typedef itk::Image<float,3> FloatImageType;
  FloatImageType::Pointer itkFloatImage;
  std::auto_ptr<itk::simple::Image> floatImage;
  std::auto_ptr<itk::simple::PixelContainer> floatPixelContainer;
  float * floatBuffer;

  typedef itk::VectorImage<float,3> FloatVectorImageType;
  std::auto_ptr<itk::simple::Image> floatVectorImage;
  FloatVectorImageType::Pointer itkFloatVectorImage;

  typedef itk::VectorImage<float,2> FloatVector2DImageType;
  std::auto_ptr<itk::simple::Image> floatVector2DImage;
  FloatVector2DImageType::Pointer itkFloatVector2DImage;

  std::auto_ptr<itk::simple::Image> differentSizedImage;
  ShortImageType::Pointer itkDifferentSizedImage;
};


TEST_F(PixelContainer,Create) {
  ASSERT_TRUE ( shortImage->GetImageBase() != NULL );
  EXPECT_EQ ( shortImage->GetWidth(), itkShortImageBase->GetLargestPossibleRegion().GetSize()[0] ) << " Checking image width";
  EXPECT_EQ ( shortImage->GetHeight(), itkShortImageBase->GetLargestPossibleRegion().GetSize()[1] ) << " Checking image height";
  EXPECT_EQ ( shortImage->GetDepth(), itkShortImageBase->GetLargestPossibleRegion().GetSize()[2] ) << " Checking image depth";
  EXPECT_EQ ( shortBuffer, itkShortImage->GetBufferPointer() ) << " Checking Short Image Buffer Pointer";

  EXPECT_EQ ( floatImage->GetWidth(), itkFloatImageBase->GetLargestPossibleRegion().GetSize()[0] ) << " Checking image width";
  EXPECT_EQ ( floatImage->GetHeight(), itkFloatImageBase->GetLargestPossibleRegion().GetSize()[1] ) << " Checking image height";
  EXPECT_EQ ( floatImage->GetDepth(), itkFloatImageBase->GetLargestPossibleRegion().GetSize()[2] ) << " Checking image depth";
  EXPECT_EQ ( floatBuffer, itkFloatImage->GetBufferPointer() ) << " Checking Float Image Buffer Pointer";
}

TEST_F(PixelContainer,ImageDataType) {

  // this test checks that the DataType of the PixelContainers are correct
  int result;

  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<short> >::Result;
  EXPECT_EQ( shortPixelContainer->GetPixelIDValue(), result);

  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<float> >::Result;
  EXPECT_EQ( floatPixelContainer->GetPixelIDValue(), result );

  result = itk::simple::PixelIDToPixelIDValue< itk::simple::BasicPixelID<short> >::Result;
  EXPECT_EQ( shortPixelContainer->GetPixelIDValue(), result);

  result = itk::simple::PixelIDToPixelIDValue< itk::simple::BasicPixelID<float> >::Result;
  EXPECT_EQ( floatPixelContainer->GetPixelIDValue(), result );

  result = typelist::IndexOf< InstantiatedPixelIDTypeList,  itk::simple::ImageTypeToPixelID<ShortImageType>::PixelIDType >::Result;
  EXPECT_EQ( shortPixelContainer->GetPixelIDValue(), result );

  result = itk::simple::ImageTypeToPixelIDValue<ShortImageType>::Result;
  EXPECT_EQ( shortPixelContainer->GetPixelIDValue(), result );
}

TEST_F(PixelContainer,Constructors) {
  std::auto_ptr<itk::simple::PixelContainer> pixelContainer;
  std::auto_ptr<itk::simple::Image> image;
  itk::simple::HashImageFilter hasher;
  int result;

  image.reset ( new itk::simple::Image ( 64, 65, 66, itk::simple::sitkUInt8 ) );

  pixelContainer.reset ( image->GetPixelContainer() );

  EXPECT_EQ ( pixelContainer->GetNumberOfPixels(), image->GetWidth() * image->GetHeight() * image->GetDepth() );

  EXPECT_EQ ( "08183e1b0c50fd2cf6f070b58e218443fb7d5317", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( *image ) ) << " SHA1 hash value sitkUInt8";
  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<unsigned char> >::Result;
  EXPECT_EQ ( image->GetPixelIDValue(), result );
  EXPECT_EQ ( image->GetPixelIDTypeAsString(), "8-bit unsigned integer" );
  EXPECT_EQ ( image->GetDimension(), 3u );
  EXPECT_EQ ( 64u, image->GetWidth() );
  EXPECT_EQ ( 65u, image->GetHeight() );
  EXPECT_EQ ( 66u, image->GetDepth() );

  image.reset ( new itk::simple::Image ( 64, 65, 66, itk::simple::sitkInt16 ) );
  EXPECT_EQ ( "645b71695b94923c868e16b943d8acf8f6788617", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( *image ) ) << " SHA1 hash value sitkUInt16";
  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<short> >::Result;
  EXPECT_EQ ( image->GetPixelIDValue(), result );
  EXPECT_EQ ( image->GetPixelIDTypeAsString(), "16-bit signed integer" );
  EXPECT_EQ ( image->GetDimension(), 3u );
  EXPECT_EQ ( 64u, image->GetWidth() );
  EXPECT_EQ ( 65u, image->GetHeight() );
  EXPECT_EQ ( 66u, image->GetDepth() );

  image.reset ( new itk::simple::Image ( 64, 65, itk::simple::sitkUInt16 ) );
  EXPECT_EQ ( "e3c464cc1b73df3f48bacf238a80f88b5ab0d3e6", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( *image ) ) << " SHA1 hash value sitkUInt16";
  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<unsigned short> >::Result;
  EXPECT_EQ ( image->GetPixelIDValue(), result );
  EXPECT_EQ ( image->GetPixelIDTypeAsString(), "16-bit unsigned integer" );
  EXPECT_EQ ( image->GetDimension(), 2u );
  EXPECT_EQ ( 64u, image->GetWidth() );
  EXPECT_EQ ( 65u, image->GetHeight() );
  EXPECT_EQ ( 0u, image->GetDepth() );
}
