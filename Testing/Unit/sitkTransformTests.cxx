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

#include "SimpleITKTestHarness.h"
#include "sitkImageFileReader.h"
#include "sitkTransform.h"
#include "sitkAffineTransform.h"
#include "sitkBSplineTransform.h"
#include "sitkDisplacementFieldTransform.h"
#include "sitkTranslationTransform.h"
#include "sitkEuler2DTransform.h"
#include "sitkEuler3DTransform.h"
#include "sitkScaleTransform.h"
#include "sitkScaleVersor3DTransform.h"
#include "sitkScaleSkewVersor3DTransform.h"
#include "sitkSimilarity2DTransform.h"
#include "sitkSimilarity3DTransform.h"
#include "sitkVersorRigid3DTransform.h"
#include "sitkVersorTransform.h"
#include "sitkAdditionalProcedures.h"
#include "sitkResampleImageFilter.h"
#include "sitkHashImageFilter.h"


#include "itkMath.h"

namespace sitk = itk::simple;
namespace nsstd = itk::simple::nsstd;

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

  // displacement fields
  sitk::Image displacement = sitk::Image( 100, 100, sitk::sitkVectorFloat64 );

  sitk::Transform tx19( displacement );
  std::cout <<  tx19.ToString() << std::endl;
  EXPECT_EQ( displacement.GetSize()[0], 0u );
  EXPECT_EQ( displacement.GetSize()[1], 0u );

  displacement = sitk::Image( 100,100, 100, sitk::sitkVectorFloat64 );
  sitk::Transform tx20( displacement );
  std::cout << tx20.ToString() << std::endl;
  EXPECT_EQ( displacement.GetSize()[0], 0u );
  EXPECT_EQ( displacement.GetSize()[1], 0u );

  ASSERT_THROW( sitk::Transform( 3, sitk::sitkDisplacementField ), sitk::GenericException );
  ASSERT_THROW( sitk::Transform( 2, sitk::sitkDisplacementField ), sitk::GenericException );


  sitk::Image bsplineReference = sitk::Image(10,10, sitk::sitkUInt8);
  sitk::Transform tx21( bsplineReference, sitk::sitkBSplineTransform );

  bsplineReference = sitk::Image(10,10, 10, sitk::sitkUInt8);
  sitk::Transform tx22( bsplineReference, sitk::sitkBSplineTransform );

  ASSERT_THROW( sitk::Transform( 3, sitk::sitkBSplineTransform ), sitk::GenericException );
  ASSERT_THROW( sitk::Transform( 2, sitk::sitkBSplineTransform ), sitk::GenericException );

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
#if (ITK_VERSION_MAJOR*100+ITK_VERSION_MINOR) >= 410
  const unsigned int euler3DNumberOfFixedParameters = 4u;
#else
  const unsigned int euler3DNumberOfFixedParameters = 3u;
#endif



  sitk::Transform tx;
  EXPECT_TRUE( tx.GetParameters().empty() );
  EXPECT_TRUE( tx.GetFixedParameters().empty() );

  tx = sitk::Transform( 3, sitk::sitkTranslation );
  EXPECT_EQ( tx.GetParameters().size(), 3u );
  EXPECT_TRUE( tx.GetFixedParameters().empty() );
  EXPECT_TRUE(tx.IsLinear());

  tx = sitk::Transform( 2, sitk::sitkScale );
  EXPECT_EQ( tx.GetParameters().size(), 2u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 2u );
  EXPECT_TRUE(tx.IsLinear());

  tx = sitk::Transform( 3, sitk::sitkScaleLogarithmic );
  EXPECT_EQ( tx.GetParameters().size(), 3u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 3u );
  EXPECT_TRUE(tx.IsLinear());

  tx = sitk::Transform( 2, sitk::sitkEuler );
  EXPECT_EQ( tx.GetParameters().size(), 3u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 2u );
  EXPECT_TRUE(tx.IsLinear());

  tx = sitk::Transform( 3, sitk::sitkEuler );
  EXPECT_EQ( tx.GetParameters().size(), 6u );
  EXPECT_EQ( tx.GetFixedParameters().size(), euler3DNumberOfFixedParameters );
  EXPECT_TRUE(tx.IsLinear());

  tx = sitk::Transform( 2, sitk::sitkSimilarity );
  EXPECT_EQ( tx.GetParameters().size(), 4u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 2u );
  EXPECT_TRUE(tx.IsLinear());

  tx = sitk::Transform( 3, sitk::sitkSimilarity );
  EXPECT_EQ( tx.GetParameters().size(), 7u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 3u );
  EXPECT_TRUE(tx.IsLinear());

  tx = sitk::Transform( 3, sitk::sitkQuaternionRigid );
  EXPECT_EQ( tx.GetParameters().size(), 7u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 3u );
  EXPECT_TRUE(tx.IsLinear());

  tx = sitk::Transform( 3, sitk::sitkVersor );
  EXPECT_EQ( tx.GetParameters().size(), 3u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 3u );
  EXPECT_TRUE(tx.IsLinear());

  tx = sitk::Transform( 3, sitk::sitkVersorRigid );
  EXPECT_EQ( tx.GetParameters().size(), 6u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 3u );
  EXPECT_TRUE(tx.IsLinear());

  tx = sitk::Transform( 2, sitk::sitkAffine );
  EXPECT_EQ( tx.GetParameters().size(), 6u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 2u );
  EXPECT_TRUE(tx.IsLinear());

  sitk::Image displacement = sitk::Image( 10, 10, sitk::sitkVectorFloat64 );

  tx =  sitk::Transform ( displacement );
  EXPECT_EQ( tx.GetParameters().size(), 200u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 10u );
  EXPECT_TRUE(!tx.IsLinear());

  displacement = sitk::Image( 10, 10, 10, sitk::sitkVectorFloat64 );

  tx =  sitk::Transform ( displacement );
  EXPECT_EQ( tx.GetParameters().size(), 3000u );
  EXPECT_EQ( tx.GetFixedParameters().size(), 18u );

  tx = sitk::Transform(3,sitk::sitkIdentity);
  tx.SetFixedParameters(std::vector<double>());
  tx.SetParameters(std::vector<double>());
  tx.SetIdentity();
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


