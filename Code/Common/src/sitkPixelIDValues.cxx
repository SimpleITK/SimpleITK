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
#include "sitkPixelIDValues.h"

namespace itk
{
namespace simple
{


const std::string GetPixelIDValueAsString( PixelIDValueEnum type )
{
  return GetPixelIDValueAsString( static_cast<PixelIDValueType>(type) );
}

const std::string GetPixelIDValueAsString( PixelIDValueType type )
{

  if ( type == sitkUnknown )
    {
    // Unknown must be first because other enums may be -1 if they are
    // not instantiated
    return "Unknown pixel id";
    }
  else if ( type == sitkUInt8 )
    {
    return "8-bit unsigned integer";
    }
  else if ( type == sitkInt8 )
    {
    return "8-bit signed integer";
    }
  else if ( type ==  sitkUInt16 )
    {
    return "16-bit unsigned integer";
    }
  else if ( type == sitkInt16 )
    {
    return "16-bit signed integer";
    }
  else if ( type == sitkUInt32 )
    {
    return "32-bit unsigned integer";
    }
  else if ( type == sitkInt32 )
    {
    return "32-bit signed integer";
    }
  else if ( type == sitkUInt64 )
    {
    return "64-bit unsigned integer";
    }
  else if ( type == sitkInt64 )
    {
    return "64-bit signed integer";
    }
  else if ( type == sitkFloat32 )
    {
    return "32-bit float";
    }
  else if ( type == sitkFloat64 )
    {
    return "64-bit float";
    }
  else if ( type == sitkComplexFloat32 )
    {
    return "complex of 32-bit float";
    }
  else if ( type == sitkComplexFloat64 )
    {
    return "complex of 64-bit float";
    }
  else if ( type == sitkVectorUInt8 )
    {
    return "vector of 8-bit unsigned integer";
    }
  else if ( type == sitkVectorInt8 )
    {
    return "vector of 8-bit signed integer";
    }
  else if ( type ==  sitkVectorUInt16 )
    {
    return "vector of 16-bit unsigned integer";
    }
  else if ( type == sitkVectorInt16 )
    {
    return "vector of 16-bit signed integer";
    }
  else if ( type == sitkVectorUInt32 )
    {
    return "vector of 32-bit unsigned integer";
    }
  else if ( type == sitkVectorInt32 )
    {
    return "vector of 32-bit signed integer";
    }
  else if ( type == sitkVectorUInt64 )
    {
    return "vector of 64-bit unsigned integer";
    }
  else if ( type == sitkVectorInt64 )
    {
    return "vector of 64-bit signed integer";
    }
  else if ( type == sitkVectorFloat32 )
    {
    return "vector of 32-bit float";
    }
  else if ( type == sitkVectorFloat64 )
    {
    return "vector of 64-bit float";
    }
  else if ( type == sitkLabelUInt8 )
    {
    return "label of 8-bit unsigned integer";
    }
  else if ( type == sitkLabelUInt16 )
    {
    return "label of 16-bit unsigned integer";
    }
  else if ( type == sitkLabelUInt32 )
    {
    return "label of 32-bit unsigned integer";
    }
  else if ( type == sitkLabelUInt64 )
    {
    return "label of 64-bit unsigned integer";
    }
  else
    {
    return "ERRONEOUS PIXEL ID!";
    }
}


PixelIDValueType GetPixelIDValueFromString(const std::string &enumString )
{

  if ( enumString == "sitkUnknown" )
    {
    // Unknown must be first because other enums may be -1 if they are
    // not instantiated
      return sitkUnknown;
    }
  else if ( enumString == "sitkUInt8" )
    {
      return sitkUInt8;
    }
  else if ( enumString == "sitkInt8" )
    {
      return sitkInt8;
    }
  else if ( enumString ==  "sitkUInt16" )
    {
      return sitkUInt16;
    }
  else if ( enumString == "sitkInt16" )
    {
      return sitkInt16;
    }
  else if ( enumString == "sitkUInt32" )
    {
      return sitkUInt32;
    }
  else if ( enumString == "sitkInt32" )
    {
      return sitkInt32;
    }
  else if ( enumString == "sitkUInt64" )
    {
      return sitkUInt64;
    }
  else if ( enumString == "sitkInt64" )
    {
      return sitkInt64;
    }
  else if ( enumString == "sitkFloat32" )
    {
      return sitkFloat32;
    }
  else if ( enumString == "sitkFloat64" )
    {
      return sitkFloat64;
    }
  else if ( enumString == "sitkComplexFloat32" )
    {
      return sitkComplexFloat32;
    }
  else if ( enumString == "sitkComplexFloat64" )
    {
      return sitkComplexFloat64;
    }
  else if ( enumString == "sitkVectorUInt8" )
    {
      return sitkVectorUInt8;
    }
  else if ( enumString == "sitkVectorInt8" )
    {
      return sitkVectorInt8;
    }
  else if ( enumString ==  "sitkVectorUInt16" )
    {
      return sitkVectorUInt16;
    }
  else if ( enumString == "sitkVectorInt16" )
    {
      return sitkVectorInt16;
    }
  else if ( enumString == "sitkVectorUInt32" )
    {
      return sitkVectorUInt32;
    }
  else if ( enumString == "sitkVectorInt32" )
    {
      return sitkVectorInt32;
    }
  else if ( enumString == "sitkVectorUInt64" )
    {
      return sitkVectorUInt64;
    }
  else if ( enumString == "sitkVectorInt64" )
    {
      return sitkVectorInt64;
    }
  else if ( enumString == "sitkVectorFloat32" )
    {
      return sitkVectorFloat32;
    }
  else if ( enumString == "sitkVectorFloat64" )
    {
      return sitkVectorFloat64;
    }
  else if ( enumString == "sitkLabelUInt8" )
    {
      return sitkLabelUInt8;
    }
  else if ( enumString == "sitkLabelUInt16" )
    {
      return sitkLabelUInt16;
    }
  else if ( enumString == "sitkLabelUInt32" )
    {
      return sitkLabelUInt32;
    }
  else if ( enumString == "sitkLabelUInt64" )
    {
      return sitkLabelUInt64;
    }
  else
    {
    return -99;
    }
}


std::ostream& operator<<(std::ostream& os, const PixelIDValueEnum id)
{
  return (os << GetPixelIDValueAsString(id));
}


}
}
