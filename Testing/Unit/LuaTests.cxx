#include "SimpleITKTestHarness.h"
#include "SimpleITK.h"

class Lua : public ExternalProgramRunner {
};


TEST_F(Lua,SimpleGaussian) {
  // Run the simple gaussian command line program
  std::string Script = dataFinder.GetSourceDirectory() + "/Examples/SimpleGaussian.lua";
  std::string output = dataFinder.GetOutputFile ( "Lua.SimpleGaussian.nrrd" );
  std::vector<std::string> CommandLine;
  
  CommandLine.push_back ( dataFinder.GetLuaExecutable() );
  CommandLine.push_back ( Script );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/HeadMRVolumeWithDirection.nhdr" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

  // Run it!
  RunExecutable ( CommandLine, true );
  ASSERT_TRUE ( dataFinder.FileExists ( output ) );
  itk::simple::ImageFileReader reader;
  itk::simple::ImageHashFilter hasher;
  itk::simple::Image::Pointer image;

  image = reader.SetFilename ( output ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() ) << "Loaded output image";
  EXPECT_EQ ( "71b3f3fd8bb79e1f355c3a3bfcbdf3fa82dd149e", hasher.Execute ( image ) );

}
