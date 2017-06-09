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

#include "sitkJoinSeriesImageFilter.h"
#include "sitkExtractImageFilter.h"

#include <itkIntTypes.h>

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkMetaDataObject.h"

namespace nsstd = itk::simple::nsstd;

const double adir[] = { 0.0,  0.0,  0.0, 1.0,
                       -1.0,  0.0,  0.0, 0.0,
                        0.0, -1.0,  0.0, 0.0,
                        0.0,  0.0, -1.0, 0.0 };

using  itk::simple::InstantiatedPixelIDTypeList;

class Image4D : public ::testing::Test {
public:
  typedef nsstd::auto_ptr<itk::simple::Image> sitkAutoImagePointer;

  virtual void SetUp() {
    itk::ImageBase<4>::IndexType index;
    itk::ImageBase<4>::SizeType size;
    itk::ImageBase<4>::RegionType region;
    itk::ImageBase<4>::PointType origin;
    itk::ImageBase<4>::SpacingType spacing;

    // Create an image
    for ( int i = 0; i < 4; i++ )
    {
      index[i] = 0;
      size[i] = 64+i;
    }

    origin[0] = 0.0;
    origin[1] = 1.1;
    origin[2] = 2.2;
    origin[3] = 3.3;

    spacing[0] = 10.0;
    spacing[1] = 11.0;
    spacing[2] = 12.0;
    spacing[3] = 13.0;

    region.SetSize( size );
    region.SetIndex( index );
    itk::Image<short,4>::Pointer im = itk::Image<short,4>::New();
    im->SetRegions( region );
    im->SetOrigin( origin );
    im->SetSpacing( spacing );
    im->Allocate();
    im->FillBuffer( 100 );
    itkShortImage = im;
    shortImage = sitkAutoImagePointer( new itk::simple::Image( im.GetPointer() ) );

    itk::Image<float,4>::Pointer fim = itk::Image<float,4>::New();
    fim->SetRegions( region );
    fim->SetOrigin( origin );
    fim->SetSpacing( spacing );
    fim->Allocate();
    fim->FillBuffer( 0 );
    itkFloatImage = fim;
    floatImage = sitkAutoImagePointer( new itk::simple::Image( fim.GetPointer() ) );

    itkFloatVectorImage = FloatVectorImageType::New();
    floatVectorImage = sitkAutoImagePointer( new itk::simple::Image( itkFloatVectorImage.GetPointer() ) );

    directionI4D = std::vector<double>(16, 0.0 );
    directionI4D[0] = directionI4D[5] = directionI4D[10] = directionI4D[15] = 1.0;

  }

  itk::ImageBase< 4 >::Pointer itkShortImage;

  typedef itk::Image< short, 4 > ShortImageType;
  sitkAutoImagePointer shortImage;

  typedef itk::Image< float, 4 > FloatImageType;
  sitkAutoImagePointer floatImage;
  FloatImageType::Pointer itkFloatImage;

  typedef itk::VectorImage<float, 4 > FloatVectorImageType;
  sitkAutoImagePointer floatVectorImage;
  FloatVectorImageType::Pointer itkFloatVectorImage;

  sitkAutoImagePointer differentSizedImage;
  ShortImageType::Pointer itkDifferentSizedImage;

  std::vector<double> directionI4D;

};

TEST_F(Image4D,Create) {
  ASSERT_TRUE ( shortImage->GetITKBase() != NULL );
  EXPECT_EQ ( shortImage->GetWidth(), itkShortImage->GetLargestPossibleRegion().GetSize()[0] ) << " Checking image width";
  EXPECT_EQ ( shortImage->GetHeight(), itkShortImage->GetLargestPossibleRegion().GetSize()[1] ) << " Checking image height";
  EXPECT_EQ ( shortImage->GetDepth(), itkShortImage->GetLargestPossibleRegion().GetSize()[2] ) << " Checking image depth";
  EXPECT_EQ ( shortImage->GetSize()[3], itkShortImage->GetLargestPossibleRegion().GetSize()[3] ) << " Checking dim4";

}

