#include "SimpleITKTestHarness.h"

#include <sitkImage.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkImageHashFilter.h>

TEST_F(Lua,SimpleGaussian) {
  // Run the simple gaussian command line program
  std::string Script = dataFinder.GetSourceDirectory() + "/Examples/SimpleGaussian.lua";
  std::string output = dataFinder.GetOutputFile ( "Lua.SimpleGaussian.nrrd" );
  std::vector<std::string> CommandLine;
  
  CommandLine.push_back ( dataFinder.GetLuaExecutable() );
  CommandLine.push_back ( Script );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

  // Run it!
  RunExecutable ( CommandLine, true );
  ASSERT_TRUE ( dataFinder.FileExists ( output ) );
  itk::simple::ImageFileReader reader;
  itk::simple::ImageHashFilter hasher;
  itk::simple::Image::Pointer image;

  image = reader.SetFileName ( output ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() ) << "Loaded output image";
  EXPECT_EQ ( "9d3d4acf41aa62b453cfd6684ad7c361290462d1", hasher.Execute ( image ) );

}