TEST(TransformTest, ReadTransformConvert) {

  EXPECT_NO_THROW(sitk::AffineTransform(sitk::ReadTransform( dataFinder.GetFile( "Input/xforms/affine_i_3.txt" ) ) ) );
  EXPECT_NO_THROW(sitk::Transform(sitk::ReadTransform( dataFinder.GetFile( "Input/xforms/composite_i_3.txt" ) ) ) );
  EXPECT_NO_THROW(sitk::Transform(sitk::ReadTransform( dataFinder.GetFile( "Input/xforms/i_3.txt" ) ) ) );
  EXPECT_NO_THROW(sitk::ScaleTransform(sitk::ReadTransform( dataFinder.GetFile( "Input/xforms/scale_i_3.txt" ) ) ) );
  EXPECT_NO_THROW(sitk::TranslationTransform(sitk::ReadTransform( dataFinder.GetFile( "Input/xforms/translation_i_3.txt" ) ) ) );
  EXPECT_NO_THROW(sitk::Transform(sitk::ReadTransform( dataFinder.GetFile( "Input/xforms/quaternion_rigid_i_3.txt" ) ) ) );
  EXPECT_NO_THROW(sitk::Transform(sitk::ReadTransform( dataFinder.GetFile( "Input/xforms/scale_logarithmic_i_3.txt" ) ) ) );
  EXPECT_NO_THROW(sitk::VersorTransform(sitk::ReadTransform( dataFinder.GetFile( "Input/xforms/versor_i_3.txt" ) ) ) );

  std::string filename = dataFinder.GetOutputFile ( "TransformTest.ReadTransformConvert.txt" );
  {
  sitk::AffineTransform tx(2);
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW(tx = sitk::AffineTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 2u);
  }
  {
  sitk::Euler2DTransform tx;
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW(tx = sitk::Euler2DTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 2u);
  }
  {
  sitk::Euler3DTransform tx;
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW(tx = sitk::Euler3DTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 3u);
  }
  {
  sitk::ScaleSkewVersor3DTransform tx;
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW(tx = sitk::ScaleSkewVersor3DTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 3u);
  }
  {
  sitk::ScaleTransform tx(2);
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW( tx = sitk::ScaleTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 2u);
  }
  {
  sitk::ScaleVersor3DTransform tx;
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW(tx = sitk::ScaleVersor3DTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 3u);
  }
  {
  sitk::Similarity2DTransform tx;
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW(tx = sitk::Similarity2DTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 2u);
  }
  {
  sitk::Similarity3DTransform tx;
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW(tx = sitk::Similarity3DTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 3u);
  }
  {
  sitk::TranslationTransform tx(3);
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW(tx = sitk::TranslationTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 3u);
  }
  {
  sitk::VersorRigid3DTransform tx;
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW(tx = sitk::VersorRigid3DTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 3u);
  }
  {
  sitk::VersorTransform tx;
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW(tx = sitk::VersorTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 3u);
  }
  {
  sitk::DisplacementFieldTransform tx(2);
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW( tx = sitk::DisplacementFieldTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 2u);
  }
  {
  sitk::DisplacementFieldTransform tx(2);
  tx.SetSmoothingGaussianOnUpdate();
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW( tx = sitk::DisplacementFieldTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 2u);
  }
  {
  sitk::BSplineTransform tx(2);
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW( tx = sitk::BSplineTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 2u);
  EXPECT_EQ(tx.GetOrder(), 3u);
  }
  {
  sitk::BSplineTransform tx(3);
  sitk::WriteTransform(tx, filename);
  EXPECT_NO_THROW( tx = sitk::BSplineTransform( sitk::ReadTransform(filename) ) );
  EXPECT_EQ(tx.GetDimension(), 3u);
  EXPECT_EQ(tx.GetOrder(), 3u);
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


TEST(TransformTest,AffineTransform)
{
  // test AffineTransform

  const std::vector<double> zeros(3,0.0);
  const std::vector<double> trans2d = v2(2.2,2.2);
  const std::vector<double> trans3d = v3(3.3,3.3,3.3);

  const std::vector<double> center2d(2, 10);
  const std::vector<double> center3d(3, 20);

  const std::vector<double> scale2d = v2(1,2);
  const std::vector<double> scale3d = v3(1,1.2,1.3);

  nsstd::auto_ptr<sitk::AffineTransform> tx;

  // 2d
  EXPECT_NO_THROW( tx.reset( new sitk::AffineTransform(2) ) );
  std::cout << tx->ToString() << std::endl;
  EXPECT_EQ( tx->GetParameters().size(), 6u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx->GetMatrix(), v4(1.0,0.0, 0.0,1.0) );

  EXPECT_EQ( tx->SetTranslation( trans2d ).GetTranslation(), trans2d );
  EXPECT_EQ( tx->SetCenter( center2d ).GetCenter(), center2d );

  tx.reset( new sitk::AffineTransform(2) );
  tx->Scale( v2(1,2));
  EXPECT_VECTOR_DOUBLE_NEAR( tx->TransformPoint( v2(0,0) ), v2(0,0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx->TransformPoint( v2(1,1) ), v2(1,2),1e-15);
  tx->Scale( 2 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx->TransformPoint( v2(0,0) ), v2(0,0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx->TransformPoint( v2(1,1) ), v2(2,4),1e-15);

  tx.reset( new sitk::AffineTransform(2) );
  tx->Shear(0,1, 2.0);
  EXPECT_VECTOR_DOUBLE_NEAR( tx->TransformPoint( v2(0,0) ), v2(0,0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx->TransformPoint( v2(1,2) ), v2(5,2),1e-15);

  tx.reset( new sitk::AffineTransform(2) );
  tx->Translate(v2(10.0,-10.0));
  EXPECT_VECTOR_DOUBLE_NEAR( tx->TransformPoint( v2(0,0) ), v2(10.0,-10.0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx->TransformPoint( v2(1,2) ), v2(11.0,-8.0),1e-15);

  tx.reset( new sitk::AffineTransform(2) );
  tx->Rotate(0,1,itk::Math::pi_over_2);
  EXPECT_VECTOR_DOUBLE_NEAR( tx->TransformPoint( v2(0,0) ), v2(0,0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx->TransformPoint( v2(1,2) ), v2(2,-1),1e-14);

  sitk::AffineTransform tx0(v4(1.0,2.0,3.0,4.0), v2(5.0,6.0));
  EXPECT_EQ( tx0.GetMatrix(), v4(1.0,2.0,3.0,4.0) );
  EXPECT_EQ( tx0.GetTranslation(), v2(5.0,6.0) );

  // 3d
  EXPECT_NO_THROW( tx.reset( new sitk::AffineTransform(3) ) );
  EXPECT_EQ( tx->GetParameters().size(), 12u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 3u );

  EXPECT_EQ( tx->SetTranslation( trans3d ).GetTranslation(), trans3d );
  EXPECT_EQ( tx->SetCenter( center3d ).GetCenter(), center3d );

  sitk::AffineTransform tx00(v9(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0), v3(10.0,11.0,12.0));
  EXPECT_EQ( tx00.GetMatrix(), v9(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0) );
  EXPECT_EQ( tx00.GetTranslation(), v3(10.0,11.0,12.0) );

  // copy and assignment
  sitk::AffineTransform tx1(*tx);
  EXPECT_EQ( tx1.GetDimension(), 3u );
  EXPECT_EQ( tx1.GetCenter(), center3d );
  EXPECT_EQ( tx1.GetParameters(), tx->GetParameters() );
  EXPECT_EQ( tx1.GetFixedParameters(), tx->GetFixedParameters() );


  tx1 = sitk::AffineTransform(2);
  EXPECT_EQ( tx1.GetDimension(), 2u );
  EXPECT_EQ( tx1.GetParameters().size(), 6u );
  EXPECT_EQ( tx1.GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx1.GetCenter(), std::vector<double>(2, 0.0) );
  EXPECT_EQ( tx1.GetTranslation(), std::vector<double>(2, 0.0) );

  // copy on write

  // exceptions
  EXPECT_THROW( sitk::AffineTransform(1), sitk::GenericException );
  EXPECT_THROW( sitk::AffineTransform(4), sitk::GenericException );
  EXPECT_THROW( tx->SetParameters( std::vector<double>(11) ), sitk::GenericException );
  EXPECT_NO_THROW( tx->SetParameters( std::vector<double>(13) ) );
  EXPECT_THROW( tx->SetFixedParameters( std::vector<double>(2) ), sitk::GenericException );
  EXPECT_NO_THROW( tx->SetFixedParameters( std::vector<double>(4) ) );

}


TEST(TransformTest,AffineTransform_3DPoints)
{
  // Test Affine by transforming some points
  sitk::AffineTransform tx(3);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(1.0,1.0,1.0),1e-15 );

  tx.Translate(v3(1.0,2.0,3.0));
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(1.0,2.0,3.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(2.0,3.0,4.0),1e-15 );

  // apply transform after and inverse before
  tx.Scale(v3(2.0,2.0,2.0),false).Scale(.5,true);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(2.0,4.0,6.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(3.0,5.0,7.0),1e-15 );

  tx = sitk::AffineTransform(3);
  tx.Translate(v3(1.0,2.0,3.0));
  tx.Shear(0,1,1.0, false).Shear(0,1,-1.0,true);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(3.0,2.0,3.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(4.0,3.0,4.0),1e-15 );

  tx = sitk::AffineTransform(3);
  tx.Translate(v3(1.0,2.0,3.0));
  tx.Rotate(0,1,1.0, false).Rotate(0,1,-1.0);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(1.0,2.0,3.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,0.0,1.0) ), v3(2.0,2.0,4.0),1e-15 );

  // inverse
  tx.SetInverse();
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,2.0,3.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(2.0,2.0,4.0) ), v3(1.0,0.0,1.0),1e-15 );
  EXPECT_NO_THROW(tx.GetCenter());

  tx.SetIdentity();
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(1.0,1.0,1.0),1e-15 );

  sitk::AffineTransform tx3(tx.GetInverse());
  EXPECT_VECTOR_DOUBLE_NEAR( tx3.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx3.TransformPoint( v3(1.0,1.0,1.0) ), v3(1.0,1.0,1.0),1e-15 );

}

TEST(TransformTest,AffineTransform_Matrix)
{
  // Test the Set/Get Matrix
  sitk::AffineTransform tx(3);
  EXPECT_EQ( v9(1.0,0.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0), tx.GetMatrix() );
  tx.SetMatrix( v9(1.0,1.0,0.0, 0.0,2.0,0.0, 0.0,0.0,3.0) );
  EXPECT_EQ( v9(1.0,1.0,0.0, 0.0,2.0,0.0, 0.0,0.0,3.0), tx.GetMatrix() );

  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,0.0) ), v3(2.0,2.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,1.0,1.0) ), v3(1.0,2.0,3.0),1e-15 );

  tx.SetMatrix( v9(1.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,1.0) );
  EXPECT_THROW(tx.GetInverse(), sitk::GenericException);
  EXPECT_TRUE( !tx.SetInverse() );
}
TEST(TransformTest,BSplineTransform)
{ // test BSplineTransform


  nsstd::auto_ptr<sitk::BSplineTransform> tx(new sitk::BSplineTransform(2));
  std::cout << tx->ToString() << std::endl;
  EXPECT_EQ( tx->GetParameters().size(), 32u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 10u );
  EXPECT_EQ( tx->GetTransformDomainDirection(), v4(1.0,0.0,0.0,1.0) );
  EXPECT_EQ( tx->GetTransformDomainMeshSize(), std::vector<unsigned int>(2,1u) );
  EXPECT_EQ( tx->GetTransformDomainOrigin(), v2(0.0,0.0) );
  EXPECT_EQ( tx->GetTransformDomainPhysicalDimensions(), v2(1.0,1.0) );

  tx.reset(new sitk::BSplineTransform(3));
  EXPECT_EQ( tx->GetParameters().size(), 192u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 18u );

  tx.reset(new sitk::BSplineTransform(2));
  EXPECT_EQ( tx->SetTransformDomainDirection(v4(-1.0,0.0,0.0,-1.0)).GetTransformDomainDirection(), v4(-1.0,0.0,0.0,-1.0) );
  EXPECT_EQ( tx->SetTransformDomainOrigin( v2(1.1,1.2) ).GetTransformDomainOrigin(), v2(1.1,1.2) );

  // copy constructor
  sitk::BSplineTransform tx1( *(tx.get()) );
  EXPECT_EQ( tx1.GetParameters().size(), 32u );
  EXPECT_EQ( tx1.GetFixedParameters().size(), 10u );
  EXPECT_EQ( tx1.GetTransformDomainDirection(), v4(-1.0,0.0,0.0,-1.0) );
  EXPECT_EQ( tx1.GetTransformDomainMeshSize(), std::vector<unsigned int>(2,1u) );
  EXPECT_EQ( tx1.GetTransformDomainOrigin(), v2(1.1,1.2) );
  EXPECT_EQ( tx1.GetTransformDomainPhysicalDimensions(), v2(1.0,1.0) );

  sitk::BSplineTransform tx2(2);

  // assignment operator
  tx1 = tx2;
  EXPECT_EQ( tx1.GetDimension(), 2u );
  EXPECT_EQ( tx1.GetTransformDomainOrigin(), v2(0.0,0.0) );

  // copy on write
  tx1.SetTransformDomainOrigin( v2(1.3,1.4) );
  EXPECT_EQ( tx1.GetTransformDomainOrigin(), v2(1.3,1.4) );
  EXPECT_EQ( tx2.GetTransformDomainOrigin(), v2(0.0,0.0) );

  // todo test other attributes...

  sitk::Transform tx3( *tx );
  tx.reset();
  EXPECT_EQ( tx3.GetParameters().size(), 32u );
  EXPECT_EQ( tx3.GetFixedParameters().size(), 10u );

  tx.reset( new sitk::BSplineTransform(2));

  // test member setters/getters
  EXPECT_EQ( tx->SetTransformDomainDirection(v4(0.0,1.0,1.0,0.0)).GetTransformDomainDirection(), v4(0.0,1.0,1.0,0.0) );
  EXPECT_EQ( tx->SetTransformDomainMeshSize(std::vector<unsigned int>(2,4u)).GetTransformDomainMeshSize(), std::vector<unsigned int>(2,4u) );
  EXPECT_EQ( tx->SetTransformDomainOrigin( v2(2.0,2.0) ).GetTransformDomainOrigin(), v2(2.0,2.0) );
  EXPECT_EQ( tx->SetTransformDomainPhysicalDimensions(v2(4.0,4.0)).GetTransformDomainPhysicalDimensions(), v2(4.0,4.0) );

  std::vector<sitk::Image> coefficientImages = tx->GetCoefficientImages();
  ASSERT_EQ( 2u, coefficientImages.size() );
  EXPECT_EQ( std::vector<unsigned int>(2, 7u), coefficientImages[0].GetSize() );
  EXPECT_EQ( std::vector<unsigned int>(2, 7u), coefficientImages[1].GetSize() );

  EXPECT_NO_THROW(tx->SetIdentity());
  EXPECT_EQ( tx3.GetParameters(), std::vector<double>(32,0.0));
  tx.reset( new sitk::BSplineTransform(2));
  EXPECT_NO_THROW(tx->SetIdentity());

  // no inverse
  EXPECT_TRUE(!tx->SetInverse());
  EXPECT_NO_THROW(tx->GetOrder());
  EXPECT_THROW(tx->GetInverse(),sitk::GenericException);
}