TEST_F(Image4D,ImageDataType) {

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



  result = itk::simple::PixelIDToPixelIDValue< itk::simple::BasicPixelID<short> >::Result;
  EXPECT_EQ( shortImage->GetPixelIDValue(), result);
  EXPECT_EQ( shortImage->GetPixelID(), result);

  result = itk::simple::PixelIDToPixelIDValue< itk::simple::BasicPixelID<float> >::Result;
  EXPECT_EQ( floatImage->GetPixelIDValue(), result );
  EXPECT_EQ( floatImage->GetPixelID(), result );

  result = itk::simple::PixelIDToPixelIDValue< itk::simple::VectorPixelID<float> >::Result;
  EXPECT_EQ( floatVectorImage->GetPixelIDValue(), result );
  EXPECT_EQ( floatVectorImage->GetPixelID(), result );



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

TEST_F(Image4D,Constructors) {
  itk::simple::HashImageFilter hasher;
  int result;

  {
  itk::simple::Image image;
  EXPECT_EQ ( 0u, image.GetWidth() );
  EXPECT_EQ ( 0u, image.GetHeight() );
  EXPECT_EQ ( 0u, image.GetDepth() );
  EXPECT_EQ ( 2u, image.GetSize().size() );
  }

  std::vector<unsigned int> s4d6(4);
  s4d6[0] = 64;
  s4d6[1] = 65;
  s4d6[2] = 66;
  s4d6[3] = 67;
  itk::simple::Image image ( s4d6, itk::simple::sitkUInt8 );
  EXPECT_EQ ( "d2ed3a9bceae811402dcb5223fb16990cd89537d", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( image ) ) << " SHA1 hash value sitkUInt8";
  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<unsigned char> >::Result;
  EXPECT_EQ ( image.GetPixelIDValue(), result );
  EXPECT_EQ ( image.GetPixelIDTypeAsString(), "8-bit unsigned integer" );
  EXPECT_EQ ( image.GetDimension(), 4u );
  EXPECT_EQ ( 64u, image.GetWidth() );
  EXPECT_EQ ( 65u, image.GetHeight() );
  EXPECT_EQ ( 66u, image.GetDepth() );
  EXPECT_EQ ( 67u, image.GetSize()[3]  );
  EXPECT_EQ( image.GetDirection(), directionI4D );

  image = itk::simple::Image ( s4d6, itk::simple::sitkInt16 );
  EXPECT_EQ ( "0e444ec26123b59643b58f84dd8f685a991dfb4b", hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).Execute ( image ) ) << " SHA1 hash value sitkUInt16";
  result = typelist::IndexOf< InstantiatedPixelIDTypeList, itk::simple::BasicPixelID<short> >::Result;
  EXPECT_EQ ( image.GetPixelIDValue(), result );
  EXPECT_EQ ( image.GetPixelIDTypeAsString(), "16-bit signed integer" );
  EXPECT_EQ ( image.GetDimension(), 4u );
  EXPECT_EQ ( 64u, image.GetWidth() );
  EXPECT_EQ ( 65u, image.GetHeight() );
  EXPECT_EQ ( 66u, image.GetDepth() );
  EXPECT_EQ ( 67u, image.GetSize()[3] );
  EXPECT_EQ( image.GetDirection(), directionI4D );

  // Test the constructors for vector images
  std::vector<unsigned int>  s4d(4, 5);

  image = itk::simple::Image( s4d, itk::simple::sitkVectorUInt8 );
  EXPECT_EQ ( image.GetDimension(), 4u );
  EXPECT_EQ ( 4u, image.GetNumberOfComponentsPerPixel() );

  image = itk::simple::Image( s4d, itk::simple::sitkVectorFloat32 );
  EXPECT_EQ ( image.GetDimension(), 4u );
  EXPECT_EQ ( 4u, image.GetNumberOfComponentsPerPixel() );

  image = itk::simple::Image( s4d, itk::simple::sitkVectorInt16, 5 );
  EXPECT_EQ ( image.GetDimension(), 4u );
  EXPECT_EQ ( 5u, image.GetNumberOfComponentsPerPixel() );

  image = itk::simple::Image( s4d, itk::simple::sitkVectorFloat64, 10 );
  EXPECT_EQ ( image.GetDimension(), 4u );
  EXPECT_EQ ( 10u, image.GetNumberOfComponentsPerPixel() );

  // check for error when incorrect number of dimensions are requested
  std::vector<unsigned int> s5d(5, 100);
  ASSERT_ANY_THROW( itk::simple::Image( s5d, itk::simple::sitkVectorFloat64 ) );

  // check for error with bad pixelID
  ASSERT_ANY_THROW( itk::simple::Image( s4d, itk::simple::sitkUnknown ) );
  ASSERT_ANY_THROW( itk::simple::Image( s4d, itk::simple::PixelIDValueEnum(-100) ) );

  // check for error when non-vector type requests components ( should
  // this be an error or should we just be converted to a vector )
  ASSERT_ANY_THROW( itk::simple::Image( s4d, itk::simple::sitkInt16, 10 ) );
  ASSERT_ANY_THROW( itk::simple::Image( s4d, itk::simple::sitkLabelUInt8, 10 ) );

  // currently we don't have a good interface to check the values of
  // these images, let just construct these types need todo better
  // testing!

  image = itk::simple::Image ( s4d6, itk::simple::sitkLabelUInt8 );
  EXPECT_EQ ( 64u, image.GetWidth() );
  EXPECT_EQ ( 65u, image.GetHeight() );
  EXPECT_EQ ( 66u, image.GetDepth() );
  EXPECT_EQ ( 67u, image.GetSize()[3] );
  EXPECT_EQ ( 1u, image.GetNumberOfComponentsPerPixel() );
  EXPECT_EQ( image.GetDirection(), directionI4D );

  image = itk::simple::Image ( s4d6, itk::simple::sitkLabelUInt16 );

  image = itk::simple::Image ( s4d6, itk::simple::sitkLabelUInt32 );

  image = itk::simple::Image ( s4d6, itk::simple::sitkVectorUInt8 );

  EXPECT_EQ ( 64u, image.GetWidth() );
  EXPECT_EQ ( 65u, image.GetHeight() );
  EXPECT_EQ ( 66u, image.GetDepth() );
  EXPECT_EQ ( 67u, image.GetSize()[3] );
  EXPECT_EQ ( 4u, image.GetNumberOfComponentsPerPixel() );

  image = itk::simple::Image ( s4d6, itk::simple::sitkVectorUInt16 );
  EXPECT_EQ ( 4u, image.GetNumberOfComponentsPerPixel() );

}

