#include "SimpleITKTestHarness.h"

#include <sitkImage.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>

#if defined(WRAP_PYTHON)

TEST_F(Python,SimpleGaussian) {
  // Run the simple gaussian command line program
  std::string Script = dataFinder.GetSourceDirectory() + "/Examples/SimpleGaussian.py";
  std::string output = dataFinder.GetOutputFile ( "Python.SimpleGaussian.nrrd" );
  std::vector<std::string> CommandLine;
  
  CommandLine.push_back ( dataFinder.GetPythonExecutable() );
  CommandLine.push_back ( Script );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

  // Set our python path
  std::string path = dataFinder.GetBuildDirectory() + "/Wrapping" 
    + GetPathSeparator() + dataFinder.GetExecutableDirectory();
  SetEnvironment ( "PYTHONPATH", path );

  // Run it!
  RunExecutable ( CommandLine, true );
  ASSERT_TRUE ( dataFinder.FileExists ( output ) );
  itk::simple::ImageFileReader reader;
  itk::simple::HashImageFilter hasher;
  itk::simple::Image* image;

  image = reader.SetFileName ( output ).Execute();
  ASSERT_TRUE ( image != NULL );
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() ) << "Loaded output image";
  EXPECT_EQ ( "9d3d4acf41aa62b453cfd6684ad7c361290462d1", hasher.Execute ( image ) );
  delete image;
}

#endif
