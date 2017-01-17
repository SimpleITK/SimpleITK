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

#include <sitkTransformToDisplacementFieldFilter.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>
#include <sitkCastImageFilter.h>
#include <sitkVersion.h>


TEST(BasicFilters,TransformToDisplacementFieldFilter) {
  itk::simple::TransformToDisplacementFieldFilter filter;

  itk::simple::Image output( 0, 0, itk::simple::sitkUInt8 );

  EXPECT_EQ ( filter.GetOutputPixelType(), itk::simple::sitkVectorFloat64 ) << "Testing get for OutputPixelType";
  for(unsigned int i = 0; i < filter.GetSize().size(); ++i)
    {
    EXPECT_EQ ( filter.GetSize()[i], std::vector<unsigned int>(3, 64)[i] ) << "Testing get for Size at " << i;
    }
  for(unsigned int i = 0; i < filter.GetOutputOrigin().size(); ++i)
    {
    EXPECT_EQ ( filter.GetOutputOrigin()[i], std::vector<double>(3, 0.0)[i] ) << "Testing get for OutputOrigin at " << i;
    }
  for(unsigned int i = 0; i < filter.GetOutputSpacing().size(); ++i)
    {
    EXPECT_EQ ( filter.GetOutputSpacing()[i], std::vector<double>(3, 1.0)[i] ) << "Testing get for OutputSpacing at " << i;
    }
  EXPECT_EQ ( filter.GetOutputDirection(), std::vector<double>() ) << "Testing get for OutputDirection";

  EXPECT_NE ( filter.ToString(), "" ) << "empty ToString method!";
  EXPECT_EQ ( filter.GetName(), "TransformToDisplacementFieldFilter" ) << "checking GetName method!";

  // Test sets / gets
  filter.SetOutputPixelType ( itk::simple::sitkVectorFloat32 );
  EXPECT_EQ ( filter.GetOutputPixelType(), itk::simple::sitkVectorFloat32 ) << "Testing set/get for OutputPixelType";
  filter.SetSize ( std::vector<unsigned int>(3, 64) );
  for(unsigned int i = 0; i < filter.GetSize().size(); ++i)
    {
    EXPECT_EQ ( filter.GetSize()[i], std::vector<unsigned int>(3, 64)[i] ) << "Testing set/get for Size at " << i;
    }
  filter.SetOutputOrigin ( std::vector<double>(3, 0.0) );
  for(unsigned int i = 0; i < filter.GetOutputOrigin().size(); ++i)
    {
    EXPECT_EQ ( filter.GetOutputOrigin()[i], std::vector<double>(3, 0.0)[i] ) << "Testing set/get for OutputOrigin at " << i;
    }
  filter.SetOutputSpacing ( std::vector<double>(3, 1.0) );
  for(unsigned int i = 0; i < filter.GetOutputSpacing().size(); ++i)
    {
    EXPECT_EQ ( filter.GetOutputSpacing()[i], std::vector<double>(3, 1.0)[i] ) << "Testing set/get for OutputSpacing at " << i;
    }
  filter.SetOutputDirection ( std::vector<double>() );
  EXPECT_EQ ( filter.GetOutputDirection(), std::vector<double>() ) << "Testing set/get for OutputDirection";
 }

TEST(BasicFilters,TransformToDisplacementFieldFilter_defaults)
  {

  itk::simple::TransformToDisplacementFieldFilter filter;
  itk::simple::Image output;
  itk::simple::HashImageFilter hasher;

  itk::simple::Transform input;

  input = itk::simple::ReadTransform( dataFinder.GetFile( "Input/xforms/affine_i_3.txt" ) );

  ASSERT_TRUE ( input.GetITKBase() != NULL ) << "Could not read.";

  // Do we get the same image back, if we use the functional interface?
  itk::simple::Image fromFunctional( 0, 0, itk::simple::sitkUInt8 );
  itk::simple::Image fromProcedural( 0, 0, itk::simple::sitkUInt8 );
  ASSERT_NO_THROW ( fromProcedural = filter.Execute ( input  ) ) << "Procedural interface to TransformToDisplacementFieldFilter";
  ASSERT_NO_THROW ( fromFunctional = itk::simple::TransformToDisplacementField ( input ) ) << "Functional interface to TransformToDisplacementFieldFilter";

  hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 );
  EXPECT_EQ ( hasher.Execute ( fromProcedural ), hasher.Execute ( fromFunctional ) ) << "procedural and functional are not the same!";

   filter.DebugOn();
   ASSERT_NO_THROW ( output =  filter.Execute ( input  ) );
   EXPECT_EQ ( output.GetPixelID(), itk::simple::sitkVectorFloat64 ) << "Testing for OutputPixelType results";
   IMAGECOMPAREWITHTOLERANCE ( output, "", 5e-4 );
}

TEST(BasicFilters,TransformToDisplacementFieldFilter_32)
  {

  itk::simple::TransformToDisplacementFieldFilter filter;
  itk::simple::Image output;
  itk::simple::HashImageFilter hasher;

  itk::simple::Transform input;

  input = itk::simple::ReadTransform( dataFinder.GetFile( "Input/xforms/affine_i_3.txt" ) );

  ASSERT_TRUE ( input.GetITKBase() != NULL ) << "Could not read.";

  // Do we get the same image back, if we use the functional interface?
  itk::simple::Image fromFunctional( 0, 0, itk::simple::sitkUInt8 );
  itk::simple::Image fromProcedural( 0, 0, itk::simple::sitkUInt8 );
  ASSERT_NO_THROW ( fromProcedural = filter.Execute ( input  ) ) << "Procedural interface to TransformToDisplacementFieldFilter";
  ASSERT_NO_THROW ( fromFunctional = itk::simple::TransformToDisplacementField ( input ) ) << "Functional interface to TransformToDisplacementFieldFilter";

  hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 );
  EXPECT_EQ ( hasher.Execute ( fromProcedural ), hasher.Execute ( fromFunctional ) ) << "procedural and functional are not the same!";

   filter.DebugOn();
   filter.SetOutputPixelType ( itk::simple::sitkVectorFloat32 );
   ASSERT_NO_THROW ( output =  filter.Execute ( input  ) );
   EXPECT_EQ ( output.GetPixelID(), itk::simple::sitkVectorFloat32 ) << "Testing for OutputPixelType results";

   IMAGECOMPAREWITHTOLERANCE ( output, "", 5e-4 );
}