TEST_F(Image4D,Transforms) {

  // Origin is [0.0, 1.1, 2.2, 3.3]
  // Spacing is [10, 11, 12, 13]

  {
    // Index to Physical Point
    std::vector<int64_t> idx(4,1u);
    std::vector<double> pt = shortImage->TransformIndexToPhysicalPoint(idx);
    EXPECT_EQ(10.0, pt[0]) << " Pt to Idx [0]";
    EXPECT_EQ(12.1, pt[1]) << " Pt to Idx [1]";
    EXPECT_EQ(14.2, pt[2]) << " Pt to Idx [2]";
    EXPECT_EQ(16.3, pt[3]) << " Pt to Idx [3]";


    // Physical Point to Index
    idx = shortImage->TransformPhysicalPointToIndex(pt);
    EXPECT_EQ(1u, idx[0]) << " Idx to Pt [0]";
    EXPECT_EQ(1u, idx[1]) << " Idx to Pt [1]";
    EXPECT_EQ(1u, idx[2]) << " Idx to Pt [2]";
    EXPECT_EQ(1u, idx[3]) << " Idx to Pt [3]";
  }

  {
    // Continuous Index to Physical Point
    std::vector<double> idx(4,2.0);
    std::vector<double> pt = shortImage->TransformContinuousIndexToPhysicalPoint(idx);
    EXPECT_EQ(20.0, pt[0]) << " Pt to Idx [0]";
    EXPECT_EQ(23.1, pt[1]) << " Pt to Idx [1]";
    EXPECT_EQ(26.2, pt[2]) << " Pt to Idx [2]";
    EXPECT_EQ(29.3, pt[3]) << " Pt to Idx [3]";

    // Physical Point to Coninuous Index
    idx = shortImage->TransformPhysicalPointToContinuousIndex(pt);
    EXPECT_EQ(2.0, idx[0]) << " Idx to Pt [0]";
    EXPECT_EQ(2.0, idx[1]) << " Idx to Pt [1]";
    EXPECT_EQ(2.0, idx[2]) << " Idx to Pt [2]";
    EXPECT_EQ(2.0, idx[3]) << " Idx to Pt [3]";
  }
}