TEST(TransformTest,BSplineTransform_order)
{
  // test features with bspline order
  EXPECT_THROW(sitk::BSplineTransform(4), sitk::GenericException);
  EXPECT_THROW(sitk::BSplineTransform(2,4), sitk::GenericException);
  EXPECT_THROW(sitk::BSplineTransform(2,20), sitk::GenericException);
  EXPECT_THROW(sitk::BSplineTransform(3,4), sitk::GenericException);
  EXPECT_THROW(sitk::BSplineTransform(3,99), sitk::GenericException);

  nsstd::auto_ptr<sitk::BSplineTransform> tx;
  EXPECT_NO_THROW(tx.reset(new sitk::BSplineTransform(3)));
  EXPECT_EQ(3u, tx->GetOrder());
  EXPECT_NO_THROW( tx.reset(new sitk::BSplineTransform(3,0)));
  EXPECT_EQ(0u, tx->GetOrder());
  EXPECT_EQ(v3(0,0,0), tx->TransformPoint(v3(0,0,0)));
  EXPECT_NO_THROW(tx.reset(new sitk::BSplineTransform(3,1)));
  EXPECT_EQ(1u, tx->GetOrder());
  EXPECT_EQ(v3(0,0,0), tx->TransformPoint(v3(0,0,0)));
  EXPECT_NO_THROW(tx.reset(new sitk::BSplineTransform(3,2)));
  EXPECT_EQ(2u, tx->GetOrder());
  EXPECT_EQ(v3(0,0,0), tx->TransformPoint(v3(0,0,0)));
  EXPECT_NO_THROW(tx.reset(new sitk::BSplineTransform(3,3)));
  EXPECT_EQ(3u, tx->GetOrder());
  EXPECT_EQ(v3(0,0,0), tx->TransformPoint(v3(0,0,0)));

  sitk::BSplineTransform tx1(*tx);
  EXPECT_EQ(3u, tx1.GetOrder());

  tx.reset(new sitk::BSplineTransform(3,1));
  EXPECT_EQ(3u, tx1.GetOrder());
  tx1 = *tx;
  EXPECT_EQ(1u, tx1.GetOrder());

  // deep copy
  tx1.SetParameters(tx1.GetParameters());
  EXPECT_EQ(1u, tx1.GetOrder());
}



TEST(TransformTest,DisplacementFieldTransform)
{
  // test DisplacementFieldTransform
  const std::vector<double> center(3,1.1);
  const std::vector<double> zeros(3,0.0);
  const std::vector<double> trans(3, 2.2);

  const std::vector<unsigned int> size(2,10u);
  const std::vector<unsigned int> idx(2,1u);

  nsstd::auto_ptr<sitk::DisplacementFieldTransform> tx(new sitk::DisplacementFieldTransform(2));
  std::cout << tx->ToString() << std::endl;
  EXPECT_EQ( tx->GetParameters().size(), 0u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 10u );
  EXPECT_EQ( tx->GetDimension(), 2u );

  // copy constructor
  sitk::DisplacementFieldTransform tx1( *tx );
  EXPECT_EQ( tx1.GetParameters().size(), 0u );
  EXPECT_EQ( tx1.GetFixedParameters().size(), 10u );
  EXPECT_EQ( tx1.GetDimension(), 2u );

  sitk::DisplacementFieldTransform tx2(3);



  // assignment operator
  tx1 = tx2;
  EXPECT_EQ( tx1.GetParameters().size(), 0u );
  EXPECT_EQ( tx1.GetFixedParameters().size(), 18u );
  EXPECT_EQ( tx1.GetDimension(), 3u );


  sitk::Image disImage(size, sitk::sitkVectorFloat64);

  sitk::DisplacementFieldTransform tx3(disImage);
  EXPECT_EQ( tx3.GetDimension(), 2u );
  EXPECT_EQ( tx3.GetParameters().size(), 200u );
  EXPECT_EQ( tx3.GetFixedParameters().size(), 10u );
  EXPECT_EQ( tx3.GetFixedParameters()[0], 10.0 );

  EXPECT_EQ( disImage.GetSize()[0], 0u);
  EXPECT_EQ( disImage.GetSize()[1], 0u);

  tx3.SetSmoothingGaussianOnUpdate();
  tx3.SetSmoothingBSplineOnUpdate();
  tx3.SetSmoothingOff();


  // test conversion methods with initial values
  tx1 = sitk::DisplacementFieldTransform(2);
  tx1.SetSmoothingGaussianOnUpdate();
  tx1.SetSmoothingBSplineOnUpdate();
  tx1.SetSmoothingOff();

  const double fixedParametersArray[] = {5.0, 5.0, 0.1, 0.2, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0};
  std::vector<double> fixedParameters(fixedParametersArray, fixedParametersArray+10);

  tx1.SetFixedParameters(fixedParameters);
  EXPECT_EQ( tx1.GetFixedParameters()[0], 5.0 );

  sitk::Image disImage2 = tx1.GetDisplacementField();
  EXPECT_EQ( disImage2.GetSize()[0], 5u);
  EXPECT_EQ( disImage2.GetOrigin()[1], 0.2);
  EXPECT_EQ( disImage2.GetSpacing()[1], 1.0);

  // EXPECT_EQ( tx1.GetInterpolator(), sitk::Linear );
  tx1.SetInterpolator( sitk::sitkNearestNeighbor );
  // EXPECT_EQ( tx1.GetInterpolator(), sitk::NearestNeighbor );
  tx1.SetInterpolator( sitk::sitkLinear );
  // EXPECT_EQ( tx1.GetInterpolator(), sitk::Linear );
  EXPECT_THROW( tx1.SetInterpolator( sitk::sitkBSpline ), sitk::GenericException );

}

TEST(TransformTest,DisplacementFieldTransform_CopyOnWrite)
{
  const std::vector<unsigned int> size(2,10u);

  sitk::DisplacementFieldTransform tx(2);
  sitk::DisplacementFieldTransform copy_tx = tx;

  sitk::Image disImage(size, sitk::sitkVectorFloat64);

  // check copy with initial state
  EXPECT_EQ( tx.GetFixedParameters()[0], 0.0 );
  tx.SetSmoothingOff();
  EXPECT_EQ( tx.GetFixedParameters()[0], 0.0 );
  EXPECT_EQ( copy_tx.GetFixedParameters()[0], 0.0 );


  // check make unique with set displacement
  tx = sitk::DisplacementFieldTransform(2);
  copy_tx = tx;

  EXPECT_EQ( tx.GetFixedParameters()[0], 0.0 );
  EXPECT_EQ( copy_tx.GetFixedParameters()[0], 0.0 );
  tx.SetDisplacementField( disImage );
  EXPECT_EQ( tx.GetFixedParameters()[0], 10.0 );
  EXPECT_EQ( copy_tx.GetFixedParameters()[0], 0.0 );

}

TEST(TransformTest,DisplacementFieldTransform_Points)
{
  const std::vector<unsigned int> size(3,5u);
  sitk::Image disImage(size, sitk::sitkVectorFloat64);

  // Test displacement field transform by transforming some points
  sitk::DisplacementFieldTransform tx(disImage);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0), 1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(1.0,1.0,1.0),1e-15 );

  const std::vector<unsigned int> idx(2,0u);

  disImage = sitk::Image( std::vector<unsigned int>(2,5u), sitk::sitkVectorFloat64 );
  disImage.SetPixelAsVectorFloat64( idx, v2(0.5,0.5) );
  tx = sitk::DisplacementFieldTransform(disImage);

  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v2(0.0,0.0) ), v2(0.5,0.5), 1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v2(0.5, 0.0) ), v2(0.75,0.25), 1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v2(0.5, 0.5) ), v2(0.625,0.625), 1e-15 );


  tx.SetInterpolator( sitk::sitkNearestNeighbor );


  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v2(0.0,0.0) ), v2(0.5,0.5), 1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v2(0.4, 0.4) ), v2(0.9,0.9), 1e-15 );

  // 0.5 is a difficult case to nearest neighbor does it, it rounds up
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v2(0.5, 0.5) ), v2(0.5,0.5), 1e-15 );

}

