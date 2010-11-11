#ifndef __SimpleITKTestHarness_h
#define __SimpleITKTestHarness_h

#include <string>
#include <gtest/gtest.h>
#include <SimpleITKTestHarnessPaths.h>
#include <itksys/SystemTools.hxx>
#include <itksys/Process.h>

// Class to help us find test data
class DataFinder {
 public:
  DataFinder () { 
    mDirectory = TEST_HARNESS_DATA_DIRECTORY;
    mOutputDirectory = TEST_HARNESS_TEMP_DIRECTORY;
  };
  void setDirectory ( const char* dir ) {
    mDirectory = dir;
  };
  void setDirectory ( std::string dir ) {
    mDirectory = dir;
  };
  void setOutputDirectory ( std::string dir ) {
    mOutputDirectory = dir;
  };
  std::string getDirectory () { return mDirectory; };
  std::string getOutputDirectory () { return mOutputDirectory; };
  std::string getOutputFile ( std::string filename ) { return mOutputDirectory + "/" + filename; };
  std::string getExecutableDirectory() { return std::string ( EXECUTABLE_PATH ); }
  std::string getSourceDirectory() { return std::string ( SIMPLEITK_SOURCE_DIR ); }
  std::string getFile ( std::string filename ) {
    return mDirectory + "/" + filename;
  };

  
 protected:
  std::string mDirectory;
  std::string mOutputDirectory;
};

extern DataFinder dataFinder;


// Support for running external commands
// Class for running external programs
class ExternalProgramRunner : public testing::Test {
public:
  void RunExecutable ( std::vector<std::string> CommandLine, bool showOutput = false ) {

    std::string fullCommand;
    for ( unsigned int idx = 0; idx < CommandLine.size(); idx++ ) {
      fullCommand += CommandLine[idx];
      fullCommand += " ";
    }

    // Allocate what we need
    char* StringCommandLine[256];
    for ( unsigned int idx = 0; idx < CommandLine.size(); idx++ ) {
      StringCommandLine[idx] = new char[CommandLine[idx].length() + 1];
      sprintf ( StringCommandLine[idx], "%s", CommandLine[idx].c_str() );
    }
    StringCommandLine[CommandLine.size()] = NULL;

    itksysProcess* process = itksysProcess_New();
    itksysProcess_SetCommand ( process, StringCommandLine );
    itksysProcess_Execute ( process );

    int status;
    char* processData;
    int processDataLength;
    while ( 1 ) {
      status = itksysProcess_WaitForData ( process, &processData, &processDataLength, NULL );
      if ( status == itksysProcess_Pipe_STDOUT || status == itksysProcess_Pipe_STDERR ) {
        if ( showOutput ) {
          std::cout << std::string ( processData ) << std::endl;
        }
      } else {
        // Nothing ready, so wait for the process to exit...
        break;
      }
    }

    bool failed = false;
    itksysProcess_WaitForExit ( process, 0 );
    if ( itksysProcess_GetState ( process ) == itksysProcess_State_Error ) {
      std::cerr << "Error executing " << CommandLine[0] << itksysProcess_GetErrorString ( process ) << std::endl;
      failed = true;
    } else if ( itksysProcess_GetState ( process ) == itksysProcess_State_Exception ) {
      std::cerr << "Error executing " << CommandLine[0] << itksysProcess_GetExceptionString ( process ) << std::endl;
      failed = true;
    }
    itksysProcess_Delete ( process );
    // Free stuff
    for ( unsigned int idx = 0; idx < CommandLine.size(); idx++ ) {
      delete[] StringCommandLine[idx];
    }
    if ( failed ) {
      FAIL();
    }
  }
};



#endif
