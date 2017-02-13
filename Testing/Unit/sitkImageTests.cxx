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
#include <SimpleITKTestHarness.h>

#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>

#include "sitkAddImageFilter.h"
#include "sitkSubtractImageFilter.h"
#include "sitkMultiplyImageFilter.h"

#include "sitkImageOperators.h"

#include "sitkComplexToRealImageFilter.h"
#include "sitkComplexToImaginaryImageFilter.h"
#include "sitkRealAndImaginaryToComplexImageFilter.h"
#include "sitkImportImageFilter.h"

#include <itkIntTypes.h>

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkMetaDataObject.h"

const double adir[] = {0.0, 0.0, 1.0,
                       -1.0, 0.0, 0.0,
                       0.0, -1.0, 0.0};

using  itk::simple::InstantiatedPixelIDTypeList;
namespace nsstd = itk::simple::nsstd;



class Image : public ::testing::Test {
public:
  typedef nsstd::auto_ptr<itk::simple::Image> sitkAutoImagePointer;

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
    shortImage = sitkAutoImagePointer( new itk::simple::Image( im.GetPointer() ) );

    itk::Image<float,3>::Pointer fim = itk::Image<float,3>::New();
    fim->SetRegions ( region );
    fim->SetOrigin( origin );
    fim->SetSpacing( spacing );
    fim->Allocate();
    fim->FillBuffer ( 0 );
    itkFloatImage = fim;
    floatImage = sitkAutoImagePointer( new itk::simple::Image( fim.GetPointer() ) );

    itkFloatVectorImage = FloatVectorImageType::New();
    floatVectorImage = sitkAutoImagePointer( new itk::simple::Image( itkFloatVectorImage.GetPointer() ) );

    itkFloatVector2DImage = FloatVector2DImageType::New();
    floatVector2DImage = sitkAutoImagePointer( new itk::simple::Image( itkFloatVector2DImage ) );

    directionI2D = std::vector<double>(4, 0.0 );
    directionI3D = std::vector<double>(9, 0.0 );

    directionI2D[0] = directionI2D[3] = 1.0;

    directionI3D[0] = directionI3D[4] = directionI3D[8] = 1.0;
  }

  itk::ImageBase<3>::Pointer itkShortImage;

  typedef itk::Image<short,3> ShortImageType;
  sitkAutoImagePointer shortImage;

  typedef itk::Image<float,3> FloatImageType;
  sitkAutoImagePointer floatImage;
  FloatImageType::Pointer itkFloatImage;

  typedef itk::VectorImage<float,3> FloatVectorImageType;
  sitkAutoImagePointer floatVectorImage;
  FloatVectorImageType::Pointer itkFloatVectorImage;

  typedef itk::VectorImage<float,2> FloatVector2DImageType;
  sitkAutoImagePointer floatVector2DImage;
  FloatVector2DImageType::Pointer itkFloatVector2DImage;

  sitkAutoImagePointer differentSizedImage;
  ShortImageType::Pointer itkDifferentSizedImage;


  std::vector<double> directionI2D;
  std::vector<double> directionI3D;

};


TEST_F(Image,Create) {
  ASSERT_TRUE ( shortImage->GetITKBase() != NULL );
  EXPECT_EQ ( shortImage->GetWidth(), itkShortImage->GetLargestPossibleRegion().GetSize()[0] ) << " Checking image width";
  EXPECT_EQ ( shortImage->GetHeight(), itkShortImage->GetLargestPossibleRegion().GetSize()[1] ) << " Checking image height";
  EXPECT_EQ ( shortImage->GetDepth(), itkShortImage->GetLargestPossibleRegion().GetSize()[2] ) << " Checking image depth";

  EXPECT_EQ ( shortImage->GetSize()[0], shortImage->GetWidth() );
  EXPECT_EQ ( shortImage->GetSize()[1], shortImage->GetHeight() );
  EXPECT_EQ ( shortImage->GetSize()[2], shortImage->GetDepth() );

  std::vector< unsigned int > size = shortImage->GetSize();

  EXPECT_EQ ( size[0], shortImage->GetWidth() );
  EXPECT_EQ ( size[1], shortImage->GetHeight() );
  EXPECT_EQ ( size[2], shortImage->GetDepth() );

  EXPECT_EQ ( 274560u, shortImage->GetNumberOfPixels() );

}

TEST_F(Image,ImageDataType) {

  // this test checks that the DataType of the images are correct
  int result;


  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<short> >::Result;
  EXPECT_EQ( shortImage->GetPixelIDValue(), result);
  EXPECT_EQ( shortImage->GetPixelID(), result);

  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<float> >::Result;
  EXPECT_EQ( floatImage->GetPixelIDValue(), result );
  EXPECT_EQ( floatImage->GetPixelID(), result );

  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::VectorPixelID<float> >::Result;
  EXPECT_EQ( floatVectorImage->GetPixelIDValue(), result );
  EXPECT_EQ( floatVectorImage->GetPixelID(), result );

  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::VectorPixelID<float> >::Result;
  EXPECT_EQ( floatVector2DImage->GetPixelIDValue(), result );
  EXPECT_EQ( floatVector2DImage->GetPixelID(), result );


  result = itk::simple::PixelIDToPixelIDValue< itk::simple::BasicPixelID<short> >::Result;
  EXPECT_EQ( shortImage->GetPixelIDValue(), result);
  EXPECT_EQ( shortImage->GetPixelID(), result);

  result = itk::simple::PixelIDToPixelIDValue< itk::simple::BasicPixelID<float> >::Result;
  EXPECT_EQ( floatImage->GetPixelIDValue(), result );
  EXPECT_EQ( floatImage->GetPixelID(), result );

  result = itk::simple::PixelIDToPixelIDValue< itk::simple::VectorPixelID<float> >::Result;
  EXPECT_EQ( floatVectorImage->GetPixelIDValue(), result );
  EXPECT_EQ( floatVectorImage->GetPixelID(), result );

  result = itk::simple::PixelIDToPixelIDValue< itk::simple::VectorPixelID<float> >::Result;
  EXPECT_EQ( floatVector2DImage->GetPixelIDValue(), result );
  EXPECT_EQ( floatVector2DImage->GetPixelID(), result );



  result = typelist::IndexOf< InstantiatedPixelIDTypeList,  itk::simple::ImageTypeToPixelID<ShortImageType>::PixelIDType >::Result;
  EXPECT_EQ( shortImage->GetPixelIDValue(), result );
  EXPECT_EQ( shortImage->GetPixelID(), result );

  result = typelist::IndexOf< InstantiatedPixelIDTypeList,  itk::simple::ImageTypeToPixelID<FloatVectorImageType>::PixelIDType >::Result;
  EXPECT_EQ( floatVectorImage->GetPixelIDValue(), result );
  EXPECT_EQ( floatVectorImage->GetPixelID(), result );


  result = itk::simple::ImageTypeToPixelIDValue<ShortImageType>::Result;
  EXPECT_EQ( shortImage->GetPixelIDValue(), result );
  EXPECT_EQ( shortImage->GetPixelID(), result );

  result = itk::simple::ImageTypeToPixelIDValue<FloatVectorImageType>::Result;
  EXPECT_EQ( floatVectorImage->GetPixelIDValue(), result );
  EXPECT_EQ( floatVectorImage->GetPixelID(), result );


}

