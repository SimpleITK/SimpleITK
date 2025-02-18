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
#include <mutex>
#include <ctype.h>

#ifdef _WIN32
#  include <process.h>
#else
#  include <unistd.h>
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

#define localDebugMacro(x)                                                    \
  {                                                                           \
    if (itk::simple::ImageViewer::GetGlobalDefaultDebug())                    \
    {                                                                         \
      std::ostringstream msg;                                                 \
      msg << "Debug: In " __FILE__ ", line " << __LINE__ << ": " x << "\n\n"; \
      ::itk::OutputWindowDisplayDebugText(msg.str().c_str());                 \
    }                                                                         \
  }

#define IMAGEJ_OPEN_MACRO "open(\"%f\"); rename(\"%t\");"
#define NIFTI_COLOR_MACRO " run(\"Make Composite\", \"display=Composite\");"

namespace itk::simple
{

namespace
{
// forward declaration of some helper functions
std::string
ReplaceWords(const std::string & command,
             const std::string & app,
             const std::string & filename,
             const std::string & title,
             bool &              fileFlag);
std::string
UnquoteWord(const std::string & word);
std::vector<std::string>
ConvertCommand(const std::string & command,
               const std::string & app,
               const std::string & filename,
               const std::string & title = "");
std::string
FormatFileName(const std::string & TempDirectory,
               const std::string & name,
               const std::string & extension,
               const int           tagID);
std::string
BuildFullFileName(const std::string & name, const std::string & extension, const int tagID);
#ifdef _WIN32
std::string
DoubleBackslashes(const std::string & word);
#endif

void
ExecuteCommand(const std::vector<std::string> & cmdLine, const unsigned int timeout = 500);

/** \class GlobalConfig
 * \brief Default Image Viewer configuration singleton class.
 *
 * The GlobalConfig class is a singleton that stores all the default
 * settings for the ImageViewer instances.  The GlobalConfig variables
 * are set at program start.  They can be changed via static methods
 * in the ImageViewer class, which is a friend class.
 */
class GlobalConfig
{
public:
  static GlobalConfig &
  getInstance();

private:
  int m_ViewerCount = 0;

  std::vector<PathType> m_DefaultSearchPath;
  std::vector<PathType> m_DefaultExecutableNames;
  unsigned int          m_ProcessDelay;

  std::string m_DefaultViewCommand;
  std::string m_DefaultFileExtension;
  PathType    m_DefaultApplication;

  bool m_DefaultDebug = false;
  GlobalConfig();

public:
  GlobalConfig(const GlobalConfig &) = delete;
  void
  operator=(const GlobalConfig &) = delete;

  std::string
  FindViewingApplication(bool debug = false);

  friend std::ostream &
  operator<<(std::ostream & os, const GlobalConfig & gc);

