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
#include "sitkMeasurementMap.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>

namespace itk {
namespace simple {

  //Constructor
  MeasurementMap::MeasurementMap() : BasicMeasurementMap()
  {
  }

  MeasurementMap::LabelListType MeasurementMap::GetVectorOfMeasurementNames () const
    {
    MeasurementMap::LabelListType returnLabelList(0);
    returnLabelList.reserve(this->size());
    for(BasicMeasurementMap::const_iterator elementIt=this->begin();
      elementIt != this->end();
      ++elementIt)
      {
      returnLabelList.push_back(elementIt->first);
      }
    return returnLabelList;
    }


  MeasurementMap::ValueListType MeasurementMap::GetVectorOfMeasurementValues () const
    {
    MeasurementMap::ValueListType returnValueList(0);
    returnValueList.reserve(this->size());
    for(BasicMeasurementMap::const_iterator elementIt=this->begin();
      elementIt != this->end();
      ++elementIt)
      {
      returnValueList.push_back(elementIt->second);
      }
    return returnValueList;
    }


  BasicMeasurementMap MeasurementMap::GetBasicMeasurementMap() const
    {
    return *this;
    }

  std::string MeasurementMap::ToString() const
  {
    std::ostringstream s;
    this->ToStream ( s );
    return s.str();
  }


  void MeasurementMap::ToStream ( std::ostream &stream ) const
    {
    const MeasurementMap::LabelListType printLabelList = this->GetVectorOfMeasurementNames();
    const MeasurementMap::ValueListType printValueList = this->GetVectorOfMeasurementValues();
    //Print with trailing comma.
      {
      std::ostream_iterator< BasicMeasurementMap::key_type > outputLabels( stream, ", " );
      std::copy( printLabelList.begin(), printLabelList.end(), outputLabels );
      stream << std::endl;
      }
      {
      std::ostream_iterator< BasicMeasurementMap::mapped_type > outputValues( stream, ", " );
      std::copy( printValueList.begin(), printValueList.end(), outputValues );
      stream << std::endl;
      }
    }


} // end namespace simple
} // end namespace itk
