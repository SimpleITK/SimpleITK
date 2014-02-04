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
#ifndef __SimpleITKTestHarness_h
#define __SimpleITKTestHarness_h

// include ITK before STL to prevent warning in std::copy
#include <itkMacro.h>

#include <string>
#include <vector>
#include <gtest/gtest.h>
#include <SimpleITKTestHarnessPaths.h>
#include <itksys/SystemTools.hxx>
#include <itksys/Process.h>

#include "sitkImage.h"
#include "sitkImageFileReader.h"
#include "sitkHashImageFilter.h"
#include "sitkCommand.h"

// Class to help us find test data
//
/*
 * DataFinder maintains several directory paths.  It also
 * helps us find executables.
 *
 * Set/GetDirectory  -- Test Data directory
 *                      should be ITK/Testing/Data
 * Set/GetOutputDirectory -- Temporary directory
 *                      SimpleITK-build/Testing/Temporary
 * Set/GetRuntimeDirectory -- Where built executables are found
 *                           SimpleITK-build/bin/$(OutDir)/
 * Set/GetLibraryDirectory -- Where built libraries are found
 *                           SimpleITK-build/lib
 * GetOutputFile --     File in the temp directory
 * GetBuildDirectory -- SimpleITK-build
 * FindExecutable --    Attempts to find an executable
 *                      Returns GetExecutableDirectory + "/" + filename
 */
class DataFinder
{

public:
  DataFinder ()
    {
    mDirectory = TEST_HARNESS_DATA_DIRECTORY;
    mOutputDirectory = TEST_HARNESS_TEMP_DIRECTORY;
    mRuntimeDirectory = RUNTIME_OUTPUT_PATH;
    mLibraryDirectory = LIBRARY_OUTPUT_PATH;
    };

  void SetDirectory ( const char* dir )
    {
    mDirectory = dir;
    };

  void SetDirectory ( std::string dir )
    {
    mDirectory = dir;
    };

  void SetRuntimeDirectoryFromArgv0 ( std::string argv0 ) ;

  void SetOutputDirectory ( std::string dir )
    {
    mOutputDirectory = dir;
    };

  std::string GetDirectory ()        const { return mDirectory; };
  std::string GetOutputDirectory ()  const { return mOutputDirectory; };
  std::string GetOutputFile ( std::string filename )
                                     const { return mOutputDirectory + "/" + filename; };
  std::string GetRuntimeDirectory () const { return mRuntimeDirectory; }
  std::string GetLibraryDirectory () const { return mLibraryDirectory; }
  std::string GetBuildDirectory ()    const { return std::string ( SIMPLEITK_BINARY_DIR ); }
  std::string GetPathSeparator ()
    {
#ifdef WIN32
    return ";";
#else
    return ":";
#endif
    }

  std::vector<std::string> FindExecutable ( std::string exe );
  std::vector<std::string> GetLuaExecutable ();
  std::vector<std::string> GetTclExecutable ();
  std::vector<std::string> GetPythonExecutable ();
  std::vector<std::string> GetRubyExecutable ();
  std::vector<std::string> GetRExecutable ();
  std::vector<std::string> GetJavaExecutable ();
  std::vector<std::string> GetCSharpCompiler ();
  std::vector<std::string> GetCSharpInterpreter ();

  std::string GetCSharpBinaryDirectory ()         { return std::string ( CSHARP_BINARY_DIRECTORY ); }
  std::string GetSourceDirectory ()               { return std::string ( SIMPLEITK_SOURCE_DIR ); }

  bool FileExists ( const std::string &filename )
    {
      return itksys::SystemTools::FileExists ( filename.c_str() );
    }

  std::string GetFile ( const std::string &filename )
    {
      std::string name;

      name = mDirectory + "/" + filename;
      if (this->FileExists(name))
        return name;

      // fall back to source code path
      name = std::string(SIMPLEITK_SOURCE_DIR) + "/Testing/Data/" + filename;

      return name;
    };

protected:
  std::string mDirectory;
  std::string mOutputDirectory;
  std::string mRuntimeDirectory;
  std::string mLibraryDirectory;
};

extern DataFinder dataFinder;


/// Class for running external programs
class ExternalProgramRunner : public testing::Test
{
public:

  // check an image file that it matches the expected hash
  void CheckImageHash ( const std::string &fileName, const std::string &hash );

  // Return the separator
  static std::string GetPathSeparator ()
    {
#ifdef WIN32
    return ";";
#else
    return ":";
#endif
    }

  /// \brief Set an environment variable
  void SetEnvironment ( std::string key, std::string value );

  /** \brief Run the command line specified in the list of arguments.
   * Call FAIL if the executable fails returning -1, return the value returned by the
   * process otherwise.
   */
  int RunExecutable ( std::vector<std::string> CommandLine, bool showOutput = false );
};

class Python : public ExternalProgramRunner { };
class Lua    : public ExternalProgramRunner { };
class Java   : public ExternalProgramRunner { };
class Tcl    : public ExternalProgramRunner { };
class R      : public ExternalProgramRunner { };
class Ruby   : public ExternalProgramRunner { };
class CSharp : public ExternalProgramRunner { };


/** Base Command Class which holds onto a process object
 */
class ProcessObjectCommand
  : public itk::simple::Command
{
public:
  ProcessObjectCommand(itk::simple::ProcessObject &po);

protected:
  itk::simple::ProcessObject &m_Process;
};

/** Print the progress to the std::cout
 */
class ProgressUpdate
  : public ProcessObjectCommand
{
public:
  ProgressUpdate(itk::simple::ProcessObject &po);

  virtual void Execute( );

  float m_Progress;
};

/** Command which will invoke ProcessObject::Abort when AbortAt
 * progress is reached.
 */
class AbortAtCommand
  : public ProcessObjectCommand
{
public:
  AbortAtCommand(itk::simple::ProcessObject &po, float abortAt);

  virtual void Execute( );

  float m_AbortAt;
};

/** Command which counts the number of time the command has been
 * invoked.
 */
class CountCommand
  : public ProcessObjectCommand
{
public:
  CountCommand(itk::simple::ProcessObject &po);

  virtual void Execute( );

  int m_Count;
};

#include "sitkImageCompare.h"

#endif
