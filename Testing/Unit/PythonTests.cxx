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
    + GetPathSeparator() + dataFinder.GetRuntimeDirectory() + GetPathSeparator() + dataFinder.GetLibraryDirectory();

  //DEBUG
  std::cout << "PYTHONPATH = " << path << std::endl;

  SetEnvironment ( "PYTHONPATH", path );

  // Run it!
  RunExecutable ( CommandLine, true );

  this->CheckImageHash( output, "02ce020f462cf05f3c354bc33a7834603d65b906" );

}

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

TEST_F(Python,IOTest) {
  // Run the simple gaussian command line program
  std::string Script = dataFinder.GetSourceDirectory() + "/Testing/Unit/IOTest.py";
  std::vector<std::string> CommandLine;

  CommandLine.push_back ( dataFinder.GetPythonExecutable() );
  CommandLine.push_back ( Script );
  CommandLine.push_back ( dataFinder.GetOutputDirectory() );

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