TEST(TransformTest,Euler2DTransform)
{
  // test Euler2DTransform

  const std::vector<double> center(2,1.1);
  const std::vector<double> zeros(2,0.0);
  const std::vector<double> trans(2, 2.2);

  nsstd::auto_ptr<sitk::Euler2DTransform> tx(new sitk::Euler2DTransform());
  std::cout << tx->ToString() << std::endl;
  EXPECT_EQ( tx->GetParameters().size(), 3u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx->GetMatrix(), v4(1.0,0.0, 0.0,1.0) );


  tx.reset( new sitk::Euler2DTransform(center));
  EXPECT_EQ( tx->GetParameters().size(), 3u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx->GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx->GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx->GetCenter(), center );


  tx.reset( new sitk::Euler2DTransform(center, 1.0 ));
  EXPECT_EQ( tx->GetParameters().size(), 3u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx->GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx->GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx->GetParameters()[0], 1.0 );
  EXPECT_EQ( tx->GetParameters()[1], 0.0 );
  EXPECT_EQ( tx->GetParameters()[2], 0.0 );
  EXPECT_EQ( tx->GetCenter(), center );

  // copy constructor
  sitk::Euler2DTransform tx1( *(tx.get()) );
  EXPECT_EQ( tx1.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx1.GetParameters()[0], 1.0 );
  EXPECT_EQ( tx1.GetCenter(), center );

  sitk::Euler2DTransform tx2;

  // assignment operator
  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );

  // copy on write
  tx1.SetFixedParameters(center);
  EXPECT_EQ( tx1.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx2.GetFixedParameters()[0], 0.0 );
  EXPECT_EQ( tx2.GetFixedParameters()[1], 0.0 );
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx2.GetCenter(), zeros );
  tx1.SetCenter(center);
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetTranslation(), zeros );
  EXPECT_EQ( tx2.GetTranslation(), zeros );
  tx1.SetTranslation(trans);
  EXPECT_EQ( tx1.GetTranslation(), trans );
  EXPECT_EQ( tx2.GetTranslation(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetAngle(), 0.0 );
  EXPECT_EQ( tx2.GetAngle(), 0.0 );
  tx1.SetAngle(0.1);
  EXPECT_EQ( tx1.GetAngle(), 0.1 );
  EXPECT_EQ( tx2.GetAngle(), 0.0 );

  sitk::Transform tx3( *tx );
  tx.reset();

  EXPECT_EQ( tx3.GetParameters().size(), 3u );
  EXPECT_EQ( tx3.GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx3.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx3.GetParameters()[0], 1.0 );
  EXPECT_EQ( tx3.GetParameters()[1], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[2], 0.0 );


  tx.reset( new sitk::Euler2DTransform());

  // test member setters/getters
  EXPECT_EQ(tx->GetCenter(), zeros);
  EXPECT_EQ(tx->SetCenter(center).GetCenter(), center);

  EXPECT_EQ(tx->GetAngle(), 0.0);
  EXPECT_EQ(tx->SetAngle(1.0).GetAngle(), 1.0);

  sitk::Euler2DTransform etx;
  etx.SetCenter(v2(1.0,1.0));
  etx.SetAngle(itk::Math::pi);
  EXPECT_VECTOR_DOUBLE_NEAR( etx.TransformPoint( v2(1,1) ), v2(1,1),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( etx.TransformPoint( v2(0,0) ), v2(2,2),1e-15);

  etx.SetTranslation(v2(-1.0,-2.0));

  EXPECT_VECTOR_DOUBLE_NEAR( etx.TransformPoint( v2(1,1) ), v2(0,-1),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( etx.TransformPoint( v2(0,0) ), v2(1,0),1e-15);

  etx.SetIdentity();
  EXPECT_VECTOR_DOUBLE_NEAR( etx.TransformPoint( v2(1,1) ), v2(1,1),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( etx.TransformPoint( v2(0,0) ), v2(0,0),1e-15);

  // inverse
  EXPECT_TRUE(etx.SetInverse());
  EXPECT_NO_THROW(etx.GetAngle());

  sitk::Euler2DTransform etx2(etx.GetInverse());
  EXPECT_NO_THROW(etx2.GetAngle());

  etx.SetMatrix(v4(1.0,0.0, 0.0,1.0));
  EXPECT_EQ( etx.GetMatrix(), v4(1.0,0.0, 0.0,1.0) );
  EXPECT_EQ( etx.GetAngle(), 0.0 );

  etx.SetMatrix(v4(0.0,-1.0, 1.0,0.0));
  EXPECT_EQ( etx.GetMatrix(), v4(0.0,-1.0, 1.0,0.0) );
  EXPECT_DOUBLE_EQ(etx.GetAngle(), itk::Math::pi/2.0);

}


TEST(TransformTest,Euler3DTransform)
{
  // test Euler3DTransform

  const std::vector<double> center(3,1.1);
  const std::vector<double> zeros(3,0.0);
  const std::vector<double> trans(3, 2.2);

#if (ITK_VERSION_MAJOR*100+ITK_VERSION_MINOR) >= 410
  const unsigned int numberOfFixedParameters = 4u;
#else
  const unsigned int numberOfFixedParameters =  numberOfFixedParameters;
#endif

  nsstd::auto_ptr<sitk::Euler3DTransform> tx(new sitk::Euler3DTransform());
  std::cout << tx->ToString() << std::endl;
  EXPECT_EQ( tx->GetParameters().size(), 6u );
  EXPECT_EQ( tx->GetFixedParameters().size(),  numberOfFixedParameters );
  EXPECT_EQ( tx->GetMatrix(), v9(1.0,0.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0) );


  tx.reset( new sitk::Euler3DTransform(center));
  EXPECT_EQ( tx->GetParameters().size(), 6u );
  EXPECT_EQ( tx->GetFixedParameters().size(),  numberOfFixedParameters );
  EXPECT_EQ( tx->GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx->GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx->GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx->GetCenter(), center );


  tx.reset( new sitk::Euler3DTransform(center, 1.0, 2.0, 3.0));
  EXPECT_EQ( tx->GetParameters().size(), 6u );
  EXPECT_EQ( tx->GetFixedParameters().size(),  numberOfFixedParameters );
  EXPECT_EQ( tx->GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx->GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx->GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx->GetParameters()[0], 1.0 );
  EXPECT_EQ( tx->GetParameters()[1], 2.0 );
  EXPECT_EQ( tx->GetParameters()[2], 3.0 );
  EXPECT_EQ( tx->GetCenter(), center );

  // copy constructor
  sitk::Euler3DTransform tx1( *(tx.get()) );
  EXPECT_EQ( tx1.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx1.GetParameters()[0], 1.0 );
  EXPECT_EQ( tx1.GetParameters()[1], 2.0 );
  EXPECT_EQ( tx1.GetParameters()[2], 3.0 );
  EXPECT_EQ( tx1.GetCenter(), center );

  sitk::Euler3DTransform tx2;

  // assignment operator
  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );

  // copy on write
  std::vector<double> fixed = center;
#if (ITK_VERSION_MAJOR*100+ITK_VERSION_MINOR) >= 410
  fixed.push_back(0.0);
#endif
  tx1.SetFixedParameters(fixed);//
  EXPECT_EQ( tx1.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx2.GetFixedParameters()[0], 0.0 );
  EXPECT_EQ( tx2.GetFixedParameters()[1], 0.0 );
  EXPECT_EQ( tx2.GetFixedParameters()[2], 0.0 );
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx2.GetCenter(), zeros );
  tx1.SetCenter(center);
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetTranslation(), zeros );
  EXPECT_EQ( tx2.GetTranslation(), zeros );
  tx1.SetTranslation(trans);
  EXPECT_EQ( tx1.GetTranslation(), trans );
  EXPECT_EQ( tx2.GetTranslation(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetAngleX(), 0.0 );
  EXPECT_EQ( tx2.GetAngleX(), 0.0 );
  tx1.SetRotation(.1,.2,.3);
  EXPECT_EQ( tx1.GetAngleX(), 0.1 );
  EXPECT_EQ( tx2.GetAngleX(), 0.0 );

  sitk::Transform tx3( *tx );
  tx.reset();

  EXPECT_EQ( tx3.GetParameters().size(), 6u );
  EXPECT_EQ( tx3.GetFixedParameters().size(),  numberOfFixedParameters );
  EXPECT_EQ( tx3.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx3.GetParameters()[0], 1.0 );
  EXPECT_EQ( tx3.GetParameters()[1], 2.0 );
  EXPECT_EQ( tx3.GetParameters()[2], 3.0 );

  tx.reset( new sitk::Euler3DTransform());

  // test member setters/getters
  EXPECT_EQ(tx->GetCenter(), zeros);
  tx->SetCenter(center);
  EXPECT_EQ(tx->GetCenter(), center);

  EXPECT_EQ(tx->GetAngleX(), 0.0);
  EXPECT_EQ(tx->GetAngleY(), 0.0);
  EXPECT_EQ(tx->GetAngleZ(), 0.0);
  tx->SetRotation(1.0,2.0,3.0);
  EXPECT_EQ(tx->GetAngleX(), 1.0);
  EXPECT_EQ(tx->GetAngleY(), 2.0);
  EXPECT_EQ(tx->GetAngleZ(), 3.0);

  EXPECT_EQ(tx->GetTranslation(), zeros);
  tx->SetTranslation(trans);
  EXPECT_EQ(tx->GetTranslation(),trans);

  EXPECT_FALSE(tx->GetComputeZYX());
  tx->SetComputeZYX(true);
  EXPECT_TRUE(tx->GetComputeZYX());
  tx->ComputeZYXOff();
  EXPECT_FALSE(tx->GetComputeZYX());
  tx->ComputeZYXOn();
  EXPECT_TRUE(tx->GetComputeZYX());

  // inverse
  EXPECT_TRUE(tx->SetInverse());
  EXPECT_NO_THROW(tx->GetCenter());

  tx.reset( new sitk::Euler3DTransform());
  tx->SetMatrix( v9(0.0,-1.0,0.0, 1.0,0.0,0.0, 0.0,0.0,1.0) );
  std::cout << tx->ToString();
  EXPECT_VECTOR_DOUBLE_NEAR( tx->GetMatrix(), v9(0.0,-1.0,0.0, 1.0,0.0,0.0, 0.0,0.0,1.0), 1e-15 );
  EXPECT_DOUBLE_EQ(tx->GetAngleX(), 0.0);
  EXPECT_DOUBLE_EQ(tx->GetAngleY(), 0.0);
  EXPECT_DOUBLE_EQ(tx->GetAngleZ(),  itk::Math::pi/2.0);
}


TEST(TransformTest,Similarity2DTransform)
{
  // test Similarity2DTransform
  const std::vector<double> center(2,1.1);
  const std::vector<double> zeros(2,0.0);
  const std::vector<double> trans(2, 2.2);

  nsstd::auto_ptr<sitk::Similarity2DTransform> tx(new sitk::Similarity2DTransform());
  std::cout << tx->ToString() << std::endl;
  EXPECT_EQ( tx->GetParameters().size(), 4u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx->GetTranslation(), v2(0.0,0.0) );
  EXPECT_EQ( tx->GetScale(), 1.0);
  EXPECT_EQ( tx->GetAngle(), 0.0 );
  EXPECT_EQ( tx->GetMatrix(), v4(1.0,0.0, 0.0,1.0) );

  EXPECT_NO_THROW( tx.reset( new sitk::Similarity2DTransform(0.5, -1.0, v2(1.1,1.1), center) ) );
  EXPECT_EQ( tx->GetCenter(), center );
  EXPECT_EQ( tx->GetAngle(), -1.0 );
  EXPECT_EQ( tx->GetTranslation(), v2(1.1,1.1) );
  EXPECT_EQ( tx->GetScale(), 0.5 );

  EXPECT_THROW( sitk::Similarity2DTransform( 1.0, -1.0, v2(1.1,1.1), std::vector<double>(1, 0.0) ), sitk::GenericException );
  EXPECT_THROW( sitk::Similarity2DTransform( 1.0, -1.0, std::vector<double>(1, 0.0), center ), sitk::GenericException );


  EXPECT_EQ( tx->SetScale(2.0).GetScale(), 2.0 );
  EXPECT_EQ( tx->SetTranslation(trans).GetTranslation(), trans );
  EXPECT_EQ( tx->SetCenter(center).GetCenter(), center );
  EXPECT_EQ( tx->SetAngle(1.0).GetAngle(), 1.0 );


  // copy constructor
  sitk::Similarity2DTransform tx1( *(tx.get()) );
  EXPECT_EQ( tx->GetParameters().size(), 4u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx1.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx1.GetParameters()[0], 2.0 ); // scale
  EXPECT_EQ( tx1.GetParameters()[1], 1.0 ); // angle
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx1.GetTranslation(), trans );

  sitk::Similarity2DTransform tx2;

  // assignment operator
  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx1.GetParameters().size(), 4u );
  EXPECT_EQ( tx1.GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx1.GetTranslation(), zeros );
  EXPECT_EQ( tx1.GetScale(), 1.0);
  EXPECT_EQ( tx1.GetAngle(), 0.0);


  // copy on write
  tx1.SetFixedParameters(center);
  EXPECT_EQ( tx1.GetCenter(), center);
  EXPECT_EQ( tx1.GetFixedParameters(), center );
  EXPECT_EQ( tx2.GetFixedParameters(), zeros );
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx2.GetCenter(), zeros );
  tx1.SetCenter(center);
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetTranslation(), zeros );
  EXPECT_EQ( tx2.GetTranslation(), zeros );
  tx1.SetTranslation(trans);
  EXPECT_EQ( tx1.GetTranslation(), trans );
  EXPECT_EQ( tx2.GetTranslation(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetScale(), 1.0 );
  EXPECT_EQ( tx2.GetScale(), 1.0 );
  tx1.SetScale(2.0);
  EXPECT_EQ( tx1.GetScale(), 2.0 );
  EXPECT_EQ( tx2.GetScale(), 1.0 );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetAngle(), 0.0 );
  EXPECT_EQ( tx2.GetAngle(), 0.0 );
  tx1.SetAngle( itk::Math::pi );
  EXPECT_NEAR( tx1.GetAngle(),  itk::Math::pi, 1e-15 );
  EXPECT_EQ( tx2.GetAngle(), 0.0 );

  sitk::Transform tx3( *tx );
  tx.reset();

  EXPECT_EQ( tx3.GetParameters().size(), 4u );
  EXPECT_EQ( tx3.GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx3.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx3.GetParameters()[0], 2.0 );
  EXPECT_EQ( tx3.GetParameters()[1], 1.0 );
  EXPECT_EQ( tx3.GetParameters()[2], 2.2 );
  EXPECT_EQ( tx3.GetParameters()[3], 2.2 );

  // inverse
  EXPECT_TRUE(tx1.SetInverse());
  EXPECT_NO_THROW(tx1.GetAngle());


  tx1.SetMatrix(v4(1.0,0.0, 0.0,1.0));
  EXPECT_EQ( tx1.GetMatrix(), v4(1.0,0.0, 0.0,1.0) );
  EXPECT_EQ( tx1.GetAngle(), 0.0 );

  tx1.SetMatrix(v4(0.0,-1.0, 1.0,0.0));
  EXPECT_EQ( tx1.GetMatrix(), v4(0.0,-1.0, 1.0,0.0) );
  EXPECT_DOUBLE_EQ(tx1.GetAngle(), itk::Math::pi/2.0);
}