TEST_F(Image4D,Properties) {

  // GetOrigin
  std::vector<double> origin = shortImage->GetOrigin();
  EXPECT_EQ(origin[0], 0.0) << " GetOrigin[0]";
  EXPECT_EQ(origin[1], 1.1) << " GetOrigin[1]";
  EXPECT_EQ(origin[2], 2.2) << " GetOrigin[2]";
  EXPECT_EQ(origin[3], 3.3) << " GetOrigin[4]";

  // SetOrigin
  std::vector<double> newOrigin;
  newOrigin.push_back(0.1);
  newOrigin.push_back(0.2);
  newOrigin.push_back(0.3);
  newOrigin.push_back(0.4);
  shortImage->SetOrigin( newOrigin );
  EXPECT_EQ(shortImage->GetOrigin()[0], 0.1) << " SetOrigin[0]";
  EXPECT_EQ(shortImage->GetOrigin()[1], 0.2) << " SetOrigin[1]";
  EXPECT_EQ(shortImage->GetOrigin()[2], 0.3) << " SetOrigin[2]";
  EXPECT_EQ(shortImage->GetOrigin()[3], 0.4) << " SetOrigin[3]";
  shortImage->SetOrigin( origin );

  // GetSpacing
  std::vector<double> spacing = shortImage->GetSpacing();
  EXPECT_EQ(spacing[0], 10.0) << " GetSpacing[0]";
  EXPECT_EQ(spacing[1], 11.0) << " GetSpacing[1]";
  EXPECT_EQ(spacing[2], 12.0) << " GetSpacing[2]";
  EXPECT_EQ(spacing[3], 13.0) << " GetSpacing[3]";

  // SetSpacing
  std::vector<double> newSpacing;
  newSpacing.push_back(1.9);
  newSpacing.push_back(2.8);
  newSpacing.push_back(3.7);
  newSpacing.push_back(4.6);
  shortImage->SetSpacing( newSpacing );
  EXPECT_EQ(shortImage->GetSpacing()[0], 1.9) << " SetSpacing[0]";
  EXPECT_EQ(shortImage->GetSpacing()[1], 2.8) << " SetSpacing[1]";
  EXPECT_EQ(shortImage->GetSpacing()[2], 3.7) << " SetSpacing[2]";
  EXPECT_EQ(shortImage->GetSpacing()[3], 4.6) << " SetSpacing[3]";
  shortImage->SetOrigin( spacing );

  // Check Error conditions for setting Spacing and Origin
  newSpacing.clear();
  newSpacing.push_back( 99 );
  newSpacing.push_back( 99 );
  newSpacing.push_back( 99 );
  ASSERT_ANY_THROW( shortImage->SetSpacing( newSpacing ) ) << " setting with too short spacing";

  newOrigin.clear();
  newOrigin.push_back( -99.99 );
  ASSERT_ANY_THROW( shortImage->SetOrigin( newOrigin ) ) << "setting with too short origin";

  // GetDirection
  EXPECT_EQ ( shortImage->GetDirection(), directionI4D ) << " Checking Get Direction matrix for identity";

  // SetDirection
  std::vector<double> vdir( adir, adir+16 );
  shortImage->SetDirection( vdir );
  for( unsigned int i = 0 ; i < 16; ++i )
  {
    EXPECT_EQ ( shortImage->GetDirection()[i], vdir[i] ) << " Checking Direction matrix at index " << i;
   }

  // Check Error Conditions for setting Directions
  ASSERT_ANY_THROW( shortImage->SetDirection( std::vector<double>( adir, adir + 4 ) ) );
  ASSERT_ANY_THROW( shortImage->SetDirection( std::vector<double>( adir, adir + 8 ) ) );
}

