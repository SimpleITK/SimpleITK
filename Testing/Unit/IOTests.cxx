#include <SimpleITK.h>
#include <SimpleITKTestHarness.h>

TEST(IO,ImageFileReader) {
  itk::simple::ImageHashFilter hasher;
  itk::simple::ImageFileReader reader;
  itk::simple::Image::Pointer image;

  typedef std::map<std::string,std::string> MapType;
  MapType mapping;

  // Configure the mapping between filename and MD5 hash
  mapping["Input/HeadMRVolume.mha"] = "269fea1c6db001f76b8c482e2fd3a24ef9866f9a";
  mapping["Input/HeadMRVolumeWithDirection.nhdr"] = "269fea1c6db001f76b8c482e2fd3a24ef9866f9a";
  mapping["Input/LittleEndian.hdr"] = "1e16b6ccb0b282069a1e278fa283efce444eeca3";
  mapping["Input/BigEndian.hdr"] = "1e16b6ccb0b282069a1e278fa283efce444eeca3";

  // Loop over the map, load each file, and compare the hash value
  for ( MapType::iterator it = mapping.begin(); it != mapping.end(); ++it ) {
    reader.SetFilename ( dataFinder.getFile ( it->first ) );
    image = reader.Execute();
    ASSERT_TRUE ( image->GetITKImage().IsNotNull() );
    EXPECT_EQ ( it->second, hasher.Execute ( image ) ) << " reading " << it->first;
  }


}






