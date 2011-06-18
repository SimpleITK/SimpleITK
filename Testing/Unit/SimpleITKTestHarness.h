#ifndef __SimpleITKTestHarness_h
#define __SimpleITKTestHarness_h

#include <string>
#include <gtest/gtest.h>
#include <SimpleITKTestHarnessPaths.h>
#include <itksys/SystemTools.hxx>
#include <itksys/Process.h>

#include "sitkImage.h"
#include "sitkImageFileReader.h"
#include "sitkHashImageFilter.h"

// Class to help us find test data
class DataFinder {
  /*
   * DataFinder maintains several directory paths.  It also
   * helps us find executables.
   *
   * Set/GetDirectory  -- Test Data directory
   *                      should be ITK/Testing/Data
   * Set/GetOutputDirectory -- Temporary directory
   *                      SimpleITK-build/Testing/Temporary
   * Set/GetExecutableDirectory -- Where built executables are found
   *                      SimpleITK-build/bin/$(OutDir)/
   * GetOutputFile --     File in the temp directory
   * GetBuildDirectory -- SimpleITK-build
   * FindExecutable --    Attempts to find an executable
   *                      Returns GetExecutableDirectory + "/" + filename
   */

 public:
  DataFinder () {
    mDirectory = TEST_HARNESS_DATA_DIRECTORY;
    mOutputDirectory = TEST_HARNESS_TEMP_DIRECTORY;
    mExecutableDirectory = EXECUTABLE_PATH;
  };
  void SetDirectory ( const char* dir ) {
    mDirectory = dir;
  };
  void SetDirectory ( std::string dir ) {
    mDirectory = dir;
  };
  void SetExecutableDirectoryFromArgv0 ( std::string argv0 ) {
    std::string errorMessage, path, dir, file;
    bool result = itksys::SystemTools::FindProgramPath ( argv0.c_str(), path, errorMessage );
    mExecutableDirectory = "";
    if ( result == false ) {
      std::cerr << "SetExecutableDirectoryFromArgv0: couldn't determine the location of " << argv0 << " error was: " << errorMessage << std::endl;
    } else {
      result = itksys::SystemTools::SplitProgramPath ( path.c_str(), dir, file );
      if ( result == false ) {
        std::cerr << "SetExecutableDirectoryFromArgv0: couldn't split directory from path " << path << std::endl;
      } else {
        mExecutableDirectory = dir;
      }
    }
  }
  void SetOutputDirectory ( std::string dir ) {
    mOutputDirectory = dir;
  };
  std::string GetDirectory () { return mDirectory; };
  std::string GetOutputDirectory () { return mOutputDirectory; };
  std::string GetOutputFile ( std::string filename ) { return mOutputDirectory + "/" + filename; };
  std::string GetExecutableDirectory() { return mExecutableDirectory; }
  std::string GetBuildDirectory() { return std::string ( SIMPLEITK_BINARY_DIR ); }
  std::string GetPathSeparator() {
#ifdef WIN32
    return ";";
#else
    return ":";
#endif
  }
  std::string FindExecutable ( std::string exe ) { return GetExecutableDirectory() + "/" + exe + EXECUTABLE_SUFFIX; }
  std::string GetLuaExecutable() { return this->FindExecutable ( "SimpleITKLua" ); }
  std::string GetTclExecutable() { return this->FindExecutable ( "SimpleITKTclsh" ); }
  std::string GetPythonExecutable() { return std::string ( PYTHON_EXECUTABLE_PATH ); }
  std::string GetRubyExecutable() { return std::string ( RUBY_EXECUTABLE_PATH ); }
  std::string GetRExecutable() { return std::string ( RSCRIPT_EXECUTABLE_PATH ); }
  std::string GetJavaExecutable() { return std::string ( JAVA_EXECUTABLE_PATH ); }
  std::string GetSourceDirectory() { return std::string ( SIMPLEITK_SOURCE_DIR ); }
  bool FileExists ( std::string filename ) { return itksys::SystemTools::FileExists ( filename.c_str() ); }
  std::string GetFile ( std::string filename ) {
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

  // check an image file that it matches the expected hash
  void CheckImageHash( const std::string &fileName, const std::string &hash )
  {
    ASSERT_TRUE ( dataFinder.FileExists ( fileName ) ) << "check if " << fileName << " exists.";

    itk::simple::Image image = itk::simple::ReadImage( fileName );
    EXPECT_EQ ( hash, itk::simple::Hash( image ) );
  }

  // Return the separator
  static std::string GetPathSeparator() {
#ifdef WIN32
    return ";";
#else
    return ":";
#endif
  }

  // Set an environment variable
  void SetEnvironment ( std::string key, std::string value ) {
#ifdef WIN32
    std::string v = key + "=" + value;
    _putenv ( v.c_str() );
    std::cout << "SetEnvironment: " << v << std::endl;
#else
    setenv ( key.c_str(), value.c_str(), 1 );
    std::cout << "SetEnvironment: " << key << "=" << value << std::endl;
#endif
  }
  /* Run the command line specified in the list of arguments.  Call
   * FAIL if the executable fails returning -1, return the value returned by the
   * process otherwise.
   */
  int RunExecutable ( std::vector<std::string> CommandLine, bool showOutput = false ) {

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
    int ret = -1;

    itksysProcess_WaitForExit ( process, 0 );

    switch (itksysProcess_GetState( process ))
      {
      case itksysProcess_State_Starting:
        std::cerr << "No process has been executed." << std::endl;
        failed = true;
        break;
      case itksysProcess_State_Executing:
        std::cerr << "The process is still executing." << std::endl;;
        failed = true;
        break;
      case itksysProcess_State_Expired:
        std::cerr << "Child was killed when timeout expired." << std::endl;
        failed = true;
        break;
      case itksysProcess_State_Exited:
        ret = itksysProcess_GetExitValue(process);
        break;
      case itksysProcess_State_Killed:
        std::cerr << "Child was killed by parent." << std::endl;
        failed = true;
        break;
      case itksysProcess_State_Exception:
        std::cerr << "Child terminated abnormally: " << itksysProcess_GetExceptionString( process ) << std::endl;;
        failed = true;
        break;
      case itksysProcess_State_Disowned:
        std::cerr << "Child was disowned." << std::endl;
        failed = true;
        break;
      case itksysProcess_State_Error:
        std::cerr << "Error in administrating child process: [" << itksysProcess_GetErrorString( process ) << "]" << std::endl;
        failed = true;
        break;
      default:
        std::cerr << "Unknown Process State" << std::endl;
        failed = true;
      };

    itksysProcess_Delete ( process );

    if ( failed )
      {
      // HACK: GTest currently expects functions of void type, by
      // using the comma operator we can get around this.
      FAIL(), -1;
      }
    return ret;
  }
};

class Python : public ExternalProgramRunner {
};

class Lua : public ExternalProgramRunner {
};

class Java : public ExternalProgramRunner {
};

class Tcl : public ExternalProgramRunner {
};

class R : public ExternalProgramRunner {
};

class Ruby : public ExternalProgramRunner {
};

#include "ImageCompare.h"

#endif