TEST_F(Image,Constructors) {
  itk::simple::HashImageFilter hasher;
  int result;

  {
  itk::simple::Image image;
  EXPECT_EQ ( 0u, image.GetWidth() );
  EXPECT_EQ ( 0u, image.GetHeight() );
  EXPECT_EQ ( 0u, image.GetDepth() );
  EXPECT_EQ ( 0u, image.GetNumberOfPixels() );
  }

  itk::simple::Image image ( 64, 65, 66, itk::simple::sitkUInt8 );
  EXPECT_EQ ( "08183e1b0c50fd2cf6f070b58e218443fb7d5317", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( image ) ) << " SHA1 hash value sitkUInt8";
  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<unsigned char> >::Result;
  EXPECT_EQ ( image.GetPixelIDValue(), result );
  EXPECT_EQ ( image.GetPixelIDTypeAsString(), "8-bit unsigned integer" );
  EXPECT_EQ ( image.GetDimension(), 3u );
  EXPECT_EQ ( 64u, image.GetWidth() );
  EXPECT_EQ ( 65u, image.GetHeight() );
  EXPECT_EQ ( 66u, image.GetDepth() );
  EXPECT_EQ ( 274560u, image.GetNumberOfPixels() );
  EXPECT_EQ( image.GetDirection(), directionI3D );

  image = itk::simple::Image ( 64, 65, 66, itk::simple::sitkInt16 );
  EXPECT_EQ ( "645b71695b94923c868e16b943d8acf8f6788617", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( image ) ) << " SHA1 hash value sitkUInt16";
  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<short> >::Result;
  EXPECT_EQ ( image.GetPixelIDValue(), result );
  EXPECT_EQ ( image.GetPixelIDTypeAsString(), "16-bit signed integer" );
  EXPECT_EQ ( image.GetDimension(), 3u );
  EXPECT_EQ ( 64u, image.GetWidth() );
  EXPECT_EQ ( 65u, image.GetHeight() );
  EXPECT_EQ ( 66u, image.GetDepth() );
  EXPECT_EQ ( 274560u, image.GetNumberOfPixels() );
  EXPECT_EQ( image.GetDirection(), directionI3D );

  image = itk::simple::Image ( 64, 65, itk::simple::sitkUInt16 );
  EXPECT_EQ ( "e3c464cc1b73df3f48bacf238a80f88b5ab0d3e6", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( image ) ) << " SHA1 hash value sitkUInt16";
  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<unsigned short> >::Result;
  EXPECT_EQ ( image.GetPixelIDValue(), result );
  EXPECT_EQ ( image.GetPixelIDTypeAsString(), "16-bit unsigned integer" );
  EXPECT_EQ ( image.GetDimension(), 2u );
  EXPECT_EQ ( 64u, image.GetWidth() );
  EXPECT_EQ ( 65u, image.GetHeight() );
  EXPECT_EQ ( 0u, image.GetDepth() );
  EXPECT_EQ ( 4160u, image.GetNumberOfPixels() );
  EXPECT_EQ ( 1u, image.GetNumberOfComponentsPerPixel() );
  EXPECT_EQ( image.GetDirection(), directionI2D );

  // Test the constructors for vector images
  std::vector<unsigned int> s2d(2, 10);
  std::vector<unsigned int> s3d(3, 5);

  image = itk::simple::Image( s2d, itk::simple::sitkVectorUInt8 );

  EXPECT_EQ ( image.GetDimension(), 2u );
  EXPECT_EQ ( 2u, image.GetNumberOfComponentsPerPixel() );
  image = itk::simple::Image( s3d, itk::simple::sitkVectorFloat32 );
  EXPECT_EQ ( image.GetDimension(), 3u );
  EXPECT_EQ ( 3u, image.GetNumberOfComponentsPerPixel() );

  image = itk::simple::Image( s2d, itk::simple::sitkVectorInt16, 5 );
  EXPECT_EQ ( image.GetDimension(), 2u );
  EXPECT_EQ ( 5u, image.GetNumberOfComponentsPerPixel() );
  image = itk::simple::Image( s3d, itk::simple::sitkVectorFloat64, 10 );
  EXPECT_EQ ( image.GetDimension(), 3u );
  EXPECT_EQ ( 10u, image.GetNumberOfComponentsPerPixel() );


  // check for error when incorrect number of dimensions are requested
  std::vector<unsigned int> s1d(1, 100);
  std::vector<unsigned int> s5d(5, 100);
  ASSERT_ANY_THROW( itk::simple::Image( s1d, itk::simple::sitkVectorFloat64 ) );
  ASSERT_ANY_THROW( itk::simple::Image( s5d, itk::simple::sitkVectorFloat64 ) );

  // check for error with bad pixelID
  ASSERT_ANY_THROW( itk::simple::Image( s2d, itk::simple::sitkUnknown ) );
  ASSERT_ANY_THROW( itk::simple::Image( s2d, itk::simple::PixelIDValueEnum(-100) ) );

  // check for error when non-vector type requests components ( should
  // this be an error or should we just be converted to a vector )
  ASSERT_ANY_THROW( itk::simple::Image( s2d, itk::simple::sitkInt16, 10 ) );
  ASSERT_ANY_THROW( itk::simple::Image( s2d, itk::simple::sitkLabelUInt8, 10 ) );

  // currently we don't have a good interface to check the values of
  // these images, let just construct these types need todo better
  // testing!

  image = itk::simple::Image ( 64, 65, 66, itk::simple::sitkLabelUInt8 );
  EXPECT_EQ ( 64u, image.GetWidth() );
  EXPECT_EQ ( 65u, image.GetHeight() );
  EXPECT_EQ ( 66u, image.GetDepth() );
  EXPECT_EQ ( 274560u, image.GetNumberOfPixels() );
  EXPECT_EQ ( 1u, image.GetNumberOfComponentsPerPixel() );
  EXPECT_EQ( image.GetDirection(), directionI3D );

  image = itk::simple::Image ( 64, 65, 66, itk::simple::sitkLabelUInt16 );

  image = itk::simple::Image ( 64, 65, 66, itk::simple::sitkLabelUInt32 );

  image = itk::simple::Image ( 64, 65, 66, itk::simple::sitkVectorUInt8 );

  EXPECT_EQ ( 64u, image.GetWidth() );
  EXPECT_EQ ( 65u, image.GetHeight() );
  EXPECT_EQ ( 66u, image.GetDepth() );
  EXPECT_EQ ( 3u, image.GetNumberOfComponentsPerPixel() );

  image = itk::simple::Image ( 64, 65, 66, itk::simple::sitkVectorUInt16 );
  EXPECT_EQ ( 3u, image.GetNumberOfComponentsPerPixel() );
  EXPECT_EQ ( 274560u, image.GetNumberOfPixels() );
}

