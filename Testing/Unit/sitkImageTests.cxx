/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#include <memory>
#include <type_traits>

const double adir[] = { 0.0, 0.0, 1.0, -1.0, 0.0, 0.0, 0.0, -1.0, 0.0 };

using itk::simple::InstantiatedPixelIDTypeList;


namespace sitk = itk::simple;


class Image : public ::testing::Test
{
public:
  using sitkAutoImagePointer = std::unique_ptr<sitk::Image>;

  void
  SetUp() override
  {
    itk::ImageBase<3>::IndexType   index;
    itk::ImageBase<3>::SizeType    size;
    itk::ImageBase<3>::RegionType  region;
    itk::ImageBase<3>::PointType   origin;
    itk::ImageBase<3>::SpacingType spacing;
    // Create an image
    for (int i = 0; i < 3; i++)
    {
      index[i] = 0;
      size[i] = 64 + i;
    }
    origin[0] = 1.1;
    origin[1] = 2.2;
    origin[2] = 3.3;
    spacing[0] = 0.5;
    spacing[1] = 0.5;
    spacing[2] = 1.5;

    region.SetSize(size);
    region.SetIndex(index);
    itk::Image<short, 3>::Pointer im = itk::Image<short, 3>::New();
    im->SetRegions(region);
    im->SetOrigin(origin);
    im->SetSpacing(spacing);
    im->Allocate();
    im->FillBuffer(100);
    itkShortImage = im;
    shortImage = std::make_unique<sitk::Image>(im.GetPointer());

    itk::Image<float, 3>::Pointer fim = itk::Image<float, 3>::New();
    fim->SetRegions(region);
    fim->SetOrigin(origin);
    fim->SetSpacing(spacing);
    fim->Allocate();
    fim->FillBuffer(0);
    itkFloatImage = fim;
    floatImage = std::make_unique<sitk::Image>(fim.GetPointer());

    itkFloatVectorImage = FloatVectorImageType::New();
    floatVectorImage = std::make_unique<sitk::Image>(itkFloatVectorImage.GetPointer());

    itkFloatVector2DImage = FloatVector2DImageType::New();
    floatVector2DImage = std::make_unique<sitk::Image>(itkFloatVector2DImage);
  }

  itk::ImageBase<3>::Pointer itkShortImage;

  using ShortImageType = itk::Image<short, 3>;
  sitkAutoImagePointer shortImage;

  using FloatImageType = itk::Image<float, 3>;
  sitkAutoImagePointer    floatImage;
  FloatImageType::Pointer itkFloatImage;

  using FloatVectorImageType = itk::VectorImage<float, 3>;
  sitkAutoImagePointer          floatVectorImage;
  FloatVectorImageType::Pointer itkFloatVectorImage;

  using FloatVector2DImageType = itk::VectorImage<float, 2>;
  sitkAutoImagePointer            floatVector2DImage;
  FloatVector2DImageType::Pointer itkFloatVector2DImage;

  sitkAutoImagePointer    differentSizedImage;
  ShortImageType::Pointer itkDifferentSizedImage;


  std::vector<double> directionI2D{ 1.0, 0.0, 0.0, 1.0 };
  std::vector<double> directionI3D{ 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };


  const std::list<sitk::PixelIDValueEnum> labelTypes = { sitk::sitkLabelUInt8,
                                                         sitk::sitkLabelUInt16,
                                                         sitk::sitkLabelUInt32,
                                                         sitk::sitkLabelUInt64 };
  const std::list<sitk::PixelIDValueEnum> basicTypes = { sitk::sitkUInt8,  sitk::sitkUInt16, sitk::sitkUInt32,
                                                         sitk::sitkUInt64, sitk::sitkInt8,   sitk::sitkInt16,
                                                         sitk::sitkInt32,  sitk::sitkInt64,  sitk::sitkFloat32,
                                                         sitk::sitkFloat64 };
  const std::list<sitk::PixelIDValueEnum> complexTypes = { sitk::sitkComplexFloat32, sitk::sitkComplexFloat64 };
  const std::list<sitk::PixelIDValueEnum> vectorTypes = { sitk::sitkVectorUInt8,   sitk::sitkVectorUInt16,
                                                          sitk::sitkVectorUInt32,  sitk::sitkVectorUInt64,
                                                          sitk::sitkVectorInt8,    sitk::sitkVectorInt16,
                                                          sitk::sitkVectorInt32,   sitk::sitkVectorInt64,
                                                          sitk::sitkVectorFloat32, sitk::sitkVectorFloat64 };
};


TEST_F(Image, Create)
{
  ASSERT_TRUE(shortImage->GetITKBase() != nullptr);
  EXPECT_EQ(shortImage->GetWidth(), itkShortImage->GetLargestPossibleRegion().GetSize()[0]) << " Checking image width";
  EXPECT_EQ(shortImage->GetHeight(), itkShortImage->GetLargestPossibleRegion().GetSize()[1])
    << " Checking image height";
  EXPECT_EQ(shortImage->GetDepth(), itkShortImage->GetLargestPossibleRegion().GetSize()[2]) << " Checking image depth";

  EXPECT_EQ(shortImage->GetSize()[0], shortImage->GetWidth());
  EXPECT_EQ(shortImage->GetSize()[1], shortImage->GetHeight());
  EXPECT_EQ(shortImage->GetSize()[2], shortImage->GetDepth());

  std::vector<unsigned int> size = shortImage->GetSize();

  EXPECT_EQ(size[0], shortImage->GetWidth());
  EXPECT_EQ(size[1], shortImage->GetHeight());
  EXPECT_EQ(size[2], shortImage->GetDepth());

  EXPECT_EQ(274560u, shortImage->GetNumberOfPixels());
}

TEST_F(Image, ImageDataType)
{

  // this test checks that the DataType of the images are correct
  int result;


  result = typelist2::index_of<InstantiatedPixelIDTypeList, sitk::BasicPixelID<short>>::value;
  EXPECT_EQ(shortImage->GetPixelIDValue(), result);
  EXPECT_EQ(shortImage->GetPixelID(), result);

  result = typelist2::index_of<InstantiatedPixelIDTypeList, sitk::BasicPixelID<float>>::value;
  EXPECT_EQ(floatImage->GetPixelIDValue(), result);
  EXPECT_EQ(floatImage->GetPixelID(), result);

  result = typelist2::index_of<InstantiatedPixelIDTypeList, sitk::VectorPixelID<float>>::value;
  EXPECT_EQ(floatVectorImage->GetPixelIDValue(), result);
  EXPECT_EQ(floatVectorImage->GetPixelID(), result);

  result = typelist2::index_of<InstantiatedPixelIDTypeList, sitk::VectorPixelID<float>>::value;
  EXPECT_EQ(floatVector2DImage->GetPixelIDValue(), result);
  EXPECT_EQ(floatVector2DImage->GetPixelID(), result);


  result = sitk::PixelIDToPixelIDValue<sitk::BasicPixelID<short>>::Result;
  EXPECT_EQ(shortImage->GetPixelIDValue(), result);
  EXPECT_EQ(shortImage->GetPixelID(), result);

  result = sitk::PixelIDToPixelIDValue<sitk::BasicPixelID<float>>::Result;
  EXPECT_EQ(floatImage->GetPixelIDValue(), result);
  EXPECT_EQ(floatImage->GetPixelID(), result);

  result = sitk::PixelIDToPixelIDValue<sitk::VectorPixelID<float>>::Result;
  EXPECT_EQ(floatVectorImage->GetPixelIDValue(), result);
  EXPECT_EQ(floatVectorImage->GetPixelID(), result);

  result = sitk::PixelIDToPixelIDValue<sitk::VectorPixelID<float>>::Result;
  EXPECT_EQ(floatVector2DImage->GetPixelIDValue(), result);
  EXPECT_EQ(floatVector2DImage->GetPixelID(), result);


  result =
    typelist2::index_of<InstantiatedPixelIDTypeList, sitk::ImageTypeToPixelID<ShortImageType>::PixelIDType>::value;
  EXPECT_EQ(shortImage->GetPixelIDValue(), result);
  EXPECT_EQ(shortImage->GetPixelID(), result);

  result = typelist2::index_of<InstantiatedPixelIDTypeList,
                               sitk::ImageTypeToPixelID<FloatVectorImageType>::PixelIDType>::value;
  EXPECT_EQ(floatVectorImage->GetPixelIDValue(), result);
  EXPECT_EQ(floatVectorImage->GetPixelID(), result);


  result = sitk::ImageTypeToPixelIDValue<ShortImageType>::Result;
  EXPECT_EQ(shortImage->GetPixelIDValue(), result);
  EXPECT_EQ(shortImage->GetPixelID(), result);

  result = sitk::ImageTypeToPixelIDValue<FloatVectorImageType>::Result;
  EXPECT_EQ(floatVectorImage->GetPixelIDValue(), result);
  EXPECT_EQ(floatVectorImage->GetPixelID(), result);
}

