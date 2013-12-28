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

#include "sitkTransform.h"
#include "sitkAdditionalProcedures.h"
#include "sitkResampleImageFilter.h"
#include "sitkHashImageFilter.h"
#include "SimpleITKTestHarness.h"

namespace sitk = itk::simple;


TEST(TransformTest, Construction) {


  sitk::Transform tx0( 2, sitk::sitkIdentity);
  std::cout << tx0.ToString() << std::endl;
  sitk::Transform tx1( 3, sitk::sitkIdentity);
  std::cout << tx1.ToString() << std::endl;

  sitk::Transform tx2( 2, sitk::sitkTranslation);
  std::cout << tx2.ToString() << std::endl;
  sitk::Transform tx3( 3, sitk::sitkTranslation);
  std::cout << tx3.ToString() << std::endl;

  sitk::Transform tx4( 2, sitk::sitkScale);
  std::cout << tx4.ToString() << std::endl;
  sitk::Transform tx5( 3, sitk::sitkScale);
  std::cout << tx5.ToString() << std::endl;

  sitk::Transform tx6( 2, sitk::sitkScaleLogarithmic);
  std::cout << tx6.ToString() << std::endl;
  sitk::Transform tx7( 3, sitk::sitkScaleLogarithmic);
  std::cout << tx7.ToString() << std::endl;

  sitk::Transform tx_0( 2, sitk::sitkEuler);
  std::cout << tx_0.ToString() << std::endl;
  sitk::Transform tx_1( 3, sitk::sitkEuler);
  std::cout << tx_1.ToString() << std::endl;

  sitk::Transform tx_2( 2, sitk::sitkSimilarity);
  std::cout << tx_2.ToString() << std::endl;
  sitk::Transform tx_3( 3, sitk::sitkSimilarity);
  std::cout << tx_3.ToString() << std::endl;

  EXPECT_ANY_THROW( sitk::Transform tx8( 2, sitk::sitkQuaternionRigid) );
  sitk::Transform tx9( 3, sitk::sitkQuaternionRigid);
  std::cout << tx9.ToString() << std::endl;

  EXPECT_ANY_THROW( sitk::Transform tx10( 2, sitk::sitkVersor) );
  sitk::Transform tx11( 3, sitk::sitkVersor);
  std::cout << tx11.ToString() << std::endl;

  EXPECT_ANY_THROW( sitk::Transform tx12( 2, sitk::sitkVersorRigid) );
  sitk::Transform tx13( 3, sitk::sitkVersorRigid);
  std::cout << tx13.ToString() << std::endl;

  sitk::Transform tx14( 2, sitk::sitkAffine);
  std::cout << tx14.ToString() << std::endl;
  sitk::Transform tx15( 3, sitk::sitkAffine);
  std::cout << tx15.ToString() << std::endl;

  sitk::Transform tx16( 2, sitk::sitkAffine);
  std::cout << tx16.ToString() << std::endl;
  sitk::Transform tx17( 3, sitk::sitkAffine);
  std::cout << tx17.ToString() << std::endl;


  // default constructable
  sitk::Transform tx18;
  std::cout << tx18.ToString() << std::endl;
}

TEST(TransformTest, Copy) {

  // Test the copy constructor and asignment operators

  sitk::Transform tx1( 2, sitk::sitkTranslation);
  sitk::Transform tx2( tx1 );
  sitk::Transform tx3 = sitk::Transform();

  tx1 = sitk::Transform();
  tx2 = tx1;

  // check self assignment
  tx3 = tx3;

}

TEST(TransformTest, SetGetParameters) {

  sitk::Transform tx;
  EXPECT_TRUE( tx.GetParameters().empty() );
  EXPECT_TRUE( tx.GetFixedParameters().empty() );

  tx = sitk::Transform( 3, sitk::sitkTranslation );
  EXPECT_EQ( tx.GetParameters().size(), 3u );
  EXPECT_TRUE( tx.GetFixedParameters().empty() );

  tx = sitk::Transform( 2, sitk::sitkScale );
  EXPECT_EQ( tx.GetParameters().size(), 2u );
  EXPECT_TRUE( tx.GetFixedParameters().empty() );

  tx = sitk::Transform( 3, sitk::sitkScaleLogarithmic );
  EXPECT_EQ( tx.GetParameters().size(), 3u );
  EXPECT_TRUE( tx.GetFixedParameters().empty() );

  tx = sitk::Transform( 2, sitk::sitkEuler );
  EXPECT_EQ( tx.GetParameters().size(), 3u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 2u );

  tx = sitk::Transform( 3, sitk::sitkEuler );
  EXPECT_EQ( tx.GetParameters().size(), 6u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 3u );

  tx = sitk::Transform( 2, sitk::sitkSimilarity );
  EXPECT_EQ( tx.GetParameters().size(), 4u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 2u );

  tx = sitk::Transform( 3, sitk::sitkSimilarity );
  EXPECT_EQ( tx.GetParameters().size(), 7u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 3u );

  tx = sitk::Transform( 3, sitk::sitkQuaternionRigid );
  EXPECT_EQ( tx.GetParameters().size(), 7u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 3u );

  tx = sitk::Transform( 3, sitk::sitkVersor );
  EXPECT_EQ( tx.GetParameters().size(), 3u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 3u );

  tx = sitk::Transform( 3, sitk::sitkVersorRigid );
  EXPECT_EQ( tx.GetParameters().size(), 6u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 3u );

  tx = sitk::Transform( 2, sitk::sitkAffine );
  EXPECT_EQ( tx.GetParameters().size(), 6u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 2u );


}

