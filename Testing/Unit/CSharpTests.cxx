#include "SimpleITKTestHarness.h"

#include <sitkImage.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>

#if defined(WRAP_CSHARP)
TEST_F(CSharp,ExampleSimpleGaussian) {

  std::string ExePath = dataFinder.GetCSharpBinaryDirectory();
  std::string ExeName = "SimpleITKCSharpExampleSimpleGaussian.exe";
  std::string ExePathAndName = ExePath + "/" + ExeName;

  // Run SimpleGaussian example
  {
  std::vector<std::string> CommandLine;
  std::string output = dataFinder.GetOutputFile ( "CSharp-ExampleSimpleGaussian.nrrd" );
  // Make sure the output is wiped
  EXPECT_NO_THROW ( itk::simple::WriteImage( itk::simple::Image ( 1,1,1,itk::simple::sitkUInt8 ), output ) ) << "Failed to overwrite";

  if ( dataFinder.GetCSharpInterpreter().length() > 0 ) {
    CommandLine.push_back ( dataFinder.GetCSharpInterpreter() );
  }
  CommandLine.push_back ( ExePathAndName );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

  RunExecutable ( CommandLine, true );

  this->CheckImageHash( output, "02ce020f462cf05f3c354bc33a7834603d65b906" );
  }

}

#endif