TEST(TransformTest,ScaleTransform)
{
  // test ScaleTransform
  const std::vector<double> center(3,1.1);
  const std::vector<double> zeros(3,0.0);


  nsstd::auto_ptr<sitk::ScaleTransform> tx(new sitk::ScaleTransform(2));
  std::cout << tx->ToString() << std::endl;
  ASSERT_EQ( tx->GetParameters().size(), 2u );
  ASSERT_EQ( tx->GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx->GetScale(), v2(1.0,1.0) );
  EXPECT_EQ( tx->GetCenter(), v2(0.0,0.0) );
  EXPECT_EQ( tx->GetMatrix(), v4(1.0,0.0,0.0,1.0) );

  EXPECT_EQ( tx->SetScale(v2(2.0,3.0)).GetScale(), v2(2.0,3.0) );
  EXPECT_EQ( tx->SetCenter(v2(1.2,1.2)).GetCenter(), v2(1.2,1.2) );

  // copy constructor
  sitk::ScaleTransform tx1( *(tx.get()) );
  EXPECT_EQ( tx1.GetFixedParameters()[0], 1.2 );
  EXPECT_EQ( tx1.GetFixedParameters()[1], 1.2 );
  EXPECT_EQ( tx1.GetParameters()[0], 2.0 ); // scale x
  EXPECT_EQ( tx1.GetParameters(), tx->GetParameters() );
  EXPECT_EQ( tx1.GetCenter(), v2(1.2,1.2) );

  sitk::ScaleTransform tx2(3);

  // assignment operator
  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  ASSERT_EQ( tx1.GetParameters().size(), 3u );
  ASSERT_EQ( tx1.GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx1.GetScale(), v3(1.0,1.0,1.0) );


  // copy on write
  tx1.SetFixedParameters(center);
  EXPECT_EQ( tx1.GetCenter(), center);
  EXPECT_EQ( tx2.GetCenter(), zeros );
  EXPECT_EQ( tx1.GetFixedParameters(), center );
  EXPECT_EQ( tx2.GetFixedParameters(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx2.GetCenter(), zeros );
  tx1.SetCenter(center);
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetScale(), v3(1.0,1.0,1.0) );
  EXPECT_EQ( tx2.GetScale(), v3(1.0,1.0,1.0) );
  tx1.SetScale(v3(3.0,2.0,1.0));
  EXPECT_EQ( tx1.GetScale(), v3(3.0,2.0,1.0) );
  EXPECT_EQ( tx2.GetScale(), v3(1.0,1.0,1.0) );


  sitk::Transform tx3( *tx );
  tx.reset();

  ASSERT_EQ( tx3.GetParameters().size(), 2u );
  ASSERT_EQ( tx3.GetFixedParameters().size(), 2u );
  EXPECT_EQ( tx3.GetFixedParameters()[0], 1.2 );
  EXPECT_EQ( tx3.GetFixedParameters()[1], 1.2 );
  EXPECT_EQ( tx3.GetParameters()[0], 2.0 );
  EXPECT_EQ( tx3.GetParameters()[1], 3.0 );

  tx.reset( new sitk::ScaleTransform(3));

  // test member setters/getters
  EXPECT_EQ(tx->GetCenter(), zeros);
  tx->SetCenter(center);
  EXPECT_EQ(tx->GetCenter(), center);
  tx->SetScale( v3(2.0,1.0,4.0) );

  EXPECT_NO_THROW( tx->SetInverse() );
  EXPECT_EQ( tx->GetScale(), v3(0.5,1.0,0.25) );

}


TEST(TransformTest,ScaleTransform_Points)
{
  // Test Scale by transforming some points
  sitk::ScaleTransform tx(3);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(1.0,1.0,1.0),1e-15 );

  tx.SetScale(v3(1.0,2.0,3.0));
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(1.0,2.0,3.0),1e-15 );

  tx.SetCenter(v3(1.0,1.0,1.0));
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,-1.0,-2.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(1.0,1.0,1.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(2.0,2.0,2.0) ), v3(2.0,3.0,4.0),1e-15 );
}


