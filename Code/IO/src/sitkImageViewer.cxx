/*=========================================================================
*
*  Copyright NumFOCUS
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
#include "sitkImageViewer.h"
#include "sitkMacro.h"
#include "sitkImageFileWriter.h"
#include <itkMacro.h>
#include <itksys/SystemTools.hxx>
#include <itksys/Process.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <ctype.h>

#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif


//
//  Dave's mental notes about ImageJ/Fiji and file formats
//
// ImageJ without plugins doesn't support MetaIO.
// ImageJ displaying a color NifTi image by defaults displays R, G, and B as separate channels.
// To display color NifTi images properly in ImageJ, you need to use the NIFTI_COLOR_MACRO
//
// Fiji does support MetaIO.
// Fiji has the same color NifTi problem as ImageJ.
//
// Invoking Fiji is simpler then ImageJ because the command line flags are the
// same on Windows and Linux.

#define localDebugMacro(x)\
  {                                                                     \
    if (itk::simple::ImageViewer::GetGlobalDefaultDebug())                     \
      {                                                                 \
      std::ostringstream msg;                                           \
      msg << "Debug: In " __FILE__ ", line " << __LINE__ << ": " x      \
          << "\n\n";                                                    \
      ::itk::OutputWindowDisplayDebugText( msg.str().c_str() );         \
      }                                                                 \
  }                                                                     \

#define IMAGEJ_OPEN_MACRO "open(\"%f\"); rename(\"%t\");"
#define NIFTI_COLOR_MACRO " run(\"Make Composite\", \"display=Composite\");"

namespace itk
{
  namespace simple
  {

namespace
{
  // forward declaration of some helper functions
  std::string ReplaceWords( const std::string & command, const std::string & app, const std::string & filename,
                            const std::string & title, bool& fileFlag );
  std::string UnquoteWord( const std::string & word );
  std::vector<std::string> ConvertCommand( const std::string & command, const std::string & app,
                                           const std::string & filename, const std::string & title="" );
  std::string FormatFileName ( const std::string & TempDirectory, const std::string & name,
                               const std::string & extension, const int tagID );
  std::string BuildFullFileName( const std::string & name, const std::string & extension, const int tagID );
#ifdef _WIN32
  std::string DoubleBackslashes( const std::string & word );
#endif

  void ExecuteCommand( const std::vector<std::string> & cmdLine, const unsigned int timeout=500 );
}


int ImageViewer::m_GlobalViewerImageCount=0;
bool ImageViewer::m_GlobalAreDefaultsInitialized=false;
unsigned int ImageViewer::m_GlobalProcessDelay;

std::vector<std::string> ImageViewer::m_GlobalDefaultSearchPath;
std::vector<std::string> ImageViewer::m_GlobalDefaultExecutableNames;

std::string ImageViewer::m_GlobalDefaultViewCommand;

std::string ImageViewer::m_GlobalDefaultApplication;
std::string ImageViewer::m_GlobalDefaultFileExtension;

bool ImageViewer::m_GlobalDefaultDebug=false;

//
// this is an ugly mess
//
void ImageViewer::initializeDefaults()
  {
  if (m_GlobalAreDefaultsInitialized)
    return;

  std::string Extension;
  std::string cmd;

  // check environment variables for user specified strings

  // File Extension
  itksys::SystemTools::GetEnv ( "SITK_SHOW_EXTENSION", Extension );
  if (Extension.length()>0)
    {
    m_GlobalDefaultFileExtension = Extension;
    }
  else
    {
    m_GlobalDefaultFileExtension = ".mha";
    }

  // Show command
  itksys::SystemTools::GetEnv ( "SITK_SHOW_COMMAND", cmd );
  if (cmd.length()>0)
    {
    m_GlobalDefaultViewCommand = cmd;
    }
  else
    {
#if defined(__APPLE__)
    m_GlobalDefaultViewCommand = "open -a %a -n --args -eval \'" IMAGEJ_OPEN_MACRO "\'";
#else
    // Linux & Windows
    m_GlobalDefaultViewCommand = "%a -eval \'" IMAGEJ_OPEN_MACRO "\'";
#endif
    }


  //
  // Build the SearchPath
  //
#ifdef _WIN32

  std::string ProgramFiles;
  std::vector<std::string> win_dirs = { "PROGRAMFILES", "PROGRAMFILES(x86)", "PROGRAMW6432" };

  for (unsigned int i=0; i<win_dirs.size(); i++)
    {
    if ( itksys::SystemTools::GetEnv ( win_dirs[i], ProgramFiles ) )
      {
      m_GlobalDefaultSearchPath.push_back ( ProgramFiles + "\\" );
      }
    }

  if ( itksys::SystemTools::GetEnv ( "USERPROFILE", ProgramFiles ) )
    {
    m_GlobalDefaultSearchPath.push_back ( ProgramFiles + "\\" );
    m_GlobalDefaultSearchPath.push_back ( ProgramFiles + "\\Desktop\\" );
    }

#elif defined(__APPLE__)

  // Common places on the Mac to look
  m_GlobalDefaultSearchPath = { "/Applications/", "/Developer/", "/opt/", "/usr/local/" };
  std::string homedir;
  if ( itksys::SystemTools::GetEnv ( "HOME", homedir ) )
    {
    m_GlobalDefaultSearchPath.push_back( homedir + "/Applications/" );
    }


#else

  // linux and other systems
  m_GlobalDefaultSearchPath = { "./" };
  std::string homedir;
  if ( itksys::SystemTools::GetEnv ( "HOME", homedir ) )
    {
    m_GlobalDefaultSearchPath.push_back( homedir + "/bin/" );
    }

  m_GlobalDefaultSearchPath.emplace_back("/opt/" );
  m_GlobalDefaultSearchPath.emplace_back("/usr/local/" );

#endif

  localDebugMacro( << "Default search path: " << m_GlobalDefaultSearchPath << std::endl );

  //
  //  Set the ExecutableNames
  //
#if defined(_WIN32)
  m_GlobalDefaultExecutableNames = { "Fiji.app/ImageJ-win64.exe", "Fiji.app/ImageJ-win32.exe" };
#elif defined(__APPLE__)
  m_GlobalDefaultExecutableNames = { "Fiji.app" };
#else
  // Linux
  m_GlobalDefaultExecutableNames = { "Fiji.app/ImageJ-linux64", "Fiji.app/ImageJ-linux32" };
#endif

#ifdef _WIN32
  m_GlobalProcessDelay = 1;
#else
  m_GlobalProcessDelay = 500;
#endif

  ImageViewer::m_GlobalDefaultApplication = ImageViewer::FindViewingApplication();

  m_GlobalViewerImageCount = 0;
  m_GlobalAreDefaultsInitialized = true;
  }


//
// Constructor
//
ImageViewer::ImageViewer()
  {

  if (!m_GlobalAreDefaultsInitialized)
    {
    initializeDefaults();
    }

  m_ViewCommand = m_GlobalDefaultViewCommand;

  m_Application = m_GlobalDefaultApplication;

  m_FileExtension = "";

  m_CustomCommand = "";
  }


std::string ImageViewer::FindViewingApplication()
  {
  std::string result;
  std::vector<std::string>::iterator name_it;


  for(name_it = m_GlobalDefaultExecutableNames.begin(); name_it != m_GlobalDefaultExecutableNames.end(); name_it++)
    {
#ifdef __APPLE__
      result = itksys::SystemTools::FindDirectory ( (*name_it).c_str(), m_GlobalDefaultSearchPath );
      if (!result.length())
        {
        // try looking for a file if no directory
        result = itksys::SystemTools::FindFile ( (*name_it).c_str(), m_GlobalDefaultSearchPath );
        }
#else
      result = itksys::SystemTools::FindFile ( (*name_it).c_str(), m_GlobalDefaultSearchPath );
#endif
      if (result.length())
        {
        break;
        }
    }

#if !defined(__APPLE__) && !defined(_WIN32)
    // is the imagej we're running a script or a binary?
    // only done on Linux/*nix
    //
    // some installations of ImageJ have a shell script front-end.  That script uses the "-eval"
    // command-line option instead of "-e".
    //
    bool ImageJScriptFlag = itksys::SystemTools::FileHasSignature( result.c_str(), "#!" );
    if (ImageJScriptFlag)
      {
      m_GlobalDefaultViewCommand = "%a -eval \'" IMAGEJ_OPEN_MACRO "\'";
      }
#endif

  localDebugMacro( << "FindViewingApplication: " << result << std::endl );
  return result;
  }


//
// A bunch of Set/Get methods for the class static variables
//

const std::vector<std::string>& ImageViewer::GetGlobalDefaultSearchPath()
  {
  return ImageViewer::m_GlobalDefaultSearchPath;
  }

void ImageViewer::SetGlobalDefaultSearchPath( const std::vector<std::string> & path )
  {
  ImageViewer::m_GlobalDefaultSearchPath = path;
  ImageViewer::m_GlobalDefaultApplication = FindViewingApplication();
  }

const std::vector<std::string>& ImageViewer::GetGlobalDefaultExecutableNames()
  {
  return ImageViewer::m_GlobalDefaultExecutableNames;
  }

void ImageViewer::SetGlobalDefaultExecutableNames( const std::vector<std::string> & names )
  {
  ImageViewer::m_GlobalDefaultExecutableNames = names;
  ImageViewer::m_GlobalDefaultApplication = FindViewingApplication();
  }

void ImageViewer::SetGlobalDefaultFileExtension( const std::string & ext )
  {
  ImageViewer::m_GlobalDefaultFileExtension = ext;
  }

const std::string & ImageViewer::GetGlobalDefaultFileExtension()
  {
  return ImageViewer::m_GlobalDefaultFileExtension;
  }

void ImageViewer::SetGlobalDefaultApplication( const std::string & app )
  {
  ImageViewer::m_GlobalDefaultApplication = app;
  }

const std::string & ImageViewer::GetGlobalDefaultApplication()
  {
  return ImageViewer::m_GlobalDefaultApplication;
  }


//
// A bunch of Set/Get methods for the class member variables
//

void ImageViewer::SetCommand(const std::string & command )
  {
  m_CustomCommand = command;
  }

const std::string & ImageViewer::GetCommand() const
  {
  // if there's a user specified, custom command, it gets used no matter what.
  if (m_CustomCommand.length() > 0)
    {
    return m_CustomCommand;
    }

  return m_ViewCommand;
  }

void ImageViewer::SetFileExtension(const std::string & ext )
  {
  m_FileExtension = ext;
  }

const std::string & ImageViewer::GetFileExtension() const
  {
  if (m_FileExtension.length())
    {
    return m_FileExtension;
    }
  return m_GlobalDefaultFileExtension;
  }

void ImageViewer::SetGlobalDefaultDebug( const bool dbg )
  {
  m_GlobalDefaultDebug = dbg;
  }

bool ImageViewer::GetGlobalDefaultDebug()
  {
  return m_GlobalDefaultDebug;
  }

void ImageViewer::SetGlobalDefaultDebugOn()
  {
  m_GlobalDefaultDebug = true;
  }

void ImageViewer::SetGlobalDefaultDebugOff()
  {
  m_GlobalDefaultDebug = false;
  }

void ImageViewer::SetProcessDelay( const unsigned int d )
  {
  m_GlobalProcessDelay = d;
  }

unsigned int ImageViewer::GetProcessDelay()
  {
  return m_GlobalProcessDelay;
  }

void ImageViewer::SetTitle(const std::string & t )
  {
  m_Title = t;
  }

const std::string & ImageViewer::GetTitle() const
  {
  return m_Title;
  }

void ImageViewer::SetApplication( const std::string & app, const std::string & command )
  {
  m_Application = app;
  this->SetCommand( command );
  }

const std::string & ImageViewer::GetApplication() const
  {
  return m_Application;
  }


std::string ImageViewer::ToString() const
  {
  std::ostringstream out;

  out << "itk::simple::ImageViewer" << std::endl;

  out << "  Title: " << this->GetTitle() << std::endl;

  out << "  Command: " << this->GetCommand() << std::endl;

  out << "  Application: " << this->GetApplication() << std::endl;
  out << "  Default Application: " << ImageViewer::GetGlobalDefaultApplication() << std::endl;
  out << "  File Extension: " << this->GetFileExtension() << std::endl;
  out << "  Default File Extension: " << ImageViewer::GetGlobalDefaultFileExtension() << std::endl;
  out << "  Search Path: " << ImageViewer::GetGlobalDefaultSearchPath() << std::endl;
  out << "  Executable Names: " << ImageViewer::GetGlobalDefaultExecutableNames() << std::endl;
  out << "  Debug Flag: " << ImageViewer::GetGlobalDefaultDebug() << std::endl;

  return out.str();
  }

//
// The Execute method
//

void ImageViewer::Execute( const Image & image )
  {
  // Try to find ImageJ, write out a file and open
  std::string Command, Command3D;
  std::string TempFile = "";
  std::string Macro = "";
  std::vector<std::string> CommandLine;
  std::string ext;

  if (m_FileExtension.length())
    {
    ext = m_FileExtension;
    }
  else
    {
    ext = m_GlobalDefaultFileExtension;
    }

  TempFile = BuildFullFileName(m_Title, ext, m_GlobalViewerImageCount++);

  // write out the image
  WriteImage ( image, TempFile );

  Command = this->GetCommand();

  // Replace the string tokens and split the command string into separate words.
  CommandLine = ConvertCommand( Command, m_Application, TempFile, m_Title );

  // run the compiled command-line in a process which will detach
  ExecuteCommand( CommandLine, ImageViewer::GetProcessDelay() );
  }


namespace
{

//
// ExecuteCommand function
//

  /**
   * This function take a list of command line arguments, and runs a
   * process based on it. It waits for a fraction of a second before
   * checking it's state, to verify it was launched OK.
   */