TEST_F(Image,Hash) {
  itk::simple::HashImageFilter hasher;
  EXPECT_EQ ( "a998ea8b4999b4db9cbad033a52fe6d654211ff9", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( *shortImage ) ) << " SHA1 hash value";
  EXPECT_EQ ( "8cdd56962c5b3aabbfac56cd4dce1c7e", hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 ).Execute ( *shortImage ) ) << " MD5 hash value";

  EXPECT_EQ ( "3b6bfcb1922bf8b29b171062ad722c82f8aa3f50", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( *floatImage ) ) << " SHA1 hash value";
  EXPECT_EQ ( "e5eba8af943d7911220c9f2fb9b5b9c8", hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 ).Execute ( *floatImage ) ) << " MD5 hash value";
}

TEST_F(Image,Transforms) {

  // Origin is [1.1, 2.2, 3.3]
  // Spacing is [0.5, 0.5, 1.5]

  {
  // Index to Physical Point
  std::vector<int64_t> idx(3,1u);
  std::vector<double> pt = shortImage->TransformIndexToPhysicalPoint(idx);
  EXPECT_EQ(1.6, pt[0]) << " Pt to Idx [0]";
  EXPECT_EQ(2.7, pt[1]) << " Pt to Idx [1]";
  EXPECT_EQ(4.8, pt[2]) << " Pt to Idx [2]";


  // Physical Point to Index
  idx = shortImage->TransformPhysicalPointToIndex(pt);
  EXPECT_EQ(1u, idx[0]) << " Idx to Pt [0]";
  EXPECT_EQ(1u, idx[1]) << " Idx to Pt [1]";
  EXPECT_EQ(1u, idx[2]) << " Idx to Pt [2]";
  }

  {
  std::vector<double> idx(3,0.5);
  std::vector<double> pt = shortImage->TransformContinuousIndexToPhysicalPoint(idx);
  EXPECT_EQ(1.35, pt[0]) << " Pt to Idx [0]";
  EXPECT_EQ(2.45, pt[1]) << " Pt to Idx [1]";
  EXPECT_EQ(4.05, pt[2]) << " Pt to Idx [2]";

  idx = shortImage->TransformPhysicalPointToContinuousIndex(pt);
  EXPECT_EQ(.5, idx[0]) << " Idx to Pt [0]";
  EXPECT_EQ(.5, idx[1]) << " Idx to Pt [1]";
  EXPECT_EQ(.5, idx[2]) << " Idx to Pt [2]";
  }
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

  // Check Error conditions for setting Spacing and Origin
  newSpacing.clear();
  newSpacing.push_back( 99 );
  newSpacing.push_back( 99 );
  ASSERT_ANY_THROW( shortImage->SetSpacing( newSpacing ) ) << " setting with too short spacing";

  newOrigin.clear();
  newOrigin.push_back( -99.99 );
  ASSERT_ANY_THROW( shortImage->SetOrigin( newOrigin ) ) << "setting with too short origin";

  // GetDirection
  EXPECT_EQ ( shortImage->GetDirection(), directionI3D ) << " Checking Get Direction matrix for identity";


  // SetDirection
  std::vector<double> vdir( adir, adir+9);
  shortImage->SetDirection( vdir );
  for( unsigned int i = 0 ; i < 9; ++i )
    {
    EXPECT_EQ ( shortImage->GetDirection()[i], vdir[i] ) << " Checking Direction matrix at index " << i;
    }

  // Check Error Conditions for setting Directions
  ASSERT_ANY_THROW( shortImage->SetDirection( std::vector<double>( adir, adir + 4 ) ) );
  ASSERT_ANY_THROW( shortImage->SetDirection( std::vector<double>( adir, adir + 8 ) ) );
}

namespace sitk = itk::simple;


