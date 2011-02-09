#include <SimpleITKTestHarness.h>

#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>

#include <itkIntTypes.h>

#include "itkImage.h"
#include "itkVectorImage.h"

using  itk::simple::InstantiatedPixelIDTypeList;

class Image : public ::testing::Test {
public:
  virtual void SetUp() {
    itk::ImageBase<3>::IndexType index;
    itk::ImageBase<3>::SizeType size;
    itk::ImageBase<3>::RegionType region;
    itk::ImageBase<3>::PointType origin;
    itk::ImageBase<3>::SpacingType spacing;
    // Create an image
    for ( int i = 0; i < 3; i++ ) {
      index[i] = 0;
      size[i] = 64+i;
    }
    origin[0] = 1.1;
    origin[1] = 2.2;
    origin[2] = 3.3;
    spacing[0] = 0.5;
    spacing[1] = 0.5;
    spacing[2] = 1.5;

    region.SetSize ( size );
    region.SetIndex ( index );
    itk::Image<short,3>::Pointer im = itk::Image<short,3>::New();
    im->SetRegions ( region );
    im->SetOrigin( origin );
    im->SetSpacing( spacing );
    im->Allocate();
    im->FillBuffer ( 100 );
    itkShortImage = im;
    shortImage = new itk::simple::Image( im.GetPointer() );
    shortImage->UnRegister();

    itk::Image<float,3>::Pointer fim = itk::Image<float,3>::New();
    fim->SetRegions ( region );
    im->SetOrigin( origin );
    im->SetSpacing( spacing );
    fim->Allocate();
    im->FillBuffer ( 0.0 );
    itkFloatImage = fim;
    floatImage = new itk::simple::Image( fim.GetPointer() );
    floatImage->UnRegister();

    itkFloatVectorImage = FloatVectorImageType::New();
    floatVectorImage = new itk::simple::Image( itkFloatVectorImage.GetPointer() );
    floatVectorImage->UnRegister();

    itkFloatVector2DImage = FloatVector2DImageType::New();
    floatVector2DImage = new itk::simple::Image( itkFloatVector2DImage );
    floatVector2DImage->UnRegister();

  }

  itk::simple::Image::Pointer image;
  itk::ImageBase<3>::Pointer itkShortImage;
  itk::ImageBase<3>::IndexType index;
  itk::ImageBase<3>::SizeType size;
  itk::ImageBase<3>::RegionType region;
  itk::ImageBase<3>::PointType origin;
  itk::ImageBase<3>::SpacingType spacing;

  typedef itk::Image<short,3> ShortImageType;
  itk::simple::Image::Pointer shortImage;

  typedef itk::Image<float,3> FloatImageType;
  itk::simple::Image::Pointer floatImage;
  FloatImageType::Pointer itkFloatImage;

  typedef itk::VectorImage<float,3> FloatVectorImageType;
  itk::simple::Image::Pointer floatVectorImage;
  FloatVectorImageType::Pointer itkFloatVectorImage;

  typedef itk::VectorImage<float,2> FloatVector2DImageType;
  itk::simple::Image::Pointer floatVector2DImage;
  FloatVector2DImageType::Pointer itkFloatVector2DImage;

  itk::simple::Image::Pointer differentSizedImage;
  ShortImageType::Pointer itkDifferentSizedImage;
};


TEST_F(Image,Create) {
  ASSERT_TRUE ( shortImage->GetImageBase().IsNotNull() );
  EXPECT_EQ ( shortImage->GetWidth(), itkShortImage->GetLargestPossibleRegion().GetSize()[0] ) << " Checking image width";
  EXPECT_EQ ( shortImage->GetHeight(), itkShortImage->GetLargestPossibleRegion().GetSize()[1] ) << " Checking image height";
  EXPECT_EQ ( shortImage->GetDepth(), itkShortImage->GetLargestPossibleRegion().GetSize()[2] ) << " Checking image depth";
}

