#include "SimpleITKTestHarness.h"

#include <SimpleITK.h>

class CXX : public ExternalProgramRunner {
};


TEST_F(CXX,SimpleGaussian) {
  // Run the simple gaussian command line program
  std::string output = dataFinder.GetOutputFile ( "CXX.SimpleGaussian.nrrd" );
  std::vector<std::string> CommandLine;

  std::string exe = dataFinder.FindExecutable ( "SimpleGaussian" );
  ASSERT_TRUE ( dataFinder.FileExists ( exe ) ) << "Couldn't find " << exe;

  CommandLine.push_back ( exe );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

  // Run it!
  RunExecutable ( CommandLine, true );

  this->CheckImageHash( output, "02ce020f462cf05f3c354bc33a7834603d65b906" );

}

TEST_F(CXX,SimpleGaussianFunctional) {
  // Run the simple gaussian command line program
  std::string output = dataFinder.GetOutputFile ( "CXX.SimpleGaussianFunctional.nrrd" );
  std::vector<std::string> CommandLine;

  std::string exe = dataFinder.FindExecutable ( "SimpleGaussianFunctional" );
  ASSERT_TRUE ( dataFinder.FileExists ( exe ) ) << "Couldn't find " << exe;

  CommandLine.push_back ( exe );
  CommandLine.push_back ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

  // Run it!
  RunExecutable ( CommandLine, true );

  this->CheckImageHash( output, "02ce020f462cf05f3c354bc33a7834603d65b906" );
}