  friend ImageViewer;
};


// GlobalConfig constructor
//
GlobalConfig::GlobalConfig()
{
  std::string Extension;
  std::string cmd;

  // check environment variables for user specified strings

  // File Extension
  itksys::SystemTools::GetEnv("SITK_SHOW_EXTENSION", Extension);
  if (Extension.length() > 0)
  {
    m_DefaultFileExtension = Extension;
  }
  else
  {
    m_DefaultFileExtension = ".mha";
  }

  // Show command
  itksys::SystemTools::GetEnv("SITK_SHOW_COMMAND", cmd);
  if (cmd.length() > 0)
  {
    m_DefaultViewCommand = cmd;
  }
  else
  {
#if defined(__APPLE__)
    m_DefaultViewCommand = "open -a %a -n --args -eval \'" IMAGEJ_OPEN_MACRO "\'";
#else
    // Linux & Windows
    m_DefaultViewCommand = "%a -eval \'" IMAGEJ_OPEN_MACRO "\'";
#endif
  }

  //
  // Build the SearchPath
  //
#ifdef _WIN32

  std::string              ProgramFiles;
  std::vector<std::string> win_dirs = { "PROGRAMFILES", "PROGRAMFILES(x86)", "PROGRAMW6432" };

  for (unsigned int i = 0; i < win_dirs.size(); i++)
  {
    if (itksys::SystemTools::GetEnv(win_dirs[i], ProgramFiles))
    {
      m_DefaultSearchPath.push_back(ProgramFiles + "\\");
    }
  }

  if (itksys::SystemTools::GetEnv("USERPROFILE", ProgramFiles))
  {
    m_DefaultSearchPath.push_back(ProgramFiles + "\\");
    m_DefaultSearchPath.push_back(ProgramFiles + "\\Desktop\\");
  }

#elif defined(__APPLE__)

  // Common places on the Mac to look
  m_DefaultSearchPath = { "/Applications/", "/Developer/", "/opt/", "/usr/local/" };
  std::string homedir;
  if (itksys::SystemTools::GetEnv("HOME", homedir))
  {
    m_DefaultSearchPath.push_back(homedir + "/Applications/");
  }


#else

  // linux and other systems
  m_DefaultSearchPath = { "./" };
  std::string homedir;
  if (itksys::SystemTools::GetEnv("HOME", homedir))
  {
    m_DefaultSearchPath.push_back(homedir + "/bin/");
  }

  m_DefaultSearchPath.emplace_back("/opt/");
  m_DefaultSearchPath.emplace_back("/usr/local/");

#endif

  //
  //  Set the ExecutableNames
  //
#if defined(_WIN32)
  m_DefaultExecutableNames = { "Fiji.app/ImageJ-win64.exe", "Fiji.app/ImageJ-win32.exe" };
#elif defined(__APPLE__)
  m_DefaultExecutableNames = { "Fiji.app" };
#else
  // Linux
  m_DefaultExecutableNames = { "Fiji.app/ImageJ-linux64", "Fiji.app/ImageJ-linux32" };
#endif

#ifdef _WIN32
  m_ProcessDelay = 1;
#else
  m_ProcessDelay = 500;
#endif


  m_DefaultApplication = FindViewingApplication();
}

std::once_flag gc_once_flag;

GlobalConfig &
GlobalConfig::getInstance()
{
  static GlobalConfig instance;

  std::call_once(gc_once_flag, []() {
    if (instance.m_DefaultDebug)
    {
      fprintf(stderr, "Call once?\n");
      std::ostringstream msg;
      msg << instance;
      ::itk::OutputWindowDisplayDebugText(msg.str().c_str());
    }
  });

  return instance;
}

std::ostream &
operator<<(std::ostream & os, const GlobalConfig & gc)
{
  os << "\nImageViewer GlobalConfig\n";

  os << "    Search path: ";
  for (auto v : gc.m_DefaultSearchPath)
  {
    os << v << ", ";
  }
  os << std::endl;

  os << "    Executable names: ";
  for (auto v : gc.m_DefaultExecutableNames)
  {
    os << v << ", ";
  }
  os << std::endl;

  os << "    View command: " << gc.m_DefaultViewCommand << std::endl;
  os << "    File extension: " << gc.m_DefaultFileExtension << std::endl;
  os << "    Application: " << gc.m_DefaultApplication << std::endl;
  os << "    Process delay: " << gc.m_ProcessDelay << std::endl;
  return os;
}


std::string
GlobalConfig::FindViewingApplication(bool debug)
{
  std::string result;

  for (auto name : m_DefaultExecutableNames)
  {
#ifdef __APPLE__
    result = itksys::SystemTools::FindDirectory(
      name.c_str(), std::vector<std::string>(m_DefaultSearchPath.begin(), m_DefaultSearchPath.end()));
    if (!result.length())
    {
      // try looking for a file if no directory
      result = itksys::SystemTools::FindFile(
        name.c_str(), std::vector<std::string>(m_DefaultSearchPath.begin(), m_DefaultSearchPath.end()));
    }
#else
    result = itksys::SystemTools::FindFile(
      name.c_str(), std::vector<std::string>(m_DefaultSearchPath.begin(), m_DefaultSearchPath.end()));
#endif
    if (result.length())
    {
      break;
    }
  }

#if !defined(__APPLE__) && !defined(_WIN32)
  // is the ImageJ we're running a script or a binary?
  // only done on Linux/*nix
  //
  // some installations of ImageJ have a shell script front-end.  That script uses the "-eval"
  // command-line option instead of "-e".
  //
  bool ImageJScriptFlag = itksys::SystemTools::FileHasSignature(result.c_str(), "#!");
  if (ImageJScriptFlag)
  {
    m_DefaultViewCommand = "%a -eval \'" IMAGEJ_OPEN_MACRO "\'";
  }
#endif

  if (debug)
  {
    std::ostringstream msg;
    msg << "Debug: In " __FILE__ ", line " << __LINE__
        << ": "
           "FindViewApplication: "
        << result << std::endl
        << "\n\n";
    ::itk::OutputWindowDisplayDebugText(msg.str().c_str());
  }
  return result;
}
} // namespace

//
// Constructor
//
ImageViewer::ImageViewer()
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  m_ViewCommand = gc.m_DefaultViewCommand;