namespace sitk = itk::simple;

TEST_F(Image4D, CopyInformation)
{
  std::vector<unsigned int> s4d(4,10);
  sitk::Image img1d( 10, 20, sitk::sitkFloat32 );
  sitk::Image img4d( s4d, sitk::sitkUInt32 );

  // number if dimension are different
  EXPECT_ANY_THROW( img1d.CopyInformation( img4d ) );

  // image sizes don't match
  s4d[3] = 20;
  sitk::Image img4d2( s4d, sitk::sitkUInt16 );
  EXPECT_ANY_THROW( img4d.CopyInformation( img4d2 ) );

  // fix the size to match
  sitk::Image img4d3 = sitk::Image( img4d.GetSize(), sitk::sitkFloat64);
  img4d3.SetOrigin( shortImage->GetOrigin() );
  img4d3.SetSpacing( shortImage->GetSpacing() );

  EXPECT_NO_THROW( img4d.CopyInformation( img4d3 ) );
  EXPECT_EQ( img4d.GetSpacing(), img4d3.GetSpacing() );
  EXPECT_EQ( img4d.GetOrigin(), img4d3.GetOrigin() );
  EXPECT_EQ( img4d.GetDirection(), img4d3.GetDirection() );

}

TEST_F(Image4D, CopyOnWrite)
{
  std::vector<unsigned int> s4d(4,10);
  // test that a just constructed image only have 1 referecne
  sitk::Image img( s4d, sitk::sitkUInt8 );
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
  imgCopy.SetOrigin( std::vector<double>( 4, 2.123 ) );
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
  imgCopy.SetSpacing( std::vector<double>( 4, 3.45 ) );
  EXPECT_EQ(static_cast<const sitk::Image *>(&imgCopy)->GetITKBase()->GetReferenceCount(), 1 )
    << " Reference Count for copy after set spacing";
  EXPECT_EQ(static_cast<const sitk::Image *>(&img0)->GetITKBase()->GetReferenceCount(), 3 )
    << " Reference Count for shared after set spacing";

  // Requires 4D hash image filter, we have that
  EXPECT_EQ( sitk::Hash( imgCopy ), sitk::Hash( img0 ) ) << "Hash for shared and copy after set spacing";
}


