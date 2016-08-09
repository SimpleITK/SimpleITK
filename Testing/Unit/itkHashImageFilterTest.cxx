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
#include <itkImageFileReader.h>
#include <itkHashImageFilter.h>
#include <sitkHashImageFilter.h>
#include <sitkImageFileReader.h>
#include <sitkCastImageFilter.h>

class HashImageFilterTest
  : public ::testing::Test {
public:

  template <typename TPixelType, unsigned int IDimension>
  void CheckImageHashMD5( const std::string &fname, const std::string &expectedHash )
  {

    typedef itk::ImageFileReader<itk::Image<TPixelType, IDimension > > ReaderType;
    typename ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( dataFinder.GetFile ( fname ) );
    reader->Update();

    typedef itk::HashImageFilter< itk::Image<TPixelType, IDimension> > HasherType;
    typename HasherType::Pointer  hasher = HasherType::New();
    hasher->SetHashFunction( HasherType::MD5 );
    hasher->SetInput( reader->GetOutput() );
    hasher->Update();

    EXPECT_EQ ( expectedHash, hasher->GetHash() );

  }

  template <typename TPixelType, unsigned int IDimension>
  void CheckImageHashSHA1( const std::string &fname, const std::string &expectedHash )
  {

    typedef itk::ImageFileReader<itk::Image<TPixelType, IDimension > > ReaderType;
    typename ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( dataFinder.GetFile ( fname ) );
    reader->Update();

    typedef itk::HashImageFilter< itk::Image<TPixelType, IDimension> > HasherType;
    typename HasherType::Pointer  hasher = HasherType::New();
    hasher->SetHashFunction( HasherType::SHA1 );
    hasher->SetInput( reader->GetOutput() );
    hasher->Update();

    EXPECT_EQ ( expectedHash, hasher->GetHash() );

  }
};

TEST_F(HashImageFilterTest, InstantiateTest) {

  typedef itk::HashImageFilter< itk::Image< unsigned char, 1> > UCHAR1HasherType;
  EXPECT_TRUE( UCHAR1HasherType::New().IsNotNull() );

  typedef itk::HashImageFilter< itk::Image< unsigned char, 2> > UCHAR2HasherType;
  EXPECT_TRUE( UCHAR2HasherType::New().IsNotNull() );

  typedef itk::HashImageFilter< itk::Image< unsigned char, 3> > UCHAR3HasherType;
  EXPECT_TRUE( UCHAR3HasherType::New().IsNotNull() );

  typedef itk::HashImageFilter< itk::Image< unsigned int, 3> > UINT23HasherType;
  EXPECT_TRUE( UINT23HasherType::New().IsNotNull() );

  typedef itk::HashImageFilter< itk::Image<int, 3> > INT23HasherType;
  EXPECT_TRUE( INT23HasherType::New().IsNotNull() );

  typedef itk::HashImageFilter< itk::Image<float, 3> > FLOATHasherType;
  EXPECT_TRUE( FLOATHasherType::New().IsNotNull() );

  typedef itk::HashImageFilter< itk::Image<double, 3> > DOUBLEHasherType;
  EXPECT_TRUE( DOUBLEHasherType::New().IsNotNull() );

#ifdef SITK_4D_IMAGES
  typedef itk::HashImageFilter< itk::Image<double, 4> > DOUBLE4DHasherType;
  EXPECT_TRUE( DOUBLE4DHasherType::New().IsNotNull() );
#endif
};


TEST_F(HashImageFilterTest, MD5HashValues ) {

  this->CheckImageHashMD5<float,3>("Input/RA-Float.nrrd", "3ccccde44efaa3d688a86e94335c1f16");

  this->CheckImageHashMD5<float,2>("Input/RA-Float.nrrd", "16142594b185c50d64dd629750b94c90");

  this->CheckImageHashMD5<float,1>("Input/RA-Float.nrrd", "606f0ee67f5b181f90286e17e6f49926");

  this->CheckImageHashMD5<short, 3>("Input/Ramp-Down-Short.nrrd", "71f5c852a6251069fa1d60f796463343" );

  this->CheckImageHashMD5<int, 3>("Input/Ramp-Down-Short.nrrd", "f945b2b5384ba6f21a0fd50a970fb5ff");
}


