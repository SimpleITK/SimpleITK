#include "sitkShow.h"
#include "sitkMacro.h"
#include "sitkImageFileWriter.h"
#include <itksys/SystemTools.hxx>
#include <itksys/Process.h>
#include <stdlib.h>

namespace itk
{
  namespace simple
  {

  static int ShowImageCount = 0;

  static std::string FormatFileName ( std::string TempDirectory, std::string name )
  {
  std::string TempFile = TempDirectory;
  if ( name != "" )
    {
    TempFile = TempFile + name + ".nii";
    }
  else
    {
    std::ostringstream tmp;
    tmp << "TempFile-" << ShowImageCount;
    ShowImageCount++;
    TempFile = TempFile + tmp.str() + ".nii";
    }
  return TempFile;
  }

    void Show( const Image &image, const std::string name)
    {
      // Try to find ImageJ, write out a file and open
      std::vector<std::string> paths;
      std::string ExecutableName = "ImageJ";
      std::string TempDirectory = "";
      std::string TempFile = "";
      std::vector<std::string> CommandLine;
#if defined(__WIN32__)
      // Windows
      // Create possible paths
      ExecutableName = "ImageJ.exe";
      std::string ProgramFiles;
      if ( itksys::SystemTools::GetEnv ( "PROGRAMFILES", ProgramFiles ) )
        {
        paths.push_back ( ProgramFiles + "\\ImageJ\\" );
        }

      // Find the executable
      ExecuteableName = itksys::SystemTools::FindFile ( ExecutableName.c_str(), paths );
      if ( ExecutableName == "" )
        {
        sitkExceptionMacro ( << "Can not find location of " << ExecutableName );
        }

      if ( !itksys::SystemTools::GetEnv ( "TMP", TempDirectory )
           && !itksys::SystemTools::GetEnv ( "TEMP", TempDirectory )
           && !itksys::SystemTools::GetEnv ( "USERPROFILE", TempDirectory )
           && !itksys::SystemTools::GetEnv ( "WINDIR", TempDirectory ) )
        {
        sitkExceptionMacro ( << "Can not find temporary directory.  Tried TMP, TEMP, USERPROFILE, and WINDIR environment variables" );
        }
      TempDirectory = TempDirectory + "\\";
      TempFile = FormatFileName ( TempDirectory, name );
      CommandLine.push_back ( "\"" + ExecutableName + "\"" );
      CommandLine.push_back ( "-o" );
      CommandLine.push_back ( TempFile );
#else
      // Handle Linux and Mac
      TempDirectory = "/tmp/";
      TempFile = FormatFileName ( TempDirectory, name );
#if defined(__APPLE__)
      CommandLine.push_back ( "open" );
      CommandLine.push_back ( "-a" );
      CommandLine.push_back ( "ImageJ" );
      CommandLine.push_back ( TempFile );
#else
      // Must be Linux
      ExecutableName = itksys::SystemTools::FindFile ( "ImageJ" );
      CommandLine.push_back ( "\"" + ExecutableName + "\"" );
      CommandLine.push_back ( "-p" );
      CommandLine.push_back ( "1" );
      CommandLine.push_back ( TempFile );
      CommandLine.push_back ( "&" );
#endif
#endif

      std::cout << "Writing image to " << TempFile << std::endl;
      WriteImage ( image, TempFile );

      // Allocate temp space for the argument...  don't forget it must be null terminated
      std::string ConcatCommand;
      const char* StringCommandLine[256];
      for ( unsigned int idx = 0; idx < CommandLine.size(); idx++ )
        {
        StringCommandLine[idx] = CommandLine[idx].c_str();
        ConcatCommand = ConcatCommand + " " + StringCommandLine[idx];
        }
      StringCommandLine[CommandLine.size()] = NULL;

      std::cout << "Command line " << ConcatCommand << std::endl;

      system ( ConcatCommand.c_str() );
/*

      itksysProcess* process = itksysProcess_New();
      itksysProcess_SetCommand ( process, StringCommandLine );
      std::cout << "Set command" << std::endl;
      itksysProcess_SetOption ( process, itksysProcess_Option_Detach, 1 );
      itksysProcess_SetOption ( process, itksysProcess_Option_HideWindow, 1 );
      // itksysProcess_SetOption ( process, itksysProcess_Option_Verbatim, 1 );
      std::cout << "Set options" << std::endl;
      itksysProcess_Execute ( process );
      std::cout << "Execute" << std::endl;
      // itksysProcess_Delete ( process );
      // std::cout << "Deleted" << std::endl;

    int status;
    char* processData;
    int processDataLength;

    // Wait until we are executing
    int ii = 0;
    while ( 1 )
      {
      status = itksysProcess_GetState ( process );
      if ( status == itksysProcess_State_Disowned )
        {
        std::cout << "Disowned" << std::endl;
        // break;
        }
      if ( status == itksysProcess_State_Executing )
        {
        std::cout << "Executing" << std::endl;
        // break;
        }
      if ( status == itksysProcess_State_Error )
        {
        std::cout << "Error" << std::endl;
        // break;
        }
      if ( ii++ > 1000 )
        {
        break;
        }
      }
      itksysProcess_Disown ( process );
      std::cout << "Disown" << std::endl;


    while ( 1 )
      {
      status = itksysProcess_WaitForData ( process, &processData, &processDataLength, NULL );
      if ( status == itksysProcess_Pipe_STDOUT || status == itksysProcess_Pipe_STDERR )
        {
        std::cout << std::string ( processData ) << std::endl;
        }
      else
        {
        // Nothing ready, so wait for the process to exit...
        break;
        }
      }

    bool failed = false;
    // itksysProcess_WaitForExit ( process, 0 );
    if ( itksysProcess_GetState ( process ) == itksysProcess_State_Disowned )
      {
      std::cerr << "Properly disowned..." << std::endl;
      }
    if ( itksysProcess_GetState ( process ) == itksysProcess_State_Error )
      {
      std::cerr << "Error executing '" << ConcatCommand << "': " << itksysProcess_GetErrorString ( process ) << std::endl;
      failed = true;
      } else if ( itksysProcess_GetState ( process ) == itksysProcess_State_Exception )
      {
      std::cerr << "Error executing '" << ConcatCommand << "': " << itksysProcess_GetExceptionString ( process ) << std::endl;
      failed = true;
      }
    itksysProcess_Delete ( process );
*/
/*
      std::cout << "Execute" << std::endl;
      itksysProcess_Disown ( process );
      std::cout << "Disown" << std::endl;
      itksysProcess_Delete ( process );
      std::cout << "Deleted" << std::endl;
*/
    }

  }
}

/*
i = SimpleITK.ReadImage ( '/home/blezek/Data/Fixed.nrrd' )
SimpleITK.Show ( i, "test" )
*/
