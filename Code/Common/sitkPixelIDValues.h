#ifndef _sitkPixelIDValues_h
#define _sitkPixelIDValues_h

#include "sitkPixelIDTypeLists.h"

namespace itk
{
namespace simple
{

typedef int PixelIDValueType;


const char * GetPixelIDValueAsString( PixelIDValueType type );


template < typename TPixelID >
struct PixelIDToPixelIDValue
{
  enum { Result = typelist::IndexOf<InstantiatedPixelIDTypeList, TPixelID >::Result };
};

template <typename TImageType>
struct ImageTypeToPixelIDValue
{
  enum { Result = PixelIDToPixelIDValue< typename ImageTypeToPixelID<TImageType>::PixelIDType>::Result };
};

enum PixelIDValueEnum {
  sitkUnknown = -1,
  sitkUInt8 = PixelIDToPixelIDValue< BasicPixelID<uint8_t> >::Result,   // Unsigned 8 bit integer
  sitkInt8 = PixelIDToPixelIDValue< BasicPixelID<int8_t> >::Result,     // Signed 8 bit integer
  sitkUInt16 = PixelIDToPixelIDValue< BasicPixelID<uint16_t> >::Result, // Unsigned 16 bit integer
  sitkInt16 = PixelIDToPixelIDValue< BasicPixelID<int16_t> >::Result,   // Signed 16 bit integer
  sitkUInt32 = PixelIDToPixelIDValue< BasicPixelID<uint32_t> >::Result, // Unsigned 32 bit integer
  sitkInt32 = PixelIDToPixelIDValue< BasicPixelID<int32_t> >::Result,   // Signed 32 bit integer
  sitkUInt64 = PixelIDToPixelIDValue< BasicPixelID<uint64_t> >::Result, // Unsigned 64 bit integer
  sitkInt64 = PixelIDToPixelIDValue< BasicPixelID<int64_t> >::Result,   // Signed 64 bit integer
  sitkFloat32 = PixelIDToPixelIDValue< BasicPixelID<float> >::Result,   // 32 bit float
  sitkFloat64 = PixelIDToPixelIDValue< BasicPixelID<double> >::Result,  // 64 bit float
  sitkComplexFloat32 = PixelIDToPixelIDValue< BasicPixelID<std::complex<float> > >::Result,  // 64 bit float
  sitkComplexFloat64 = PixelIDToPixelIDValue< BasicPixelID<std::complex<double> > >::Result,  // 64 bit float
  sitkVectorUInt8 = PixelIDToPixelIDValue< VectorPixelID<uint8_t> >::Result,
  sitkVectorInt8 = PixelIDToPixelIDValue< VectorPixelID<int8_t> >::Result,
  sitkVectorUInt16 = PixelIDToPixelIDValue< VectorPixelID<uint16_t> >::Result,
  sitkVectorInt16 = PixelIDToPixelIDValue< VectorPixelID<int16_t> >::Result,
  sitkVectorUInt32 = PixelIDToPixelIDValue< VectorPixelID<uint32_t> >::Result,
  sitkVectorInt32 = PixelIDToPixelIDValue< VectorPixelID<int32_t> >::Result,
  sitkVectorUInt64 = PixelIDToPixelIDValue< VectorPixelID<uint64_t> >::Result,
  sitkVectorInt64 = PixelIDToPixelIDValue< VectorPixelID<int64_t> >::Result,
  sitkVectorFloat32 = PixelIDToPixelIDValue< VectorPixelID<float> >::Result,
  sitkVectorFloat64 = PixelIDToPixelIDValue< VectorPixelID<double> >::Result,
  sitkLabelUInt8 = PixelIDToPixelIDValue< LabelPixelID<uint8_t> >::Result,
  sitkLabelUInt16 = PixelIDToPixelIDValue< LabelPixelID<uint16_t> >::Result,
  sitkLabelUInt32 = PixelIDToPixelIDValue< LabelPixelID<uint32_t> >::Result,
  sitkLabelUInt64 = PixelIDToPixelIDValue< LabelPixelID<uint64_t> >::Result,
};

}
}
#endif // _sitkPixelIDValues_h
