#include <gtest/gtest.h>
#include <SimpleITKMacro.h>
#include "SimpleITKTestHarness.h"
#include "itkAffineTransform.h"

#include <SimpleITK.h>
typedef itk::AffineTransform< double > TransformType;

class Registration : public testing::Test {
public:
  virtual void SetUp() {
    itk::simple::ImageFileReader reader;
    itk::simple::CastImageFilter cast;
    reader.setFilename ( dataFinder.getFile ( "Input/HeadMRVolume.mha" ) );
    shortImage = cast.setOutputDataType ( itk::simple::sitkInt16 ).execute ( reader.execute() );
    charImage = cast.setOutputDataType ( itk::simple::sitkUInt8 ).execute ( reader.execute() );
    intImage = cast.setOutputDataType ( itk::simple::sitkInt32 ).execute ( reader.execute() );
    floatImage = cast.setOutputDataType ( itk::simple::sitkFloat32 ).execute ( reader.execute() );
    // Check our inputs
    EXPECT_TRUE ( shortImage.IsNotNull() ) << " Short image";
    EXPECT_TRUE ( charImage.IsNotNull() ) << " Char image";
    EXPECT_TRUE ( intImage.IsNotNull() ) << " Int image";
    EXPECT_TRUE ( floatImage.IsNotNull() ) << " Float image";
    // Create a transform
    affineTransform = TransformType::New();
    TransformType::OutputVectorType offset;
    offset[0] = 10; offset[1] = 20; offset[2] = 5;
    affineTransform->Translate ( offset );
    affineTransform->Shear ( 0, 1, 0.5 );
  }

  itk::simple::Image::Pointer shortImage;
  itk::simple::Image::Pointer intImage;
  itk::simple::Image::Pointer charImage;
  itk::simple::Image::Pointer floatImage;
  itk::simple::AffineRegistration affine;
  itk::simple::Transform transform;
  itk::simple::Resample resample;
  TransformType::Pointer affineTransform;
};

TEST_F(Registration,ShortToInt) {
  itk::simple::ImageHash hasher;
  transform = affine.execute ( shortImage, intImage );
  resample.setInterpolationType ( itk::simple::NearestNeighborInterpolation );
  resample.setTransform ( transform );
  resample.setOutputCoordinateSystemFromImage ( shortImage );
  itk::simple::Image::Pointer output = resample.execute ( intImage );
  EXPECT_EQ ( "4a5208af1448e5a297ec4d2402e834c6605a1557", hasher.execute ( output ) );
}

TEST_F(Registration,ShortToFloat) {
  itk::simple::ImageHash hasher;
  transform = affine.execute ( shortImage, floatImage );
  resample.setInterpolationType ( itk::simple::NearestNeighborInterpolation );
  resample.setTransform ( transform );
  resample.setOutputCoordinateSystemFromImage ( shortImage );
  itk::simple::Image::Pointer output = resample.execute ( floatImage );
  EXPECT_EQ ( "0eb980e1de1e0d08d4662a51db1c6a89b58d0c87", hasher.execute ( output ) );
}

TEST_F(Registration,ShortToChar) {
  itk::simple::ImageHash hasher;
  transform = affine.execute ( shortImage, charImage );
  resample.setInterpolationType ( itk::simple::NearestNeighborInterpolation );
  resample.setTransform ( transform );
  resample.setOutputCoordinateSystemFromImage ( shortImage );
  itk::simple::Image::Pointer output = resample.execute ( charImage );
  EXPECT_EQ ( "269fea1c6db001f76b8c482e2fd3a24ef9866f9a", hasher.execute ( output ) );
}

TEST_F(Registration,LinearInterpolation) {
  itk::simple::ImageHash hasher;
  transform.setITKTransform ( affineTransform.GetPointer() );

  resample.setInterpolationType ( itk::simple::LinearInterpolation );
  resample.setTransform ( transform );
  resample.setOutputCoordinateSystemFromImage ( shortImage );
  itk::simple::Image::Pointer output = resample.execute ( intImage );
  EXPECT_EQ ( "25b7d380e058ce735fc1c95981ac2e3ae556a9c8", hasher.execute ( output ) );
}

TEST_F(Registration,NearestNeighborInterpolation) {
  itk::simple::ImageHash hasher;
  transform.setITKTransform ( affineTransform.GetPointer() );

  resample.setInterpolationType ( itk::simple::NearestNeighborInterpolation );
  resample.setTransform ( transform );
  resample.setOutputCoordinateSystemFromImage ( shortImage );
  itk::simple::Image::Pointer output = resample.execute ( intImage );
  EXPECT_EQ ( "261d0c36e173fb8e50425dba08760c3962488f54", hasher.execute ( output ) );
}

TEST_F(Registration,SincInterpolation) /* Long */ {
  itk::simple::ImageHash hasher;
  transform.setITKTransform ( affineTransform.GetPointer() );

  resample.setInterpolationType ( itk::simple::SincInterpolation );
  resample.setTransform ( transform );
  resample.setOutputCoordinateSystemFromImage ( shortImage );
  itk::simple::Image::Pointer output = resample.execute ( intImage );
  EXPECT_EQ ( "", hasher.execute ( output ) );
}

TEST_F(Registration,BSplineInterpolation) /* Long */ {
  itk::simple::ImageHash hasher;
  transform.setITKTransform ( affineTransform.GetPointer() );

  resample.setInterpolationType ( itk::simple::BSplineInterpolation );
  resample.setTransform ( transform );
  resample.setOutputCoordinateSystemFromImage ( shortImage );
  itk::simple::Image::Pointer output = resample.execute ( intImage );
  EXPECT_EQ ( "", hasher.execute ( output ) );
}
