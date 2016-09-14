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
#ifndef sitkVersion_h
#define sitkVersion_h

#include "sitkCommon.h"

namespace itk
{

namespace simple
{

  /** \class Version
   * \brief Version info for SimpleITK
   */
  class SITKCommon_EXPORT Version
  {
  public:
    static unsigned int MajorVersion();
    static unsigned int MinorVersion();
    static unsigned int PatchVersion();
    static unsigned int TweakVersion();
    static const std::string &VersionString();
    static const std::string &BuildDate();


    static unsigned int ITKMajorVersion();
    static unsigned int ITKMinorVersion();
    static unsigned int ITKPatchVersion();
    static const std::string &ITKVersionString();

    static const std::string &ExtendedVersionString();
    std::string ToString() { return Version::ExtendedVersionString(); }
  };

}
}

#endif
