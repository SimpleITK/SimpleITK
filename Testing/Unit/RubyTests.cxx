#include "SimpleITKTestHarness.h"

#include <sitkImage.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>

#if defined(WRAP_RUBY)
TEST_F(Ruby,SimpleGaussian) {
  // Run the simple gaussian command line program
  std::string Script = dataFinder.GetSourceDirectory() + "/Examples/SimpleGaussian.rb";
  std::string output = dataFinder.GetOutputFile ( "Ruby.SimpleGaussian.nrrd" );
  std::vector<std::string> CommandLine;
  
  CommandLine.push_back ( dataFinder.GetRubyExecutable() );
  CommandLine.push_back ( Script );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

  // Set our Ruby path
  SetEnvironment ( "RUBYLIB", dataFinder.GetExecutableDirectory() );

  // Run it!
  RunExecutable ( CommandLine, true );
  ASSERT_TRUE ( dataFinder.FileExists ( output ) );
  itk::simple::ImageFileReader reader;
  itk::simple::HashImageFilter hasher;

  itk::simple::Image image = reader.SetFileName ( output ).Execute();
  ASSERT_TRUE ( image.GetImageBase() != NULL ) << "Loaded output image";
  EXPECT_EQ ( "de64d7d8ebfa529581f57b8c603f3d656564284f", hasher.Execute ( image ) );
}

#endif
