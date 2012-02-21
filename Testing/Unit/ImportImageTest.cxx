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
#include <sitkImportImageFilter.h>
#include <SimpleITKTestHarness.h>

namespace
{
template < class T >
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v)
{
  os << "[";
  std::copy( v.begin(), v.end(), std::ostream_iterator<T>(os, ", " ) );
  return os << "]";
}
}


// Common fixture for Import tests
class Import
  : public ::testing::Test {
public:
  virtual void SetUp() {
    spacing1 = std::vector<double>( 3, 1.0 );
    spacing2.push_back( 1.1 );
    spacing2.push_back( 1.2 );

    origin0 = std::vector<double>( 3, 0.0 );
    origin1 = std::vector<double>( 3, 1.0 );
    origin2.push_back( 2.71828183 );
    origin2.push_back( 3.14159265 );
    direction2D = std::vector<double>(4, 0.0 );
    direction3D = std::vector<double>(9, 0.0 );

    direction2D[0] = direction2D[3] = 1.0;

    direction3D[0] = direction3D[4] = direction3D[8] = 1.0;
  }

  std::vector<double> spacing1;
  std::vector<double> spacing2;

  std::vector<double> origin0;
  std::vector<double> origin1;
  std::vector<double> origin2;

  std::vector< uint8_t > uint8_buffer;
  std::vector< int8_t > int8_buffer;
  std::vector< uint16_t > uint16_buffer;
  std::vector< int16_t > int16_buffer;
  std::vector< uint32_t > uint32_buffer;
  std::vector< int32_t > int32_buffer;
  std::vector< float > float_buffer;
  std::vector< double > double_buffer;

  std::vector<double> direction2D;
  std::vector<double> direction3D;
};

namespace sitk = itk::simple;

TEST_F(Import,Required) {
  // the purpose of this test is to verify that the filter has certain
  // methods, and to imporve coverage

  // Check has Self
  typedef itk::simple::ImportImageFilter::Self ImportFilterType;

  // default constructable
   itk::simple::ImportImageFilter importer;

  // has ToString method
  std::cout << importer.ToString() << std::endl;
}

TEST_F(Import,BasicUsage) {

  // This test is designed to set everything and verify it

  uint8_buffer = std::vector< uint8_t >( 128*128*128, 17 );

  sitk::ImportImageFilter importer;
  importer.SetSize( std::vector< unsigned int >( 3, 128u ) );
  importer.SetSpacing( spacing1 );
  importer.SetOrigin( origin0 );
  importer.SetDirection( direction3D );
  importer.SetBufferAsUInt8( &uint8_buffer[0] );

  sitk::Image image = importer.Execute();

  ASSERT_EQ( image.GetDimension(), 3u ) << "image dimension check";

  EXPECT_EQ( image.GetSize()[0], 128u ) << "X size check";
  EXPECT_EQ( image.GetSize()[1], 128u ) << "Y size check";
  EXPECT_EQ( image.GetSize()[2], 128u ) << "Z size check";

  EXPECT_EQ( image.GetOrigin(), origin0 ) << "origin check";
  EXPECT_EQ( image.GetSpacing(), spacing1 ) << "spacing check";


  for ( unsigned int k = 0; k < image.GetSize()[2]; ++k )
    {
    std::vector<uint32_t> idx(3, 0 );
    idx[2] = k;
    for ( unsigned int j = 0; j < image.GetSize()[1]; ++j )
      {
      idx[1] = j;
      for ( unsigned int i = 0; i < image.GetSize()[0]; ++i )
          {
          idx[0] = i;
          EXPECT_EQ( image.GetPixelAsUInt8( idx ), 17 ) << " expect all pixel to be 17";
          }
      }
    }


  EXPECT_EQ ( "a2178ce2d158a4a7c5a9ef3d03a33a6099b9c5be", sitk::Hash( image ) ) << " hash value for basic uin8_t";

  // ================================================
  //
  // TEST FOR 2D IMAGE
  //
  int32_buffer = std::vector< int32_t >( 73*73, 21 );

  importer.SetSize( std::vector< unsigned int >( 2, 73u ) );
  importer.SetSpacing( spacing2 );
  importer.SetOrigin( origin2 );
  importer.SetDirection( direction2D );
  importer.SetBufferAsInt32( &int32_buffer[0] );

  image = importer.Execute();

  ASSERT_EQ( image.GetDimension(), 2u ) << "image dimension check";

  EXPECT_EQ( image.GetSize()[0], 73u ) << "X size check";
  EXPECT_EQ( image.GetSize()[1], 73u ) << "Y size check";

  EXPECT_EQ( image.GetOrigin(), origin2 ) << "origin check";
  EXPECT_EQ( image.GetSpacing(), spacing2 ) << "spacing check";

  for ( unsigned int j = 0; j < image.GetSize()[1]; ++j )
    {
    std::vector<uint32_t> idx(2, 0 );
    idx[1] = j;
    for ( unsigned int i = 0; i < image.GetSize()[0]; ++i )
      {
      idx[0] = i;
      EXPECT_EQ( image.GetPixelAsInt32( idx ), 21 ) << " expect all pixel to be 21";
      }
    }


  EXPECT_EQ ( "6f6eefc4c1833e3e29b0968023ead2141fdbee3f", sitk::Hash( image ) ) << " hash value for basic uin32_t";
}

