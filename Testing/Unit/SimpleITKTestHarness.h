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
    mExecutableDirectory = EXECUTABLE_PATH;
  };
  void setDirectory ( const char* dir ) {
    mDirectory = dir;
  };
  void setDirectory ( std::string dir ) {
    mDirectory = dir;
  };
  void setExecutableDirectory ( std::string dir ) {
    mExecutableDirectory = dir;
  }
  void setOutputDirectory ( std::string dir ) {
    mOutputDirectory = dir;
  };
  std::string getDirectory () { return mDirectory; };
  std::string getOutputDirectory () { return mOutputDirectory; };
  std::string getOutputFile ( std::string filename ) { return mOutputDirectory + "/" + filename; };
  std::string getExecutableDirectory() { return mExecutableDirectory; }
  std::string findExecutable ( std::string exe ) { return getExecutableDirectory() + "/" + exe + EXECUTABLE_SUFFIX; }
  std::string getLuaExecutable() { return std::string ( SIMPLEITK_LUA_EXECUTABLE_PATH ); }
  std::string getSourceDirectory() { return std::string ( SIMPLEITK_SOURCE_DIR ); }
  bool fileExists ( std::string filename ) { return itksys::SystemTools::FileExists ( filename.c_str() ); }
  std::string getFile ( std::string filename ) {
    return mDirectory + "/" + filename;
  };

  
 protected:
  std::string mDirectory;
  std::string mExecutableDirectory;
  std::string mOutputDirectory;
};

extern DataFinder dataFinder;


// Support for running external commands
// Class for running external programs
class ExternalProgramRunner : public testing::Test {
public:
  /* Run the command line specified in the list of arguments.  Call FAIL if the executable fails
   */
  void RunExecutable ( std::vector<std::string> CommandLine, bool showOutput = false ) {

    std::string fullCommand;
    for ( unsigned int idx = 0; idx < CommandLine.size(); idx++ ) {
      fullCommand += CommandLine[idx];
      fullCommand += " ";
    }

    if ( showOutput ) {
      std::cout << "Running command: '" << fullCommand << "'" << std::endl;
    }

    // Allocate what we need
    const char* StringCommandLine[256];
    for ( unsigned int idx = 0; idx < CommandLine.size(); idx++ ) {
      StringCommandLine[idx] = CommandLine[idx].c_str();
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
      std::cerr << "Error executing '" << fullCommand << "': " << itksysProcess_GetErrorString ( process ) << std::endl;
      failed = true;
    } else if ( itksysProcess_GetState ( process ) == itksysProcess_State_Exception ) {
      std::cerr << "Error executing '" << fullCommand << "': " << itksysProcess_GetExceptionString ( process ) << std::endl;
      failed = true;
    }
    itksysProcess_Delete ( process );
    // Free stuff
    for ( unsigned int idx = 0; idx < CommandLine.size(); idx++ ) {
      // delete[] StringCommandLine[idx];
    }
    if ( failed ) {
      FAIL();
    }
  }
};



#endif