TEST_F(Image,ImageDataType) {

  // this test checks that the DataType of the images are correct
  int result;


  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<short> >::Result;
  EXPECT_EQ( shortImage->GetPixelIDValue(), result);

  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<float> >::Result;
  EXPECT_EQ( floatImage->GetPixelIDValue(), result );

  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::VectorPixelID<float> >::Result;
  EXPECT_EQ( floatVectorImage->GetPixelIDValue(), result );

  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::VectorPixelID<float> >::Result;
  EXPECT_EQ( floatVector2DImage->GetPixelIDValue(), result );


  result = itk::simple::PixelIDToPixelIDValue< itk::simple::BasicPixelID<short> >::Result;
  EXPECT_EQ( shortImage->GetPixelIDValue(), result);

  result = itk::simple::PixelIDToPixelIDValue< itk::simple::BasicPixelID<float> >::Result;
  EXPECT_EQ( floatImage->GetPixelIDValue(), result );

  result = itk::simple::PixelIDToPixelIDValue< itk::simple::VectorPixelID<float> >::Result;
  EXPECT_EQ( floatVectorImage->GetPixelIDValue(), result );

  result = itk::simple::PixelIDToPixelIDValue< itk::simple::VectorPixelID<float> >::Result;
  EXPECT_EQ( floatVector2DImage->GetPixelIDValue(), result );



  result = typelist::IndexOf< InstantiatedPixelIDTypeList,  itk::simple::ImageTypeToPixelID<ShortImageType>::PixelIDType >::Result;
  EXPECT_EQ( shortImage->GetPixelIDValue(), result );

  result = typelist::IndexOf< InstantiatedPixelIDTypeList,  itk::simple::ImageTypeToPixelID<FloatVectorImageType>::PixelIDType >::Result;
  EXPECT_EQ( floatVectorImage->GetPixelIDValue(), result );


  result = itk::simple::ImageTypeToPixelIDValue<ShortImageType>::Result;
  EXPECT_EQ( shortImage->GetPixelIDValue(), result );

  result = itk::simple::ImageTypeToPixelIDValue<FloatVectorImageType>::Result;
  EXPECT_EQ( floatVectorImage->GetPixelIDValue(), result );

}

TEST_F(Image,Constructors) {
  itk::simple::Image::Pointer image;
  itk::simple::HashImageFilter hasher;
  int result;

  image = new itk::simple::Image ( 64, 65, 66, itk::simple::sitkUInt8 );
  image->UnRegister();
  EXPECT_EQ ( "08183e1b0c50fd2cf6f070b58e218443fb7d5317", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( image ) ) << " SHA1 hash value sitkUInt8";
  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<unsigned char> >::Result;
  EXPECT_EQ ( image->GetPixelIDValue(), result );
  EXPECT_EQ ( image->GetPixelIDTypeAsString(), "8-bit unsigned integer" );
  EXPECT_EQ ( image->GetDimension(), 3u );
  EXPECT_EQ ( 64u, image->GetWidth() );
  EXPECT_EQ ( 65u, image->GetHeight() );
  EXPECT_EQ ( 66u, image->GetDepth() );

  image = new itk::simple::Image ( 64, 65, 66, itk::simple::sitkInt16 );
  image->UnRegister();
  EXPECT_EQ ( "645b71695b94923c868e16b943d8acf8f6788617", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( image ) ) << " SHA1 hash value sitkUInt16";
  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<short> >::Result;
  EXPECT_EQ ( image->GetPixelIDValue(), result );
  EXPECT_EQ ( image->GetPixelIDTypeAsString(), "16-bit signed integer" );
  EXPECT_EQ ( image->GetDimension(), 3u );
  EXPECT_EQ ( 64u, image->GetWidth() );
  EXPECT_EQ ( 65u, image->GetHeight() );
  EXPECT_EQ ( 66u, image->GetDepth() );

  image = new itk::simple::Image ( 64, 65, itk::simple::sitkUInt16 );
  image->UnRegister();
  EXPECT_EQ ( "e3c464cc1b73df3f48bacf238a80f88b5ab0d3e6", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( image ) ) << " SHA1 hash value sitkUInt16";
  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<unsigned short> >::Result;
  EXPECT_EQ ( image->GetPixelIDValue(), result );
  EXPECT_EQ ( image->GetPixelIDTypeAsString(), "16-bit unsigned integer" );
  EXPECT_EQ ( image->GetDimension(), 2u );
  EXPECT_EQ ( 64u, image->GetWidth() );
  EXPECT_EQ ( 65u, image->GetHeight() );
  EXPECT_EQ ( 0u, image->GetDepth() );

  // currently we don't have a good interface to check the values of
  // these images, let just construct these types need todo better
  // testing!

  image = new itk::simple::Image ( 64, 65, 66, itk::simple::sitkLabelUInt8 );
  image->UnRegister();
  EXPECT_EQ ( 64u, image->GetWidth() );
  EXPECT_EQ ( 65u, image->GetHeight() );
  EXPECT_EQ ( 66u, image->GetDepth() );
  image = new itk::simple::Image ( 64, 65, 66, itk::simple::sitkLabelUInt16 );
  image->UnRegister();
  image = new itk::simple::Image ( 64, 65, 66, itk::simple::sitkLabelUInt32 );
  image->UnRegister();

  image = new itk::simple::Image ( 64, 65, 66, itk::simple::sitkVectorUInt8 );
  image->UnRegister();
  EXPECT_EQ ( 64u, image->GetWidth() );
  EXPECT_EQ ( 65u, image->GetHeight() );
  EXPECT_EQ ( 66u, image->GetDepth() );
  image = new itk::simple::Image ( 64, 65, 66, itk::simple::sitkVectorUInt16 );
  image->UnRegister();

}