void ExecuteCommand( const std::vector<std::string> & cmdLine, const unsigned int timeout )
  {
  unsigned int i;
  std::ostringstream cmdstream;

  for ( i = 0; i < cmdLine.size(); ++i )
    cmdstream << '\'' << cmdLine[i] << "\' ";

  localDebugMacro( << "ExecuteCommand: " << cmdstream.str() << std::endl );

  std::vector<const char*> cmd( cmdLine.size() + 1, NULL );

  for ( i = 0; i < cmdLine.size(); ++i )
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
  // immediate result of the initial execution.
  double t = timeout;
  itksysProcess_WaitForExit( kp, &t );


  switch (itksysProcess_GetState(kp))
    {
    case itksysProcess_State_Executing:
      // This first case is what we expect if everything went OK.

      // We want the other process to continue going
      break;

    case itksysProcess_State_Exited:
      {
      int exitValue = itksysProcess_GetExitValue(kp);
      localDebugMacro( << "Normal process exit.  exitValue = " << exitValue );
      if ( exitValue != 0 )
        {
        itksysProcess_Delete( kp );
        sitkExceptionMacro (  << "Process returned " << exitValue << ".\n" << "Command line: " << cmdstream.str() );
        }
      }
      break;

    case itksysProcess_State_Killed:
      itksysProcess_Delete( kp );
      sitkExceptionMacro (  << "Child was killed by parent." << "\nCommand line: " << cmdstream.str() );
      break;

    case itksysProcess_State_Exception:
      {
      std::string exceptionString = itksysProcess_GetExceptionString(kp);
      itksysProcess_Delete( kp );
      sitkExceptionMacro (  << "Child terminated abnormally: " << exceptionString << ".\nCommand line: " << cmdstream.str() );
      }
      break;

    case itksysProcess_State_Error:
      {
      std::string errorString = itksysProcess_GetErrorString(kp);
      itksysProcess_Delete( kp );
      sitkExceptionMacro (  << "Error in administrating child process: [" << errorString << "]" << ".\nCommand line: " << cmdstream.str() );
      }
      break;

    // these states should not occur, because they are the result
    // from actions we don't take
    case itksysProcess_State_Expired:
    case itksysProcess_State_Disowned:
    case itksysProcess_State_Starting:
    default:
      itksysProcess_Delete( kp );
      sitkExceptionMacro (  << "Unexpected process state!" << "\nCommand line: " << cmdstream.str() );
    }

  localDebugMacro( << "Done.  Deleting process." );
  itksysProcess_Delete( kp );
  }


