#include "sitkShow.h"
#include "sitkMacro.h"
#include "sitkImageFileWriter.h"
#include <itksys/SystemTools.hxx>
#include <itksys/Process.h>
#include <stdlib.h>
#include <iostream>
#include <iterator>

namespace itk
{
  namespace simple
  {

  static int ShowImageCount = 0;

  // time to wait in mili-seconds before we check if the process is OK
  const unsigned int ProcessDelay = 500;


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

  /**
   * This function take a list of command line arguments, and runs a
   * process based on it. It waits for a fraction of a second before
   * checking it's state, to verify it was launched OK.
   */
  static void ExecuteShow( const std::vector<std::string> & cmdLine )
  {

    // if debug
    // std::copy( cmdLine.begin(), cmdLine.end(), std::ostream_iterator<std::string>( std::cout, " " ) );
    // std::cout << std::endl;

    std::vector<const char*> cmd( cmdLine.size() + 1, NULL );

    for ( unsigned int i = 0; i < cmdLine.size(); ++i )
      {
      cmd[i] = cmdLine[i].c_str();
      }

    itksysProcess *kp = itksysProcess_New();

    itksysProcess_SetCommand( kp, &cmd[0] );

    itksysProcess_SetOption( kp, itksysProcess_Option_Detach, 1 );

    // For detached processes, this appears not to be the default
    itksysProcess_SetPipeShared( kp, itksysProcess_Pipe_STDERR, 1);
    itksysProcess_SetPipeShared( kp, itksysProcess_Pipe_STDOUT, 1);

    itksysProcess_Execute( kp );

    // Wait one second then check to see if we launched ok.
    // N.B. Because the launched process may spawn a child process for
    // the acutal application we want, this methods is needed to be
    // called before the GetState, so that we get more then the
    // imediate result of the initial execution.
    double timeout = ProcessDelay;
    itksysProcess_WaitForExit( kp, &timeout );


    switch (itksysProcess_GetState(kp))
      {
      case itksysProcess_State_Executing:
        // This first case is what we expect if everything went OK.

        // We want the other process to continue going
        itksysProcess_Delete( kp ); // implicitly disowns
        break;

      case itksysProcess_State_Exited:
        {
        int exitValue = itksysProcess_GetExitValue(kp);
        if ( exitValue != 0 )
          {
          sitkExceptionMacro (  << "Process returned " << exitValue << "." );
          }
        }
        break;

      case itksysProcess_State_Killed:
        itksysProcess_Delete( kp );
        sitkExceptionMacro (  << "Child was killed by parent." );
        break;

      case itksysProcess_State_Exception:
        {
        std::string exceptionString = itksysProcess_GetExceptionString(kp);
        itksysProcess_Delete( kp );
        sitkExceptionMacro (  << "Child terminated abnormally: " << exceptionString );;
        }
        break;

      case itksysProcess_State_Error:
        {
        std::string errorString = itksysProcess_GetErrorString(kp);
        itksysProcess_Delete( kp );
        sitkExceptionMacro (  << "Error in administrating child process: [" << errorString << "]" );
        }
        break;

      // these states should not occour, because they are the result
      // from actions we don't take
      case itksysProcess_State_Expired:
      case itksysProcess_State_Disowned:
      case itksysProcess_State_Starting:
      default:
        itksysProcess_Delete( kp );
        sitkExceptionMacro (  << "Unexpected process state!" );
      };

  }

    void Show( const Image &image, const std::string name)
    {
      // Try to find ImageJ, write out a file and open
      std::vector<std::string> paths;
      std::string ExecutableName = itksys::SystemTools::FindFile( "ImageJ" );
      std::string TempDirectory = "";
      std::string TempFile = "";
      std::vector<std::string> CommandLine;
#if defined(WIN32)

      // Windows
      // Create possible paths
      ExecutableName = "ImageJ.exe";
      std::string ProgramFiles;
      if ( itksys::SystemTools::GetEnv ( "PROGRAMFILES", ProgramFiles ) )
        {
        paths.push_back ( ProgramFiles + "\\ImageJ\\" );
        }

      // Find the executable
      ExecutableName = itksys::SystemTools::FindFile ( ExecutableName.c_str(), paths );
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
      CommandLine.push_back( ExecutableName );
      CommandLine.push_back( "-o" );
      CommandLine.push_back( TempFile );
#else
      // Handle Linux and Mac
      TempDirectory = "/tmp/";
      TempFile = FormatFileName ( TempDirectory, name );
#if defined(__APPLE__)
      paths.push_back("/Applications"); //A common place to look
      paths.push_back("/Developer"); //A common place to look
      paths.push_back("/opt/ImageJ");   //A common place to look
      paths.push_back("/usr/local/ImageJ");   //A common place to look

#ifdef __x86_64__
      // Mac 64-bit
      //
      ExecutableName = itksys::SystemTools::FindDirectory( "ImageJ64.app" );
      if( ExecutableName == "" )
        {
        // Just assume it is registered properly in a place where the open command will find it.
        ExecutableName="ImageJ64";
        }
      WriteImage ( image, TempFile );

      CommandLine.push_back( "open" );
      CommandLine.push_back( "-a" );
      CommandLine.push_back( ExecutableName );
      CommandLine.push_back( TempFile );

      try
        {
        ExecuteShow( CommandLine );
        }
      catch(...)
        {
        // failed to find ImageJ64.app.  Try ImageJ.app

        ExecutableName = itksys::SystemTools::FindDirectory( "ImageJ.app" );
        if( ExecutableName == "" )
          {
          // Just assume it is registered properly in a place where the open command will find it.
          ExecutableName="ImageJ";
          }
        CommandLine[2] = ExecutableName;
        // run the compiled command-line in a process which will detach
        ExecuteShow( CommandLine );
        }
      return;
#endif

      // Mac 32-bit
      ExecutableName = itksys::SystemTools::FindDirectory( "ImageJ.app" );
      if( ExecutableName == "" )
        {
        // Just assume it is registered properly in a place where the open command will find it.
        ExecutableName="ImageJ";
        }
      CommandLine.push_back( "open" );
      CommandLine.push_back( "-a" );
      CommandLine.push_back( ExecutableName );
      CommandLine.push_back( TempFile );

#else
      // Must be Linux
      ExecutableName = itksys::SystemTools::FindFile ( "ImageJ" );
      if ( ExecutableName == "" )
        {
        ExecutableName = itksys::SystemTools::FindFile ( "imagej" );
        }
      CommandLine.push_back( ExecutableName );
      CommandLine.push_back( "-o" );
      CommandLine.push_back( TempFile );
#endif
#endif

      WriteImage ( image, TempFile );

      // run the compiled command-line in a process which will detach
      ExecuteShow( CommandLine );

    }

  }
}