TEST(TransformTest,ScaleSkewVersor3DTransform)
{
  // test ScaleSkewVersor3DTransform
  const std::vector<double> center(3,1.1);
  const std::vector<double> zeros(3,0.0);
  const std::vector<double> trans(3, 2.2);
  const std::vector<double> skew(6,2.7);

  nsstd::auto_ptr<sitk::ScaleSkewVersor3DTransform> tx(new sitk::ScaleSkewVersor3DTransform());
  std::cout << tx->ToString() << std::endl;
  EXPECT_EQ( tx->GetParameters().size(), 15u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx->GetTranslation(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx->GetScale(), v3(1.0,1.0,1.0) );
  EXPECT_EQ( tx->GetVersor(), v4(0.0,0.0,0.0,1.0) );
  EXPECT_EQ( tx->GetMatrix(), v9(1.0,0.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0) );

  EXPECT_EQ( tx->SetScale(v3(1.0,2.0,3.0)).GetScale(), v3(1.0,2.0,3.0) );
  EXPECT_EQ( tx->SetTranslation(trans).GetTranslation(), trans );

  EXPECT_EQ( tx->SetCenter(center).GetCenter(), center );

  sitk::ScaleSkewVersor3DTransform tx0(v3(0.4,0.5,0.6), skew, v4(0.0,0.0,0.0,1.0), trans );
  EXPECT_EQ( tx0.GetCenter(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx0.GetTranslation(), trans );
  EXPECT_EQ( tx0.GetScale(), v3(0.4,0.5,0.6) );
  EXPECT_EQ( tx0.GetSkew(), skew );
  EXPECT_EQ( tx0.GetVersor(),  v4(0.0,0.0,0.0,1.0) );

  //constructor using axis-angle (rotation of 90 degrees around z)
  sitk::ScaleSkewVersor3DTransform tx00(v3(0.4,0.5,0.6), skew, v3(0.0,0.0,1.0),1.5707963267948966, trans );
  EXPECT_EQ( tx00.GetCenter(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx00.GetTranslation(), trans );
  EXPECT_EQ( tx00.GetScale(), v3(0.4,0.5,0.6) );
  EXPECT_EQ( tx00.GetSkew(), skew );
  EXPECT_VECTOR_DOUBLE_NEAR(tx00.GetVersor(), v4(0.0,0.0,0.70710678118654757,0.70710678118654757), 1e-15);

  // copy constructor
  sitk::ScaleSkewVersor3DTransform tx1( *(tx.get()) );
  EXPECT_EQ( tx1.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx1.GetParameters()[7], 2.0 ); // scale y
  EXPECT_EQ( tx1.GetParameters(), tx->GetParameters() );
  EXPECT_EQ( tx1.GetCenter(), center );

  sitk::ScaleSkewVersor3DTransform tx2;

  // assignment operator
  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx1.GetParameters().size(), 15u );
  EXPECT_EQ( tx1.GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx1.GetTranslation(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx1.GetScale(), v3(1.0,1.0,1.0) );
  EXPECT_EQ( tx1.GetVersor(), v4(0.0,0.0,0.0,1.0) );


  // copy on write
  tx1.SetFixedParameters(center);
  EXPECT_EQ( tx1.GetCenter(), center);
  EXPECT_EQ( tx1.GetFixedParameters(), center );
  EXPECT_EQ( tx2.GetFixedParameters(), zeros );
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx2.GetCenter(), zeros );
  tx1.SetCenter(center);
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetTranslation(), zeros );
  EXPECT_EQ( tx2.GetTranslation(), zeros );
  tx1.SetTranslation(trans);
  EXPECT_EQ( tx1.GetTranslation(), trans );
  EXPECT_EQ( tx2.GetTranslation(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetScale(), v3(1.0,1.0,1.0) );
  EXPECT_EQ( tx2.GetScale(), v3(1.0,1.0,1.0) );
  tx1.SetScale(v3(3.0,2.0,1.0));
  EXPECT_EQ( tx1.GetScale(), v3(3.0,2.0,1.0) );
  EXPECT_EQ( tx2.GetScale(), v3(1.0,1.0,1.0) );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetVersor(), v4(0.0,0.0,0.0,1.0) );
  EXPECT_EQ( tx2.GetVersor(), v4(0.0,0.0,0.0,1.0) );
  tx1.SetRotation(v3(1.0,0.0,0.0), itk::Math::pi);
  EXPECT_VECTOR_DOUBLE_NEAR( tx1.GetVersor(), v4(1.0,0.0,0.0,0.0), 1e-15 );
  EXPECT_EQ( tx2.GetVersor(), v4(0.0,0.0,0.0,1.0) );


  sitk::Transform tx3( *tx );
  tx.reset();

  EXPECT_EQ( tx3.GetParameters().size(), 15u );
  EXPECT_EQ( tx3.GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx3.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx3.GetParameters()[0], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[1], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[2], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[7], 2.0 );


  tx.reset( new sitk::ScaleSkewVersor3DTransform());

  // test member setters/getters
  EXPECT_EQ(tx->GetCenter(), zeros);
  tx->SetCenter(center);
  EXPECT_EQ(tx->GetCenter(), center);

  EXPECT_EQ( tx->SetRotation(v4(0.0,1.0,0.0,0.0)).GetVersor(), v4(0.0,1.0,0.0,0.0) );
  EXPECT_THROW( tx->SetRotation(v3(1.0,0.0,0.0)).GetVersor(), sitk::GenericException );

  EXPECT_EQ(tx->GetTranslation(), zeros);
  tx->SetTranslation(trans);
  EXPECT_EQ(tx->GetTranslation(),trans);

  // BUG: inverse does not work!!!!
  //EXPECT_NO_THROW(tx->SetInverse());

}


TEST(TransformTest,ScaleVersor3DTransform)
{
  // test ScaleVersor3DTransform
  const std::vector<double> center(3,1.1);
  const std::vector<double> zeros(3,0.0);
  const std::vector<double> trans(3, 2.2);

  nsstd::auto_ptr<sitk::ScaleVersor3DTransform> tx(new sitk::ScaleVersor3DTransform());
  EXPECT_EQ( tx->GetParameters().size(), 9u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx->GetTranslation(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx->GetScale(), v3(1.0,1.0,1.0) );
  EXPECT_EQ( tx->GetVersor(), v4(0.0,0.0,0.0,1.0) );
  EXPECT_EQ( tx->GetMatrix(), v9(1.0,0.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0) );

  EXPECT_EQ( tx->SetScale(v3(1.0,2.0,3.0)).GetScale(), v3(1.0,2.0,3.0) );
  EXPECT_EQ( tx->SetTranslation(trans).GetTranslation(), trans );
  EXPECT_EQ( tx->SetCenter(center).GetCenter(), center );

  sitk::ScaleVersor3DTransform tx0(v3(0.4,0.5,0.6), v4(0.0,0.0,0.0,1.0), trans );
  EXPECT_EQ( tx0.GetCenter(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx0.GetTranslation(), trans );
  EXPECT_EQ( tx0.GetScale(), v3(0.4,0.5,0.6) );
  EXPECT_EQ( tx0.GetVersor(),  v4(0.0,0.0,0.0,1.0) );

  //constructor using axis-angle (rotation of 90 degrees around z)
  sitk::ScaleVersor3DTransform tx00(v3(0.4,0.5,0.6), v3(0.0,0.0,1.0),1.5707963267948966, trans );
  EXPECT_EQ( tx00.GetCenter(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx00.GetTranslation(), trans );
  EXPECT_EQ( tx00.GetScale(), v3(0.4,0.5,0.6) );
   EXPECT_VECTOR_DOUBLE_NEAR(tx00.GetVersor(), v4(0.0,0.0,0.70710678118654757,0.70710678118654757), 1e-15);

  // copy constructor
  sitk::ScaleVersor3DTransform tx1( *(tx.get()) );
  EXPECT_EQ( tx1.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx1.GetParameters()[7], 2.0 ); // scale y
  EXPECT_EQ( tx1.GetParameters(), tx->GetParameters() );
  EXPECT_EQ( tx1.GetCenter(), center );

  sitk::ScaleVersor3DTransform tx2;

  // assignment operator
  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx1.GetParameters().size(), 9u );
  EXPECT_EQ( tx1.GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx1.GetTranslation(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx1.GetScale(), v3(1.0,1.0,1.0) );
  EXPECT_EQ( tx1.GetVersor(), v4(0.0,0.0,0.0,1.0) );


  // copy on write
  tx1.SetFixedParameters(center);
  EXPECT_EQ( tx1.GetCenter(), center);
  EXPECT_EQ( tx1.GetFixedParameters(), center );
  EXPECT_EQ( tx2.GetFixedParameters(), zeros );
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx2.GetCenter(), zeros );
  tx1.SetCenter(center);
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetTranslation(), zeros );
  EXPECT_EQ( tx2.GetTranslation(), zeros );
  tx1.SetTranslation(trans);
  EXPECT_EQ( tx1.GetTranslation(), trans );
  EXPECT_EQ( tx2.GetTranslation(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetScale(), v3(1.0,1.0,1.0) );
  EXPECT_EQ( tx2.GetScale(), v3(1.0,1.0,1.0) );
  tx1.SetScale(v3(3.0,2.0,1.0));
  EXPECT_EQ( tx1.GetScale(), v3(3.0,2.0,1.0) );
  EXPECT_EQ( tx2.GetScale(), v3(1.0,1.0,1.0) );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetVersor(), v4(0.0,0.0,0.0,1.0) );
  EXPECT_EQ( tx2.GetVersor(), v4(0.0,0.0,0.0,1.0) );
  tx1.SetRotation(v3(1.0,0.0,0.0), itk::Math::pi);
  EXPECT_VECTOR_DOUBLE_NEAR( tx1.GetVersor(), v4(1.0,0.0,0.0,0.0), 1e-15 );
  EXPECT_EQ( tx2.GetVersor(), v4(0.0,0.0,0.0,1.0) );


  sitk::Transform tx3( *tx );
  tx.reset();

  EXPECT_EQ( tx3.GetParameters().size(), 9u );
  EXPECT_EQ( tx3.GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx3.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx3.GetParameters()[0], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[1], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[2], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[7], 2.0 );


  tx.reset( new sitk::ScaleVersor3DTransform());

  // test member setters/getters
  EXPECT_EQ(tx->GetCenter(), zeros);
  tx->SetCenter(center);
  EXPECT_EQ(tx->GetCenter(), center);

  EXPECT_EQ( tx->SetRotation(v4(0.0,1.0,0.0,0.0)).GetVersor(), v4(0.0,1.0,0.0,0.0) );
  EXPECT_THROW( tx->SetRotation(v3(1.0,0.0,0.0)).GetVersor(), sitk::GenericException );

  EXPECT_EQ(tx->GetTranslation(), zeros);
  tx->SetTranslation(trans);
  EXPECT_EQ(tx->GetTranslation(),trans);

  // BUG: inverse does not work!!!!
  //EXPECT_NO_THROW(tx->SetInverse());
}


TEST(TransformTest,ScaleSkewVersor3DTransform_Points)
{
  // Test ScaleSkewVersor3D by transforming some points
  sitk::ScaleSkewVersor3DTransform tx;
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(1.0,1.0,1.0),1e-15 );

  EXPECT_EQ( tx.Translate(v3(1.0,2.0,3.0)).GetTranslation(), v3(1.0,2.0,3.0) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(1.0,2.0,3.0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(2.0,3.0,4.0),1e-15);

  tx = sitk::ScaleSkewVersor3DTransform();
  EXPECT_EQ( tx.SetRotation(v4(0.0,1.0,0.0,0.0)).GetVersor(), v4(0.0,1.0,0.0,0.0) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,0.0,0.0) ), v3(-1.0,0.0,0.0),1e-15 );

  EXPECT_EQ( tx.Translate(v3(1.0,2.0,3.0)).GetTranslation(), v3(1.0,2.0,3.0) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(1.0,2.0,3.0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,0.0,0.0) ), v3(0.0,2.0,3.0),1e-15);


  tx = sitk::ScaleSkewVersor3DTransform();
  const std::vector<double> zeroSkew = tx.GetSkew();

  std::vector<double> skew = zeroSkew;
  skew[0] = 1.0;
  EXPECT_EQ( tx.SetSkew(skew).GetSkew(), skew );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0), 1e-17);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,0.0,0.0) ), v3(1.0,0.0,0.0), 1e-17);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,0.0) ), v3(2.0,1.0,0.0), 1e-17);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,1.0,1.0) ), v3(1.0,1.0,1.0), 1e-17);

  skew = zeroSkew;
  skew[3] = 1.0;
  EXPECT_EQ( tx.SetSkew(skew).GetSkew(), skew );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0), 1e-17);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,0.0,0.0) ), v3(1.0,0.0,0.0), 1e-17);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,0.0) ), v3(1.0,1.0,0.0), 1e-17);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,1.0,1.0) ), v3(0.0,2.0,1.0), 1e-17);

  tx.SetIdentity();
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,0.0) ), v3(1.0,1.0,0.0), 1e-17);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,1.0,1.0) ), v3(0.0,1.0,1.0), 1e-17);
}


