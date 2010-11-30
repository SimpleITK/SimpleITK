#include <SimpleITK.h>
#include <SimpleITKTestHarness.h>

TEST(IO,ImageFileReader) {
  itk::simple::ImageHashFilter hasher;
  itk::simple::ImageFileReader reader;
  itk::simple::Image::Pointer image;

  typedef std::map<std::string,std::string> MapType;
  MapType mapping;

  // Configure the mapping between filename and MD5 hash
  mapping["Input/HeadMRVolume.mha"] = "dd13d3cbfd470c6e3cd2ddb2302fd466";
  mapping["Input/HeadMRVolumeWithDirection.nhdr"] = "dd13d3cbfd470c6e3cd2ddb2302fd466";
  mapping["Input/LittleEndian.hdr"] = "61cefb1edcdef195131470f03a8238c6";
  mapping["Input/BigEndian.hdr"] = "61cefb1edcdef195131470f03a8238c6";

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
  std::string md5 = "dd13d3cbfd470c6e3cd2ddb2302fd466";
  std::string sha1 = "269fea1c6db001f76b8c482e2fd3a24ef9866f9a";


  image = reader.SetFilename ( dataFinder.GetFile ( "Input/HeadMRVolumeWithDirection.nhdr" ) ).Execute();
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
  image = reader.SetFilename ( dataFinder.GetFile ( "Input/circle.png" ) ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() );
  ASSERT_EQ ( 2u, image->GetDimension() );
}




