#include <sitkImportImageFilter.h>
#include <SimpleITKTestHarness.h>

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
  }

  std::vector<double> spacing1;
  std::vector<double> spacing2;

  std::vector<double> origin0;
  std::vector<double> origin1;
  std::vector<double> origin2;

  std::vector< uint8_t > uint8_buffer;
  std::vector< uint16_t > uint16_buffer;
  std::vector< int16_t > int16_buffer;
  std::vector< uint32_t > uint32_buffer;
  std::vector< int32_t > int32_buffer;
  std::vector< float > float_buffer;
  std::vector< double > double_buffer;
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
  importer.SetBufferAsUInt8( &uint8_buffer[0] );

  sitk::Image image = importer.Execute();

  ASSERT_EQ( image.GetDimension(), 3u ) << "image dimension check";

  EXPECT_EQ( image.GetSize()[0], 128u ) << "X size check";
  EXPECT_EQ( image.GetSize()[1], 128u ) << "Y size check";
  EXPECT_EQ( image.GetSize()[2], 128u ) << "Z size check";

  //EXPECT_EQ( image.GetOrigin(), origin0 ) << "origin check";
  //EXPECT_EQ( image.GetSpacing(), spacing1 ) << "spacing check";


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
  importer.SetBufferAsInt32( &int32_buffer[0] );

  image = importer.Execute();

  ASSERT_EQ( image.GetDimension(), 2u ) << "image dimension check";

  EXPECT_EQ( image.GetSize()[0], 73u ) << "X size check";
  EXPECT_EQ( image.GetSize()[1], 73u ) << "Y size check";

  //EXPECT_EQ( image.GetOrigin(), origin2 ) << "origin check";
  //EXPECT_EQ( image.GetSpacing(), spacing2 ) << "spacing check";

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


TEST_F(Import,ExhaustiveTypes) {

  sitk::ImportImageFilter importer;
  importer.SetSize( std::vector< unsigned int >( 2, 16u ) );
  importer.SetSpacing( spacing1 );
  importer.SetOrigin( origin0 );

  uint8_buffer = std::vector< uint8_t >( 16*16, 1 );
  importer.SetBufferAsUInt8( &uint8_buffer[0] );
  EXPECT_EQ ( "ac458b067c6b021c7e9358229b636e9d1e4cb154", sitk::Hash( importer.Execute() ) ) << " hash value for uint8";

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
