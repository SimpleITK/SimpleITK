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
#ifndef __sitkMeasurementMap_h
#define __sitkMeasurementMap_h

#include <map>
#include <vector>
#include <string>

#include "sitkBasicFilters.h"

namespace itk {
namespace simple {

typedef std::map<std::string, double> BasicMeasurementMap;

/** \class MeasurementMap
 *   \brief A generic class that simply holds key value pairs
 *          intended primarily for holding measurements
 *          It is a thin wrapper around an std::map<std::string,double>
 *          that adds some convenience functions.
 */
class SITKBasicFilters0_EXPORT MeasurementMap: public BasicMeasurementMap
{
public:
  MeasurementMap();

  typedef std::vector<BasicMeasurementMap::key_type> LabelListType;
  //Return a vector of measurement names
  LabelListType GetVectorOfMeasurementNames( ) const;

  typedef std::vector<BasicMeasurementMap::mapped_type> ValueListType;
  //Return a vector of values for the measurements
  ValueListType GetVectorOfMeasurementValues( ) const;

  BasicMeasurementMap GetBasicMeasurementMap( ) const;

  // Format a string in csv format that can be easily pasted to a spreadsheet.
  std::string ToString( ) const;
  // Helper to write to a stream
  void ToStream ( std::ostream& ) const;

};
}
}
#endif
