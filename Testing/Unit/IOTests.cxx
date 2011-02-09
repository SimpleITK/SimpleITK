#include <SimpleITKTestHarness.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>

TEST(IO,ImageFileReader) {
  itk::simple::HashImageFilter hasher;
  itk::simple::ImageFileReader reader;
  itk::simple::Image::Pointer image;

  typedef std::map<std::string,std::string> MapType;
  MapType mapping;

  // Configure the mapping between filename and MD5 hash
  mapping["Input/RA-Short.nrrd"]            = "a963bd6a755b853103a2d195e01a50d3";
  mapping["Input/RA-Float.nrrd"]            = "3ccccde44efaa3d688a86e94335c1f16";
  mapping["Input/RA-Slice-Short.nrrd"]      = "22cdc0af7d51934a744b9c4fd4748cd1";
  mapping["Input/RA-Slice-Float.nrrd"]      = "999078d36a4491d691cc93d8c3ed29fc";
  mapping["Input/Ramp-Zero-One-Float.nrrd"] = "f47efe1a6f48cb5cfe1aa23232f1168b";
  mapping["Input/Ramp-One-Zero-Float.nrrd"] = "0b18fac85955571d069b3666ff987119";
  mapping["Input/Ramp-Up-Short.nrrd"]       = "86f2ea8a68b3069f33f2271829a30aa2";
  mapping["Input/Ramp-Down-Short.nrrd"]     = "71f5c852a6251069fa1d60f796463343";
  mapping["Input/STAPLE1.png"]              = "095f00a68a84df4396914fa758f34dcc";
  mapping["Input/STAPLE2.png"]              = "301858f5eee39b092d28d9837f008fb8";


  // Loop over the map, load each file, and compare the hash value
  for ( MapType::iterator it = mapping.begin(); it != mapping.end(); ++it ) {
    reader.SetFileName ( dataFinder.GetFile ( it->first ) );
    EXPECT_EQ ( reader.GetFileName(), dataFinder.GetFile ( it->first ) );
    image = reader.Execute();
    ASSERT_TRUE ( image->GetImageBase().IsNotNull() );
    hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 );
    EXPECT_EQ ( it->second, hasher.Execute ( image ) ) << " reading " << it->first;
    // Try the functional interface
    EXPECT_EQ ( it->second, hasher.Execute ( itk::simple::ReadImage ( dataFinder.GetFile ( it->first ) ) ) ) << "Functional interface";
  }

}

TEST(IO,ReadWrite) {
  itk::simple::HashImageFilter hasher;
  itk::simple::ImageFileReader reader;
  itk::simple::ImageFileWriter writer;
  itk::simple::Image::Pointer image;

  // From the command line utility
  std::string md5 = "a963bd6a755b853103a2d195e01a50d3";
  std::string sha1 = "126ea8c3ef5573ca1e4e0deece920c2c4a4f38b5";


  image = reader.SetFileName ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ) ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() );
  hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 );
  EXPECT_EQ ( md5, hasher.Execute ( image ) );
  hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 );
  EXPECT_EQ ( sha1, hasher.Execute ( image ) );

  // Write it out
  std::string filename = dataFinder.GetOutputFile ( "IO.ReadWrite.nrrd" );
  writer.SetFileName ( filename ).Execute ( image );
  ASSERT_TRUE ( dataFinder.FileExists ( filename ) );
  image = reader.SetFileName ( filename ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() );

  // Make sure we wrote and read the file correctly
  hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 );
  EXPECT_EQ ( md5, hasher.Execute ( image ) );
  hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 );
  EXPECT_EQ ( sha1, hasher.Execute ( image ) );

  // Again, with the functional interface
  filename = dataFinder.GetOutputFile ( "IO.ReadWrite-Functional.nrrd" );
  itk::simple::WriteImage ( image, filename );
  ASSERT_TRUE ( dataFinder.FileExists ( filename ) );
  image = reader.SetFileName ( filename ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() );

  // Make sure we wrote and read the file correctly
  hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 );
  EXPECT_EQ ( md5, hasher.Execute ( image ) );
  hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 );
  EXPECT_EQ ( sha1, hasher.Execute ( image ) );
}
  
  
TEST(IO,2DFormats) {
  itk::simple::HashImageFilter hasher;
  itk::simple::ImageFileReader reader;
  itk::simple::Image::Pointer image;
  image = reader.SetFileName ( dataFinder.GetFile ( "Input/RA-Slice-Short.png" ) ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() );
  hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 );
  EXPECT_EQ ( "bf0f7bae60b0322222e224941c31f37a981901aa", hasher.Execute ( image ) );
  ASSERT_EQ ( 2u, image->GetDimension() );
  EXPECT_EQ ( 64u, image->GetWidth() );
  EXPECT_EQ ( 64u, image->GetHeight() );
  EXPECT_EQ ( 0u, image->GetDepth() );

}