TEST( IO, Image4D )
{
  // Image

  std::vector<unsigned int> size(4);
  size[0] = 10;
  size[1] = 11;
  size[2] = 12;
  size[3] = 13;
  sitk::Image image = sitk::Image( size, sitk::sitkUInt8 );
  sitk::Image imageRead;

  EXPECT_EQ( 10u, image.GetWidth() );
  EXPECT_EQ( 11u, image.GetHeight() );
  EXPECT_EQ( 12u, image.GetDepth() );
  EXPECT_EQ( 13u, image.GetSize()[3] );
  EXPECT_EQ( 1u, image.GetNumberOfComponentsPerPixel() );

  sitk::ImageFileWriter imageWriter;
  imageWriter.SetFileName( dataFinder.GetOutputDirectory()+"image4d.nii" );
  ASSERT_NO_THROW( imageWriter.Execute( image ) );

  sitk::ImageFileReader imageReader;
  imageReader.SetFileName( dataFinder.GetOutputDirectory()+"image4d.nii" );
  ASSERT_NO_THROW( imageRead = imageReader.Execute() );
  EXPECT_EQ ( sitk::Hash( image ), sitk::Hash( imageRead ) );

  sitk::Image imageRead2;
  imageReader.SetFileName( dataFinder.GetFile( "Input/4D.nii.gz" ) );
  ASSERT_NO_THROW( imageRead2 = imageReader.Execute() );
  EXPECT_EQ ( "9e81d4b3cdf10a4da5d54c8cd7c4954449d76d5d", sitk::Hash( imageRead2 ) );

  EXPECT_EQ( 36u, imageRead2.GetWidth() );
  EXPECT_EQ( 48u, imageRead2.GetHeight() );
  EXPECT_EQ( 21u, imageRead2.GetDepth() );
  EXPECT_EQ( 4u, imageRead2.GetSize()[3] );

  imageWriter.SetFileName( dataFinder.GetOutputDirectory()+"image4d2.nii" );
  ASSERT_NO_THROW( imageWriter.Execute( imageRead2 ) );

  sitk::Image imageRead3;
  ASSERT_NO_THROW( imageRead3 = imageReader.Execute() );
  imageReader.SetFileName( dataFinder.GetOutputDirectory()+"image4d2.nii" );
  EXPECT_EQ ( "9e81d4b3cdf10a4da5d54c8cd7c4954449d76d5d", sitk::Hash( imageRead3 ) );

  // VectorImage
  sitk::Image vectorImage = sitk::Image( size, sitk::sitkVectorUInt8 );
  sitk::Image vectorImageRead;

  EXPECT_EQ( 10u, vectorImage.GetWidth() );
  EXPECT_EQ( 11u, vectorImage.GetHeight() );
  EXPECT_EQ( 12u, vectorImage.GetDepth() );
  ASSERT_EQ( 4u, vectorImage.GetSize().size() );
  EXPECT_EQ( 13u, vectorImage.GetSize()[3] );
  EXPECT_EQ( 4u, vectorImage.GetNumberOfComponentsPerPixel() );

  sitk::ImageFileWriter vectorImageWriter;
  vectorImageWriter.SetFileName( "image4d.nii" );
  ASSERT_NO_THROW( vectorImageWriter.Execute( vectorImage ) );

  sitk::ImageFileReader vectorImageReader;
  vectorImageReader.SetFileName( "image4d.nii" );
  ASSERT_NO_THROW( vectorImageRead = vectorImageReader.Execute() );

  EXPECT_EQ ( sitk::Hash( vectorImage ), sitk::Hash( vectorImageRead ) );

}


TEST_F(Image4D, JoinSeriesImageFilter)
{
  std::vector<unsigned int> size(3);
  size[0] = 10;
  size[1] = 11;
  size[2] = 12;

  sitk::Image img = sitk::Image( size, sitk::sitkUInt8 );

  sitk::Image out = sitk::JoinSeries(img, img, img);

  ASSERT_EQ ( out.GetDimension(), 4 );
  EXPECT_EQ ( out.GetSize()[3], 3 );
}

TEST_F(Image4D, ExtractImageFilter)
{
  std::vector<unsigned int> size(4);
  size[0] = 10;
  size[1] = 11;
  size[2] = 12;
  size[3] = 13;

  sitk::Image img = sitk::Image( size, sitk::sitkUInt8 );

  std::vector<unsigned int> extractSize(4);
  extractSize[0] = 10;
  extractSize[1] = 11;
  extractSize[2] = 0;
  extractSize[3] = 13;

  sitk::Image out = sitk::Extract(img, extractSize);

  ASSERT_EQ ( 3u, out.GetDimension() );
  EXPECT_EQ ( 10u, out.GetSize().at(0) );
  EXPECT_EQ ( 11u, out.GetSize().at(1) );
  EXPECT_EQ ( 13u, out.GetSize().at(2) );
  EXPECT_EQ ( 1430u, out.GetNumberOfPixels() );
}