  m_Application = GetGlobalDefaultApplication();

  m_FileExtension = GetGlobalDefaultFileExtension();

  m_CustomCommand = "";
}


//
// A bunch of Set/Get methods for the class static variables
//

const std::vector<PathType> &
ImageViewer::GetGlobalDefaultSearchPath()
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  return gc.m_DefaultSearchPath;
}

void
ImageViewer::SetGlobalDefaultSearchPath(const std::vector<PathType> & path)
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  gc.m_DefaultSearchPath = path;
  gc.m_DefaultApplication = gc.FindViewingApplication();
}

const std::vector<PathType> &
ImageViewer::GetGlobalDefaultExecutableNames()
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  return gc.m_DefaultExecutableNames;
}

void
ImageViewer::SetGlobalDefaultExecutableNames(const std::vector<PathType> & names)
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  gc.m_DefaultExecutableNames = names;
  gc.m_DefaultApplication = gc.FindViewingApplication();
}

void
ImageViewer::SetGlobalDefaultFileExtension(const std::string & ext)
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  gc.m_DefaultFileExtension = ext;
}

const std::string &
ImageViewer::GetGlobalDefaultFileExtension()
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  return gc.m_DefaultFileExtension;
}

void
ImageViewer::SetGlobalDefaultApplication(const PathType & app)
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  gc.m_DefaultApplication = app;
}

const PathType &
ImageViewer::GetGlobalDefaultApplication()
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  return gc.m_DefaultApplication;
}


//
// A bunch of Set/Get methods for the class member variables
//

void
ImageViewer::SetCommand(const std::string & command)
{
  m_CustomCommand = command;
}

const std::string &
ImageViewer::GetCommand() const
{
  // if there's a user specified, custom command, it gets used no matter what.
  if (m_CustomCommand.length() > 0)
  {
    return m_CustomCommand;
  }

  return m_ViewCommand;
}

void
ImageViewer::SetFileExtension(const std::string & ext)
{
  m_FileExtension = ext;
}

const std::string &
ImageViewer::GetFileExtension() const
{
  if (m_FileExtension.length())
  {
    return m_FileExtension;
  }
  GlobalConfig & gc = GlobalConfig::getInstance();
  return gc.m_DefaultFileExtension;
}

void
ImageViewer::SetGlobalDefaultDebug(const bool dbg)
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  gc.m_DefaultDebug = dbg;
  if (dbg)
  {
    std::ostringstream msg;
    msg << gc;
    ::itk::OutputWindowDisplayDebugText(msg.str().c_str());
  }
}

bool
ImageViewer::GetGlobalDefaultDebug()
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  return gc.m_DefaultDebug;
}

void
ImageViewer::SetGlobalDefaultDebugOn()
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  gc.m_DefaultDebug = true;
}

void
ImageViewer::SetGlobalDefaultDebugOff()
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  gc.m_DefaultDebug = false;
}

void
ImageViewer::SetProcessDelay(const unsigned int d)
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  gc.m_ProcessDelay = d;
}

unsigned int
ImageViewer::GetProcessDelay()
{
  GlobalConfig & gc = GlobalConfig::getInstance();
  return gc.m_ProcessDelay;
}

void
ImageViewer::SetTitle(const std::string & t)
{
  m_Title = t;
}

const std::string &
ImageViewer::GetTitle() const
{
  return m_Title;
}

