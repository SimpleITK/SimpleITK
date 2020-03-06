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

#include "sitkImageOperators.h"
#include "SimpleITK.h"
#include "SimpleITKTestHarness.h"



namespace sitk = itk::simple;

TEST(OperatorTests,ComparisonLogic)
{

  sitk::Image img1 ( 10, 10, sitk::sitkUInt8 );
  sitk::Image img2 ( 10, 10, sitk::sitkUInt8 );

  img1 += 1;
  img2 += 2;

  EXPECT_EQ( sitk::Hash( img1 ), "3f3feea4f73d400fe98b7518a4b21ad4fc80476d" ) << "original";
  EXPECT_EQ( sitk::Hash( img2 ), "aca12668dde9598b74907488ae060a9c1cb71bd9" ) << "original";


  EXPECT_EQ( sitk::Hash( sitk::Greater( img1, 0 )), "3f3feea4f73d400fe98b7518a4b21ad4fc80476d" );
  EXPECT_EQ( sitk::Hash( sitk::Greater( 2,  img1 )), "3f3feea4f73d400fe98b7518a4b21ad4fc80476d" );
  EXPECT_EQ( sitk::Hash( sitk::Greater( img1, img2 )), "ed4a77d1b56a118938788fc53037759b6c501e3d" );

  EXPECT_EQ( sitk::Hash( sitk::GreaterEqual( img1, 0 )), "3f3feea4f73d400fe98b7518a4b21ad4fc80476d" ) ;
  EXPECT_EQ( sitk::Hash( sitk::GreaterEqual( 1,  img1 )), "3f3feea4f73d400fe98b7518a4b21ad4fc80476d" );
  EXPECT_EQ( sitk::Hash( sitk::GreaterEqual( img1, img2 )), "ed4a77d1b56a118938788fc53037759b6c501e3d" );


  EXPECT_EQ( sitk::Hash( sitk::Less( img1, 1 )), "ed4a77d1b56a118938788fc53037759b6c501e3d" );
  EXPECT_EQ( sitk::Hash( sitk::Less( 2,  img1 )),  "ed4a77d1b56a118938788fc53037759b6c501e3d" );
  EXPECT_EQ( sitk::Hash( sitk::Less( img1, img2 )), "3f3feea4f73d400fe98b7518a4b21ad4fc80476d" );

  EXPECT_EQ( sitk::Hash( sitk::LessEqual( img1, 1 )), "3f3feea4f73d400fe98b7518a4b21ad4fc80476d" );
  EXPECT_EQ( sitk::Hash( sitk::LessEqual( 2,  img1 )), "ed4a77d1b56a118938788fc53037759b6c501e3d" );
  EXPECT_EQ( sitk::Hash( sitk::LessEqual( img1, img2 )), "3f3feea4f73d400fe98b7518a4b21ad4fc80476d" );


  EXPECT_EQ( sitk::Hash( sitk::Equal( img1, 1 )), "3f3feea4f73d400fe98b7518a4b21ad4fc80476d" );
  EXPECT_EQ( sitk::Hash( sitk::Equal( 2,  img2 )),  "3f3feea4f73d400fe98b7518a4b21ad4fc80476d" );
  EXPECT_EQ( sitk::Hash( sitk::Equal( img1, img2 )), "ed4a77d1b56a118938788fc53037759b6c501e3d" );

  EXPECT_EQ( sitk::Hash( sitk::NotEqual( img1, 1 )), "ed4a77d1b56a118938788fc53037759b6c501e3d" );
  EXPECT_EQ( sitk::Hash( sitk::NotEqual( 2,  img2 )), "ed4a77d1b56a118938788fc53037759b6c501e3d" );
  EXPECT_EQ( sitk::Hash( sitk::NotEqual( img1, img2 )), "3f3feea4f73d400fe98b7518a4b21ad4fc80476d" );

}



TEST(OperatorTests,BinaryLogic)
{

  sitk::Image img1 ( 10, 10, sitk::sitkUInt8 );
  sitk::Image img2 ( 10, 10, sitk::sitkUInt8 );

  img1 += 1;
  img2 += 2;

  EXPECT_EQ( "f7463d12320e59d6f359abde8e957a7f3babf6e2", sitk::Hash( ~img1 ) );
  EXPECT_EQ( "5c74df2a1c141d6aaa817464c4db000c944d0068", sitk::Hash( ~img2 ) );

  EXPECT_EQ( "ed4a77d1b56a118938788fc53037759b6c501e3d", sitk::Hash( img1&2 ) );
  EXPECT_EQ( "ed4a77d1b56a118938788fc53037759b6c501e3d", sitk::Hash( 1&img2 ) );
  EXPECT_EQ( "ed4a77d1b56a118938788fc53037759b6c501e3d", sitk::Hash( img1&img2 ) );

  EXPECT_EQ( "69521af7751e8475fa976e49d9568a808f5a4bfa", sitk::Hash( img1|2 ) );
  EXPECT_EQ( "69521af7751e8475fa976e49d9568a808f5a4bfa", sitk::Hash( 1|img2 ) );
  EXPECT_EQ( "69521af7751e8475fa976e49d9568a808f5a4bfa", sitk::Hash( img1|img2 ));

  EXPECT_EQ( "69521af7751e8475fa976e49d9568a808f5a4bfa", sitk::Hash( img1^2 ) );
  EXPECT_EQ( "69521af7751e8475fa976e49d9568a808f5a4bfa", sitk::Hash( 1^img2 ) );
  EXPECT_EQ( "69521af7751e8475fa976e49d9568a808f5a4bfa", sitk::Hash( img1^img2 ));

}


