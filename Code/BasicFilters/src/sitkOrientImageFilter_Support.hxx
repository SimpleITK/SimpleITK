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
#ifndef sitkOrientImageFilter_Support_hxx
#define sitkOrientImageFilter_Support_hxx

#include "itkSpatialOrientation.h"
#include "itkSpatialOrientationAdapter.h"

// This file is intended to contain the definition of static
// membervariables needed by JSON Expand templated image filters.
// It may also contain other member declarations, or other useful
// items that could be specified here, as opposed to the JSON.

namespace itk {
  namespace simple {

    namespace {

    std::map< std::string, itk::SpatialOrientation::ValidCoordinateOrientationFlags > sitkCreateStringToCode()
    {
      std::map< std::string, itk::SpatialOrientation::ValidCoordinateOrientationFlags > stringToCode;

      // Map between axis string labels and SpatialOrientation
      stringToCode["RIP"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_RIP;
      stringToCode["LIP"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_LIP;
      stringToCode["RSP"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_RSP;
      stringToCode["LSP"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_LSP;
      stringToCode["RIA"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_RIA;
      stringToCode["LIA"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_LIA;
      stringToCode["RSA"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_RSA;
      stringToCode["LSA"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_LSA;
      stringToCode["IRP"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_IRP;
      stringToCode["ILP"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_ILP;
      stringToCode["SRP"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_SRP;
      stringToCode["SLP"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_SLP;
      stringToCode["IRA"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_IRA;
      stringToCode["ILA"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_ILA;
      stringToCode["SRA"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_SRA;
      stringToCode["SLA"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_SLA;
      stringToCode["RPI"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_RPI;
      stringToCode["LPI"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_LPI;
      stringToCode["RAI"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_RAI;
      stringToCode["LAI"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_LAI;
      stringToCode["RPS"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_RPS;
      stringToCode["LPS"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_LPS;
      stringToCode["RAS"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_RAS;
      stringToCode["LAS"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_LAS;
      stringToCode["PRI"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_PRI;
      stringToCode["PLI"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_PLI;
      stringToCode["ARI"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_ARI;
      stringToCode["ALI"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_ALI;
      stringToCode["PRS"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_PRS;
      stringToCode["PLS"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_PLS;
      stringToCode["ARS"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_ARS;
      stringToCode["ALS"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_ALS;
      stringToCode["IPR"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_IPR;
      stringToCode["SPR"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_SPR;
      stringToCode["IAR"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_IAR;
      stringToCode["SAR"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_SAR;
      stringToCode["IPL"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_IPL;
      stringToCode["SPL"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_SPL;
      stringToCode["IAL"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_IAL;
      stringToCode["SAL"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_SAL;
      stringToCode["PIR"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_PIR;
      stringToCode["PSR"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_PSR;
      stringToCode["AIR"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_AIR;
      stringToCode["ASR"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_ASR;
      stringToCode["PIL"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_PIL;
      stringToCode["PSL"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_PSL;
      stringToCode["AIL"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_AIL;
      stringToCode["ASL"] = SpatialOrientation::ITK_COORDINATE_ORIENTATION_ASL;

      return stringToCode;
    }


    const std::map< std::string, itk::SpatialOrientation::ValidCoordinateOrientationFlags > &sitkGetStringToCode()
    {
      const static std::map< std::string, SpatialOrientation::ValidCoordinateOrientationFlags> stringToCode = sitkCreateStringToCode();
      return stringToCode;
    }

    itk::SpatialOrientation::ValidCoordinateOrientationFlags
    sitkStringToSpatialOrientation(const std::string &str)
    {
      const  std::map< std::string, SpatialOrientation::ValidCoordinateOrientationFlags> &stringToCode = sitkGetStringToCode();

      std::map< std::string, SpatialOrientation::ValidCoordinateOrientationFlags>::const_iterator iter = stringToCode.find(str);

      if ( iter == stringToCode.end())
        {
        sitkExceptionMacro("Invalid spatial orientation string \"" << str << "\"!");
        }
      return iter->second;
    }

    }

  std::string OrientImageFilter::GetOrientationFromDirectionCosines( const std::vector<double> &direction )
  {
    const  std::map< std::string, SpatialOrientation::ValidCoordinateOrientationFlags> &stringToCode = sitkGetStringToCode();

    typedef typename itk::ImageBase<3>::DirectionType DirectionType;
    const DirectionType itkDirection = sitkSTLToITKDirection<DirectionType>(direction);

    itk::SpatialOrientation::ValidCoordinateOrientationFlags itkOrientation =
      itk::SpatialOrientationAdapter().FromDirectionCosines(itkDirection);

    for ( std::map< std::string, SpatialOrientation::ValidCoordinateOrientationFlags>::const_iterator iter = stringToCode.begin();
          iter != stringToCode.end();
          ++iter)
      {
      if (iter->second == itkOrientation)
        {
        return iter->first;
        }
      }

    return "unknown";
  }

  std::vector<double> OrientImageFilter::GetDirectionCosinesFromOrientation( const std::string &str )
  {
    itk::SpatialOrientation::ValidCoordinateOrientationFlags itkOrientation =
      sitkStringToSpatialOrientation(str);

    typedef typename itk::ImageBase<3>::DirectionType DirectionType;
    const DirectionType itkDirection =
      itk::SpatialOrientationAdapter().ToDirectionCosines(itkOrientation);

    return sitkITKDirectionToSTL(itkDirection);

  }

  }
}

#endif
