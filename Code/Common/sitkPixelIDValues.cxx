#include "sitkPixelIDValues.h"

namespace itk
{
namespace simple
{


const char * GetPixelIDValueAsString( PixelIDValueType type )
{

  if ( type == sitkUnknown )
    {
    // Unknow must be first because other enums may be -1 if they are
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
    return "conplex of 32-bit float";
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
  else if ( sitkLabelUInt16 )
    {
    return "label of 16-bit unsigned integer";
    }
  else if ( sitkLabelUInt32 )
    {
    return "label of 32-bit unsigned integer";
    }
  else if ( sitkLabelUInt64 )
    {
    return "label of 64-bit unsigned integer";
    }
  else
    {
    return "ERRONEOUS PIXEL ID!";
    }
}


}
}