TEST_F(Image, CopyInformation)
{

  sitk::Image img1( 10, 20, sitk::sitkFloat32 );
  sitk::Image img3d( 10, 10, 10, sitk::sitkUInt32 );


  // number if dimension are different
  EXPECT_ANY_THROW( img1.CopyInformation( img3d ) );

  sitk::Image img2( 10, 10, sitk::sitkUInt16 );

  // image sizes don't match
  EXPECT_ANY_THROW( img1.CopyInformation( img2 ) );

  // fix the size to match

  img2 = sitk::Image( img1.GetSize(), sitk::sitkFloat64);
  img2.SetOrigin( shortImage->GetOrigin() );
  img2.SetSpacing( shortImage->GetSpacing() );

  EXPECT_NO_THROW( img1.CopyInformation( img2 ) );
  EXPECT_EQ( img1.GetSpacing(), img2.GetSpacing() );
  EXPECT_EQ( img1.GetOrigin(), img2.GetOrigin() );
  EXPECT_EQ( img1.GetDirection(), img2.GetDirection() );
  EXPECT_EQ( img1.GetNumberOfPixels(), img2.GetNumberOfPixels() );
}

TEST_F(Image, CopyOnWrite)
{
  // test that a just constructed image only have 1 referecne
  sitk::Image img( 10, 10, sitk::sitkInt16 );
  EXPECT_EQ(static_cast<const sitk::Image *>(&img)->GetITKBase()->GetReferenceCount(), 1 )
    << " Reference Count for just constructed Image";

  // use the image from the fixture to test some copy constructor
  EXPECT_EQ(static_cast<const sitk::Image *>(shortImage.get())->GetITKBase()->GetReferenceCount(), 2 )
    << " Reference Count for shared shortImage initial";
  sitk::Image img0 = *shortImage;
  EXPECT_EQ(static_cast<const sitk::Image *>(shortImage.get())->GetITKBase()->GetReferenceCount(), 3 )
    << " Reference Count for shared shortImage copy";
  sitk::Image imgCopy = img0;
  EXPECT_EQ(static_cast<const sitk::Image *>(shortImage.get())->GetITKBase()->GetReferenceCount(), 4 )
    << " Reference Count for shared shortImage second copy";

  // check set origin for copy on write
  imgCopy.SetOrigin( std::vector<double>( 3, 2.123 ) );
  EXPECT_EQ(static_cast<const sitk::Image *>(&imgCopy)->GetITKBase()->GetReferenceCount(), 1 )
    << " Reference Count for copy after set origin";
  EXPECT_EQ(static_cast<const sitk::Image *>(&img0)->GetITKBase()->GetReferenceCount(), 3 )
    << " Reference Count for shared after set origin";

  // check shallow copy on assignment
  imgCopy = img0;
  EXPECT_EQ(static_cast<const sitk::Image *>(&imgCopy)->GetITKBase()->GetReferenceCount(), 4 )
    << " Reference Count for copy after assigment";
  EXPECT_EQ(static_cast<const sitk::Image *>(&img0)->GetITKBase()->GetReferenceCount(), 4 )
    << " Reference Count for shared after assignment";

  // check copy on write with set spacing
  imgCopy.SetSpacing( std::vector<double>( 3, 3.45 ) );
  EXPECT_EQ(static_cast<const sitk::Image *>(&imgCopy)->GetITKBase()->GetReferenceCount(), 1 )
    << " Reference Count for copy after set spacing";
  EXPECT_EQ(static_cast<const sitk::Image *>(&img0)->GetITKBase()->GetReferenceCount(), 3 )
    << " Reference Count for shared after set spacing";
  EXPECT_EQ( sitk::Hash( imgCopy ), sitk::Hash( img0 ) ) << "Hash for shared and copy after set spacing";
}

TEST_F(Image,Operators)
{

  // the float image should begin as all zeros
  sitk::Image imgA = *floatImage;
  sitk::Image imgB = *floatImage;
  sitk::Image imgC = *floatImage;

  itk::Index<3> idx;
  idx.Fill( 0 );

  std::cout << "Testing Arithmetic operators" << std::endl;
  imgA += 1; // all 1s
  imgB = imgA;

  // 2 = 1 + 1
  imgC = imgA + imgB;

  // 1 = 2 - 1
  imgA = imgC - imgA;

  float v =  dynamic_cast<itk::Image<float,3>*>( imgA.GetITKBase() )->GetPixel( idx);
  EXPECT_EQ( v, 1 ) << "value check 1";

  // 4 = 2 * 2
  imgB = imgC * imgC;

  // 2 = 4 / 2
  imgA = imgB / imgC;

  // .4 = 4 * .1
  imgC = imgB * .1;

  // 20 = .4 * 50;
  imgA = imgC * 50;

  v =  dynamic_cast<itk::Image<float,3>*>( imgA.GetITKBase() )->GetPixel( idx);
  EXPECT_EQ( v, 20 ) << "value check 2";

  // original value should have never changed
  v =  dynamic_cast<itk::Image<float,3>*>( floatImage->GetITKBase() )->GetPixel( idx);
  EXPECT_EQ( v, 0 ) << "value check 3";

  // 0 = 20 + -20
  imgC = imgA + -20;

  // 10 = 6 + 4
  imgB = 6 + imgB;

  // 2 = 10 - 8
  imgA = imgB - 8;

  // .5 = 2 / 4
  imgC = imgA / 4;

  std::cout << "Testing Logical Operators" << std::endl;
  imgA = ~*shortImage;

  v =  dynamic_cast<itk::Image<short,3>*>( imgA.GetITKBase() )->GetPixel( idx);
  EXPECT_EQ( v, -101 );

  imgA = sitk::Image(10,10,10, sitk::sitkUInt8)+1;
  imgB = ~imgA; // <- 253

  v =  dynamic_cast<itk::Image<uint8_t,3>*>( imgB.GetITKBase() )->GetPixel( idx);
  EXPECT_EQ( 254, v );

  // 0 = 1 & 254
  imgC = imgA & imgB;

  // 254 = 254 | 0
  imgA = imgB | imgC;

  // 254 = 254 ^ 0
  imgB = imgA ^ imgC;

  // 0 = 254 ^ 254
  imgA = imgB ^ imgA;

  v =  dynamic_cast<itk::Image<uint8_t,3>*>( imgA.GetITKBase() )->GetPixel( idx);
  EXPECT_EQ( 0 ,v ) << "value check 4";
  v =  dynamic_cast<itk::Image<uint8_t,3>*>( imgB.GetITKBase() )->GetPixel( idx);
  EXPECT_EQ( v, 254 ) << "value check 5";

  std::cout << "Testing Compoung assignment operators" << std::endl;
  imgA = *floatImage;

  // 1.5 = 0 + 1.5
  imgA += 1.5;

  // 3.0 = 1.5 + 1.5
  imgA += imgA;

  // 0 = 1.5 - 1.5
  imgA -= imgA;

  // -8 = 0 - 8
  imgA -= 8;

  // 4 = 8 * .5
  imgA *= .5;

  // 16 = 4 * 4
  imgA *= imgA;

  // 8 = 16 / 2
  imgA /= 2;

  v =  dynamic_cast<itk::Image<float,3>*>( imgA.GetITKBase() )->GetPixel( idx);
  EXPECT_EQ( v, 8 ) << "value check 6";

  // 1 = 8 / 8
  imgA /= imgA;

  // 100 = ~~100
  imgA = ~~*shortImage;

  // 100 = 100  & 100
  imgA &= imgA;

  v =  dynamic_cast<itk::Image<short,3>*>( imgA.GetITKBase() )->GetPixel( idx);
  EXPECT_EQ( v, 100 ) << "value check 7";

  // 100 = 100 | 100
  imgA |= *shortImage;

  // 1 = 100 ^ 100
  imgA ^= *shortImage;


  v =  dynamic_cast<itk::Image<short,3>*>( imgA.GetITKBase() )->GetPixel( idx);
  EXPECT_EQ( 0, v ) << "value check 8";
}