TEST(TransformTest,Similarity3DTransform)
{
  // test Similarity3DTransform
  const std::vector<double> center(3,1.1);
  const std::vector<double> zeros(3,0.0);
  const std::vector<double> trans(3, 2.2);

  nsstd::auto_ptr<sitk::Similarity3DTransform> tx(new sitk::Similarity3DTransform());
  std::cout << tx->ToString() << std::endl;
  EXPECT_EQ( tx->GetParameters().size(), 7u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx->GetTranslation(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx->GetScale(), 1.0);
  EXPECT_EQ( tx->GetVersor(), v4(0.0,0.0,0.0,1.0) );
  EXPECT_EQ( tx->GetMatrix(), v9(1.0,0.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0) );

  EXPECT_EQ( tx->SetScale(2.0).GetScale(), 2.0 );
  EXPECT_EQ( tx->SetTranslation(trans).GetTranslation(), trans );

  EXPECT_EQ( tx->SetCenter(center).GetCenter(), center );

  sitk::Similarity3DTransform tx0(0.5, v4(1.0,0.0,0.0,0.0), trans );
  EXPECT_EQ( tx0.GetCenter(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx0.GetTranslation(), trans );
  EXPECT_EQ( tx0.GetScale(), 0.5 );
  EXPECT_EQ( tx0.GetVersor(), v4(1.0,0.0,0.0,0.0));

  // copy constructor
  sitk::Similarity3DTransform tx1( *(tx.get()) );
  EXPECT_EQ( tx1.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx1.GetParameters()[6], 2.0 ); // scale
  EXPECT_EQ( tx1.GetCenter(), center );

  sitk::Similarity3DTransform tx2;

  // assignment operator
  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx1.GetParameters().size(), 7u );
  EXPECT_EQ( tx1.GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx1.GetTranslation(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx1.GetScale(), 1.0);
  EXPECT_EQ( tx1.GetVersor(), v4(0.0,0.0,0.0,1.0) );


  // copy on write
  tx1.SetFixedParameters(center);
  EXPECT_EQ( tx1.GetCenter(), center);
  EXPECT_EQ( tx1.GetFixedParameters(), center );
  EXPECT_EQ( tx2.GetFixedParameters(), zeros );
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx2.GetCenter(), zeros );
  tx1.SetCenter(center);
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetTranslation(), zeros );
  EXPECT_EQ( tx2.GetTranslation(), zeros );
  tx1.SetTranslation(trans);
  EXPECT_EQ( tx1.GetTranslation(), trans );
  EXPECT_EQ( tx2.GetTranslation(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetScale(), 1.0 );
  EXPECT_EQ( tx2.GetScale(), 1.0 );
  tx1.SetScale(2.0);
  EXPECT_EQ( tx1.GetScale(), 2.0 );
  EXPECT_EQ( tx2.GetScale(), 1.0 );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetVersor(), v4(0.0,0.0,0.0,1.0) );
  EXPECT_EQ( tx2.GetVersor(), v4(0.0,0.0,0.0,1.0) );
  tx1.SetRotation(v3(1.0,0.0,0.0), itk::Math::pi);
  EXPECT_VECTOR_DOUBLE_NEAR( tx1.GetVersor(), v4(1.0,0.0,0.0,0.0), 1e-15 );
  EXPECT_EQ( tx2.GetVersor(), v4(0.0,0.0,0.0,1.0) );


  sitk::Transform tx3( *tx );
  tx.reset();

  EXPECT_EQ( tx3.GetParameters().size(), 7u );
  EXPECT_EQ( tx3.GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx3.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx3.GetParameters()[0], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[1], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[2], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[6], 2.0 );


  tx.reset( new sitk::Similarity3DTransform());

  // test member setters/getters
  EXPECT_EQ(tx->GetCenter(), zeros);
  tx->SetCenter(center);
  EXPECT_EQ(tx->GetCenter(), center);

  EXPECT_EQ( tx->SetRotation(v4(0.0,1.0,0.0,0.0)).GetVersor(), v4(0.0,1.0,0.0,0.0) );
  EXPECT_THROW( tx->SetRotation(v3(1.0,0.0,0.0)).GetVersor(), sitk::GenericException );

  EXPECT_EQ(tx->GetTranslation(), zeros);
  tx->SetTranslation(trans);
  EXPECT_EQ(tx->GetTranslation(),trans);

  // inverse
  EXPECT_TRUE(tx->SetInverse());
  EXPECT_NO_THROW(tx->GetVersor());

  tx.reset( new sitk::Similarity3DTransform());
  tx->SetMatrix(v9(-1.0,0.0,0.0, 0.0,-1.0,0.0, 0.0,0.0,1.0));
  EXPECT_EQ( tx->GetMatrix(), v9(-1.0,0.0,0.0, 0.0,-1.0,0.0, 0.0,0.0,1.0) );
  EXPECT_VECTOR_DOUBLE_NEAR(tx->GetVersor(),  v4(0.0,0.0,1.0,0.0), 1e-15);
}


TEST(TransformTest,Similarity3DTransform_Points)
{
  // Test Similarity3D by transforming some points
  sitk::Similarity3DTransform tx;
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(1.0,1.0,1.0),1e-15 );

  EXPECT_EQ( tx.Translate(v3(1.0,2.0,3.0)).GetTranslation(), v3(1.0,2.0,3.0) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(1.0,2.0,3.0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(2.0,3.0,4.0),1e-15);

  tx = sitk::Similarity3DTransform();
  EXPECT_EQ( tx.SetRotation(v4(0.0,1.0,0.0,0.0)).GetVersor(), v4(0.0,1.0,0.0,0.0) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,0.0,0.0) ), v3(-1.0,0.0,0.0),1e-15 );

  EXPECT_EQ( tx.Translate(v3(1.0,2.0,3.0)).GetTranslation(), v3(1.0,2.0,3.0) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(1.0,2.0,3.0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,0.0,0.0) ), v3(0.0,2.0,3.0),1e-15);

  tx.SetIdentity();
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,0.0,0.0) ), v3(1.0,0.0,0.0),1e-15);

}


TEST(TransformTest,TranslationTransform)
{
  // test TranslationTransform

  const std::vector<double> zeros(3,0.0);
  const std::vector<double> trans2d(2, 2.2);
  const std::vector<double> trans3d(3, 3.3);

  nsstd::auto_ptr<sitk::TranslationTransform> tx;

  EXPECT_NO_THROW( tx.reset( new sitk::TranslationTransform(2) ) );
  std::cout << tx->ToString() << std::endl;
  EXPECT_EQ( tx->GetParameters().size(), 2u );
  EXPECT_EQ( tx->GetParameters()[0], 0.0 );
  EXPECT_EQ( tx->GetParameters()[1], 0.0 );
  EXPECT_EQ( tx->GetFixedParameters().size(), 0u );
  EXPECT_EQ( tx->GetOffset(), std::vector<double>(2,0.0));

  EXPECT_NO_THROW( tx.reset( new sitk::TranslationTransform(3) ) );
  EXPECT_EQ( tx->GetParameters().size(), 3u );
  EXPECT_EQ( tx->GetParameters()[0], 0.0 );
  EXPECT_EQ( tx->GetParameters()[1], 0.0 );
  EXPECT_EQ( tx->GetParameters()[2], 0.0 );
  EXPECT_EQ( tx->GetFixedParameters().size(), 0u );
  EXPECT_EQ( tx->GetOffset(), std::vector<double>(3,0.0));

  EXPECT_NO_THROW( tx.reset( new sitk::TranslationTransform(2, trans2d) ) );
  EXPECT_EQ( tx->GetParameters().size(), 2u );
  EXPECT_EQ( tx->GetParameters()[0], 2.2 );
  EXPECT_EQ( tx->GetParameters()[1], 2.2 );
  EXPECT_EQ( tx->GetFixedParameters().size(), 0u );
  EXPECT_EQ( tx->GetOffset(), trans2d);

  // copy constructor
  sitk::TranslationTransform tx1(*(tx.get()));
  EXPECT_EQ( tx1.GetParameters().size(), 2u );
  EXPECT_EQ( tx1.GetParameters()[0], 2.2 );
  EXPECT_EQ( tx1.GetParameters()[1], 2.2 );
  EXPECT_EQ( tx1.GetFixedParameters().size(), 0u );;
  EXPECT_EQ( tx->GetOffset(), trans2d);

  // shallow assignment
  sitk::TranslationTransform tx2(3);
  tx1 = tx2;
  EXPECT_EQ( tx1.GetDimension(), 3u );
  EXPECT_EQ( tx->GetDimension(), 2u );
  EXPECT_EQ( tx1.GetOffset(), std::vector<double>(3,0.0));
  EXPECT_EQ( tx->GetOffset(), trans2d);

  // copy on write
  tx1.SetParameters(std::vector<double>(3, 9.9));
  EXPECT_EQ( tx2.GetOffset(), std::vector<double>(3,0.0) );

  tx2.SetOffset( trans3d );
  EXPECT_EQ(tx2.GetOffset(), trans3d);

  EXPECT_THROW( tx.reset( new sitk::TranslationTransform(3, trans2d) ), sitk::GenericException );
  EXPECT_THROW( tx1.SetOffset(trans2d), sitk::GenericException );

  // inverse
  EXPECT_TRUE(tx1.SetInverse());
  EXPECT_NO_THROW(tx1.GetOffset());

}

