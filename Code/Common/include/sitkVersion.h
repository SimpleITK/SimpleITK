#ifndef __sitkVersion_h
#define __sitkVersion_h

#include "sitkMacro.h"

namespace itk
{

namespace simple
{

  /** \class Version
   * \brief Version info for SimpleITK
   */
  class Version
  {
  public:
    static unsigned int MajorVersion();
    static unsigned int MinorVersion();
    static unsigned int PatchVersion();

    static std::string VersionString();
    static std::string BuildDate();
    static std::string GitRefspec();
    static std::string GitSHA1();
    static std::string GitTag();

    static std::string ExtendedVersionString();
    std::string ToString() { return Version::ExtendedVersionString(); }
  };

}
}

#endif