TEST_F(Image,SetPixel)
{

  // this test is designed to run all SetPixel methods

  sitk::Image img = sitk::Image( 10, 10, sitk::sitkFloat64 );


  ASSERT_NO_THROW( img.SetPixelAsDouble( std::vector<uint32_t>( 2, 0 ), 99.0 ) ) << " correct setting";
  EXPECT_EQ( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ), 99.0 ) << "Set value check";
  ASSERT_NO_THROW( img.SetPixelAsDouble( std::vector<uint32_t>( 3, 0 ), 99.0 ) ) << " correct setting, with extra size index";
  EXPECT_EQ( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ), 99.0 ) << "Set value check";
  ASSERT_ANY_THROW( img.SetPixelAsDouble( std::vector<uint32_t>( 1, 0 ), 99.0 ) ) << " too short index";

  ASSERT_ANY_THROW( img.SetPixelAsInt8( std::vector<uint32_t>( 2, 0 ), 99 ) ) <<  " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ), 99u ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsInt16( std::vector<uint32_t>( 2, 0 ), 99 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ), 99u ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsInt32( std::vector<uint32_t>( 2, 0 ), 99 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ), 99u ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsInt64( std::vector<uint32_t>( 2, 0 ), 99 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsUInt64( std::vector<uint32_t>( 2, 0 ), 99u ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsFloat( std::vector<uint32_t>( 2, 0 ), 99.0 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ), std::vector<int8_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ), std::vector<uint8_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ), std::vector<int16_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ), std::vector<uint16_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ), std::vector<int32_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ), std::vector<uint32_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ), std::vector<int64_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ), std::vector<uint64_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ), std::vector<float>(3,99.0) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ), std::vector<double>(3,99.0) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ), std::complex<float>(99.0,1.0) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ), std::complex<float>(99, -1.0) ) ) << " Get with wrong type";


  img = sitk::Image( 10, 10, sitk::sitkVectorFloat64 );

  ASSERT_NO_THROW( img.SetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ), std::vector<double>(2,99.0 ) ) ) << " correct setting";
  EXPECT_EQ( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ), std::vector<double>(2,99.0 )) << "Set value check";
  ASSERT_ANY_THROW( img.SetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ), std::vector<double>(3,99.0 ) ) ) << " too long length";
  ASSERT_ANY_THROW( img.SetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ), std::vector<double>(1,99.0 ) ) ) << " too short length";
  ASSERT_NO_THROW( img.SetPixelAsVectorFloat64( std::vector<uint32_t>( 3, 0 ), std::vector<double>(2,98.0 ) ) ) << " correct setting, long idx ";
  EXPECT_EQ( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ), std::vector<double>(2,98.0 )) << "Set value check";
  ASSERT_ANY_THROW( img.SetPixelAsVectorFloat64( std::vector<uint32_t>( 1, 0 ), std::vector<double>(2,98.0 ) ) ) << " too short idx ";

  ASSERT_ANY_THROW( img.SetPixelAsInt8( std::vector<uint32_t>( 2, 0 ), 99 ) ) <<  " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ), 99u ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsInt16( std::vector<uint32_t>( 2, 0 ), 99 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ), 99u ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsInt32( std::vector<uint32_t>( 2, 0 ), 99 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ), 99u ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsInt64( std::vector<uint32_t>( 2, 0 ), 99 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsUInt64( std::vector<uint32_t>( 2, 0 ), 99u ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsFloat( std::vector<uint32_t>( 2, 0 ), 99.0 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsDouble( std::vector<uint32_t>( 2, 0 ), 99.0 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ), std::vector<int8_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ), std::vector<uint8_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ), std::vector<int16_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ), std::vector<uint16_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ), std::vector<int32_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ), std::vector<uint32_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ), std::vector<int64_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ), std::vector<uint64_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ), std::vector<float>(3,99.0) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ), std::vector<double>(3,99.0) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ), std::complex<float>(99.0,1.0) ) ) << " Get with wrong type";


  img = sitk::Image( 10, 10, sitk::sitkLabelUInt8 );

  try
    {
    img.SetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ), 99u );
    }
  catch( std::exception &e)
    {
    std::cerr << e.what() << std::endl;
    }
  EXPECT_EQ( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ), 99.0 ) << "Set value check";
  ASSERT_NO_THROW( img.SetPixelAsUInt8( std::vector<uint32_t>( 3, 0 ), 99u ) ) << " correct setting, with extra size index";
  EXPECT_EQ( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ), 99.0 ) << "Set value check";
  ASSERT_ANY_THROW( img.SetPixelAsUInt8( std::vector<uint32_t>( 1, 0 ), 99u ) ) << " too short index";

  std::cout << "check\n";
  ASSERT_ANY_THROW( img.SetPixelAsInt8( std::vector<uint32_t>( 2, 0 ), 99 ) ) <<  " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsInt16( std::vector<uint32_t>( 2, 0 ), 99 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ), 99u ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsInt32( std::vector<uint32_t>( 2, 0 ), 99 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ), 99u ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsInt64( std::vector<uint32_t>( 2, 0 ), 99 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsUInt64( std::vector<uint32_t>( 2, 0 ), 99u ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsFloat( std::vector<uint32_t>( 2, 0 ), 99.0 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsDouble( std::vector<uint32_t>( 2, 0 ), 99.0 ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ), std::vector<int8_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ), std::vector<uint8_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ), std::vector<int16_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ), std::vector<uint16_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ), std::vector<int32_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ), std::vector<uint32_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ), std::vector<int64_t>(3,99) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ), std::vector<uint64_t>(3,99u) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ), std::vector<float>(3,99.0) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ), std::vector<double>(3,99.0) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ), std::complex<float>(99.0,1.0) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.SetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ), std::complex<float>(99, -1.0) ) ) << " Get with wrong type";


  img = sitk::Image( 10, 10, sitk::sitkFloat64 );

  // Check that out of bounds throw
  uint32_t xOOB[] = {10,0,0};
  uint32_t yOOB[] = {0,10,0};
  uint32_t zOOB[] = {0,0,10};
  ASSERT_THROW( img.SetPixelAsDouble(  std::vector<uint32_t>( xOOB, xOOB+3 ), 0.0 ), itk::simple::GenericException ) << "x out of bounds";
  ASSERT_THROW( img.SetPixelAsDouble(  std::vector<uint32_t>( yOOB, yOOB+3 ), 0.0 ), itk::simple::GenericException ) << "y out of bounds";
  ASSERT_NO_THROW( img.SetPixelAsDouble(  std::vector<uint32_t>( zOOB, zOOB+3 ), 0.0 ) ) << "z out of bounds, expect truncation of z-dim";

}


