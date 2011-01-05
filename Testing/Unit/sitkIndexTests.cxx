#include <sitkIndex.h>
#include <itkIndex.h>

#include <sstream>

#include "SimpleITKTestHarness.h"

class sitkIndexTest
  : public ::testing::Test
{
public:

  itk::simple::Index index1;
  itk::simple::Index index2;

};



//
// Test all functionality of itk::simple::Index
//
TEST_F(sitkIndexTest, Test1)
  {
  
  // Test with empty constructor
  ASSERT_EQ(index1.GetDim(), 2);
  ASSERT_EQ(index1[0], 0);
  ASSERT_EQ(index1[1], 0);
  ASSERT_EQ(index1[2], 0);

  // Test with 2D constructor
  index1 = itk::simple::Index(50,40);
  ASSERT_EQ(index1.GetDim(), 2);
  ASSERT_EQ(index1.GetX(), 50);
  ASSERT_EQ(index1[0], 50);
  ASSERT_EQ(index1.GetY(), 40);
  ASSERT_EQ(index1[1], 40);
  ASSERT_EQ(index1.GetZ(), 0);
  ASSERT_EQ(index1[2], 0);

  // Test copy constructor
  index2 = itk::simple::Index(index1);
  ASSERT_TRUE(index1 == index2);

  // Test with 3D constructor
  index2 = itk::simple::Index(50,40,0);
  ASSERT_EQ(index2.GetDim(), 3);
  ASSERT_EQ(index2.GetX(), 50);
  ASSERT_EQ(index2[0], 50);
  ASSERT_EQ(index2.GetY(), 40);
  ASSERT_EQ(index2[1], 40);
  ASSERT_EQ(index2.GetZ(), 0);
  ASSERT_EQ(index2[2], 0);

  // Test inequality based on dimension
  ASSERT_FALSE(index1 == index2);

  // Test inequality based on value
  index1 = itk::simple::Index(51, 40, 0);
  ASSERT_FALSE(index1 == index2);
  index1 = itk::simple::Index(50, 41, 0);
  ASSERT_FALSE(index1 == index2);
  index1 = itk::simple::Index(50, 40, 1);
  ASSERT_FALSE(index1 == index2);

  // Test printing
  std::stringstream ss;
  ss << index1;
  ASSERT_EQ(strcmp(ss.str().c_str(), "[50, 40, 1]"), 0);

  // Test cast to itk 2D
  index1 = itk::simple::Index(50, 40);
  itk::Index<2> itkIndex2D = {{50, 40}};
  ASSERT_TRUE(itkIndex2D == (itk::Index<2>)index1);

  // Test cast to itk 3D
  index1 = itk::simple::Index(50, 40, 1);
  itk::Index<3> itkIndex3D = {{50, 40, 1}};
  ASSERT_TRUE(itkIndex3D == (itk::Index<3>)index1);

  // Everything passed
  SUCCEED();
  }

