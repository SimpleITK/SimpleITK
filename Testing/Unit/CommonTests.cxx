#include <SimpleITKTestHarness.h>

#include <sitkImage.h>
#include <sitkIndex.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkImageHashFilter.h>
#include <sitkRecursiveGaussianImageFilter.h>

TEST(Common,Index) {
  {
  itk::simple::Index index;
  EXPECT_EQ ( index[0], 0 );
  EXPECT_EQ ( index[1], 0 );
  EXPECT_EQ ( index[2], 0 );
  EXPECT_EQ ( index.GetDim(), 2u );
  }

  {
  itk::simple::Index index ( 1, 2, 3 );
  EXPECT_EQ ( index[0], 1 );
  EXPECT_EQ ( index[1], 2 );
  EXPECT_EQ ( index[2], 3 );
  EXPECT_EQ ( index.GetDim(), 3u );
  }

  {
  itk::simple::Index index ( 1, 2 );
  EXPECT_EQ ( index[0], 1 );
  EXPECT_EQ ( index[1], 2 );
  EXPECT_EQ ( index[2], 0 );
  EXPECT_EQ ( index.GetDim(), 2u );
  }

  {
  itk::Index<3> itkIndex = {{ 1, 2, 3 }};
  itk::simple::Index index ( itkIndex );
  EXPECT_EQ ( index[0], 1 );
  EXPECT_EQ ( index[1], 2 );
  EXPECT_EQ ( index[2], 3 );
  EXPECT_EQ ( index.GetDim(), 3u );
  }

  {
  itk::Index<2> itkIndex = {{ 1, 2 }};
  itk::simple::Index index ( itkIndex );
  EXPECT_EQ ( index[0], 1 );
  EXPECT_EQ ( index[1], 2 );
  EXPECT_EQ ( index[2], 0 );
  EXPECT_EQ ( index.GetDim(), 2u );
  }

  {
  itk::simple::Index index ( 1, 2, 3 );
  EXPECT_EQ ( index.ToString(), "[1, 2, 3]" );
  EXPECT_EQ ( index[0], index.GetX() );
  EXPECT_EQ ( index[1], index.GetY() );
  EXPECT_EQ ( index[2], index.GetZ() );
  }

  


}
