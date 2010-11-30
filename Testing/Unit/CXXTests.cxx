#include "SimpleITKTestHarness.h"
#include "SimpleITK.h"

class CXX : public ExternalProgramRunner {
};


TEST_F(CXX,SimpleGaussian) {
  // Run the simple gaussian command line program
  std::string output = dataFinder.GetOutputFile ( "CXX.SimpleGaussian.nrrd" );
  std::vector<std::string> CommandLine;
  
  std::string exe = dataFinder.FindExecutable ( "SimpleGaussian" );
  ASSERT_TRUE ( dataFinder.FileExists ( exe ) ) << "Couldn't find " << exe;

  CommandLine.push_back ( exe );
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

TEST_F(CXX,Add) {
  // Run the simple gaussian command line program
  std::string output = dataFinder.GetOutputFile ( "CXX.Add.nrrd" );
  std::vector<std::string> CommandLine;
  
  std::string exe = dataFinder.FindExecutable ( "Add" );
  ASSERT_TRUE ( dataFinder.FileExists ( exe ) ) << "Couldn't find " << exe;

  CommandLine.push_back ( exe );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/HeadMRVolumeWithDirection.nhdr" ).c_str() );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/HeadMRVolumeWithDirection.nhdr" ).c_str() );
  CommandLine.push_back ( output );

  // Run it!
  RunExecutable ( CommandLine, true );
  ASSERT_TRUE ( dataFinder.FileExists ( output ) );
  itk::simple::ImageFileReader reader;
  itk::simple::ImageHashFilter hasher;
  itk::simple::Image::Pointer image;

  image = reader.SetFilename ( output ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() ) << "Loaded output image";
  EXPECT_EQ ( "be139aab45c82c27163134688a92245670e75f74", hasher.Execute ( image ) );
}

TEST_F(CXX,BinaryThreshold) {
  // Run the simple gaussian command line program
  std::string output = dataFinder.GetOutputFile ( "CXX.BinaryThreshold.nrrd" );
  std::vector<std::string> CommandLine;
  
  std::string exe = dataFinder.FindExecutable ( "BinaryThreshold" );
  ASSERT_TRUE ( dataFinder.FileExists ( exe ) ) << "Couldn't find " << exe;

  CommandLine.push_back ( exe );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/HeadMRVolumeWithDirection.nhdr" ).c_str() );
  CommandLine.push_back ( "10.0" );
  CommandLine.push_back ( "100.0" );
  CommandLine.push_back ( output );

  // Run it!
  RunExecutable ( CommandLine, true );
  ASSERT_TRUE ( dataFinder.FileExists ( output ) );
  itk::simple::ImageFileReader reader;
  itk::simple::ImageHashFilter hasher;
  itk::simple::Image::Pointer image;

  image = reader.SetFilename ( output ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() ) << "Loaded output image";
  EXPECT_EQ ( "36eac6525231e0cdf8c20d3c7d405b199f30d779", hasher.Execute ( image ) );
}