TEST_F(HashImageFilterTest, SHA1HashValues ) {

  this->CheckImageHashSHA1<float,3>("Input/RA-Float.nrrd", "b187541bdcc89843d0a25a3761f344c358f3518a" );

  this->CheckImageHashSHA1<float,2>("Input/RA-Float.nrrd", "7bd2146732f1e6f38fe5ed387332d3ad3541b182" );

  this->CheckImageHashSHA1<float,1>("Input/RA-Float.nrrd",  "0eac9ac1f19b27743dfeabe76e69ae251c02b641" );

  this->CheckImageHashSHA1<short, 3>("Input/Ramp-Down-Short.nrrd", "4b0bd9dcf1f7d78101ce24da7f51de212f302ae9" );

  this->CheckImageHashSHA1<int, 3>("Input/Ramp-Down-Short.nrrd",  "3dc54908746f25fd42f17c5fe44935013e508b1b" );

#ifdef SITK_4D_IMAGES
  this->CheckImageHashSHA1<short, 4>("Input/4D.nii.gz", "9e81d4b3cdf10a4da5d54c8cd7c4954449d76d5d" );
#endif
}

TEST_F(HashImageFilterTest, VectorImages ) {

  // test image of vectors
  {
  typedef itk::Image<itk::Vector<float, 1>, 3 > VectorImageType;

  typedef itk::ImageFileReader<VectorImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) );
  reader->Update();

  typedef itk::HashImageFilter< VectorImageType > HasherType;
  HasherType::Pointer  hasher = HasherType::New();
  hasher->SetHashFunction( HasherType::MD5 );
  hasher->SetInput( reader->GetOutput() );
  hasher->Update();

  EXPECT_EQ( hasher->GetHash(), "3ccccde44efaa3d688a86e94335c1f16" );
  }

  // test vector image
  {
  typedef itk::VectorImage<float, 3> VectorImageType;

  typedef itk::ImageFileReader<VectorImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) );
  reader->Update();

  typedef itk::HashImageFilter< VectorImageType > HasherType;
  HasherType::Pointer  hasher = HasherType::New();
  hasher->SetHashFunction( HasherType::MD5 );
  hasher->SetInput( reader->GetOutput() );
  hasher->Update();


  EXPECT_EQ( hasher->GetHash(), "3ccccde44efaa3d688a86e94335c1f16" );
  }
}

TEST_F(HashImageFilterTest, LabelMap ) {

  itk::simple::Image img = itk::simple::ReadImage( dataFinder.GetFile ( "Input/2th_cthead1.png" ) );

  std::string hash;

  EXPECT_NO_THROW( hash = itk::simple::Hash( itk::simple::Cast( img, itk::simple::sitkLabelUInt16 ) ) );
  EXPECT_EQ( hash, "134248ff026387fe17bd0bfa62357fa390d52985" );

  EXPECT_NO_THROW( hash = itk::simple::Hash( itk::simple::Cast( img, itk::simple::sitkLabelUInt32 ) ) );
  EXPECT_EQ( hash, "c4dc6e128902159fe04cacec27b784cd995533af" );

}

TEST_F(HashImageFilterTest, Coverage ) {

 typedef itk::HashImageFilter< itk::Image< unsigned char, 2> > UCHAR2HasherType;
 UCHAR2HasherType::Pointer hasher = UCHAR2HasherType::New();

 // PrintSelf
 std::ostringstream out;
 out << hasher;
 EXPECT_NE ( out.str(), "" );  // So the test fails if we don’t have any print self output...


 // Set/Get Methods
 hasher->SetHashFunction( UCHAR2HasherType::MD5 );
 EXPECT_EQ(  hasher->GetHashFunction(), UCHAR2HasherType::MD5 ) << "expected default hash type to be MD5";

 hasher->SetHashFunction( UCHAR2HasherType::SHA1 );
 EXPECT_EQ(  hasher->GetHashFunction(), UCHAR2HasherType::SHA1 ) << "expected default hash type to be SHA1";
}