//
// ------------------------------------------------------
// Helper string, file name, and command string functions
//


// Function to replace %tokens in a string.  The tokens are %a and %f for
// application and file name respectively.  %% will send % to the output string.
// Multiple occurrences of a token are allowed.
//
std::string ReplaceWords( const std::string & command,  const std::string & app,  const std::string & filename,
                          const std::string & title, bool& fileFlag )
  {
  std::string result;

  unsigned int i=0;
  while (i<command.length())
    {

    if (command[i] != '%')
      {
      result.push_back(command[i]);
      }
    else
      {
      if (i<command.length()-1)
        {
        // check the next character after the %
        switch(command[i+1])
          {
          case '%':
            // %%
            result.push_back(command[i]);
            i++;
            break;
          case 'a':
            // %a for application
            if (!app.length())
              {
              sitkExceptionMacro( "No ImageJ/Fiji application found." )
              }
            result.append(app);
            i++;
            break;
          case 't':
            // %t for title
            result.append(title);
            i++;
            break;
          case 'f':
            // %f for filename
            result.append(filename);
            fileFlag = true;
            i++;
            break;
          }

        }
      else
        {
        // if the % is the last character in the string just pass it through
        result.push_back(command[i]);
        }
      }
    i++;
    }
  return result;
  }

// Function to strip the matching leading and trailing quotes off a string
// if there are any.  We need to do this because the way arguments are passed
// to itksysProcess_Execute
//
std::string UnquoteWord( const std::string & word )
  {
  size_t l = word.length();

  if (l<2)
    {
    return word;
    }

  switch(word[0])
    {

    case '\'':
    case '\"':
      if (word[l-1] == word[0])
        {
        return word.substr(1, l-2);
        }
      else
        {
        return word;
        }
      break;

    default:
      return word;
      break;
    }
  }