TEST_F(Image,GetPixel)
{

  // this test is designed to run all GetPixel methods for scalar types

  sitk::Image img = sitk::Image( 10, 10, sitk::sitkInt8 );
  EXPECT_EQ( img.GetPixelAsInt8( std::vector<uint32_t>( 2, 0 ) ), 0 ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsInt8( std::vector<uint32_t>( 3, 0 ) ), 0 ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsInt8( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkUInt8 );
  EXPECT_EQ( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ), 0 ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsUInt8( std::vector<uint32_t>( 3, 0 ) ), 0 ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, 10, sitk::sitkUInt8 );
  EXPECT_EQ( img.GetPixelAsUInt8( std::vector<uint32_t>( 3, 0 ) ), 0 ) << " Get 3D with 3D ";
  EXPECT_EQ( img.GetPixelAsUInt8( std::vector<uint32_t>( 4, 0 ) ), 0 ) << " Get 3D with 4D ";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";


  img = sitk::Image( 10, 10, sitk::sitkInt16 );
  EXPECT_EQ( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ), 0 ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsInt16( std::vector<uint32_t>( 3, 0 ) ), 0 ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkUInt16 );
  EXPECT_EQ( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ), 0 ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsUInt16( std::vector<uint32_t>( 3, 0 ) ), 0 ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkInt32 );
  EXPECT_EQ( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ), 0 ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsInt32( std::vector<uint32_t>( 3, 0 ) ), 0 ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkUInt32 );
  EXPECT_EQ( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ), 0u ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsUInt32( std::vector<uint32_t>( 3, 0 ) ), 0u ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  if ( sitk::sitkInt64 != sitk::sitkUnknown )
    {
    img = sitk::Image( 10, 10, sitk::sitkInt64 );
    EXPECT_EQ( img.GetPixelAsInt64( std::vector<uint32_t>( 2, 0 ) ), 0 ) << " Get 2D with 2D ";
    EXPECT_EQ( img.GetPixelAsInt64( std::vector<uint32_t>( 3, 0 ) ), 0 ) << " Get 2D with 3D ";
    ASSERT_ANY_THROW( img.GetPixelAsInt64( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
    ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    }

 if ( sitk::sitkUInt64 != sitk::sitkUnknown )
    {
    img = sitk::Image( 10, 10, sitk::sitkUInt64 );
    EXPECT_EQ( img.GetPixelAsUInt64( std::vector<uint32_t>( 2, 0 ) ), 0u ) << " Get 2D with 2D ";
    EXPECT_EQ( img.GetPixelAsUInt64( std::vector<uint32_t>( 3, 0 ) ), 0u ) << " Get 2D with 3D ";
    ASSERT_ANY_THROW( img.GetPixelAsUInt64( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
    ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    }

  img = sitk::Image( 10, 10, sitk::sitkFloat32 );
  EXPECT_EQ( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ), 0u ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsFloat( std::vector<uint32_t>( 3, 0 ) ), 0u ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkFloat64 );
  EXPECT_EQ( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ), 0 ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsDouble( std::vector<uint32_t>( 3, 0 ) ), 0 ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkComplexFloat32 );
  EXPECT_EQ( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ), std::complex<float>(0.0) ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 3, 0 ) ), std::complex<float>(0.0) ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkComplexFloat64 );
  EXPECT_EQ( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ), std::complex<double>(0.0) ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 3, 0 ) ), std::complex<double>(0.0) ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";



  img = sitk::Image( 10, 10, sitk::sitkFloat64 );

  // Check that out of bounds throw
  uint32_t xOOB[] = {10,0,0};
  uint32_t yOOB[] = {0,10,0};
  uint32_t zOOB[] = {0,0,10};
  ASSERT_THROW( img.GetPixelAsDouble(  std::vector<uint32_t>( xOOB, xOOB+3 ) ), itk::simple::GenericException ) << "x out of bounds";
  ASSERT_THROW( img.GetPixelAsDouble(  std::vector<uint32_t>( yOOB, yOOB+3 ) ), itk::simple::GenericException ) << "y out of bounds";
  ASSERT_NO_THROW( img.GetPixelAsDouble(  std::vector<uint32_t>( zOOB, zOOB+3 ) ) ) << "z out of bounds, expect truncation of z-dim";

}