TEST(TransformTest, CopyOnWrite) {

  sitk::Transform tx1 = sitk::Transform( 2, sitk::sitkAffine );
  sitk::Transform tx2 = tx1;
  sitk::Transform tx3 = tx1;

  std::vector<double> params = tx1.GetParameters();
  params[1] = 0.2;

  tx2.SetParameters( params );

  ASSERT_EQ( tx1.GetParameters().size(), 6u );
  EXPECT_EQ( tx1.GetParameters()[1], 0.0 );

  ASSERT_EQ( tx2.GetParameters().size(), 6u );
  EXPECT_EQ( tx2.GetParameters()[1], 0.2 );

  ASSERT_EQ( tx3.GetParameters().size(), 6u );
  EXPECT_EQ( tx3.GetParameters()[1], 0.0 );

  params[1] = 0.3;
  tx3.SetParameters( params );

  ASSERT_EQ( tx1.GetParameters().size(), 6u );
  EXPECT_EQ( tx1.GetParameters()[1], 0.0 );

  ASSERT_EQ( tx2.GetParameters().size(), 6u );
  EXPECT_EQ( tx2.GetParameters()[1], 0.2 );

  ASSERT_EQ( tx3.GetParameters().size(), 6u );
  EXPECT_EQ( tx3.GetParameters()[1], 0.3 );

  tx1 = tx2;

  ASSERT_EQ( tx1.GetParameters().size(), 6u );
  EXPECT_EQ( tx1.GetParameters()[1], 0.2 );

  ASSERT_EQ( tx2.GetParameters().size(), 6u );
  EXPECT_EQ( tx2.GetParameters()[1], 0.2 );

  ASSERT_EQ( tx3.GetParameters().size(), 6u );
  EXPECT_EQ( tx3.GetParameters()[1], 0.3 );


  params[1] = 0.4;
  tx1.SetParameters( params );

  ASSERT_EQ( tx1.GetParameters().size(), 6u );
  EXPECT_EQ( tx1.GetParameters()[1], 0.4 );

  ASSERT_EQ( tx2.GetParameters().size(), 6u );
  EXPECT_EQ( tx2.GetParameters()[1], 0.2 );

  ASSERT_EQ( tx3.GetParameters().size(), 6u );
  EXPECT_EQ( tx3.GetParameters()[1], 0.3 );

}



TEST(TransformTest, AddTransform) {

  sitk::Transform tx1 = sitk::Transform( 2, sitk::sitkAffine );
  tx1.AddTransform( sitk::Transform( 2, sitk::sitkAffine ) );
  // check we can't add miss match dimension
  ASSERT_ANY_THROW( tx1.AddTransform( sitk::Transform( 3, sitk::sitkAffine ) ) );


  sitk::Transform tx2 = tx1;
  tx1.AddTransform( sitk::Transform( 2, sitk::sitkIdentity ) );


  sitk::Transform tx3( 3, sitk::sitkComposite );
  tx1 = tx3;
  tx3.AddTransform( sitk::Transform( 3, sitk::sitkAffine ) );

}

TEST(TransformTest, ReadTransformResample) {

  const char *txFiles[] = {
    "Input/xforms/affine_i_3.txt",
    "Input/xforms/composite_i_3.txt",
    "Input/xforms/i_3.txt",
    "Input/xforms/scale_i_3.txt",
    "Input/xforms/translation_i_3.txt",
    "Input/xforms/quaternion_rigid_i_3.txt",
    "Input/xforms/scale_logarithmic_i_3.txt",
    "Input/xforms/versor_i_3.txt",
    "" // end with zero length string
  };

  sitk::Transform tx;

  sitk::Image img = sitk::ReadImage( dataFinder.GetFile("Input/RA-Short.nrrd" ) );

  const char **ptxFiles = txFiles;
  while( strlen( *ptxFiles ) != 0 )
    {
    std::string fname = dataFinder.GetFile( *ptxFiles );
    std::cout << "Reading: " << *ptxFiles << std::endl;

    EXPECT_NO_THROW( tx = sitk::ReadTransform( fname ) );

    sitk::Image out = sitk::Resample( img, tx, sitk::sitkNearestNeighbor );

    EXPECT_EQ( "126ea8c3ef5573ca1e4e0deece920c2c4a4f38b5", sitk::Hash( out ) ) << "Resampling with identity matrix:" << tx.ToString();

    ++ptxFiles;
    }


}

TEST(TransformTest, TransformPoint) {
  sitk::Transform tx2 = sitk::Transform( 2, sitk::sitkIdentity );
  sitk::Transform tx3 = sitk::Transform( 3, sitk::sitkIdentity );

  std::vector<double> ipt;
  ipt.push_back( 1.1 );
  ipt.push_back( 2.22 );

  std::vector<double> opt;

  opt = tx2.TransformPoint( ipt );
  ASSERT_EQ( opt.size(), 2u );
  EXPECT_EQ( opt[0], 1.1 );
  EXPECT_EQ( opt[1], 2.22 );

  EXPECT_ANY_THROW( tx3.TransformPoint( ipt ) );

  ipt.push_back( 3.333 );

  EXPECT_ANY_THROW( opt = tx2.TransformPoint( ipt ) );
  ASSERT_EQ( opt.size(), 2u );
  EXPECT_EQ( opt[0], 1.1 );
  EXPECT_EQ( opt[1], 2.22 );

  opt = tx3.TransformPoint( ipt );
  ASSERT_EQ( opt.size(), 3u );
  EXPECT_EQ( opt[0], 1.1 );
  EXPECT_EQ( opt[1], 2.22 );
  EXPECT_EQ( opt[2], 3.333 );

}