TEST_F(Image,Hash) {
  itk::simple::HashImageFilter hasher;
  EXPECT_EQ ( "645b71695b94923c868e16b943d8acf8f6788617", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( shortImage ) ) << " SHA1 hash value";
  EXPECT_EQ ( "d4ca27c766665f7422027ab1b977b2ef", hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 ).Execute ( shortImage ) ) << " MD5 hash value";

  EXPECT_EQ ( "3b6bfcb1922bf8b29b171062ad722c82f8aa3f50", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( floatImage ) ) << " SHA1 hash value";
  EXPECT_EQ ( "e5eba8af943d7911220c9f2fb9b5b9c8", hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 ).Execute ( floatImage ) ) << " MD5 hash value";
}

TEST_F(Image,Transforms) {

  // Origin is [1.1, 2.2, 3.3]
  // Spacing is [0.5, 0.5, 1.5]

  // Index to Physical Point
  std::vector<unsigned int> idx;
  idx.push_back(1);
  idx.push_back(1);
  idx.push_back(1);
  std::vector<double> pt = shortImage->TransformIndexToPhysicalPoint(idx);
  EXPECT_EQ(pt[0], 1.6) << " Pt to Idx [0]";
  EXPECT_EQ(pt[1], 2.7) << " Pt to Idx [1]";
  EXPECT_EQ(pt[2], 4.8) << " Pt to Idx [2]";

  // Physical Point to Index
  idx = shortImage->TransformPhysicalPointToIndex(pt);
  EXPECT_EQ(idx[0], 1u) << " Idx to Pt [0]";
  EXPECT_EQ(idx[1], 1u) << " Idx to Pt [1]";
  EXPECT_EQ(idx[2], 1u) << " Idx to Pt [2]";
}

TEST_F(Image,Properties) {

  // GetOrigin
  std::vector<double> origin = shortImage->GetOrigin();
  EXPECT_EQ(origin[0], 1.1) << " GetOrigin[0]";
  EXPECT_EQ(origin[1], 2.2) << " GetOrigin[1]";
  EXPECT_EQ(origin[2], 3.3) << " GetOrigin[2]";

  // SetOrigin
  std::vector<double> newOrigin;
  newOrigin.push_back(0.1);
  newOrigin.push_back(0.2);
  newOrigin.push_back(0.3);
  shortImage->SetOrigin( newOrigin );
  EXPECT_EQ(shortImage->GetOrigin()[0], 0.1) << " SetOrigin[0]";
  EXPECT_EQ(shortImage->GetOrigin()[1], 0.2) << " SetOrigin[1]";
  EXPECT_EQ(shortImage->GetOrigin()[2], 0.3) << " SetOrigin[2]";
  shortImage->SetOrigin( origin );

  // GetSpacing
  std::vector<double> spacing = shortImage->GetSpacing();
  EXPECT_EQ(spacing[0], 0.5) << " GetSpacing[0]";
  EXPECT_EQ(spacing[1], 0.5) << " GetSpacing[1]";
  EXPECT_EQ(spacing[2], 1.5) << " GetSpacing[2]";

  // SetSpacing
  std::vector<double> newSpacing;
  newSpacing.push_back(1.9);
  newSpacing.push_back(2.8);
  newSpacing.push_back(3.7);
  shortImage->SetSpacing( newSpacing );
  EXPECT_EQ(shortImage->GetSpacing()[0], 1.9) << " SetSpacing[0]";
  EXPECT_EQ(shortImage->GetSpacing()[1], 2.8) << " SetSpacing[1]";
  EXPECT_EQ(shortImage->GetSpacing()[2], 3.7) << " SetSpacing[2]";
  shortImage->SetOrigin( spacing );
}
