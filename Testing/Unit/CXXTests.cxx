/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#include "SimpleITKTestHarness.h"

#include <sitkImage.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>

class CXX : public ExternalProgramRunner {
};


TEST_F(CXX,SimpleGaussian) {
  // Run the simple gaussian command line program
  std::string output = dataFinder.GetOutputFile ( "CXX.SimpleGaussian.nrrd" );
  std::vector<std::string> CommandLine;

  std::vector<std::string> exe = dataFinder.FindExecutable ( "SimpleGaussian" );
  ASSERT_TRUE ( dataFinder.FileExists ( exe[0] ) ) << "Couldn't find " << exe[0];

  CommandLine = exe;
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

  std::vector<std::string> exe = dataFinder.FindExecutable ( "SimpleGaussianFunctional" );
  ASSERT_TRUE ( dataFinder.FileExists ( exe[0] ) ) << "Couldn't find " << exe[0];

  CommandLine = exe;
  CommandLine.push_back ( dataFinder.GetFile ( "Input/RA-Short.nrrd" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

  // Run it!
  RunExecutable ( CommandLine, true );

  this->CheckImageHash( output, "02ce020f462cf05f3c354bc33a7834603d65b906" );
}