TEST(OperatorTests, Arithmetic)
{

  sitk::Image img1 ( 10, 10, sitk::sitkInt32 );
  sitk::Image img2 ( 10, 10, sitk::sitkInt32 );

  img1 += 1;
  img2 += 2;

  EXPECT_EQ( "0dfef91fb04d1c86259591af2bb8c47498910af1", sitk::Hash( -img1 ) );
  EXPECT_EQ( "c6de42ea986ac4d0614de084ac2b08353ab01304", sitk::Hash( -img2 ) );

  EXPECT_EQ( "9477ff236835c28038e92121453738c7d4e9b471", sitk::Hash( img1+2 ) );
  EXPECT_EQ( "9477ff236835c28038e92121453738c7d4e9b471", sitk::Hash( 1+img2 ) );
  EXPECT_EQ( "9477ff236835c28038e92121453738c7d4e9b471", sitk::Hash( img1+img2 ) );

  EXPECT_EQ( "0dfef91fb04d1c86259591af2bb8c47498910af1", sitk::Hash( img1-2 ) );
  EXPECT_EQ( "0dfef91fb04d1c86259591af2bb8c47498910af1", sitk::Hash( 1-img2 ) );
  EXPECT_EQ( "0dfef91fb04d1c86259591af2bb8c47498910af1", sitk::Hash( img1-img2 ));

  EXPECT_EQ( "01e56888e4d212385251a2697aaf24a4287c1745", sitk::Hash( img1*2 ) );
  EXPECT_EQ( "61ca6324796009ce9132e8e1e364a2557241d1c5", sitk::Hash( 3*img2 ) );
  EXPECT_EQ( "01e56888e4d212385251a2697aaf24a4287c1745", sitk::Hash( img1*img2 ));

  EXPECT_EQ( "9477ff236835c28038e92121453738c7d4e9b471", sitk::Hash( 3/img1 ) );
  EXPECT_EQ( "116d707122e1c00c7328c57232a904df3a1f629d", sitk::Hash( img2/2 ) );
  EXPECT_EQ( "01e56888e4d212385251a2697aaf24a4287c1745", sitk::Hash( img2/img1 ));


  img1 = sitk::Image( 10,10, sitk::sitkUInt32 );
  img2 = sitk::Image( 10,10, sitk::sitkUInt32 );

  img1 += 10;
  img2 += 3;

  EXPECT_EQ( "116d707122e1c00c7328c57232a904df3a1f629d", sitk::Hash( img1%img2 ) );
  EXPECT_EQ( "01e56888e4d212385251a2697aaf24a4287c1745", sitk::Hash( img1%4 ) );
  EXPECT_EQ( "3d59f8de55a42cc13fb2ebda6de3a5193f2ee561", sitk::Hash( 3%img2 ));

}


TEST(OperatorTests, AdditionalDivide)
{

  sitk::Image img1 ( 10, 10, sitk::sitkInt32 );
  sitk::Image img2 ( 10, 10, sitk::sitkInt32 );

  img1 += 1;
  img2 += 2;

  std::vector<uint32_t> idx( 2, 4);

  EXPECT_EQ( "3d59f8de55a42cc13fb2ebda6de3a5193f2ee561", sitk::Hash( sitk::DivideFloor(img1, img2) ) );
  EXPECT_EQ( "0dfef91fb04d1c86259591af2bb8c47498910af1", sitk::Hash( sitk::DivideFloor(-img1, img2) ) );

  EXPECT_EQ( "3d59f8de55a42cc13fb2ebda6de3a5193f2ee561", sitk::Hash( sitk::DivideFloor(1, img2) ) );
  EXPECT_EQ( "0dfef91fb04d1c86259591af2bb8c47498910af1", sitk::Hash( sitk::DivideFloor(img1, -2) ) );

  EXPECT_EQ( 0.5,  sitk::DivideReal(img1, img2).GetPixelAsDouble(idx) );
  EXPECT_EQ( -0.5,  sitk::DivideReal(-img1, img2).GetPixelAsDouble(idx) );

  EXPECT_EQ( 0.5,  sitk::DivideReal(1, img2).GetPixelAsDouble(idx) );
  EXPECT_EQ( -0.25,  sitk::DivideReal(img1, -4).GetPixelAsDouble(idx) );

}
