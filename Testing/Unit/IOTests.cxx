#include <SimpleITK.h>
#include <SimpleITKTestHarness.h>

TEST(IO,ImageFileReader) {
  itk::simple::ImageHashFilter hasher;
  itk::simple::ImageFileReader reader;
  itk::simple::Image::Pointer image;

  typedef std::map<std::string,std::string> MapType;
  MapType mapping;

  // Configure the mapping between filename and MD5 hash
  mapping["Input/RA-Short.nrrd"] = "a963bd6a755b853103a2d195e01a50d3";
  mapping["Input/RA-Float.nrrd"] = "3ccccde44efaa3d688a86e94335c1f16";
  mapping["Input/RA-Slice-Short.nrrd"] = "22cdc0af7d51934a744b9c4fd4748cd1";
  mapping["Input/RA-Slice-Float.nrrd"] = "999078d36a4491d691cc93d8c3ed29fc";

  // Loop over the map, load each file, and compare the hash value
  for ( MapType::iterator it = mapping.begin(); it != mapping.end(); ++it ) {
    reader.SetFilename ( dataFinder.GetFile ( it->first ) );
    image = reader.Execute();
    ASSERT_TRUE ( image->GetImageBase().IsNotNull() );
    hasher.SetHashFunction ( itk::simple::ImageHashFilter::MD5 );
    EXPECT_EQ ( it->second, hasher.Execute ( image ) ) << " reading " << it->first;
  }

}

TEST(IO,ReadWrite) {
  itk::simple::ImageHashFilter hasher;
  itk::simple::ImageFileReader reader;
  itk::simple::ImageFileWriter writer;
  itk::simple::Image::Pointer image;

  // From the command line utility
  std::string md5 = "a963bd6a755b853103a2d195e01a50d3";
  std::string sha1 = "126ea8c3ef5573ca1e4e0deece920c2c4a4f38b5";


  image = reader.SetFilename ( dataFinder.GetFile ( "Input/RA-short.nrrd" ) ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() );
  hasher.SetHashFunction ( itk::simple::ImageHashFilter::MD5 );
  EXPECT_EQ ( md5, hasher.Execute ( image ) );
  hasher.SetHashFunction ( itk::simple::ImageHashFilter::SHA1 );
  EXPECT_EQ ( sha1, hasher.Execute ( image ) );

  // Write it out
  std::string filename = dataFinder.GetOutputFile ( "IO.ReadWrite.nrrd" );
  writer.SetFilename ( filename ).Execute ( image );
  ASSERT_TRUE ( dataFinder.FileExists ( filename ) );
  image = reader.SetFilename ( filename ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() );

  // Make sure we wrote and read the file correctly
  hasher.SetHashFunction ( itk::simple::ImageHashFilter::MD5 );
  EXPECT_EQ ( md5, hasher.Execute ( image ) );
  hasher.SetHashFunction ( itk::simple::ImageHashFilter::SHA1 );
  EXPECT_EQ ( sha1, hasher.Execute ( image ) );
}
  
  
TEST(IO,2DFormats) {
  itk::simple::ImageHashFilter hasher;
  itk::simple::ImageFileReader reader;
  itk::simple::Image::Pointer image;
  image = reader.SetFilename ( dataFinder.GetFile ( "Input/RA-Slice-Short.png" ) ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() );
  hasher.SetHashFunction ( itk::simple::ImageHashFilter::SHA1 );
  EXPECT_EQ ( "da39a3ee5e6b4b0d3255bfef95601890afd80709", hasher.Execute ( image ) );
  ASSERT_EQ ( 2u, image->GetDimension() );
  EXPECT_EQ ( 64u, image->GetWidth() );
  EXPECT_EQ ( 64u, image->GetHeight() );
  EXPECT_EQ ( 0u, image->GetDepth() );

}




