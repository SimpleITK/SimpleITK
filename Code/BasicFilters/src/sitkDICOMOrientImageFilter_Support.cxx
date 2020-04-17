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

#include "sitkDICOMOrientImageFilter.h"
#include "itkDICOMOrientation.h"

// This file is intended to contain the definition of static
// member variables needed by JSON Expand templated image filters.
// It may also contain other member declarations, or other useful
// items that could be specified here, as opposed to the JSON.

namespace itk {
  namespace simple {

  std::string DICOMOrientImageFilter::GetOrientationFromDirectionCosines( const std::vector<double> &direction )
  {
    using DirectionType = typename itk::ImageBase<3>::DirectionType;
    const DirectionType itkDirection = sitkSTLToITKDirection<DirectionType>(direction);

    const DICOMOrientation orientation(itkDirection);
    return orientation.GetAsString();
  }

  std::vector<double> DICOMOrientImageFilter::GetDirectionCosinesFromOrientation( const std::string &str )
  {
    const DICOMOrientation orientation(str);

    const auto itkDirection = orientation.GetAsDirection();

    return sitkITKDirectionToSTL(itkDirection);

  }

  }
}