TEST(TransformTest,VersorRigid3DTransform)
{
  // test VersorRigid3DTransform
  const std::vector<double> center(3,1.1);
  const std::vector<double> zeros(3,0.0);
  const std::vector<double> trans(3, 2.2);

  nsstd::auto_ptr<sitk::VersorRigid3DTransform> tx(new sitk::VersorRigid3DTransform());
  std::cout << tx->ToString() << std::endl;
  EXPECT_EQ( tx->GetParameters().size(), 6u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx->GetTranslation(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx->GetVersor(), v4(0.0,0.0,0.0,1.0) );
  EXPECT_EQ( tx->GetMatrix(), v9(1.0,0.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0) );

  EXPECT_EQ( tx->SetTranslation(trans).GetTranslation(), trans );
  EXPECT_EQ( tx->SetCenter(center).GetCenter(), center );

  //constructor using versor
  sitk::VersorRigid3DTransform tx0(v4(1.0,0.0,0.0,0.0), trans);
  EXPECT_EQ( tx0.GetVersor(), v4(1.0,0.0,0.0,0.0) );
  EXPECT_EQ( tx0.GetTranslation(), trans );
  EXPECT_EQ( tx0.GetCenter(), v3(0.0,0.0,0.0) );

  //constructor using axis-angle (rotation of 90 degrees around z)
  sitk::VersorRigid3DTransform tx00(v3(0.0,0.0,1.0),1.5707963267948966);
  EXPECT_VECTOR_DOUBLE_NEAR(tx00.GetVersor(), v4(0.0,0.0,0.70710678118654757,0.70710678118654757), 1e-15);

  // copy constructor
  sitk::VersorRigid3DTransform tx1( *(tx.get()) );
  EXPECT_EQ( tx1.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx1.GetCenter(), center );

  sitk::VersorRigid3DTransform tx2;

  // assignment operator
  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx1.GetParameters().size(), 6u );
  EXPECT_EQ( tx1.GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx1.GetTranslation(), v3(0.0,0.0,0.0) );
  EXPECT_EQ( tx1.GetVersor(), v4(0.0,0.0,0.0,1.0) );


  // copy on write
  tx1.SetFixedParameters(center);
  EXPECT_EQ( tx1.GetCenter(), center);
  EXPECT_EQ( tx1.GetFixedParameters(), center );
  EXPECT_EQ( tx2.GetFixedParameters(), zeros );
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx2.GetCenter(), zeros );
  tx1.SetCenter(center);
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetTranslation(), zeros );
  EXPECT_EQ( tx2.GetTranslation(), zeros );
  tx1.SetTranslation(trans);
  EXPECT_EQ( tx1.GetTranslation(), trans );
  EXPECT_EQ( tx2.GetTranslation(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetVersor(), v4(0.0,0.0,0.0,1.0) );
  EXPECT_EQ( tx2.GetVersor(), v4(0.0,0.0,0.0,1.0) );
  tx1.SetRotation(v3(1.0,0.0,0.0), itk::Math::pi);
  EXPECT_VECTOR_DOUBLE_NEAR( tx1.GetVersor(), v4(1.0,0.0,0.0,0.0), 1e-15 );
  EXPECT_EQ( tx2.GetVersor(), v4(0.0,0.0,0.0,1.0) );


  sitk::Transform tx3( *tx );
  tx.reset();

  EXPECT_EQ( tx3.GetParameters().size(), 6u );
  EXPECT_EQ( tx3.GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx3.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx3.GetParameters()[0], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[1], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[2], 0.0 );


  tx.reset( new sitk::VersorRigid3DTransform());

  // test member setters/getters
  EXPECT_EQ(tx->GetCenter(), zeros);
  tx->SetCenter(center);
  EXPECT_EQ(tx->GetCenter(), center);

  EXPECT_EQ( tx->SetRotation(v4(0.0,1.0,0.0,0.0)).GetVersor(), v4(0.0,1.0,0.0,0.0) );
  EXPECT_THROW( tx->SetRotation(v3(1.0,0.0,0.0)).GetVersor(), sitk::GenericException );

  EXPECT_EQ(tx->GetTranslation(), zeros);
  tx->SetTranslation(trans);
  EXPECT_EQ(tx->GetTranslation(),trans);

  // inverse
  EXPECT_TRUE(tx->SetInverse());
  EXPECT_NO_THROW(tx->GetTranslation());

  tx->SetIdentity();
  EXPECT_EQ(tx->GetTranslation(), zeros);


  tx.reset( new sitk::VersorRigid3DTransform());
  tx->SetMatrix(v9(-1.0,0.0,0.0, 0.0,-1.0,0.0, 0.0,0.0,1.0));
  EXPECT_EQ( tx->GetMatrix(), v9(-1.0,0.0,0.0, 0.0,-1.0,0.0, 0.0,0.0,1.0) );
  EXPECT_VECTOR_DOUBLE_NEAR(tx->GetVersor(),  v4(0.0,0.0,1.0,0.0), 1e-15);
}

TEST(TransformTest,VersorRigid3DTransform_Points)
{
  // Test VersorRigid3D by transforming some points
  sitk::VersorRigid3DTransform tx;
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(1.0,1.0,1.0),1e-15 );

  EXPECT_EQ( tx.Translate(v3(1.0,2.0,3.0)).GetTranslation(), v3(1.0,2.0,3.0) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(1.0,2.0,3.0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,1.0,1.0) ), v3(2.0,3.0,4.0),1e-15);

  tx = sitk::VersorRigid3DTransform();
  EXPECT_EQ( tx.SetRotation(v4(0.0,1.0,0.0,0.0)).GetVersor(), v4(0.0,1.0,0.0,0.0) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0),1e-15 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,0.0,0.0) ), v3(-1.0,0.0,0.0),1e-15 );

  EXPECT_EQ( tx.Translate(v3(1.0,2.0,3.0)).GetTranslation(), v3(1.0,2.0,3.0) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(0.0,0.0,0.0) ), v3(1.0,2.0,3.0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,0.0,0.0) ), v3(0.0,2.0,3.0),1e-15);

  // inverse
  EXPECT_TRUE(tx.SetInverse());
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint( v3(1.0,2.0,3.0) ), v3(0.0,0.0,0.0),1e-15);
  EXPECT_VECTOR_DOUBLE_NEAR( tx.TransformPoint(  v3(0.0,2.0,3.0) ), v3(1.0,0.0,0.0),1e-15);
  EXPECT_NO_THROW(tx.GetCenter());

}


TEST(TransformTest,VersorRigid3DTransform_NoPolymorphicCast)
{
  sitk::ScaleSkewVersor3DTransform ssv3dt;
//  sitk::ScaleVersor3DTransform sv3dt;
  sitk::Similarity3DTransform s3dt;
  sitk::VersorRigid3DTransform tx;

  EXPECT_THROW( tx = sitk::VersorRigid3DTransform(ssv3dt), sitk::GenericException );
//  EXPECT_THROW( sitk::VersorRigid3DTransform( sv3dt), sitk::GenericException );
  EXPECT_THROW(  tx = sitk::VersorRigid3DTransform( s3dt), sitk::GenericException );
}

TEST(TransformTest,VersorTransform)
{
  // test VersorTransform
  const std::vector<double> center(3,1.1);
  const std::vector<double> zeros(3,0.0);
  const std::vector<double> trans(3, 2.2);

  nsstd::auto_ptr<sitk::VersorTransform> tx(new sitk::VersorTransform());
  std::cout << tx->ToString() << std::endl;
  EXPECT_EQ( tx->GetParameters().size(), 3u );
  EXPECT_EQ( tx->GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx->GetVersor(), v4(0.0,0.0,0.0,1.0) );
  EXPECT_EQ( tx->GetCenter(), zeros );
  EXPECT_EQ( tx->GetMatrix(), v9(1.0,0.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0) );

  EXPECT_EQ( tx->SetCenter(center).GetCenter(), center );

  //constructor using versor
  sitk::VersorTransform tx0(v4(1.0,0.0,0.0,0.0));
  EXPECT_EQ( tx0.GetVersor(), v4(1.0,0.0,0.0,0.0) );
  EXPECT_EQ( tx0.GetCenter(), v3(0.0,0.0,0.0) );

  //constructor using axis-angle (rotation of 90 degrees around z)
  sitk::VersorTransform tx00(v3(0.0,0.0,1.0),1.5707963267948966);
  EXPECT_VECTOR_DOUBLE_NEAR(tx00.GetVersor(), v4(0.0,0.0,0.70710678118654757,0.70710678118654757), 1e-15);

  // copy constructor
  sitk::VersorTransform tx1( *(tx.get()) );
  EXPECT_EQ( tx1.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx1.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx1.GetCenter(), center );

  sitk::VersorTransform tx2;

  // assignment operator
  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx1.GetParameters().size(), 3u );
  EXPECT_EQ( tx1.GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx1.GetVersor(), v4(0.0,0.0,0.0,1.0) );


  // copy on write
  tx1.SetFixedParameters(center);
  EXPECT_EQ( tx1.GetCenter(), center);
  EXPECT_EQ( tx1.GetFixedParameters(), center );
  EXPECT_EQ( tx2.GetFixedParameters(), zeros );
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );

  tx1 = tx2;
  EXPECT_EQ( tx1.GetCenter(), zeros );
  EXPECT_EQ( tx2.GetCenter(), zeros );
  tx1.SetCenter(center);
  EXPECT_EQ( tx1.GetCenter(), center );
  EXPECT_EQ( tx2.GetCenter(), zeros );


  tx1 = tx2;
  EXPECT_EQ( tx1.GetVersor(), v4(0.0,0.0,0.0,1.0) );
  EXPECT_EQ( tx2.GetVersor(), v4(0.0,0.0,0.0,1.0) );
  tx1.SetRotation(v3(1.0,0.0,0.0), itk::Math::pi);
  EXPECT_VECTOR_DOUBLE_NEAR( tx1.GetVersor(), v4(1.0,0.0,0.0,0.0), 1e-15 );
  EXPECT_EQ( tx2.GetVersor(), v4(0.0,0.0,0.0,1.0) );


  sitk::Transform tx3( *tx );
  tx.reset();

  EXPECT_EQ( tx3.GetParameters().size(), 3u );
  EXPECT_EQ( tx3.GetFixedParameters().size(), 3u );
  EXPECT_EQ( tx3.GetFixedParameters()[0], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[1], 1.1 );
  EXPECT_EQ( tx3.GetFixedParameters()[2], 1.1 );
  EXPECT_EQ( tx3.GetParameters()[0], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[1], 0.0 );
  EXPECT_EQ( tx3.GetParameters()[2], 0.0 );


  tx.reset( new sitk::VersorTransform());

  // test member setters/getters
  EXPECT_EQ(tx->GetCenter(), zeros);
  tx->SetCenter(center);
  EXPECT_EQ(tx->GetCenter(), center);

  EXPECT_EQ( tx->SetRotation(v4(0.0,1.0,0.0,0.0)).GetVersor(), v4(0.0,1.0,0.0,0.0) );
  EXPECT_THROW( tx->SetRotation(v3(1.0,0.0,0.0)).GetVersor(), sitk::GenericException );
  EXPECT_NO_THROW(tx->SetIdentity());

  // inverse
  EXPECT_TRUE(tx->SetInverse());
  EXPECT_NO_THROW(tx->GetVersor());

  tx.reset( new sitk::VersorTransform());
  tx->SetMatrix(v9(-1.0,0.0,0.0, 0.0,-1.0,0.0, 0.0,0.0,1.0));
  EXPECT_EQ( tx->GetMatrix(), v9(-1.0,0.0,0.0, 0.0,-1.0,0.0, 0.0,0.0,1.0) );
  EXPECT_VECTOR_DOUBLE_NEAR(tx->GetVersor(),  v4(0.0,0.0,1.0,0.0), 1e-15);
}



TEST(TransformTest,VersorTransform_NoPolymorphicCast)
{
  sitk::ScaleSkewVersor3DTransform ssv3dt;
//  sitk::ScaleVersor3DTransform sv3dt;
  sitk::Similarity3DTransform s3dt;
  sitk::VersorRigid3DTransform vr3dt;

  sitk::VersorTransform tx;

  EXPECT_THROW( tx = sitk::VersorTransform( ssv3dt), sitk::GenericException );
//  EXPECT_THROW( sitk::VersorTransform( sv3dt), sitk::GenericException );
  EXPECT_THROW( tx = sitk::VersorTransform( s3dt), sitk::GenericException );
  EXPECT_THROW( tx = sitk::VersorTransform( vr3dt), sitk::GenericException );
}
