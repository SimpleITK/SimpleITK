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

#include "itksys/SystemTools.hxx"
#include "itksys/SystemInformation.hxx"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>



namespace
{

void SystemInformationPrintFile(const std::string &name, std::ostream& os)
{
  const char* div = "=======================================================================";
  os << "System Information File \"" << name << "\"";

  if(! itksys::SystemTools::FileExists( name.c_str(), true) )
    {
    os << " does not exist.\n";
    return;
    }

  std::ifstream fin(name.c_str());
  if(fin)
    {
    os << ":\n[" << div << "[\n";
    os << fin.rdbuf();
    os << "]" << div << "]\n";
    os.flush();
    }
  else
    {
    os << " but cannot be opened for read.\n";
    }
}


void SystemInformationPrint(std::ostream& os)
{
  itksys::SystemInformation mySys;
  mySys.RunCPUCheck();
  mySys.RunOSCheck();
  mySys.RunMemoryCheck();

  os << "---------- System Information ----------" << std::endl;

  os << "VendorString:                 "
     << mySys.GetVendorString() << std::endl;
  os << "VendorID:                     "
     << mySys.GetVendorID() << std::endl;
  os << "TypeID:                       "
     << mySys.GetTypeID() << std::endl;
  os << "FamilyID:                     "
     << mySys.GetFamilyID() << std::endl;
  os << "ModelID:                      "
     << mySys.GetModelID() << std::endl;
  os << "SteppingCode:                 "
     << mySys.GetSteppingCode() << std::endl;
  os << "ExtendedProcessorName:        "
     << mySys.GetExtendedProcessorName() << std::endl;
  os << "DoesCPUSupportCPUID:          "
     << mySys.DoesCPUSupportCPUID() << std::endl;;
  os << "ProcessorSerialNumber:        "
     << mySys.GetProcessorSerialNumber() << std::endl;
  os << "ProcessorCacheSize:           "
     << mySys.GetProcessorCacheSize() << std::endl;
  os << "LogicalProcessorsPerPhysical: "
     << mySys.GetLogicalProcessorsPerPhysical() << std::endl;
  os << "ProcessorClockFrequency:      "
     << mySys.GetProcessorClockFrequency() << std::endl;
  os << "ProcessorAPICID:              "
     << mySys.GetProcessorAPICID() << std::endl;

  os << "OSName:                       "
     << mySys.GetOSName() << std::endl;
  os << "Hostname:                     "
     << mySys.GetHostname() << std::endl;
  os << "OSRelease:                    "
     << mySys.GetOSRelease() << std::endl;
  os << "OSVersion:                    "
     << mySys.GetOSVersion() << std::endl;
  os << "OSPlatform:                   "
     << mySys.GetOSPlatform() << std::endl;

  os << "Is64Bits:                     "
     << mySys.Is64Bits() << std::endl;

  os << "NumberOfLogicalCPU:           "
     << mySys.GetNumberOfLogicalCPU() << std::endl;
  os << "NumberOfPhysicalCPU:          "
     << mySys.GetNumberOfPhysicalCPU() << std::endl;

  // Retrieve memory information in megabyte.
  os << "TotalVirtualMemory:           "
     << mySys.GetTotalVirtualMemory() << std::endl;
  os << "AvailableVirtualMemory:       "
     << mySys.GetAvailableVirtualMemory() << std::endl;
  os << "TotalPhysicalMemory:          "
     << mySys.GetTotalPhysicalMemory() << std::endl;
  os << "AvailablePhysicalMemory:      "
     << mySys.GetAvailablePhysicalMemory() << std::endl;
}



}

int main(int argc, char* argv[])
{
  if(argc != 2)
    {
    std::cerr << "Usage: itkSystemInformationTest <top-of-build-tree>\n";
    return EXIT_FAILURE;
    }
  std::string build_dir = argv[1];
  build_dir += "/";

  const char* files[] =
    {
      "CMakeCache.txt",
      "CMakeCacheInit.txt",
      "sitkConfigure.h",
      "CMakeFiles/CMakeOutput.log",
      "CMakeFiles/CMakeError.log",
      "SimpleITKConfig.cmake",
      "SimpleITKConfigVersion.cmake",
      "SimpleITKTargets.cmake",
      0
    };

  // Preserve valuable output regardless of the limits set in
  // CMake/CTestCustom.cmake
  std::cout << "CTEST_FULL_OUTPUT" << std::endl;

  for(const char** f = files; *f; ++f)
    {
    std::string fname = build_dir + *f;
    SystemInformationPrintFile(fname.c_str(), std::cout);
    }

  SystemInformationPrint( std::cout );

  return EXIT_SUCCESS;
}