TEST_F(Image, Constructors)
{
  sitk::HashImageFilter hasher;
  int                   result;

  {
    sitk::Image image;
    EXPECT_EQ(0u, image.GetWidth());
    EXPECT_EQ(0u, image.GetHeight());
    EXPECT_EQ(0u, image.GetDepth());
    EXPECT_EQ(0u, image.GetNumberOfPixels());
  }

  sitk::Image image(64, 65, 66, sitk::sitkUInt8);
  EXPECT_EQ("08183e1b0c50fd2cf6f070b58e218443fb7d5317",
            hasher.SetHashFunction(sitk::HashImageFilter::SHA1).Execute(image))
    << " SHA1 hash value sitkUInt8";
  result = typelist2::index_of<InstantiatedPixelIDTypeList, sitk::BasicPixelID<unsigned char>>::value;
  EXPECT_EQ(image.GetPixelIDValue(), result);
  EXPECT_EQ(image.GetPixelIDTypeAsString(), "8-bit unsigned integer");
  EXPECT_EQ(image.GetDimension(), 3u);
  EXPECT_EQ(64u, image.GetWidth());
  EXPECT_EQ(65u, image.GetHeight());
  EXPECT_EQ(66u, image.GetDepth());
  EXPECT_EQ(274560u, image.GetNumberOfPixels());
  EXPECT_EQ(sizeof(uint8_t), image.GetSizeOfPixelComponent());
  EXPECT_EQ(image.GetDirection(), directionI3D);

  image = sitk::Image(64, 65, 66, sitk::sitkInt16);
  EXPECT_EQ("645b71695b94923c868e16b943d8acf8f6788617",
            hasher.SetHashFunction(sitk::HashImageFilter::SHA1).Execute(image))
    << " SHA1 hash value sitkUInt16";
  result = typelist2::index_of<InstantiatedPixelIDTypeList, sitk::BasicPixelID<short>>::value;
  EXPECT_EQ(image.GetPixelIDValue(), result);
  EXPECT_EQ(image.GetPixelIDTypeAsString(), "16-bit signed integer");
  EXPECT_EQ(image.GetDimension(), 3u);
  EXPECT_EQ(64u, image.GetWidth());
  EXPECT_EQ(65u, image.GetHeight());
  EXPECT_EQ(66u, image.GetDepth());
  EXPECT_EQ(274560u, image.GetNumberOfPixels());
  EXPECT_EQ(sizeof(int16_t), image.GetSizeOfPixelComponent());
  EXPECT_EQ(image.GetDirection(), directionI3D);

  image = sitk::Image(64, 65, sitk::sitkUInt16);
  EXPECT_EQ("e3c464cc1b73df3f48bacf238a80f88b5ab0d3e6",
            hasher.SetHashFunction(sitk::HashImageFilter::SHA1).Execute(image))
    << " SHA1 hash value sitkUInt16";
  result = typelist2::index_of<InstantiatedPixelIDTypeList, sitk::BasicPixelID<unsigned short>>::value;
  EXPECT_EQ(image.GetPixelIDValue(), result);
  EXPECT_EQ(image.GetPixelIDTypeAsString(), "16-bit unsigned integer");
  EXPECT_EQ(image.GetDimension(), 2u);
  EXPECT_EQ(64u, image.GetWidth());
  EXPECT_EQ(65u, image.GetHeight());
  EXPECT_EQ(0u, image.GetDepth());
  EXPECT_EQ(4160u, image.GetNumberOfPixels());
  EXPECT_EQ(1u, image.GetNumberOfComponentsPerPixel());
  EXPECT_EQ(sizeof(uint16_t), image.GetSizeOfPixelComponent());
  EXPECT_EQ(image.GetDirection(), directionI2D);

  // Test the constructors for vector images
  std::vector<unsigned int> s2d(2, 10);
  std::vector<unsigned int> s3d(3, 5);

  image = sitk::Image(s2d, sitk::sitkVectorUInt8);

  EXPECT_EQ(image.GetDimension(), 2u);
  EXPECT_EQ(2u, image.GetNumberOfComponentsPerPixel());
  image = sitk::Image(s3d, sitk::sitkVectorFloat32);
  EXPECT_EQ(image.GetDimension(), 3u);
  EXPECT_EQ(3u, image.GetNumberOfComponentsPerPixel());
  EXPECT_EQ(sizeof(float), image.GetSizeOfPixelComponent());

  image = sitk::Image(s2d, sitk::sitkVectorInt16, 5);
  EXPECT_EQ(image.GetDimension(), 2u);
  EXPECT_EQ(5u, image.GetNumberOfComponentsPerPixel());
  EXPECT_EQ(sizeof(int16_t), image.GetSizeOfPixelComponent());
  image = sitk::Image(s3d, sitk::sitkVectorFloat64, 10);
  EXPECT_EQ(image.GetDimension(), 3u);
  EXPECT_EQ(10u, image.GetNumberOfComponentsPerPixel());
  EXPECT_EQ(sizeof(double), image.GetSizeOfPixelComponent());


  // check for error when incorrect number of dimensions are requested
  std::vector<unsigned int> s1d(1, 100);
  std::vector<unsigned int> s5d(SITK_MAX_DIMENSION + 1, 100);
  ASSERT_ANY_THROW(sitk::Image(s1d, sitk::sitkVectorFloat64));
  ASSERT_ANY_THROW(sitk::Image(s5d, sitk::sitkVectorFloat64));

  // check for error with bad pixelID
  ASSERT_ANY_THROW(sitk::Image(s2d, sitk::sitkUnknown));
  ASSERT_ANY_THROW(sitk::Image(s2d, sitk::PixelIDValueEnum(-100)));

  // check for error when non-vector type requests components ( should
  // this be an error or should we just be converted to a vector )
  ASSERT_ANY_THROW(sitk::Image(s2d, sitk::sitkInt16, 10));
  ASSERT_ANY_THROW(sitk::Image(s2d, sitk::sitkLabelUInt8, 10));

  // currently we don't have a good interface to check the values of
  // these images, let just construct these types need todo better
  // testing!

  image = sitk::Image(64, 65, 66, sitk::sitkLabelUInt8);
  EXPECT_EQ(64u, image.GetWidth());
  EXPECT_EQ(65u, image.GetHeight());
  EXPECT_EQ(66u, image.GetDepth());
  EXPECT_EQ(274560u, image.GetNumberOfPixels());
  EXPECT_EQ(1u, image.GetNumberOfComponentsPerPixel());
  EXPECT_EQ(0, image.GetSizeOfPixelComponent());

  EXPECT_EQ(image.GetDirection(), directionI3D);

  image = sitk::Image(64, 65, 66, sitk::sitkLabelUInt16);

  image = sitk::Image(64, 65, 66, sitk::sitkLabelUInt32);

  image = sitk::Image(64, 65, 66, sitk::sitkVectorUInt8);

  EXPECT_EQ(64u, image.GetWidth());
  EXPECT_EQ(65u, image.GetHeight());
  EXPECT_EQ(66u, image.GetDepth());
  EXPECT_EQ(3u, image.GetNumberOfComponentsPerPixel());

  image = sitk::Image(64, 65, 66, sitk::sitkVectorUInt16);
  EXPECT_EQ(3u, image.GetNumberOfComponentsPerPixel());
  EXPECT_EQ(274560u, image.GetNumberOfPixels());
}

TEST_F(Image, Hash)
{
  sitk::HashImageFilter hasher;
  EXPECT_EQ("a998ea8b4999b4db9cbad033a52fe6d654211ff9",
            hasher.SetHashFunction(sitk::HashImageFilter::SHA1).Execute(*shortImage))
    << " SHA1 hash value";
  EXPECT_EQ("8cdd56962c5b3aabbfac56cd4dce1c7e", hasher.SetHashFunction(sitk::HashImageFilter::MD5).Execute(*shortImage))
    << " MD5 hash value";

  EXPECT_EQ("3b6bfcb1922bf8b29b171062ad722c82f8aa3f50",
            hasher.SetHashFunction(sitk::HashImageFilter::SHA1).Execute(*floatImage))
    << " SHA1 hash value";
  EXPECT_EQ("e5eba8af943d7911220c9f2fb9b5b9c8", hasher.SetHashFunction(sitk::HashImageFilter::MD5).Execute(*floatImage))
    << " MD5 hash value";
}

