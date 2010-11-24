#include "SimpleITKTestHarness.h"
#include "SimpleITK.h"

class CXX : public ExternalProgramRunner {
};


TEST_F(CXX,SimpleGaussian) {
  // Run the simple gaussian command line program
  std::string output = dataFinder.getOutputFile ( "CXX.SimpleGaussian.nrrd" );
  std::vector<std::string> CommandLine;
  
  std::string exe = dataFinder.findExecutable ( "SimpleGaussian" );
  ASSERT_TRUE ( dataFinder.fileExists ( exe ) ) << "Couldn't find " << exe;

  CommandLine.push_back ( exe );
  CommandLine.push_back ( dataFinder.getFile ( "Input/HeadMRVolumeWithDirection.nhdr" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

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

TEST_F(CXX,Add) {
  // Run the simple gaussian command line program
  std::string output = dataFinder.getOutputFile ( "CXX.Add.nrrd" );
  std::vector<std::string> CommandLine;
  
  std::string exe = dataFinder.findExecutable ( "Add" );
  ASSERT_TRUE ( dataFinder.fileExists ( exe ) ) << "Couldn't find " << exe;

  CommandLine.push_back ( exe );
  CommandLine.push_back ( dataFinder.getFile ( "Input/HeadMRVolumeWithDirection.nhdr" ).c_str() );
  CommandLine.push_back ( dataFinder.getFile ( "Input/HeadMRVolumeWithDirection.nhdr" ).c_str() );
  CommandLine.push_back ( output );

  // Run it!
  RunExecutable ( CommandLine, true );
  ASSERT_TRUE ( dataFinder.fileExists ( output ) );
  itk::simple::ImageFileReader reader;
  itk::simple::ImageHashFilter hasher;
  itk::simple::Image::Pointer image;

  image = reader.SetFilename ( output ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() ) << "Loaded output image";
  EXPECT_EQ ( "", hasher.Execute ( image ) );
}

TEST_F(CXX,BinaryThreshold) {
  // Run the simple gaussian command line program
  std::string output = dataFinder.getOutputFile ( "CXX.BinaryThreshold.nrrd" );
  std::vector<std::string> CommandLine;
  
  std::string exe = dataFinder.findExecutable ( "BinaryThreshold" );
  ASSERT_TRUE ( dataFinder.fileExists ( exe ) ) << "Couldn't find " << exe;

  CommandLine.push_back ( exe );
  CommandLine.push_back ( dataFinder.getFile ( "Input/HeadMRVolumeWithDirection.nhdr" ).c_str() );
  CommandLine.push_back ( "10.0" );
  CommandLine.push_back ( "100.0" );
  CommandLine.push_back ( output );

  // Run it!
  RunExecutable ( CommandLine, true );
  ASSERT_TRUE ( dataFinder.fileExists ( output ) );
  itk::simple::ImageFileReader reader;
  itk::simple::ImageHashFilter hasher;
  itk::simple::Image::Pointer image;

  image = reader.SetFilename ( output ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() ) << "Loaded output image";
  EXPECT_EQ ( "", hasher.Execute ( image ) );
}