std::vector<std::string> ConvertCommand( const std::string & command, const std::string & app,
                                         const std::string & filename, const std::string & title )
  {

  std::string t;
  if (title.empty())
    {
    t = filename;
    }
  else
    {
    t = title;
    }

  bool fileFlag=false;
  std::string new_command = ReplaceWords(command, app, filename, t, fileFlag);
  std::istringstream iss(new_command);
  std::vector<std::string> result;
  std::vector<unsigned char> quoteStack;
  std::string word;
  unsigned int i=0;

  while (i<new_command.length())
    {
    switch (new_command[i])
      {

      case '\'':
      case '\"':
        word.push_back(new_command[i]);
        if (!quoteStack.empty())
          {
          if (new_command[i] == quoteStack[quoteStack.size()-1])
            {
            // we have a matching pair, so pop it off the stack
            quoteStack.pop_back();
            }
          else
            {
            // the top of the stack and the new one don't match, so push it on
            quoteStack.push_back(new_command[i]);
            }
          }
        else
          {
          // quoteStack is empty so push this new quote on the stack.
          quoteStack.push_back(new_command[i]);
          }
        break;

      case ' ':
        if (!quoteStack.empty())
          {
          // the space occurs inside a quote, so tack it onto the current word.
          word.push_back(new_command[i]);
          }
        else
          {
          // the space isn't inside a quote, so we've ended a word.
          word = UnquoteWord(word);
          result.push_back(word);
          word.clear();
          }
        break;

      default:
        word.push_back(new_command[i]);
        break;
      }
    i++;

    }

  if (word.length())
    {
    word = UnquoteWord(word);
    result.push_back(word);
    }


  // if the filename token wasn't found in the command string, add the filename to the end of the command vector.
  if (!fileFlag)
    {
    result.push_back(filename);
    }
  return result;
  }

