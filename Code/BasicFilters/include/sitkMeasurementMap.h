#ifndef __sitkMeasurementMap_h
#define __sitkMeasurementMap_h

#include <map>
#include <vector>

namespace itk {
namespace simple {

typedef std::map<std::string, double> BasicMeasurementMap;

/** \class MeasurementMap
 *   \brief A generic class that simply holds key value pairs
 *          intended primarily for holding measurements
 *          It is a thin wrapper around an std::map<std::string,double>
 *          that adds some convenience functions.
 */
class MeasurementMap: public BasicMeasurementMap
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
