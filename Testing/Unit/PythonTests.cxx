#include "SimpleITKTestHarness.h"

#include <sitkImage.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>

#if defined(WRAP_PYTHON)

TEST_F(Python,ImageTest) {
  // Run the simple gaussian command line program
  std::string Script = dataFinder.GetSourceDirectory() + "/Testing/Unit/ImageTest.py";
  std::vector<std::string> CommandLine;

  CommandLine.push_back ( dataFinder.GetPythonExecutable() );
  CommandLine.push_back ( Script );

  // Set our python path
  std::string path = dataFinder.GetBuildDirectory() + "/Wrapping"
    + GetPathSeparator() + dataFinder.GetRuntimeDirectory() + GetPathSeparator() + dataFinder.GetLibraryDirectory();
  SetEnvironment ( "PYTHONPATH", path );

  // Run it!
  EXPECT_EQ( 0, RunExecutable ( CommandLine, true ) ) << "Failing return value.";

}


TEST_F(Python,N4BiasFieldCorrection) {

  // run the example python code
  std::string Script = dataFinder.GetSourceDirectory() + "/Examples/N4BiasFieldCorrection.py";
  std::string output = dataFinder.GetOutputFile ( "Python.N4BiasFieldCorrection.nrrd" );
  std::vector<std::string> CommandLine;

  CommandLine.push_back ( dataFinder.GetPythonExecutable() );
  CommandLine.push_back ( Script );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/cthead1.png" ).c_str() );
  CommandLine.push_back ( output );
  CommandLine.push_back ( "1" );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/2th_cthead1.png" ).c_str() );
  CommandLine.push_back ( "20" );
  CommandLine.push_back ( "2" );


  CommandLine.push_back ( output );

  // Set our python path
  std::string path = dataFinder.GetBuildDirectory() + "/Wrapping"
    + GetPathSeparator() + dataFinder.GetRuntimeDirectory() + GetPathSeparator() + dataFinder.GetLibraryDirectory();

  SetEnvironment ( "PYTHONPATH", path );

  // Run it!
  RunExecutable ( CommandLine, true );

  // We are bad and don't check the output

}

#endif