TEST_F(Import,Direction) {

  // This test is to run the direction parameter though it's passes

  sitk::Image img(0,0,sitk::sitkUInt8);

  uint8_buffer = std::vector< uint8_t >( 128*128*128, 17 );


  {
  sitk::ImportImageFilter importer;
  importer.SetSize( std::vector< unsigned int >( 3, 128u ) );
  importer.SetBufferAsUInt8( &uint8_buffer[0] );

  // check defaults to identity
  ASSERT_NO_THROW( img = importer.Execute() );
  EXPECT_EQ( img.GetDirection(), direction3D );


  importer.SetDirection( direction2D );
  ASSERT_ANY_THROW( importer.Execute() ) << "Checking 2D direction to 3D import ";
  }

  {
  sitk::ImportImageFilter importer;
  importer.SetSize( std::vector< unsigned int >( 2, 128u ) );
  importer.SetBufferAsUInt8( &uint8_buffer[0] );

  // check defaults to identity
  ASSERT_NO_THROW( img = importer.Execute() );
  EXPECT_EQ( img.GetDirection(), direction2D );

  importer.SetDirection( direction3D  );
  ASSERT_ANY_THROW( importer.Execute() ) << "Checking 3D direction to 2D import";
  }

}


TEST_F(Import,ExhaustiveTypes) {

  sitk::ImportImageFilter importer;
  importer.SetSize( std::vector< unsigned int >( 2, 16u ) );
  importer.SetSpacing( spacing1 );
  importer.SetOrigin( origin0 );

  uint8_buffer = std::vector< uint8_t >( 16*16, 1 );
  importer.SetBufferAsUInt8( &uint8_buffer[0] );
  EXPECT_EQ ( "ac458b067c6b021c7e9358229b636e9d1e4cb154", sitk::Hash( importer.Execute() ) ) << " hash value for uint8";

  int8_buffer = std::vector< int8_t >( 16*16, -1 );
  importer.SetBufferAsInt8( &int8_buffer[0] );
  EXPECT_EQ ( "c744cac6af7621524fc3a2b0a9a135a32b33c81b", sitk::Hash( importer.Execute() ) ) << " hash value for int8";

  uint16_buffer = std::vector< uint16_t >( 16*16, 2 );
  importer.SetBufferAsUInt16( &uint16_buffer[0] );
  EXPECT_EQ ( "adbc44d359d3b3c032629bab34e3ee62c4563223", sitk::Hash( importer.Execute() ) ) << " hash value for uint16";

  int16_buffer = std::vector< int16_t >( 16*16, -3 );
  importer.SetBufferAsInt16( &int16_buffer[0] );
  EXPECT_EQ ( "8111171305e02db2276c7366d117598b1f6789ff", sitk::Hash( importer.Execute() ) ) << " hash value for int16";

  uint32_buffer = std::vector< uint32_t >( 16*16, 8 );
  importer.SetBufferAsUInt32( &uint32_buffer[0] );
  EXPECT_EQ ( "4b710847b34bc5e96520de8a1d7b97563077423c", sitk::Hash( importer.Execute() ) ) << " hash value for uint32";

  int32_buffer = std::vector< int32_t >( 16*16, -123 );
  importer.SetBufferAsInt32( &int32_buffer[0] );
  EXPECT_EQ ( "d5748f3800b837611dc94c089ac7926f2bbea973" , sitk::Hash( importer.Execute() ) ) << " hash value for int32";

  float_buffer = std::vector< float >( 16*16, 1.123 );
  importer.SetBufferAsFloat( &float_buffer[0] );
  EXPECT_EQ ( "8588f5624f56bb55693d54505388dc06b93d2f14", sitk::Hash( importer.Execute() ) ) << " hash value for float";

  double_buffer = std::vector< double >( 16*16, 321.123 );
  importer.SetBufferAsDouble( &double_buffer[0] );
  EXPECT_EQ ( "00393fe0b94729ff0f777ce848104697ce689c70", sitk::Hash( importer.Execute() ) ) << " hash value for double";

}


