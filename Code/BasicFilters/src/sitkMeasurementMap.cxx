#include "sitkMeasurementMap.h"

#include <algorithm>
#include <iterator>
#include <iostream>

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

  void MeasurementMap::PrintToCSVString() const
    {
    const MeasurementMap::LabelListType printLabelList = this->GetVectorOfMeasurementNames();
    const MeasurementMap::ValueListType printValueList = this->GetVectorOfMeasurementValues();
    //Print with trailing comma.
      {
      std::ostream_iterator< BasicMeasurementMap::key_type > outputLabels( std::cout, ", " );
      std::copy( printLabelList.begin(), printLabelList.end(), outputLabels );
      std::cout << std::endl;
      }
      {
      std::ostream_iterator< BasicMeasurementMap::mapped_type > outputValues( std::cout, ", " );
      std::copy( printValueList.begin(), printValueList.end(), outputValues );
      std::cout << std::endl;
      }
    }


} // end namespace simple
} // end namespace itk