TEST_F(Image, Transforms)
{

  // Origin is [1.1, 2.2, 3.3]
  // Spacing is [0.5, 0.5, 1.5]

  {
    // Index to Physical Point
    std::vector<int64_t> idx(3, 1u);
    std::vector<double>  pt = shortImage->TransformIndexToPhysicalPoint(idx);
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
    std::vector<double> idx(3, 0.5);
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

TEST_F(Image, Properties)
{

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
  shortImage->SetOrigin(newOrigin);
  EXPECT_EQ(shortImage->GetOrigin()[0], 0.1) << " SetOrigin[0]";
  EXPECT_EQ(shortImage->GetOrigin()[1], 0.2) << " SetOrigin[1]";
  EXPECT_EQ(shortImage->GetOrigin()[2], 0.3) << " SetOrigin[2]";
  shortImage->SetOrigin(origin);

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
  shortImage->SetSpacing(newSpacing);
  EXPECT_EQ(shortImage->GetSpacing()[0], 1.9) << " SetSpacing[0]";
  EXPECT_EQ(shortImage->GetSpacing()[1], 2.8) << " SetSpacing[1]";
  EXPECT_EQ(shortImage->GetSpacing()[2], 3.7) << " SetSpacing[2]";
  shortImage->SetOrigin(spacing);

  // Check Error conditions for setting Spacing and Origin
  newSpacing.clear();
  newSpacing.push_back(99);
  newSpacing.push_back(99);
  ASSERT_ANY_THROW(shortImage->SetSpacing(newSpacing)) << " setting with too short spacing";

  newOrigin.clear();
  newOrigin.push_back(-99.99);
  ASSERT_ANY_THROW(shortImage->SetOrigin(newOrigin)) << "setting with too short origin";

  // GetDirection
  EXPECT_EQ(shortImage->GetDirection(), directionI3D) << " Checking Get Direction matrix for identity";


  // SetDirection
  std::vector<double> vdir(adir, adir + 9);
  shortImage->SetDirection(vdir);
  for (unsigned int i = 0; i < 9; ++i)
  {
    EXPECT_EQ(shortImage->GetDirection()[i], vdir[i]) << " Checking Direction matrix at index " << i;
  }

  // Check Error Conditions for setting Directions
  ASSERT_ANY_THROW(shortImage->SetDirection(std::vector<double>(adir, adir + 4)));
  ASSERT_ANY_THROW(shortImage->SetDirection(std::vector<double>(adir, adir + 8)));
}

TEST_F(Image, CopyInformation)
{

  sitk::Image img1(10, 20, sitk::sitkFloat32);
  sitk::Image img3d(10, 10, 10, sitk::sitkUInt32);


  // number if dimension are different
  EXPECT_ANY_THROW(img1.CopyInformation(img3d));

  sitk::Image img2(10, 10, sitk::sitkUInt16);

  // image sizes don't match
  EXPECT_ANY_THROW(img1.CopyInformation(img2));

  // fix the size to match

  img2 = sitk::Image(img1.GetSize(), sitk::sitkFloat64);
  img2.SetOrigin(shortImage->GetOrigin());
  img2.SetSpacing(shortImage->GetSpacing());

  EXPECT_NO_THROW(img1.CopyInformation(img2));
  EXPECT_EQ(img1.GetSpacing(), img2.GetSpacing());
  EXPECT_EQ(img1.GetOrigin(), img2.GetOrigin());
  EXPECT_EQ(img1.GetDirection(), img2.GetDirection());
  EXPECT_EQ(img1.GetNumberOfPixels(), img2.GetNumberOfPixels());
}

sitkClangDiagnosticPush();
sitkClangWarningIgnore("-Wself-assign-overloaded");
TEST_F(Image, CopyOnWrite)
{
  // test that a just constructed image only have 1 reference
  sitk::Image img(10, 10, sitk::sitkInt16);
  EXPECT_EQ(static_cast<const sitk::Image *>(&img)->GetITKBase()->GetReferenceCount(), 1)
    << " Reference Count for just constructed Image";
  EXPECT_TRUE(img.IsUnique());

  // use the image from the fixture to test some copy constructor
  EXPECT_EQ(static_cast<const sitk::Image *>(shortImage.get())->GetITKBase()->GetReferenceCount(), 2)
    << " Reference Count for shared shortImage initial";
  EXPECT_FALSE(shortImage->IsUnique());
  sitk::Image img0 = *shortImage;
  EXPECT_EQ(static_cast<const sitk::Image *>(shortImage.get())->GetITKBase()->GetReferenceCount(), 3)
    << " Reference Count for shared shortImage copy";
  EXPECT_FALSE(shortImage->IsUnique());
  sitk::Image imgCopy = img0;
  EXPECT_EQ(static_cast<const sitk::Image *>(shortImage.get())->GetITKBase()->GetReferenceCount(), 4)
    << " Reference Count for shared shortImage second copy";
  EXPECT_FALSE(shortImage->IsUnique());

  // check set origin for copy on write
  imgCopy.SetOrigin(std::vector<double>(3, 2.123));
  EXPECT_EQ(static_cast<const sitk::Image *>(&imgCopy)->GetITKBase()->GetReferenceCount(), 1)
    << " Reference Count for copy after set origin";
  EXPECT_TRUE(imgCopy.IsUnique());
  EXPECT_EQ(static_cast<const sitk::Image *>(&img0)->GetITKBase()->GetReferenceCount(), 3)
    << " Reference Count for shared after set origin";
  EXPECT_FALSE(img0.IsUnique());

  // check shallow copy on assignment
  imgCopy = img0;
  EXPECT_EQ(static_cast<const sitk::Image *>(&imgCopy)->GetITKBase()->GetReferenceCount(), 4)
    << " Reference Count for copy after assigment";
  EXPECT_FALSE(imgCopy.IsUnique());
  EXPECT_EQ(static_cast<const sitk::Image *>(&img0)->GetITKBase()->GetReferenceCount(), 4)
    << " Reference Count for shared after assignment";
  EXPECT_FALSE(img0.IsUnique());

  // check copy on write with set spacing
  imgCopy.SetSpacing(std::vector<double>(3, 3.45));
  EXPECT_EQ(static_cast<const sitk::Image *>(&imgCopy)->GetITKBase()->GetReferenceCount(), 1)
    << " Reference Count for copy after set spacing";
  EXPECT_TRUE(imgCopy.IsUnique());
  EXPECT_EQ(static_cast<const sitk::Image *>(&img0)->GetITKBase()->GetReferenceCount(), 3)
    << " Reference Count for shared after set spacing";
  EXPECT_FALSE(img0.IsUnique());
  EXPECT_EQ(sitk::Hash(imgCopy), sitk::Hash(img0)) << "Hash for shared and copy after set spacing";

  sitk::Image labelImage1(10, 10, sitk::sitkLabelUInt8);
  EXPECT_TRUE(labelImage1.IsUnique());
  sitk::Image labelImage2(labelImage1);
  EXPECT_FALSE(labelImage1.IsUnique());
  EXPECT_FALSE(labelImage2.IsUnique());

  // copy on write
  labelImage2.SetSpacing(std::vector<double>({ 1.2, 3.4 }));
  EXPECT_TRUE(labelImage1.IsUnique());
  EXPECT_TRUE(labelImage2.IsUnique());
}

TEST_F(Image, Operators)
{

  // the float image should begin as all zeros
  sitk::Image imgA = *floatImage;
  sitk::Image imgB = *floatImage;
  sitk::Image imgC = *floatImage;

  itk::Index<3> idx;
  idx.Fill(0);

  std::cout << "Testing Arithmetic operators" << std::endl;
  imgA += 1; // all 1s
  imgB = imgA;

  // 2 = 1 + 1
  imgC = imgA + imgB;

  // 1 = 2 - 1
  imgA = imgC - imgA;

  float v = dynamic_cast<itk::Image<float, 3> *>(imgA.GetITKBase())->GetPixel(idx);
  EXPECT_EQ(v, 1) << "value check 1";

  // 4 = 2 * 2
  imgB = imgC * imgC;

  // 2 = 4 / 2
  imgA = imgB / imgC;

  // .4 = 4 * .1
  imgC = imgB * .1;

  // 20 = .4 * 50;
  imgA = imgC * 50;

  v = dynamic_cast<itk::Image<float, 3> *>(imgA.GetITKBase())->GetPixel(idx);
  EXPECT_EQ(v, 20) << "value check 2";

  // original value should have never changed
  v = dynamic_cast<itk::Image<float, 3> *>(floatImage->GetITKBase())->GetPixel(idx);
  EXPECT_EQ(v, 0) << "value check 3";

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

  v = dynamic_cast<itk::Image<short, 3> *>(imgA.GetITKBase())->GetPixel(idx);
  EXPECT_EQ(v, -101);

  imgA = sitk::Image(10, 10, 10, sitk::sitkUInt8) + 1;
  imgB = ~imgA; // <- 253

  v = dynamic_cast<itk::Image<uint8_t, 3> *>(imgB.GetITKBase())->GetPixel(idx);
  EXPECT_EQ(254, v);

  // 0 = 1 & 254
  imgC = imgA & imgB;

  // 254 = 254 | 0
  imgA = imgB | imgC;

  // 254 = 254 ^ 0
  imgB = imgA ^ imgC;

  // 0 = 254 ^ 254
  imgA = imgB ^ imgA;

  v = dynamic_cast<itk::Image<uint8_t, 3> *>(imgA.GetITKBase())->GetPixel(idx);
  EXPECT_EQ(0, v) << "value check 4";
  v = dynamic_cast<itk::Image<uint8_t, 3> *>(imgB.GetITKBase())->GetPixel(idx);
  EXPECT_EQ(v, 254) << "value check 5";

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

  v = dynamic_cast<itk::Image<float, 3> *>(imgA.GetITKBase())->GetPixel(idx);
  EXPECT_EQ(v, 8) << "value check 6";

  // 1 = 8 / 8
  imgA /= imgA;

  // 100 = ~~100
  imgA = ~~*shortImage;

  // 100 = 100  & 100
  imgA &= imgA;

  v = dynamic_cast<itk::Image<short, 3> *>(imgA.GetITKBase())->GetPixel(idx);
  EXPECT_EQ(v, 100) << "value check 7";

  // 100 = 100 | 100
  imgA |= *shortImage;

  // 1 = 100 ^ 100
  imgA ^= *shortImage;


  v = dynamic_cast<itk::Image<short, 3> *>(imgA.GetITKBase())->GetPixel(idx);
  EXPECT_EQ(0, v) << "value check 8";
}
sitkClangDiagnosticPop();

TEST_F(Image, SetPixel)
{

  // this test is designed to run all SetPixel methods

  sitk::Image img = sitk::Image(10, 10, sitk::sitkFloat64);


  ASSERT_NO_THROW(img.SetPixelAsDouble({ 0, 0 }, 99.0)) << " correct setting";
  EXPECT_EQ(img.GetPixelAsDouble({ 0, 0 }), 99.0) << "Set value check";
  ASSERT_NO_THROW(img.SetPixelAsDouble({ 0, 0, 0 }, 99.0)) << " correct setting, with extra size index";
  EXPECT_EQ(img.GetPixelAsDouble({ 0, 0 }), 99.0) << "Set value check";
  ASSERT_ANY_THROW(img.SetPixelAsDouble({ 0 }, 99.0)) << " too short index";

  ASSERT_ANY_THROW(img.SetPixelAsInt8({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsUInt8({ 0, 0 }, 99u)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsInt16({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsUInt16({ 0, 0 }, 99u)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsInt32({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsUInt32({ 0, 0 }, 99u)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsInt64({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsUInt64({ 0, 0 }, 99u)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsFloat({ 0, 0 }, 99.0)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt8({ 0, 0 }, std::vector<int8_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt8({ 0, 0 }, std::vector<uint8_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt16({ 0, 0 }, std::vector<int16_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt16({ 0, 0 }, std::vector<uint16_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt32({ 0, 0 }, std::vector<int32_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt32({ 0, 0 }, std::vector<uint32_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt64({ 0, 0 }, std::vector<int64_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt64({ 0, 0 }, std::vector<uint64_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorFloat32({ 0, 0 }, std::vector<float>(3, 99.0))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorFloat64({ 0, 0 }, std::vector<double>(3, 99.0))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsComplexFloat32({ 0, 0 }, std::complex<float>(99.0, 1.0))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsComplexFloat64({ 0, 0 }, std::complex<float>(99, -1.0))) << " Get with wrong type";


  img = sitk::Image(10, 10, sitk::sitkVectorFloat64);

  ASSERT_NO_THROW(img.SetPixelAsVectorFloat64({ 0, 0 }, std::vector<double>(2, 99.0))) << " correct setting";
  EXPECT_EQ(img.GetPixelAsVectorFloat64({ 0, 0 }), std::vector<double>(2, 99.0)) << "Set value check";
  ASSERT_ANY_THROW(img.SetPixelAsVectorFloat64({ 0, 0 }, std::vector<double>(3, 99.0))) << " too long length";
  ASSERT_ANY_THROW(img.SetPixelAsVectorFloat64({ 0, 0 }, std::vector<double>(1, 99.0))) << " too short length";
  ASSERT_NO_THROW(img.SetPixelAsVectorFloat64({ 0, 0, 0 }, std::vector<double>(2, 98.0)))
    << " correct setting, long idx ";
  EXPECT_EQ(img.GetPixelAsVectorFloat64({ 0, 0 }), std::vector<double>(2, 98.0)) << "Set value check";
  ASSERT_ANY_THROW(img.SetPixelAsVectorFloat64({ 0 }, std::vector<double>(2, 98.0))) << " too short idx ";

  ASSERT_ANY_THROW(img.SetPixelAsInt8({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsUInt8({ 0, 0 }, 99u)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsInt16({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsUInt16({ 0, 0 }, 99u)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsInt32({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsUInt32({ 0, 0 }, 99u)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsInt64({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsUInt64({ 0, 0 }, 99u)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsFloat({ 0, 0 }, 99.0)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsDouble({ 0, 0 }, 99.0)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt8({ 0, 0 }, std::vector<int8_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt8({ 0, 0 }, std::vector<uint8_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt16({ 0, 0 }, std::vector<int16_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt16({ 0, 0 }, std::vector<uint16_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt32({ 0, 0 }, std::vector<int32_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt32({ 0, 0 }, std::vector<uint32_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt64({ 0, 0 }, std::vector<int64_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt64({ 0, 0 }, std::vector<uint64_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorFloat32({ 0, 0 }, std::vector<float>(3, 99.0))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorFloat64({ 0, 0 }, std::vector<double>(3, 99.0))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsComplexFloat32({ 0, 0 }, std::complex<float>(99.0, 1.0))) << " Get with wrong type";


  img = sitk::Image(10, 10, sitk::sitkLabelUInt8);

  try
  {
    img.SetPixelAsUInt8({ 0, 0 }, 99u);
  }
  catch (std::exception & e)
  {
    std::cerr << e.what() << std::endl;
  }
  EXPECT_EQ(img.GetPixelAsUInt8({ 0, 0 }), 99.0) << "Set value check";
  ASSERT_NO_THROW(img.SetPixelAsUInt8({ 0, 0, 0 }, 99u)) << " correct setting, with extra size index";
  EXPECT_EQ(img.GetPixelAsUInt8({ 0, 0 }), 99.0) << "Set value check";
  ASSERT_ANY_THROW(img.SetPixelAsUInt8({ 0 }, 99u)) << " too short index";

  std::cout << "check\n";
  ASSERT_ANY_THROW(img.SetPixelAsInt8({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsInt16({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsUInt16({ 0, 0 }, 99u)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsInt32({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsUInt32({ 0, 0 }, 99u)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsInt64({ 0, 0 }, 99)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsUInt64({ 0, 0 }, 99u)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsFloat({ 0, 0 }, 99.0)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsDouble({ 0, 0 }, 99.0)) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt8({ 0, 0 }, std::vector<int8_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt8({ 0, 0 }, std::vector<uint8_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt16({ 0, 0 }, std::vector<int16_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt16({ 0, 0 }, std::vector<uint16_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt32({ 0, 0 }, std::vector<int32_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt32({ 0, 0 }, std::vector<uint32_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorInt64({ 0, 0 }, std::vector<int64_t>(3, 99))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorUInt64({ 0, 0 }, std::vector<uint64_t>(3, 99u))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorFloat32({ 0, 0 }, std::vector<float>(3, 99.0))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsVectorFloat64({ 0, 0 }, std::vector<double>(3, 99.0))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsComplexFloat32({ 0, 0 }, std::complex<float>(99.0, 1.0))) << " Get with wrong type";
  ASSERT_ANY_THROW(img.SetPixelAsComplexFloat64({ 0, 0 }, std::complex<float>(99, -1.0))) << " Get with wrong type";


  img = sitk::Image(10, 10, sitk::sitkFloat64);

  // Check that out of bounds throw
  uint32_t xOOB[] = { 10, 0, 0 };
  uint32_t yOOB[] = { 0, 10, 0 };
  uint32_t zOOB[] = { 0, 0, 10 };
  ASSERT_THROW(img.SetPixelAsDouble(std::vector<uint32_t>(xOOB, xOOB + 3), 0.0), sitk::GenericException)
    << "x out of bounds";
  ASSERT_THROW(img.SetPixelAsDouble(std::vector<uint32_t>(yOOB, yOOB + 3), 0.0), sitk::GenericException)
    << "y out of bounds";
  ASSERT_NO_THROW(img.SetPixelAsDouble(std::vector<uint32_t>(zOOB, zOOB + 3), 0.0))
    << "z out of bounds, expect truncation of z-dim";
}


sitkClangDiagnosticPush();
sitkClangWarningIgnore("-Wself-assign-overloaded");
TEST_F(Image, Operators_InPlace)
{
  sitk::Image img(10, 10, sitk::sitkUInt16);

  img += img;
  img -= img;
  img *= img;

  img += 1;
  img /= img;
  img %= img;
  img &= img;
  img |= img;
  img ^= img;

  img += 2.0;
  img -= 2.0;
  img *= 1.0;

  img /= 1.0;
  img %= 2;
  img &= 1;
  img |= 1;
  img ^= 0;

  img = (img *= 0) + 5;
  EXPECT_EQ(img.GetPixelAsUInt16({ 1, 1 }), 5);
}
sitkClangDiagnosticPop();


TEST_F(Image, GetPixel)
{

  // this test is designed to run all GetPixel methods for scalar types

  sitk::Image img = sitk::Image(10, 10, sitk::sitkInt8);
  EXPECT_EQ(img.GetPixelAsInt8({ 0, 0 }), 0) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsInt8({ 0, 0, 0 }), 0) << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsInt8({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(int8_t), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkUInt8);
  EXPECT_EQ(img.GetPixelAsUInt8({ 0, 0 }), 0) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsUInt8({ 0, 0, 0 }), 0) << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(uint8_t), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, 10, sitk::sitkUInt8);
  EXPECT_EQ(img.GetPixelAsUInt8({ 0, 0, 0 }), 0) << " Get 3D with 3D ";
  EXPECT_EQ(img.GetPixelAsUInt8(std::vector<uint32_t>(4, 0)), 0) << " Get 3D with 4D ";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(uint8_t), img.GetSizeOfPixelComponent());


  img = sitk::Image(10, 10, sitk::sitkInt16);
  EXPECT_EQ(img.GetPixelAsInt16({ 0, 0 }), 0) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsInt16({ 0, 0, 0 }), 0) << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(int16_t), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkUInt16);
  EXPECT_EQ(img.GetPixelAsUInt16({ 0, 0 }), 0) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsUInt16({ 0, 0, 0 }), 0) << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(uint16_t), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkInt32);
  EXPECT_EQ(img.GetPixelAsInt32({ 0, 0 }), 0) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsInt32({ 0, 0, 0 }), 0) << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(int32_t), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkUInt32);
  EXPECT_EQ(img.GetPixelAsUInt32({ 0, 0 }), 0u) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsUInt32({ 0, 0, 0 }), 0u) << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(int32_t), img.GetSizeOfPixelComponent());

  if (sitk::sitkInt64 != sitk::sitkUnknown)
  {
    img = sitk::Image(10, 10, sitk::sitkInt64);
    EXPECT_EQ(img.GetPixelAsInt64({ 0, 0 }), 0) << " Get 2D with 2D ";
    EXPECT_EQ(img.GetPixelAsInt64({ 0, 0, 0 }), 0) << " Get 2D with 3D ";
    ASSERT_ANY_THROW(img.GetPixelAsInt64({ 0 })) << " Get with idx too small";
    ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsUInt64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
    EXPECT_EQ(sizeof(int64_t), img.GetSizeOfPixelComponent());
  }

  if (sitk::sitkUInt64 != sitk::sitkUnknown)
  {
    img = sitk::Image(10, 10, sitk::sitkUInt64);
    EXPECT_EQ(img.GetPixelAsUInt64({ 0, 0 }), 0u) << " Get 2D with 2D ";
    EXPECT_EQ(img.GetPixelAsUInt64({ 0, 0, 0 }), 0u) << " Get 2D with 3D ";
    ASSERT_ANY_THROW(img.GetPixelAsUInt64({ 0 })) << " Get with idx too small";
    ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsInt64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
    EXPECT_EQ(sizeof(uint64_t), img.GetSizeOfPixelComponent());
  }

  img = sitk::Image(10, 10, sitk::sitkFloat32);
  EXPECT_EQ(img.GetPixelAsFloat({ 0, 0 }), 0u) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsFloat({ 0, 0, 0 }), 0u) << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(float), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkFloat64);
  EXPECT_EQ(img.GetPixelAsDouble({ 0, 0 }), 0) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsDouble({ 0, 0, 0 }), 0) << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(double), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkComplexFloat32);
  EXPECT_EQ(img.GetPixelAsComplexFloat32({ 0, 0 }), std::complex<float>(0.0)) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsComplexFloat32({ 0, 0, 0 }), std::complex<float>(0.0)) << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(std::complex<float>), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkComplexFloat64);
  EXPECT_EQ(img.GetPixelAsComplexFloat64({ 0, 0 }), std::complex<double>(0.0)) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsComplexFloat64({ 0, 0, 0 }), std::complex<double>(0.0)) << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(std::complex<double>), img.GetSizeOfPixelComponent());


  img = sitk::Image(10, 10, sitk::sitkFloat64);

  // Check that out of bounds throw
  uint32_t xOOB[] = { 10, 0, 0 };
  uint32_t yOOB[] = { 0, 10, 0 };
  uint32_t zOOB[] = { 0, 0, 10 };
  ASSERT_THROW(img.GetPixelAsDouble(std::vector<uint32_t>(xOOB, xOOB + 3)), sitk::GenericException)
    << "x out of bounds";
  ASSERT_THROW(img.GetPixelAsDouble(std::vector<uint32_t>(yOOB, yOOB + 3)), sitk::GenericException)
    << "y out of bounds";
  ASSERT_NO_THROW(img.GetPixelAsDouble(std::vector<uint32_t>(zOOB, zOOB + 3)))
    << "z out of bounds, expect truncation of z-dim";
}


TEST_F(Image, GetPixelVector)
{

  std::vector<unsigned char> zero(2, 0);


  // this test is designed to run all GetPixel methods for Vector types

  sitk::Image img = sitk::Image(10, 10, sitk::sitkVectorInt8);
  EXPECT_EQ(img.GetPixelAsVectorInt8({ 0, 0 }), std::vector<int8_t>(zero.begin(), zero.end())) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsVectorInt8({ 0, 0, 0 }), std::vector<int8_t>(zero.begin(), zero.end())) << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(int8_t), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkVectorUInt8);
  EXPECT_EQ(img.GetPixelAsVectorUInt8({ 0, 0 }), std::vector<uint8_t>(zero.begin(), zero.end())) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsVectorUInt8({ 0, 0, 0 }), std::vector<uint8_t>(zero.begin(), zero.end()))
    << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(uint8_t), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, 10, sitk::sitkVectorUInt8);
  EXPECT_EQ(img.GetPixelAsVectorUInt8({ 0, 0, 0 }), std::vector<uint8_t>(3, 0)) << " Get 3D with 3D ";
  EXPECT_EQ(img.GetPixelAsVectorUInt8(std::vector<uint32_t>(4, 0)), std::vector<uint8_t>(3, 0)) << " Get 3D with 4D ";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(uint8_t), img.GetSizeOfPixelComponent());


  img = sitk::Image(10, 10, sitk::sitkVectorInt16);
  EXPECT_EQ(img.GetPixelAsVectorInt16({ 0, 0 }), std::vector<int16_t>(zero.begin(), zero.end())) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsVectorInt16({ 0, 0, 0 }), std::vector<int16_t>(zero.begin(), zero.end()))
    << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(int16_t), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkVectorUInt16);
  EXPECT_EQ(img.GetPixelAsVectorUInt16({ 0, 0 }), std::vector<uint16_t>(zero.begin(), zero.end()))
    << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsVectorUInt16({ 0, 0, 0 }), std::vector<uint16_t>(zero.begin(), zero.end()))
    << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(uint16_t), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkVectorInt32);
  EXPECT_EQ(img.GetPixelAsVectorInt32({ 0, 0 }), std::vector<int32_t>(zero.begin(), zero.end())) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsVectorInt32({ 0, 0, 0 }), std::vector<int32_t>(zero.begin(), zero.end()))
    << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(int32_t), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkVectorUInt32);
  EXPECT_EQ(img.GetPixelAsVectorUInt32({ 0, 0 }), std::vector<uint32_t>(zero.begin(), zero.end()))
    << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsVectorUInt32({ 0, 0, 0 }), std::vector<uint32_t>(zero.begin(), zero.end()))
    << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(uint32_t), img.GetSizeOfPixelComponent());

  if (sitk::sitkVectorInt64 != sitk::sitkUnknown)
  {
    img = sitk::Image(10, 10, sitk::sitkVectorInt64);
    EXPECT_EQ(img.GetPixelAsVectorInt64({ 0, 0 }), std::vector<int64_t>(zero.begin(), zero.end()))
      << " Get 2D with 2D ";
    EXPECT_EQ(img.GetPixelAsVectorInt64({ 0, 0, 0 }), std::vector<int64_t>(zero.begin(), zero.end()))
      << " Get 2D with 3D ";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0 })) << " Get with idx too small";
    ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsUInt64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
    EXPECT_EQ(sizeof(int64_t), img.GetSizeOfPixelComponent());
  }

  if (sitk::sitkVectorUInt64 != sitk::sitkUnknown)
  {
    img = sitk::Image(10, 10, sitk::sitkVectorUInt64);
    EXPECT_EQ(img.GetPixelAsVectorUInt64({ 0, 0 }), std::vector<uint64_t>(zero.begin(), zero.end()))
      << " Get 2D with 2D ";
    EXPECT_EQ(img.GetPixelAsVectorUInt64({ 0, 0, 0 }), std::vector<uint64_t>(zero.begin(), zero.end()))
      << " Get 2D with 3D ";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0 })) << " Get with idx too small";
    ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsInt64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
    ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
    EXPECT_EQ(sizeof(uint64_t), img.GetSizeOfPixelComponent());
  }

  img = sitk::Image(10, 10, sitk::sitkVectorFloat32);
  EXPECT_EQ(img.GetPixelAsVectorFloat32({ 0, 0 }), std::vector<float>(zero.begin(), zero.end())) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsVectorFloat32({ 0, 0, 0 }), std::vector<float>(zero.begin(), zero.end()))
    << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsDouble({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(float), img.GetSizeOfPixelComponent());

  img = sitk::Image(10, 10, sitk::sitkVectorFloat64);
  EXPECT_EQ(img.GetPixelAsVectorFloat64({ 0, 0 }), std::vector<double>(zero.begin(), zero.end())) << " Get 2D with 2D ";
  EXPECT_EQ(img.GetPixelAsVectorFloat64({ 0, 0, 0 }), std::vector<double>(zero.begin(), zero.end()))
    << " Get 2D with 3D ";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat64({ 0 })) << " Get with idx too small";
  ASSERT_ANY_THROW(img.GetPixelAsUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsFloat({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt8({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt16({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorUInt64({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsVectorFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat32({ 0, 0 })) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetPixelAsComplexFloat64({ 0, 0 })) << " Get with wrong type";
  EXPECT_EQ(sizeof(double), img.GetSizeOfPixelComponent());


  // Check that out of bounds throw
  uint32_t xOOB[] = { 10, 0, 0 };
  uint32_t yOOB[] = { 0, 10, 0 };
  uint32_t zOOB[] = { 0, 0, 10 };
  ASSERT_THROW(img.GetPixelAsVectorFloat64(std::vector<uint32_t>(xOOB, xOOB + 3)), sitk::GenericException)
    << "x out of bounds";
  ASSERT_THROW(img.GetPixelAsVectorFloat64(std::vector<uint32_t>(yOOB, yOOB + 3)), sitk::GenericException)
    << "y out of bounds";
  ASSERT_NO_THROW(img.GetPixelAsVectorFloat64(std::vector<uint32_t>(zOOB, zOOB + 3)))
    << "z out of bounds, expect truncation of z-dim";
}

TEST_F(Image, GetBuffer)
{

  // this test is designed to run all GetBuffer methods
  sitk::Image img = sitk::Image(10, 10, sitk::sitkUInt8);
  EXPECT_EQ(img.GetBufferAsUInt8()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt64()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt64()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkInt8);
  EXPECT_EQ(img.GetBufferAsInt8()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt64()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt64()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, 10, sitk::sitkUInt8);
  EXPECT_EQ(img.GetBufferAsUInt8()[99], 0) << " Get 3D with 3D ";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";


  img = sitk::Image(10, 10, sitk::sitkInt16);
  EXPECT_EQ(img.GetBufferAsInt16()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkUInt16);
  EXPECT_EQ(img.GetBufferAsUInt16()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkInt32);
  EXPECT_EQ(img.GetBufferAsInt32()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkUInt32);
  EXPECT_EQ(img.GetBufferAsUInt32()[99], 0u) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";


  // Int64 pixel types might not be instantiated
  if (sitk::sitkUInt64 != sitk::sitkUnknown)
  {
    img = sitk::Image(10, 10, sitk::sitkUInt64);
    EXPECT_EQ(img.GetBufferAsUInt64()[99], 0u) << " Get last element in buffer ";
  }
  if (sitk::sitkInt64 != sitk::sitkUnknown)
  {
    img = sitk::Image(10, 10, sitk::sitkInt64);
    EXPECT_EQ(img.GetBufferAsInt64()[99], 0u) << " Get last element in buffer ";
  }
  img = sitk::Image(10, 10, sitk::sitkFloat32);
  EXPECT_EQ(img.GetBufferAsFloat()[99], 0u) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkFloat64);
  EXPECT_EQ(img.GetBufferAsDouble()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkComplexFloat32);
  EXPECT_EQ(img.GetBufferAsFloat()[199], 0.0f) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkComplexFloat64);
  EXPECT_EQ(img.GetBufferAsDouble()[199], 0.0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
}


TEST_F(Image, GetBufferVector)
{

  // this test is designed to run all GetBuffer methods for vector images
  sitk::Image img = sitk::Image(10, 10, sitk::sitkVectorUInt8);

  EXPECT_EQ(img.GetBufferAsUInt8()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt64()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt64()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkVectorInt8);
  EXPECT_EQ(img.GetBufferAsInt8()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt64()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt64()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, 10, sitk::sitkVectorUInt8);
  EXPECT_EQ(img.GetBufferAsUInt8()[99], 0) << " Get 3D with 3D ";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";


  img = sitk::Image(10, 10, sitk::sitkVectorInt16);
  EXPECT_EQ(img.GetBufferAsInt16()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkVectorUInt16);
  EXPECT_EQ(img.GetBufferAsUInt16()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkVectorInt32);
  EXPECT_EQ(img.GetBufferAsInt32()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkVectorUInt32);
  EXPECT_EQ(img.GetBufferAsUInt32()[99], 0u) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  // Int64 pixel types might not be instantiated
  if (sitk::sitkVectorUInt64 != sitk::sitkUnknown)
  {
    img = sitk::Image(10, 10, sitk::sitkVectorUInt64);
    EXPECT_EQ(img.GetBufferAsUInt64()[99], 0u) << " Get last element in buffer ";
  }
  if (sitk::sitkVectorInt64 != sitk::sitkUnknown)
  {
    img = sitk::Image(10, 10, sitk::sitkVectorInt64);
    EXPECT_EQ(img.GetBufferAsInt64()[99], 0u) << " Get last element in buffer ";
  }

  img = sitk::Image(10, 10, sitk::sitkVectorFloat32);
  EXPECT_EQ(img.GetBufferAsFloat()[99], 0u) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsDouble()) << " Get with wrong type";

  img = sitk::Image(10, 10, sitk::sitkVectorFloat64);
  EXPECT_EQ(img.GetBufferAsDouble()[99], 0) << " Get last element in buffer ";
  ASSERT_ANY_THROW(img.GetBufferAsUInt8()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt16()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsUInt32()) << " Get with wrong type";
  ASSERT_ANY_THROW(img.GetBufferAsFloat()) << " Get with wrong type";
}

TEST_F(Image, MetaDataDictionary)
{
  sitk::Image img = sitk::Image(10, 10, 10, sitk::sitkFloat32);


  EXPECT_EQ(0u, img.GetMetaDataKeys().size());
  EXPECT_FALSE(img.HasMetaDataKey("nothing"));
  EXPECT_ANY_THROW(img.GetMetaData("anything"));

  {
    itk::DataObject::Pointer dataObject = img.GetITKBase();

    itk::MetaDataDictionary & mdd = dataObject->GetMetaDataDictionary();

    itk::EncapsulateMetaData<float>(mdd, "Float", static_cast<float>(1.234560F));
    itk::EncapsulateMetaData<std::string>(mdd, "String", std::string("std::string"));
  }

  EXPECT_EQ(2u, img.GetMetaDataKeys().size());
  EXPECT_FALSE(img.HasMetaDataKey("nothing"));
  EXPECT_TRUE(img.HasMetaDataKey("Float"));
  EXPECT_TRUE(img.HasMetaDataKey("String"));

  EXPECT_EQ("std::string", img.GetMetaData("String"));

  std::vector<std::string> keys = img.GetMetaDataKeys();
  for (size_t i = 0; i < keys.size(); ++i)
  {
    std::string value;

    EXPECT_NO_THROW(value = img.GetMetaData(keys[i]));
    std::cout << "Key = \"" << keys[i] << "\" Value = \"" << value << "\"" << std::endl;
  }

  img = sitk::Image(10, 10, 10, sitk::sitkFloat32);
  img.SetMetaData("k1", "somevalue");

  EXPECT_EQ(1u, img.GetMetaDataKeys().size());
  EXPECT_TRUE(img.HasMetaDataKey("k1"));
  EXPECT_EQ("somevalue", img.GetMetaData("k1"));

  EXPECT_FALSE(img.EraseMetaData("wrong"));
  EXPECT_EQ(1u, img.GetMetaDataKeys().size());
  EXPECT_TRUE(img.HasMetaDataKey("k1"));

  EXPECT_TRUE(img.EraseMetaData("k1"));
  EXPECT_FALSE(img.HasMetaDataKey("k1"));
  EXPECT_EQ(0u, img.GetMetaDataKeys().size());

  EXPECT_FALSE(img.EraseMetaData("k1"));
}

TEST_F(Image, ProxyForInPlaceOperation)
{
  sitk::Image img{ 10, 10, sitk::sitkFloat32 };

  img.SetPixelAsFloat({ 0, 0 }, 1.0f);

  auto proxyImage = img.ProxyForInPlaceOperation();
  EXPECT_EQ(proxyImage.GetPixelAsFloat({ 0, 0 }), 1.0f);
  EXPECT_TRUE(proxyImage.IsUnique());
  EXPECT_TRUE(img.IsUnique());

  proxyImage.SetPixelAsFloat({ 0, 1 }, 2.0f);
  EXPECT_EQ(proxyImage.GetPixelAsFloat({ 0, 1 }), 2.0f);
  EXPECT_EQ(img.GetPixelAsFloat({ 0, 1 }), 2.0f);

  sitk::Image img2{ { 10, 10 }, sitk::sitkVectorUInt8, 3 };

  img2.SetPixelAsVectorUInt8({ 0, 0 }, { 1, 1, 1 });

  proxyImage = img2.ProxyForInPlaceOperation();
  ASSERT_EQ(proxyImage.GetPixelID(), sitk::sitkVectorUInt8);
  EXPECT_EQ(proxyImage.GetPixelAsVectorUInt8({ 0, 0 }), std::vector<uint8_t>({ 1, 1, 1 }));
  EXPECT_TRUE(proxyImage.IsUnique());
  EXPECT_TRUE(img2.IsUnique());

  proxyImage.SetPixelAsVectorUInt8({ 0, 1 }, { 3, 2, 1 });
  EXPECT_EQ(proxyImage.GetPixelAsVectorUInt8({ 0, 1 }), std::vector<uint8_t>({ 3, 2, 1 }));
  EXPECT_EQ(img2.GetPixelAsVectorUInt8({ 0, 1 }), std::vector<uint8_t>({ 3, 2, 1 }));
}

TEST_F(Image, MoveOperations)
{
  sitk::Image img;

  static_assert(std::is_move_constructible<sitk::Image>::value, "Verify method availability");
  static_assert(std::is_move_assignable<sitk::Image>::value, "Verify method availability");

  img = sitk::Image(10, 10, sitk::sitkUInt8);

  EXPECT_EQ(img.GetSize()[0], 10);

  sitk::Image img2(5, 6, sitk::sitkUInt8);

  // The details of when an image has a nullptr for the ITKBase are
  // not specified, so that part of the tests are to verify the
  // internal implementation details
  auto itkBasePtr = img2.GetITKBase();

  img = std::move(img2);

  EXPECT_EQ(img.GetSize()[1], 6);
  EXPECT_EQ(static_cast<const sitk::Image &>(img).GetITKBase(), itkBasePtr);

  sitk::Image img3(std::move(img));

  EXPECT_EQ(img3.GetSize()[0], 5);
  EXPECT_EQ(static_cast<const sitk::Image &>(img3).GetITKBase(), itkBasePtr);
  EXPECT_NE(static_cast<const sitk::Image &>(img).GetITKBase(), nullptr);
  EXPECT_NE(static_cast<const sitk::Image &>(img).GetITKBase(), itkBasePtr);

  img = std::move(img3);

  EXPECT_EQ(img.GetSize()[0], 5);
  EXPECT_EQ(static_cast<const sitk::Image &>(img).GetITKBase(), itkBasePtr);
  EXPECT_NE(static_cast<const sitk::Image &>(img3).GetITKBase(), nullptr);
  EXPECT_NE(static_cast<const sitk::Image &>(img3).GetITKBase(), itkBasePtr);

  img2 = img;


  EXPECT_EQ(img2.GetSize()[0], 5);
  EXPECT_EQ(static_cast<const sitk::Image &>(img2).GetITKBase(), itkBasePtr);
  EXPECT_EQ(static_cast<const sitk::Image &>(img).GetITKBase(), itkBasePtr);

  const sitk::Image img4(std::move(img2));

  EXPECT_EQ(img4.GetSize()[0], 5);
  EXPECT_EQ(img4.GetITKBase(), itkBasePtr);
  EXPECT_EQ(static_cast<const sitk::Image &>(img).GetITKBase(), itkBasePtr);
  EXPECT_NE(static_cast<const sitk::Image &>(img2).GetITKBase(), nullptr);
  EXPECT_NE(static_cast<const sitk::Image &>(img2).GetITKBase(), itkBasePtr);
}


TEST_F(Image, Mandelbrot)
{
  unsigned int xs = 35 * 100;
  unsigned int ys = 20 * 100;

  sitk::Image real = sitk::Image(xs, ys, sitk::sitkFloat32);
  sitk::Image imagine = sitk::Image(xs, ys, sitk::sitkFloat32);

  for (unsigned int i = 0; i < xs; ++i)
  {
    for (unsigned int j = 0; j < ys; ++j)
    {
      std::vector<unsigned int> idx(2);
      idx[0] = i;
      idx[1] = j;

      real.SetPixelAsFloat(idx, -2.5 + (double(i) / xs) * 3.5);
      imagine.SetPixelAsFloat(idx, -1 + (double(j) / ys) * 2);
    }
  }

  sitk::Image C = sitk::RealAndImaginaryToComplex(real, imagine);
  std::cout << "Generated C" << std::endl;

  // initial image filled with 0s
  sitk::Image img(xs, ys, sitk::sitkComplexFloat32);

  for (unsigned int i = 0; i < 25; ++i)
  {
    img *= img;
    img += C;
  }

  sitk::Image R = sitk::ComplexToReal(img);
  sitk::Image I = sitk::ComplexToImaginary(img);
  img = R * R + I * I;

  sitk::WriteImage(img, "mandelbrot.nrrd");
}

TEST_F(Image, Evaluate)
{

  sitk::Image img;

  img = sitk::Image(10, 10, sitk::sitkUInt8);
  EXPECT_VECTOR_DOUBLE_NEAR(img.EvaluateAtPhysicalPoint({ 0.5, 0.5 }), { 0.0 }, 1e-10);
  EXPECT_VECTOR_DOUBLE_NEAR(img.EvaluateAtContinuousIndex({ 0.5, 0.5 }), { 0.0 }, 1e-10);

  img = sitk::Image(10, 10, sitk::sitkFloat32);

  for (auto interp : { sitk::sitkNearestNeighbor,
                       sitk::sitkLinear,
                       sitk::sitkBSpline,
                       sitk::sitkBSpline1,
                       sitk::sitkBSpline2,
                       sitk::sitkBSpline3,
                       sitk::sitkBSpline4,
                       sitk::sitkBSpline5,
                       sitk::sitkGaussian,
                       sitk::sitkLabelGaussian,
                       sitk::sitkHammingWindowedSinc,
                       sitk::sitkCosineWindowedSinc,
                       sitk::sitkWelchWindowedSinc,
                       sitk::sitkLanczosWindowedSinc,
                       sitk::sitkBSplineResamplerOrder1,
                       sitk::sitkBSplineResamplerOrder2,
                       sitk::sitkBSplineResamplerOrder3,
                       sitk::sitkBSplineResamplerOrder4,
                       sitk::sitkBSplineResamplerOrder5,
                       sitk::sitkLabelLinear })
  {
    std::vector<double> result;
    EXPECT_NO_THROW(result = img.EvaluateAtPhysicalPoint({ 0.5, 0.5 }, interp));
    EXPECT_VECTOR_DOUBLE_NEAR(result, { 0.0 }, 1e-10) << " with interp as" << interp;
    EXPECT_NO_THROW(result = img.EvaluateAtContinuousIndex({ 0.5, 0.5 }, interp));
    EXPECT_VECTOR_DOUBLE_NEAR(result, { 0.0 }, 1e-10) << " with interp as" << interp;
  }

  img = sitk::Image(10, 10, sitk::sitkComplexFloat32);

  for (auto interp : { sitk::sitkNearestNeighbor, sitk::sitkLinear })
  {
    std::vector<double> result;
    EXPECT_NO_THROW(result = img.EvaluateAtPhysicalPoint({ 0.5, 0.5 }, interp));
    EXPECT_VECTOR_DOUBLE_NEAR(result, v2(.0, 0.0), 1e-10) << " with interp as" << interp;
    EXPECT_NO_THROW(result = img.EvaluateAtContinuousIndex({ 0.5, 0.5 }, interp));
    EXPECT_VECTOR_DOUBLE_NEAR(result, v2(0.0, 0.0), 1e-10) << " with interp as" << interp;
  }

  for (auto interp : { sitk::sitkBSpline,
                       sitk::sitkGaussian,
                       sitk::sitkLabelGaussian,
                       sitk::sitkHammingWindowedSinc,
                       sitk::sitkCosineWindowedSinc,
                       sitk::sitkWelchWindowedSinc,
                       sitk::sitkLanczosWindowedSinc,
                       sitk::sitkBSplineResamplerOrder1,
                       sitk::sitkBSplineResamplerOrder2,
                       sitk::sitkBSplineResamplerOrder3,
                       sitk::sitkBSplineResamplerOrder4,
                       sitk::sitkBSplineResamplerOrder5,
                       sitk::sitkLabelLinear })
  {
    EXPECT_ANY_THROW(img.EvaluateAtPhysicalPoint({ 0.0, 0.0 }, interp));
  }

  img = sitk::Image({ 10, 10 }, sitk::sitkVectorFloat32, 2);

  for (auto interp : { sitk::sitkNearestNeighbor, sitk::sitkLinear })
  {
    std::vector<double> result;
    EXPECT_NO_THROW(result = img.EvaluateAtPhysicalPoint({ 0.5, 0.5 }, interp));
    EXPECT_VECTOR_DOUBLE_NEAR(result, v2(0.0, 0.0), 1e-10) << " with interp as" << interp;
    EXPECT_NO_THROW(result = img.EvaluateAtContinuousIndex({ 0.5, 0.5 }, interp));
    EXPECT_VECTOR_DOUBLE_NEAR(result, v2(0.0, 0.0), 1e-10) << " with interp as" << interp;
  }
  for (auto interp : { sitk::sitkBSpline,
                       sitk::sitkGaussian,
                       sitk::sitkLabelGaussian,
                       sitk::sitkHammingWindowedSinc,
                       sitk::sitkCosineWindowedSinc,
                       sitk::sitkWelchWindowedSinc,
                       sitk::sitkLanczosWindowedSinc,
                       sitk::sitkBSplineResamplerOrder1,
                       sitk::sitkBSplineResamplerOrder2,
                       sitk::sitkBSplineResamplerOrder3,
                       sitk::sitkBSplineResamplerOrder4,
                       sitk::sitkBSplineResamplerOrder5,
#ifdef SITK_GENERIC_LABEL_INTERPOLATOR
                       sitk::sitkLabelLinear
#endif
       })
  {
    EXPECT_ANY_THROW(img.EvaluateAtPhysicalPoint({ 0.0, 0.0 }, interp));
  }

  img = sitk::Image({ 3, 3 }, sitk::sitkLabelUInt8);
  for (auto interp : { sitk::sitkNearestNeighbor,
                       sitk::sitkLinear,
                       sitk::sitkBSpline,
                       sitk::sitkBSpline1,
                       sitk::sitkBSpline2,
                       sitk::sitkBSpline3,
                       sitk::sitkBSpline4,
                       sitk::sitkBSpline5,
                       sitk::sitkGaussian,
                       sitk::sitkLabelGaussian,
                       sitk::sitkHammingWindowedSinc,
                       sitk::sitkCosineWindowedSinc,
                       sitk::sitkWelchWindowedSinc,
                       sitk::sitkLanczosWindowedSinc,
                       sitk::sitkBSplineResamplerOrder1,
                       sitk::sitkBSplineResamplerOrder2,
                       sitk::sitkBSplineResamplerOrder3,
                       sitk::sitkBSplineResamplerOrder4,
                       sitk::sitkBSplineResamplerOrder5,
                       sitk::sitkLabelLinear })
  {
    EXPECT_ANY_THROW(img.EvaluateAtContinuousIndex({ 0.0, 0.0 }, interp));
  }
}

TEST_F(Image, Evaluate_boundary)
{

  sitk::Image img;

  for (auto pixelType : { sitk::sitkUInt8, sitk::sitkFloat32, sitk::sitkComplexFloat64, sitk::sitkVectorFloat32 })
  {
    img = sitk::Image(10, 10, pixelType);

    EXPECT_NO_THROW(img.EvaluateAtContinuousIndex({ -0.5, -0.5 }));
    EXPECT_NO_THROW(img.EvaluateAtContinuousIndex({ 9.5, 9.5 }));

    EXPECT_NO_THROW(img.EvaluateAtPhysicalPoint({ -0.5, -0.5 }));
    EXPECT_NO_THROW(img.EvaluateAtPhysicalPoint({ 9.5, 9.5 }));

    EXPECT_ANY_THROW(img.EvaluateAtContinuousIndex({ -0.51, -0.51 }));
    EXPECT_ANY_THROW(img.EvaluateAtContinuousIndex({ 9.51, 9.51 }));

    EXPECT_ANY_THROW(img.EvaluateAtPhysicalPoint({ -0.51, -0.51 }));
    EXPECT_ANY_THROW(img.EvaluateAtPhysicalPoint({ 9.51, 9.51 }));

    img.SetDirection({ 0.0, 1.0, 1.0, 0.0 });
    img.SetSpacing({ 1.0, 10.0 });


    EXPECT_NO_THROW(img.EvaluateAtContinuousIndex({ -0.5, -0.5 }));
    EXPECT_NO_THROW(img.EvaluateAtContinuousIndex({ 9.5, 9.5 }));

    EXPECT_NO_THROW(img.EvaluateAtPhysicalPoint({ -5, -0.5 }));
    EXPECT_NO_THROW(img.EvaluateAtPhysicalPoint({ 95, 9.5 }));

    EXPECT_ANY_THROW(img.EvaluateAtPhysicalPoint({ -5.1, 0 }));
    EXPECT_ANY_THROW(img.EvaluateAtPhysicalPoint({ 95.01, 9.5 }));
  }
}

TEST_F(Image, ToVector)
{
  for (auto pixelType : basicTypes)
  {
    sitk::Image img = sitk::Image(3, 10, 10, pixelType);
    img.SetSpacing({ 1.0, 2.0, 3.0 });
    img.SetOrigin({ 1.0, 2.0, 3.0 });
    img.SetDirection({ 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 });

    const std::string hash = sitk::Hash(img);

    sitk::Image converted = img.ToVectorImage(false);
    EXPECT_EQ(converted.GetDimension(), 2u);
    EXPECT_EQ(converted.GetSize(), std::vector<unsigned int>({ 10, 10 }));
    EXPECT_EQ(converted.GetNumberOfComponentsPerPixel(), 3);
    EXPECT_EQ(converted.GetSpacing(), std::vector<double>({ 2.0, 3.0 }));
    EXPECT_EQ(converted.GetOrigin(), std::vector<double>({ 2.0, 3.0 }));
    EXPECT_EQ(converted.GetDirection(), std::vector<double>({ 0.0, 1.0, 1.0, 0.0 }));
    EXPECT_TRUE(converted.IsUnique());
    EXPECT_TRUE(img.IsUnique());

    EXPECT_EQ(sitk::Hash(converted), hash);

    img.ToVectorImage(true);
    EXPECT_EQ(img.GetDimension(), 2u);
    EXPECT_EQ(img.GetSize(), std::vector<unsigned int>({ 10, 10 }));
    EXPECT_EQ(img.GetNumberOfComponentsPerPixel(), 3);
    EXPECT_EQ(img.GetSpacing(), std::vector<double>({ 2.0, 3.0 }));
    EXPECT_EQ(img.GetOrigin(), std::vector<double>({ 2.0, 3.0 }));
    EXPECT_EQ(img.GetDirection(), std::vector<double>({ 0.0, 1.0, 1.0, 0.0 }));
    EXPECT_TRUE(img.IsUnique());

    img = sitk::Image(std::vector<unsigned int>(SITK_MAX_DIMENSION, 5), pixelType);
    EXPECT_NO_THROW(img.ToVectorImage(false));

    img = sitk::Image(std::vector<unsigned int>(2, 5), pixelType);
    EXPECT_ANY_THROW(img.ToVectorImage(false));

    sitk::Image img2 = sitk::Image(5, 16, 16, pixelType);

    img2.SetDirection({ -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 });
    EXPECT_ANY_THROW(img2.ToVectorImage(false));

    img2.SetDirection({ 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0 });
    EXPECT_ANY_THROW(img2.ToVectorImage(false));

    img2.SetDirection({ 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0 });
    EXPECT_ANY_THROW(img2.ToVectorImage(false));
  }

  for (auto pixelType : vectorTypes)
  {
    sitk::Image img = sitk::Image({ 10u, 10u }, pixelType, 3);

    sitk::Image converted;
    EXPECT_NO_THROW(converted = img.ToVectorImage(false));
    EXPECT_EQ(converted.GetDimension(), 2u);
    EXPECT_EQ(converted.GetSize(), std::vector<unsigned int>({ 10, 10 }));
    EXPECT_EQ(converted.GetNumberOfComponentsPerPixel(), 3);
    EXPECT_EQ(converted.GetPixelID(), pixelType);
    EXPECT_FALSE(converted.IsUnique());
    EXPECT_FALSE(img.IsUnique());

    EXPECT_NO_THROW(converted = img.ToVectorImage(true));
    EXPECT_EQ(img.GetDimension(), 2u);
    EXPECT_EQ(img.GetSize(), std::vector<unsigned int>({ 10, 10 }));
    EXPECT_EQ(img.GetNumberOfComponentsPerPixel(), 3);
    EXPECT_FALSE(img.IsUnique());
    EXPECT_FALSE(img.IsUnique());

    img = sitk::Image(std::vector<unsigned int>(SITK_MAX_DIMENSION, 5u), pixelType, 3);


    EXPECT_NO_THROW(converted = img.ToVectorImage(false));
    EXPECT_EQ(converted.GetDimension(), SITK_MAX_DIMENSION);
    EXPECT_EQ(converted.GetNumberOfComponentsPerPixel(), 3);

    EXPECT_NO_THROW(converted = img.ToVectorImage(true));
  }

  for (auto pixelType : labelTypes)
  {

    for (unsigned int d = 2; d <= SITK_MAX_DIMENSION; ++d)
    {
      sitk::Image img = sitk::Image(std::vector<unsigned int>(d, 5), pixelType);

      EXPECT_ANY_THROW(img.ToVectorImage(false));
      EXPECT_ANY_THROW(img.ToVectorImage(true));
    }
  }

  for (auto pixelType : complexTypes)
  {
    for (unsigned int d = 2; d <= SITK_MAX_DIMENSION; ++d)
    {
      sitk::Image img = sitk::Image(std::vector<unsigned int>(d, 5), pixelType);

      EXPECT_ANY_THROW(img.ToVectorImage(false));
      EXPECT_ANY_THROW(img.ToVectorImage(true));
    }
  }
}

TEST_F(Image, ToScalar)
{
  for (auto pixelType : vectorTypes)
  {
    sitk::Image img({ 10u, 10u }, pixelType, 3);
    img.SetOrigin({ 1.0, 2.0 });
    img.SetSpacing({ 3.0, 4.0 });
    img.SetDirection({ 0.0, 1.0, 1.0, 0.0 });


    sitk::Image converted = img.ToScalarImage(false);
    EXPECT_EQ(converted.GetDimension(), 3u);
    EXPECT_EQ(converted.GetSize(), std::vector<unsigned int>({ 3, 10, 10 }));
    EXPECT_EQ(converted.GetNumberOfComponentsPerPixel(), 1u);
    EXPECT_EQ(converted.GetSpacing(), std::vector<double>({ 1.0, 3.0, 4.0 }));
    EXPECT_EQ(converted.GetOrigin(), std::vector<double>({ 0.0, 1.0, 2.0 }));
    EXPECT_EQ(converted.GetDirection(), std::vector<double>({ 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 }));
    EXPECT_TRUE(converted.IsUnique());
    EXPECT_TRUE(img.IsUnique());

    converted = img.ToScalarImage(true);
    EXPECT_EQ(img.GetDimension(), 3u);
    EXPECT_EQ(img.GetSize(), std::vector<unsigned int>({ 3, 10, 10 }));
    EXPECT_EQ(img.GetNumberOfComponentsPerPixel(), 1u);
    EXPECT_FALSE(img.IsUnique());
    EXPECT_FALSE(converted.IsUnique());

    img = sitk::Image(std::vector<unsigned int>(SITK_MAX_DIMENSION, 5u), pixelType, 3);
    EXPECT_ANY_THROW(img.ToScalarImage(false));

    img = sitk::Image(std::vector<unsigned int>(2, 5u), pixelType, 3);
    EXPECT_NO_THROW(img.ToScalarImage(false));
  }

  for (auto pixelType : basicTypes)
  {
    sitk::Image img({ 10u, 10u }, pixelType);

    sitk::Image converted = img.ToScalarImage(false);
    EXPECT_EQ(converted.GetDimension(), 2u);
    EXPECT_EQ(converted.GetSize(), std::vector<unsigned int>({ 10, 10 }));
    EXPECT_EQ(converted.GetNumberOfComponentsPerPixel(), 1u);
    EXPECT_EQ(converted.GetPixelID(), pixelType);
    EXPECT_FALSE(converted.IsUnique());
    EXPECT_FALSE(img.IsUnique());

    converted = img.ToScalarImage(true);
    EXPECT_EQ(img.GetDimension(), 2u);
    EXPECT_EQ(img.GetSize(), std::vector<unsigned int>({ 10, 10 }));
    EXPECT_EQ(img.GetNumberOfComponentsPerPixel(), 1u);
    EXPECT_EQ(img.GetPixelID(), pixelType);
    EXPECT_FALSE(img.IsUnique());
    EXPECT_FALSE(converted.IsUnique());

    img = sitk::Image(std::vector<unsigned int>(SITK_MAX_DIMENSION, 5u), pixelType);
    EXPECT_NO_THROW(img.ToScalarImage(false));

    img = sitk::Image(std::vector<unsigned int>(2, 5u), pixelType);
    EXPECT_NO_THROW(img.ToScalarImage(false));
  }


  for (auto pixelType : labelTypes)
  {

    for (unsigned int d = 2; d <= SITK_MAX_DIMENSION; ++d)
    {
      sitk::Image img = sitk::Image(std::vector<unsigned int>(d, 5), pixelType);

      EXPECT_ANY_THROW(img.ToScalarImage(false));
      EXPECT_ANY_THROW(img.ToScalarImage(true));
    }
  }

  for (auto pixelType : complexTypes)
  {
    for (unsigned int d = 2; d <= SITK_MAX_DIMENSION; ++d)
    {
      sitk::Image img = sitk::Image(std::vector<unsigned int>(d, 5), pixelType);

      EXPECT_ANY_THROW(img.ToScalarImage(false));
      EXPECT_ANY_THROW(img.ToScalarImage(true));
    }
  }
}


TEST_F(Image, CompareGeometry)
{
  const sitk::Image img1 = sitk::Image(10, 10, sitk::sitkUInt8);

  auto image_list = {
    sitk::Image(10, 10, itk::simple::sitkUInt8),          sitk::Image(10, 10, itk::simple::sitkFloat32),
    sitk::Image(10, 10, itk::simple::sitkComplexFloat32), sitk::Image(10, 10, itk::simple::sitkVectorUInt8),
    sitk::Image(10, 10, itk::simple::sitkLabelUInt32),
  };

  const double tol = 1e-8;


  for (auto img2 : image_list)
  {
    EXPECT_TRUE(img1.IsCongruentImageGeometry(img2, tol, tol));
    EXPECT_TRUE(img2.IsCongruentImageGeometry(img1, tol, tol));
    EXPECT_TRUE(img1.IsSameImageGeometryAs(img2));
    EXPECT_TRUE(img2.IsSameImageGeometryAs(img1));

    img2.SetSpacing({ 1.0 + tol, 1.0 });
    EXPECT_TRUE(img1.IsCongruentImageGeometry(img2, tol, tol));
    EXPECT_TRUE(img2.IsCongruentImageGeometry(img1, tol, tol));
    EXPECT_TRUE(img1.IsSameImageGeometryAs(img2));
    EXPECT_TRUE(img2.IsSameImageGeometryAs(img1));
    img2.SetSpacing(img1.GetSpacing());

    img2.SetSpacing({ 1.0 + 2 * tol, 1.0 });
    EXPECT_FALSE(img1.IsCongruentImageGeometry(img2, tol, tol));
    EXPECT_FALSE(img2.IsCongruentImageGeometry(img1, tol, tol));
    EXPECT_FALSE(img1.IsSameImageGeometryAs(img2, tol, tol));
    EXPECT_FALSE(img2.IsSameImageGeometryAs(img1, tol, tol));
    EXPECT_TRUE(img1.IsSameImageGeometryAs(img2));
    EXPECT_TRUE(img2.IsSameImageGeometryAs(img1));
    img2.SetSpacing(img1.GetSpacing());

    img2.SetOrigin({ 0.0 + tol, 0.0 });
    EXPECT_TRUE(img1.IsCongruentImageGeometry(img2, tol, tol));
    EXPECT_TRUE(img2.IsCongruentImageGeometry(img1, tol, tol));
    EXPECT_TRUE(img1.IsSameImageGeometryAs(img2));
    EXPECT_TRUE(img2.IsSameImageGeometryAs(img1));
    img2.SetOrigin(img1.GetOrigin());

    img2.SetDirection({ 1.0 + tol, 0.0, 0.0, 1.0 });
    EXPECT_TRUE(img1.IsCongruentImageGeometry(img2, tol, tol));
    EXPECT_TRUE(img2.IsCongruentImageGeometry(img1, tol, tol));
    EXPECT_TRUE(img1.IsSameImageGeometryAs(img2));
    EXPECT_TRUE(img2.IsSameImageGeometryAs(img1));
    img2.SetDirection(img1.GetDirection());

    img2.SetDirection({ 1.0 + sitk::Image::DefaultImageCoordinateTolerance * 2.0, 0.0, 0.0, 1.0 });
    EXPECT_FALSE(img1.IsCongruentImageGeometry(img2, tol, tol));
    EXPECT_FALSE(img2.IsCongruentImageGeometry(img1, tol, tol));
    EXPECT_FALSE(img1.IsSameImageGeometryAs(img2));
    EXPECT_FALSE(img2.IsSameImageGeometryAs(img1));
    img2.SetDirection(img1.GetDirection());
  }


  auto img3 = sitk::Image(2, 2, sitk::sitkUInt8);

  EXPECT_TRUE(img1.IsCongruentImageGeometry(img3, tol, tol));
  EXPECT_TRUE(img3.IsCongruentImageGeometry(img1, tol, tol));
  EXPECT_FALSE(img1.IsSameImageGeometryAs(img3));
  EXPECT_FALSE(img3.IsSameImageGeometryAs(img1));


  auto img4 = sitk::Image(10, 10, 10, sitk::sitkUInt8);
  EXPECT_FALSE(img1.IsCongruentImageGeometry(img4, tol, tol));
  EXPECT_FALSE(img4.IsCongruentImageGeometry(img1, tol, tol));
  EXPECT_FALSE(img1.IsSameImageGeometryAs(img4));
  EXPECT_FALSE(img4.IsSameImageGeometryAs(img1));
}
