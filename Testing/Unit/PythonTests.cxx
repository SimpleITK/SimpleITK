#include "SimpleITKTestHarness.h"
#include "SimpleITK.h"

class Python : public ExternalProgramRunner {
};


TEST_F(Python,SimpleGaussian) {
  // Run the simple gaussian command line program
  std::string Script = dataFinder.getSourceDirectory() + "/Examples/SimpleGaussian.py";
  std::string output = dataFinder.getOutputFile ( "Python.SimpleGaussian.nrrd" );
  std::vector<std::string> CommandLine;
  
  CommandLine.push_back ( "python" + std::string ( EXECUTABLE_SUFFIX ) );
  CommandLine.push_back ( Script );
  CommandLine.push_back ( dataFinder.getFile ( "Input/HeadMRVolumeWithDirection.nhdr" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

  // Set our python path
  std::string path = dataFinder.getExecutableDirectory() + "../Wrapping";
  setenv ( "PYTHONPATH", path.c_str(), 1 );
  // Run it!
  RunExecutable ( CommandLine, true );
  ASSERT_TRUE ( dataFinder.fileExists ( output ) );
  itk::simple::ImageFileReader reader;
  itk::simple::ImageHashFilter hasher;
  itk::simple::Image::Pointer image;

  image = reader.SetFilename ( output ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() ) << "Loaded output image";
  EXPECT_EQ ( "71b3f3fd8bb79e1f355c3a3bfcbdf3fa82dd149e", hasher.Execute ( image ) );

}
