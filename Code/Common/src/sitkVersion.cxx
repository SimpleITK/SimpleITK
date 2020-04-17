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
#include "sitkVersion.h"
#include "sitkVersionConfig.h"

#include "itkConfigure.h"

#include <cstring>
#include <algorithm>

namespace
{

std::string MakeExtendedVersionString()
{
  std::ostringstream v;
  v << "SimpleITK Version: " << itk::simple::Version::VersionString()
    << " (ITK " << ITK_VERSION_STRING << ")" << std::endl
    << "Compiled: " << itk::simple::Version::BuildDate() << std::endl;
  return v.str();
}

static const std::string itkVersionString = ITK_VERSION_STRING;
static const std::string extendedVersionString = MakeExtendedVersionString();
static const char * itkModulesEnabled = ITK_MODULES_ENABLED;
}

namespace itk
{
  namespace simple
  {

  unsigned int Version::MajorVersion()
  {
    return SimpleITK_VERSION_MAJOR;
  }
  unsigned int Version::MinorVersion()
  {
    return SimpleITK_VERSION_MINOR;
  }
  unsigned int Version::PatchVersion()
  {
    return SimpleITK_VERSION_PATCH;
  }
  unsigned int Version::TweakVersion()
  {
    return 0;
  }
  const std::string &Version::VersionString()
  {
    static const std::string v( SimpleITK_VERSION );
    return v;
  }
  const std::string &Version::BuildDate()
  {
    static const std::string v( __DATE__ " " __TIME__ );
    return v;
  }
  unsigned int Version::ITKMajorVersion()
  {
    return ITK_VERSION_MAJOR;
  }
  unsigned int Version::ITKMinorVersion()
  {
    return ITK_VERSION_MINOR;
  }
  unsigned int Version::ITKPatchVersion()
  {
    return ITK_VERSION_PATCH;
  }
  const std::string &Version::ITKVersionString()
  {
    return itkVersionString;
  }


  std::vector<std::string> Version::ITKModulesEnabled()
  {
    // itkModulesEnabled is a semi-colon separate list of the ITK modules
    // enabled during compilation. This method splits that one string
    // into separate strings.
    const char * strMods = itkModulesEnabled;
    const char * strModsEnd = strMods+strlen( itkModulesEnabled );


    std::vector<std::string> modules_vector;
    modules_vector.reserve(std::count(strMods,
                                      strModsEnd,
                                      ';'));

    while (strMods < strModsEnd)
      {
      const char *tokenMod = std::find(strMods, strModsEnd, ';');

      modules_vector.emplace_back(strMods, tokenMod);

      strMods = tokenMod+1;
      }
    return modules_vector;

  }

  const std::string &Version::ExtendedVersionString()
  {
    return extendedVersionString;
  }
  }
}