//
std::string FormatFileName ( const std::string & TempDirectory, const std::string & name, const std::string & extension,
                             const int tagID )
  {
  std::string TempFile = TempDirectory;

#ifdef _WIN32
  int pid = _getpid();
#else
  int pid = getpid();
#endif

  std::ostringstream tmp;

  if ( !name.empty() )
    {
    std::string n = name;
    // remove whitespace
    n.erase(std::remove_if(n.begin(), n.end(), &::isspace), n.end());

    tmp << n << "-" << pid << "-" << tagID;
    TempFile = TempFile + tmp.str() + extension;
    }
  else
    {


    tmp << "TempFile-" << pid << "-" << tagID;
    TempFile = TempFile + tmp.str() + extension;
    }
  return TempFile;
  }

#if defined(_WIN32)
  //
  // Function that converts slashes or backslashes to double backslashes.  We need
  // to do this so the file name is properly parsed by ImageJ if it's used in a macro.
  //
  std::string DoubleBackslashes(const std::string & word)
  {
    std::string result;

    for (unsigned int i=0; i<word.length(); i++)
      {
      // put in and extra backslash
      if (word[i] == '\\' || word[i]=='/')
        {
        result.push_back('\\');
        result.push_back('\\');
        }
      else
        {
        result.push_back(word[i]);
        }
      }

    return result;
  }
#endif

//
//
std::string BuildFullFileName(const std::string & name, const std::string & extension, const int tagID )
  {
  std::string TempDirectory;

#ifdef _WIN32
  if ( !itksys::SystemTools::GetEnv ( "TMP", TempDirectory )
    && !itksys::SystemTools::GetEnv ( "TEMP", TempDirectory )
    && !itksys::SystemTools::GetEnv ( "USERPROFILE", TempDirectory )
    && !itksys::SystemTools::GetEnv ( "WINDIR", TempDirectory ) )
    {
    sitkExceptionMacro ( << "Can not find temporary directory.  Tried TMP, TEMP, USERPROFILE, and WINDIR environment variables" );
    }
  TempDirectory = TempDirectory + "\\";
  TempDirectory = DoubleBackslashes(TempDirectory);
#else
  TempDirectory = "/tmp/";
#endif
  return FormatFileName ( TempDirectory, name, extension, tagID );
  }

}

  } // namespace simple
} // namespace itk