TEST_F(Import,Procedual) {

  sitk::Image img(0,0,sitk::sitkUInt8);
  std::vector< unsigned int > size( 2, 16u );

  direction2D[0] = direction2D[3] = -1.0;

  uint8_buffer = std::vector< uint8_t >( 16*16, 1 );
  img = sitk::ImportAsUInt8( &uint8_buffer[0],
                             size,
                             spacing2,
                             origin2,
                             direction2D );
  EXPECT_EQ ( "ac458b067c6b021c7e9358229b636e9d1e4cb154", sitk::Hash( img ) ) << " hash value for uint8";
  EXPECT_EQ ( img.GetSpacing(), spacing2 ) << " spacing for uint8";
  EXPECT_EQ ( img.GetOrigin(), origin2 ) << " origin for uint8";
  EXPECT_EQ ( img.GetDirection(), direction2D ) << " direction for uint8";

  int8_buffer = std::vector< int8_t >( 16*16, -1 );
  img = sitk::ImportAsInt8( &int8_buffer[0],
                            size,
                            spacing2,
                            origin2,
                            direction2D );
  EXPECT_EQ ( "c744cac6af7621524fc3a2b0a9a135a32b33c81b", sitk::Hash( img ) ) << " hash value for int8";
  EXPECT_EQ ( img.GetSpacing(), spacing2 ) << " spacing for int8";
  EXPECT_EQ ( img.GetOrigin(), origin2 )  << " origin for int8";
  EXPECT_EQ ( img.GetDirection(), direction2D ) << " direction for int8";


  uint16_buffer = std::vector< uint16_t >( 16*16, 2 );
  img = sitk::ImportAsUInt16( &uint16_buffer[0],
                              size,
                              spacing2,
                              origin2,
                              direction2D );
  EXPECT_EQ ( "adbc44d359d3b3c032629bab34e3ee62c4563223", sitk::Hash( img ) ) << " hash value for uint16";
  EXPECT_EQ ( img.GetSpacing(), spacing2 ) << " spacing for uint16";
  EXPECT_EQ ( img.GetOrigin(), origin2 ) << " origin for uint16";
  EXPECT_EQ ( img.GetDirection(), direction2D ) << " direction for uint16";


  int16_buffer = std::vector< int16_t >( 16*16, -3 );
  img = sitk::ImportAsInt16( &int16_buffer[0],
                             size,
                             spacing2,
                             origin2,
                             direction2D );
  EXPECT_EQ ( "8111171305e02db2276c7366d117598b1f6789ff", sitk::Hash( img ) ) << " hash value for int16";
  EXPECT_EQ ( img.GetSpacing(), spacing2 ) << " spacing for int16";
  EXPECT_EQ ( img.GetOrigin(), origin2 )  << " origin for int16";
  EXPECT_EQ ( img.GetDirection(), direction2D ) << " direction for int16";


  uint32_buffer = std::vector< uint32_t >( 16*16, 8 );
  img = sitk::ImportAsUInt32( &uint32_buffer[0],
                              size,
                              spacing2,
                              origin2,
                              direction2D );
  EXPECT_EQ ( "4b710847b34bc5e96520de8a1d7b97563077423c", sitk::Hash( img ) ) << " hash value for uint32";
  EXPECT_EQ ( img.GetSpacing(), spacing2 )  << " spacing for uint32";
  EXPECT_EQ ( img.GetOrigin(), origin2 )  << " origin for uint32";
  EXPECT_EQ ( img.GetDirection(), direction2D ) << " direction for uint32";


  int32_buffer = std::vector< int32_t >( 16*16, -123 );
  img = sitk::ImportAsInt32( &int32_buffer[0],
                             size,
                             spacing2,
                             origin2,
                             direction2D );
  EXPECT_EQ ( "d5748f3800b837611dc94c089ac7926f2bbea973" , sitk::Hash( img ) ) << " hash value for int32";
  EXPECT_EQ ( img.GetSpacing(), spacing2 ) << " spacing for int32";
  EXPECT_EQ ( img.GetOrigin(), origin2 )  << " origin for int32";
  EXPECT_EQ ( img.GetDirection(), direction2D ) << " direction for int32";


  float_buffer = std::vector< float >( 16*16, 1.123 );
  img = sitk::ImportAsFloat( &float_buffer[0],
                             size,
                             spacing2,
                             origin2,
                             direction2D );
  EXPECT_EQ ( "8588f5624f56bb55693d54505388dc06b93d2f14", sitk::Hash( img ) ) << " hash value for float";
  EXPECT_EQ ( img.GetSpacing(), spacing2 ) << " spacing for float";
  EXPECT_EQ ( img.GetOrigin(), origin2 ) << " origin for float";
  EXPECT_EQ ( img.GetDirection(), direction2D ) << " direction for float";


  double_buffer = std::vector< double >( 16*16, 321.123 );
  img = sitk::ImportAsDouble( &double_buffer[0],
                              size,
                              spacing2,
                              origin2,
                              direction2D );
  EXPECT_EQ ( "00393fe0b94729ff0f777ce848104697ce689c70", sitk::Hash( img ) ) << " hash value for double";
  EXPECT_EQ ( img.GetSpacing(), spacing2 ) << " spacing for double";
  EXPECT_EQ ( img.GetOrigin(), origin2 ) << " origin for float";
  EXPECT_EQ ( img.GetDirection(), direction2D ) << " direction for double";

}