TEST_F(Image,GetPixelVector)
{

  std::vector<unsigned char> zero(2,0);


  // this test is designed to run all GetPixel methods for Vector types

  sitk::Image img = sitk::Image( 10, 10, sitk::sitkVectorInt8 );
  EXPECT_EQ( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ), std::vector<int8_t>(zero.begin(),zero.end()) ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 3, 0 ) ), std::vector<int8_t>(zero.begin(),zero.end()) ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkVectorUInt8 );
  EXPECT_EQ( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ), std::vector<uint8_t>(zero.begin(),zero.end()) ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 3, 0 ) ), std::vector<uint8_t>(zero.begin(),zero.end()) ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, 10, sitk::sitkVectorUInt8 );
  EXPECT_EQ( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 3, 0 ) ), std::vector<uint8_t>(3,0) ) << " Get 3D with 3D ";
  EXPECT_EQ( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 4, 0 ) ), std::vector<uint8_t>(3,0) ) << " Get 3D with 4D ";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 3, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";


  img = sitk::Image( 10, 10, sitk::sitkVectorInt16 );
  EXPECT_EQ( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ), std::vector<int16_t>(zero.begin(),zero.end())  ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 3, 0 ) ), std::vector<int16_t>(zero.begin(),zero.end())  ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkVectorUInt16 );
  EXPECT_EQ( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ), std::vector<uint16_t>(zero.begin(),zero.end()) ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 3, 0 ) ), std::vector<uint16_t>(zero.begin(),zero.end()) ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkVectorInt32 );
  EXPECT_EQ( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ), std::vector<int32_t>(zero.begin(),zero.end()) ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 3, 0 ) ), std::vector<int32_t>(zero.begin(),zero.end()) ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkVectorUInt32 );
  EXPECT_EQ( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ), std::vector<uint32_t>(zero.begin(),zero.end()) ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 3, 0 ) ), std::vector<uint32_t>(zero.begin(),zero.end()) ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  if ( sitk::sitkVectorInt64 != sitk::sitkUnknown )
    {
    img = sitk::Image( 10, 10, sitk::sitkVectorInt64 );
    EXPECT_EQ( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ), std::vector<int64_t>(zero.begin(),zero.end()) ) << " Get 2D with 2D ";
    EXPECT_EQ( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 3, 0 ) ), std::vector<int64_t>(zero.begin(),zero.end()) ) << " Get 2D with 3D ";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
    ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    }

  if ( sitk::sitkVectorUInt64 != sitk::sitkUnknown )
    {
    img = sitk::Image( 10, 10, sitk::sitkVectorUInt64 );
    EXPECT_EQ( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ), std::vector<uint64_t>(zero.begin(),zero.end()) ) << " Get 2D with 2D ";
    EXPECT_EQ( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 3, 0 ) ), std::vector<uint64_t>(zero.begin(),zero.end()) ) << " Get 2D with 3D ";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
    ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    }

  img = sitk::Image( 10, 10, sitk::sitkVectorFloat32 );
  EXPECT_EQ( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ), std::vector<float>(zero.begin(),zero.end()) ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 3, 0 ) ), std::vector<float>(zero.begin(),zero.end()) ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsDouble( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
    ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkVectorFloat64 );
  EXPECT_EQ( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 2, 0 ) ), std::vector<double>(zero.begin(),zero.end()) ) << " Get 2D with 2D ";
  EXPECT_EQ( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 3, 0 ) ), std::vector<double>(zero.begin(),zero.end()) ) << " Get 2D with 3D ";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat64( std::vector<uint32_t>( 1, 0 ) ) ) << " Get with idx too small";
  ASSERT_ANY_THROW( img.GetPixelAsUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsFloat( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt8( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt16( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorUInt64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsVectorFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat32( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetPixelAsComplexFloat64( std::vector<uint32_t>( 2, 0 ) ) ) << " Get with wrong type";


  // Check that out of bounds throw
  uint32_t xOOB[] = {10,0,0};
  uint32_t yOOB[] = {0,10,0};
  uint32_t zOOB[] = {0,0,10};
  ASSERT_THROW( img.GetPixelAsVectorFloat64(  std::vector<uint32_t>( xOOB, xOOB+3 ) ), itk::simple::GenericException ) << "x out of bounds";
  ASSERT_THROW( img.GetPixelAsVectorFloat64(  std::vector<uint32_t>( yOOB, yOOB+3 ) ), itk::simple::GenericException ) << "y out of bounds";
  ASSERT_NO_THROW( img.GetPixelAsVectorFloat64(  std::vector<uint32_t>( zOOB, zOOB+3 ) ) ) << "z out of bounds, expect truncation of z-dim";

}

TEST_F(Image, GetBuffer)
{

  // this test is designed to run all GetBuffer methods
  sitk::Image img = sitk::Image( 10, 10, sitk::sitkUInt8 );
  EXPECT_EQ( img.GetBufferAsUInt8()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt64() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt64() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkInt8 );
  EXPECT_EQ( img.GetBufferAsInt8()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt64() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt64() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, 10, sitk::sitkUInt8 );
  EXPECT_EQ( img.GetBufferAsUInt8()[99], 0 ) << " Get 3D with 3D ";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";


  img = sitk::Image( 10, 10, sitk::sitkInt16 );
  EXPECT_EQ( img.GetBufferAsInt16()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkUInt16 );
  EXPECT_EQ( img.GetBufferAsUInt16()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkInt32 );
  EXPECT_EQ( img.GetBufferAsInt32()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkUInt32 );
  EXPECT_EQ( img.GetBufferAsUInt32()[99], 0u ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";


  // currently Int64 pixel types are instantiated yet,
  // so an exception will be thrown.
  try
    {
    img = sitk::Image( 10, 10, sitk::sitkUInt64 );
    EXPECT_EQ( img.GetBufferAsUInt64()[99], 0u ) << " Get last element in buffer ";

    img = sitk::Image( 10, 10, sitk::sitkInt64 );
    EXPECT_EQ( img.GetBufferAsInt64()[99], 0u ) << " Get last element in buffer ";
    }
  catch ( std::exception &e)
    {
    std::cout << "Exception: " << e.what() << std::endl;
    }

  img = sitk::Image( 10, 10, sitk::sitkFloat32 );
  EXPECT_EQ( img.GetBufferAsFloat()[99], 0u ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkFloat64 );
  EXPECT_EQ( img.GetBufferAsDouble()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";

}


TEST_F(Image, GetBufferVector)
{

  // this test is designed to run all GetBuffer methods for vector images
  sitk::Image img = sitk::Image( 10, 10, sitk::sitkVectorUInt8 );

  EXPECT_EQ( img.GetBufferAsUInt8()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt64() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt64() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkVectorInt8 );
  EXPECT_EQ( img.GetBufferAsInt8()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt64() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt64() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, 10, sitk::sitkVectorUInt8 );
  EXPECT_EQ( img.GetBufferAsUInt8()[99], 0 ) << " Get 3D with 3D ";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";


  img = sitk::Image( 10, 10, sitk::sitkVectorInt16 );
  EXPECT_EQ( img.GetBufferAsInt16()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkVectorUInt16 );
  EXPECT_EQ( img.GetBufferAsUInt16()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkVectorInt32 );
  EXPECT_EQ( img.GetBufferAsInt32()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkVectorUInt32 );
  EXPECT_EQ( img.GetBufferAsUInt32()[99], 0u ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";


  // currently Int64 pixel types are instantiated yet,
  // so an exception will be thrown.
  try
    {
    img = sitk::Image( 10, 10, sitk::sitkVectorUInt64 );
    EXPECT_EQ( img.GetBufferAsUInt64()[99], 0u ) << " Get last element in buffer ";

    img = sitk::Image( 10, 10, sitk::sitkVectorInt64 );
    EXPECT_EQ( img.GetBufferAsInt64()[99], 0u ) << " Get last element in buffer ";
    }
  catch ( std::exception &e)
    {
    std::cout << "Exception: " << e.what() << std::endl;
    }

  img = sitk::Image( 10, 10, sitk::sitkVectorFloat32 );
  EXPECT_EQ( img.GetBufferAsFloat()[99], 0u ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsDouble() ) << " Get with wrong type";

  img = sitk::Image( 10, 10, sitk::sitkVectorFloat64 );
  EXPECT_EQ( img.GetBufferAsDouble()[99], 0 ) << " Get last element in buffer ";
  ASSERT_ANY_THROW( img.GetBufferAsUInt8() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt16() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsUInt32() ) << " Get with wrong type";
  ASSERT_ANY_THROW( img.GetBufferAsFloat() ) << " Get with wrong type";

}

TEST_F(Image,MetaDataDictionary)
{
  sitk::Image img = sitk::Image( 10,10, 10, sitk::sitkFloat32 );


  EXPECT_EQ( 0u, img.GetMetaDataKeys().size() );
  EXPECT_FALSE( img.HasMetaDataKey("nothing") );
  EXPECT_ANY_THROW( img.GetMetaData("anything") );

  {
  itk::DataObject::Pointer dataObject = img.GetITKBase();

  itk::MetaDataDictionary &mdd = dataObject->GetMetaDataDictionary();

  itk::EncapsulateMetaData<float>(mdd,"Float",static_cast<float>(1.234560F));
  itk::EncapsulateMetaData<std::string>(mdd,"String",std::string("std::string"));
  }

  EXPECT_EQ( 2u, img.GetMetaDataKeys().size() );
  EXPECT_FALSE( img.HasMetaDataKey("nothing") );
  EXPECT_TRUE( img.HasMetaDataKey("Float") );
  EXPECT_TRUE( img.HasMetaDataKey("String") );

  EXPECT_EQ( "std::string", img.GetMetaData("String") );

  std::vector<std::string> keys = img.GetMetaDataKeys();
  for ( size_t i = 0; i < keys.size(); ++i )
    {
    std::string value;

    EXPECT_NO_THROW( value = img.GetMetaData( keys[i]) );
    std::cout << "Key = \"" << keys[i] << "\" Value = \"" << value << "\"" << std::endl;
    }

  img = sitk::Image( 10,10, 10, sitk::sitkFloat32 );
  img.SetMetaData( "k1", "somevalue");

  EXPECT_EQ( 1u, img.GetMetaDataKeys().size() );
  EXPECT_TRUE( img.HasMetaDataKey("k1") );
  EXPECT_EQ( "somevalue", img.GetMetaData("k1") );

  EXPECT_FALSE( img.EraseMetaData("wrong") );
  EXPECT_EQ( 1u, img.GetMetaDataKeys().size() );
  EXPECT_TRUE( img.HasMetaDataKey("k1") );

  EXPECT_TRUE( img.EraseMetaData("k1") );
  EXPECT_FALSE( img.HasMetaDataKey("k1") );
  EXPECT_EQ( 0u, img.GetMetaDataKeys().size() );

  EXPECT_FALSE( img.EraseMetaData("k1") );

}


TEST_F(Image,Mandelbrot)
{
  unsigned int xs = 35*100;
  unsigned int ys = 20*100;

  sitk::Image real = sitk::Image( xs, ys, sitk::sitkFloat32 );
  sitk::Image imagine = sitk::Image( xs, ys, sitk::sitkFloat32 );

  for (unsigned int i = 0; i < xs; ++i )
    {
    for ( unsigned int j = 0; j < ys; ++j )
      {
      std::vector<unsigned int> idx(2);
      idx[0] = i;
      idx[1] = j;

      real.SetPixelAsFloat( idx, -2.5 + ( double(i)/xs ) * 3.5 );
      imagine.SetPixelAsFloat( idx, -1 + ( double(j)/ys ) * 2 );
      }
    }

  sitk::Image C = sitk::RealAndImaginaryToComplex( real, imagine );
  std::cout << "Generated C" << std::endl;

  // initial image filled with 0s
  sitk::Image img( xs, ys, sitk::sitkComplexFloat32 );

  for ( unsigned int i = 0; i < 25; ++i )
    {
    img *= img;
    img += C;
    }

  sitk::Image R = sitk::ComplexToReal( img );
  sitk::Image I = sitk::ComplexToImaginary( img );
  img = R*R + I*I;

  sitk::WriteImage( img, "mandelbrot.nrrd" );
}
