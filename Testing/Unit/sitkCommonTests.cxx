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

#include <sitkConditional.h>

#include <sitkKernel.h>

TEST( ConditionalTest, ConditionalTest1 ) {

  // a quick check to make sure the conditional works
  typedef itk::simple::Conditional<true, int, float>::Type IntType;
  typedef itk::simple::Conditional<false, int, float>::Type FloatType;


  EXPECT_EQ ( typeid( IntType ).name(), typeid( int ).name() );
  EXPECT_EQ ( typeid( FloatType ).name(), typeid( float ).name() );

  return;

}

TEST( Kernel, Test1 )
{
  // Test print of KernelEnum with output operator
  namespace sitk = itk::simple;

  std::stringstream ss;
  ss << sitk::sitkAnnulus;
  EXPECT_EQ("Annulus", ss.str());
  ss.str("");
  ss << sitk::sitkBall;
  EXPECT_EQ("Ball", ss.str());
  ss.str("");
  ss << sitk::sitkBox;
  EXPECT_EQ("Box", ss.str());
  ss.str("");
  ss << sitk::sitkCross;
  EXPECT_EQ("Cross", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon3;
  EXPECT_EQ("Polygon3", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon4;
  EXPECT_EQ("Polygon4", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon4;
  EXPECT_EQ("Polygon4", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon5;
  EXPECT_EQ("Polygon5", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon6;
  EXPECT_EQ("Polygon6", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon7;
  EXPECT_EQ("Polygon7", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon8;
  EXPECT_EQ("Polygon8", ss.str());
  ss.str("");
  ss << sitk::sitkPolygon9;
  EXPECT_EQ("Polygon9", ss.str());

}