void
ImageViewer::SetApplication(const PathType & app, const std::string & command)
{
  m_Application = app;
  this->SetCommand(command);
}

const PathType &
ImageViewer::GetApplication() const
{
  return m_Application;
}


std::string
ImageViewer::ToString() const
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

void
ImageViewer::Execute(const Image & image)
{
  // Try to find ImageJ, write out a file and open
  std::string              Command, Command3D;
  std::string              TempFile = "";
  std::string              Macro = "";
  std::vector<std::string> CommandLine;
  std::string              ext;
  GlobalConfig &           gc = GlobalConfig::getInstance();

  if (!m_FileExtension.empty())
  {
    ext = m_FileExtension;
  }
  else
  {
    ext = gc.m_DefaultFileExtension;
  }

  TempFile = BuildFullFileName(m_Title, ext, gc.m_ViewerCount++);

  // write out the image
  WriteImage(image, TempFile);

  Command = this->GetCommand();

  // Replace the string tokens and split the command string into separate words.
  CommandLine = ConvertCommand(Command, m_Application, TempFile, m_Title);

  // run the compiled command-line in a process which will detach
  ExecuteCommand(CommandLine, ImageViewer::GetProcessDelay());
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
void
ExecuteCommand(const std::vector<std::string> & cmdLine, const unsigned int timeout)
{
  unsigned int       i;
  std::ostringstream cmdstream;

  for (i = 0; i < cmdLine.size(); ++i)
    cmdstream << '\'' << cmdLine[i] << "\' ";

  localDebugMacro(<< "ExecuteCommand: " << cmdstream.str() << std::endl);

  std::vector<const char *> cmd(cmdLine.size() + 1, NULL);

  for (i = 0; i < cmdLine.size(); ++i)
  {
    cmd[i] = cmdLine[i].c_str();
  }

  itksysProcess * kp = itksysProcess_New();

  itksysProcess_SetCommand(kp, &cmd[0]);

  itksysProcess_SetOption(kp, itksysProcess_Option_Detach, 1);

  // For detached processes, this appears not to be the default
  itksysProcess_SetPipeShared(kp, itksysProcess_Pipe_STDERR, 1);
  itksysProcess_SetPipeShared(kp, itksysProcess_Pipe_STDOUT, 1);

  itksysProcess_Execute(kp);

  // Wait one second then check to see if we launched ok.
  // N.B. Because the launched process may spawn a child process for
  // the actual application we want, this methods is needed to be
  // called before the GetState, so that we get more then the
  // immediate result of the initial execution.
  double t = timeout;
  itksysProcess_WaitForExit(kp, &t);


  switch (itksysProcess_GetState(kp))
  {
    case itksysProcess_State_Executing:
      // This first case is what we expect if everything went OK.

      // We want the other process to continue going
      break;

    case itksysProcess_State_Exited:
    {
      int exitValue = itksysProcess_GetExitValue(kp);
      localDebugMacro(<< "Normal process exit.  exitValue = " << exitValue);
      if (exitValue != 0)
      {
        itksysProcess_Delete(kp);
        sitkExceptionMacro(<< "Process returned " << exitValue << ".\n"
                           << "Command line: " << cmdstream.str());
      }
    }
    break;

    case itksysProcess_State_Killed:
      itksysProcess_Delete(kp);
      sitkExceptionMacro(<< "Child was killed by parent."
                         << "\nCommand line: " << cmdstream.str());
      break;

    case itksysProcess_State_Exception:
    {
      std::string exceptionString = itksysProcess_GetExceptionString(kp);
      itksysProcess_Delete(kp);
      sitkExceptionMacro(<< "Child terminated abnormally: " << exceptionString
                         << ".\nCommand line: " << cmdstream.str());
    }
    break;

    case itksysProcess_State_Error:
    {
      std::string errorString = itksysProcess_GetErrorString(kp);
      itksysProcess_Delete(kp);
      sitkExceptionMacro(<< "Error in administrating child process: [" << errorString << "]"
                         << ".\nCommand line: " << cmdstream.str());
    }
    break;

    // these states should not occur, because they are the result
    // from actions we don't take
    case itksysProcess_State_Expired:
    case itksysProcess_State_Disowned:
    case itksysProcess_State_Starting:
    default:
      itksysProcess_Delete(kp);
      sitkExceptionMacro(<< "Unexpected process state!"
                         << "\nCommand line: " << cmdstream.str());
  }

  localDebugMacro(<< "Done.  Deleting process.");
  itksysProcess_Delete(kp);
}


//
// ------------------------------------------------------
// Helper string, file name, and command string functions
//


// Function to replace %tokens in a string.  The tokens are %a and %f for
// application and file name respectively.  %% will send % to the output string.
// Multiple occurrences of a token are allowed.
//
std::string
ReplaceWords(const std::string & command,
             const std::string & app,
             const std::string & filename,
             const std::string & title,
             bool &              fileFlag)
{
  std::string result;

  unsigned int i = 0;
  while (i < command.length())
  {

    if (command[i] != '%')
    {
      result.push_back(command[i]);
    }
    else
    {
      if (i < command.length() - 1)
      {
        // check the next character after the %
        switch (command[i + 1])
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
              sitkExceptionMacro("No ImageJ/Fiji application found.")
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
std::string
UnquoteWord(const std::string & word)
{
  size_t l = word.length();

  if (l < 2)
  {
    return word;
  }

  switch (word[0])
  {

    case '\'':
    case '\"':
      if (word[l - 1] == word[0])
      {
        return word.substr(1, l - 2);
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

std::vector<std::string>
ConvertCommand(const std::string & command,
               const std::string & app,
               const std::string & filename,
               const std::string & title)
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

  bool                       fileFlag = false;
  std::string                new_command = ReplaceWords(command, app, filename, t, fileFlag);
  std::istringstream         iss(new_command);
  std::vector<std::string>   result;
  std::vector<unsigned char> quoteStack;
  std::string                word;
  unsigned int               i = 0;

  while (i < new_command.length())
  {
    switch (new_command[i])
    {

      case '\'':
      case '\"':
        word.push_back(new_command[i]);
        if (!quoteStack.empty())
        {
          if (new_command[i] == quoteStack[quoteStack.size() - 1])
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


// Check if character is not allowed for the temporary file name.
//
bool
IsBadCharacter(char c)
{
  if (!isgraph(c))
  {
    return true;
  }

  switch (c)
  {
    case '/':
    case '\\':
    case ' ':
    case ':':
    case '\"':
    case '\'':
      return true;
    default:
      return false;
  }
}

//
std::string
FormatFileName(const std::string & TempDirectory,
               const std::string & name,
               const std::string & extension,
               const int           tagID)
{
  std::string TempFile = TempDirectory;

#ifdef _WIN32
  int pid = _getpid();
#else
  int pid = getpid();
#endif

  std::ostringstream tmp;

  if (!name.empty())
  {
    std::string n = name;
    // remove whitespace
    n.erase(std::remove_if(n.begin(), n.end(), &IsBadCharacter), n.end());

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
std::string
DoubleBackslashes(const std::string & word)
{
  std::string result;

  for (unsigned int i = 0; i < word.length(); i++)
  {
    // put in and extra backslash
    if (word[i] == '\\' || word[i] == '/')
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
std::string
BuildFullFileName(const std::string & name, const std::string & extension, const int tagID)
{
  std::string TempDirectory;

#ifdef _WIN32
  if (!itksys::SystemTools::GetEnv("TMP", TempDirectory) && !itksys::SystemTools::GetEnv("TEMP", TempDirectory) &&
      !itksys::SystemTools::GetEnv("USERPROFILE", TempDirectory) &&
      !itksys::SystemTools::GetEnv("WINDIR", TempDirectory))
  {
    sitkExceptionMacro(
      << "Can not find temporary directory.  Tried TMP, TEMP, USERPROFILE, and WINDIR environment variables");
  }
  TempDirectory = TempDirectory + "\\";
  TempDirectory = DoubleBackslashes(TempDirectory);
#else
  TempDirectory = "/tmp/";
#endif
  return FormatFileName(TempDirectory, name, extension, tagID);
}

} // namespace

} // namespace itk::simple
