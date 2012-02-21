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
      std::string ExecutableName = itksys::SystemTools::FindFile( "ImageJ" );
      std::string TempDirectory = "";
      std::string TempFile = "";
      std::ostringstream CommandLine;
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
      CommandLine << "\"" + ExecutableName + "\" -o \"" + TempFile + "\"";
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
      CommandLine << "open -a " << ExecutableName  << " \"" << TempFile << "\"";
      WriteImage ( image, TempFile );
      // try executing the command
      int ret = system ( CommandLine.str().c_str() );

      // failed to find ImageJ64.app.  Try ImageJ.app
      if (ret) {
	  ExecutableName = itksys::SystemTools::FindDirectory( "ImageJ.app" );
	  if( ExecutableName == "" )
	  {
          // Just assume it is registered properly in a place where the open command will find it.
	  ExecutableName="ImageJ";
        }
        CommandLine << "open -a " << ExecutableName  << " \"" << TempFile << "\"";
        system ( CommandLine.str().c_str() );
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
      CommandLine << "open -a " << ExecutableName  << " \"" << TempFile << "\"";

#else
      // Must be Linux
      ExecutableName = itksys::SystemTools::FindFile ( "ImageJ" );
      if ( ExecutableName == "" )
        {
        ExecutableName = itksys::SystemTools::FindFile ( "imagej" );
        }
      CommandLine << "\"" + ExecutableName + "\" -o \"" << TempFile << "\" &";
#endif
#endif

      WriteImage ( image, TempFile );
      //std::cout << "Attempting: " << CommandLine.str().c_str() << std::endl;
      system ( CommandLine.str().c_str() );
    }

  }
}

/*

i = SimpleITK.ReadImage ( '/home/blezek/Data/Fixed.nrrd' )
SimpleITK.Show ( i, "test" )

 i = SimpleITK.ReadImage ( 'RA-Float.nrrd' )
 SimpleITK.Show ( i )
*/
