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
#ifndef sitkPixelIDValues_h
#define sitkPixelIDValues_h

#include "sitkCommon.h"
#include "sitkPixelIDTypeLists.h"

#include <string>
#include <ostream>

namespace itk
{
namespace simple
{

using PixelIDValueType = int;

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


template <unsigned int VImageDimension>
struct ImageTypeToPixelIDValue< itk::ImageBase<VImageDimension> >
{
  enum { Result = -1 };
};


/** \brief Enumerated values of pixelIDs
 *
 * Each PixelID's value corresponds to the index of the PixelID type,
 * in the type list "InstantiatedPixelIDTypeList". It is possible that
 * different configurations for SimpleITK could result in different
 * values for pixelID. So these enumerated values should be used.
 *
 * Additionally, not all PixelID an instantiated in for the tool
 * kit. If a PixelID is not instantiated then it's value is
 * -1. Therefore it is likely that multiple elements in the
 * enumeration will have a zero value. Therefore the first preferred
 * method is to use "if" statements, with the first branch checking
 * for the Unknown value.
 *
 * If a switch case statement is needed the ConditionalValue
 * meta-programming object can be used as follows:
 * \code
 *  switch( pixelIDValue )
 *     {
 *   case sitk::sitkUnknown:
 *     // handle exceptional case
 *     break
 *   case sitk::ConditionalValue< sitk::sitkUInt8 != sitk::sitkUnknown, sitk::sitkUInt8, -2 >::Value:
 *     ...
 *     break;
 *   case sitk::ConditionalValue< sitk::sitkInt8 != sitk::sitkUnknown, sitk::sitkInt8, -3 >::Value:
 *     ...
 *     break;
 *   case sitk::ConditionalValue< sitk::N != sitk::sitkUnknown, sitk::N, -N >::Value:
 *     ...
 *     break;
 *   default:
 *      // handle another exceptional case
 *     }
 * \endcode
 */
enum PixelIDValueEnum {
  sitkUnknown = -1,
  sitkUInt8 = PixelIDToPixelIDValue< BasicPixelID<uint8_t> >::Result,   ///< Unsigned 8 bit integer
  sitkInt8 = PixelIDToPixelIDValue< BasicPixelID<int8_t> >::Result,     ///< Signed 8 bit integer
  sitkUInt16 = PixelIDToPixelIDValue< BasicPixelID<uint16_t> >::Result, ///< Unsigned 16 bit integer
  sitkInt16 = PixelIDToPixelIDValue< BasicPixelID<int16_t> >::Result,   ///< Signed 16 bit integer
  sitkUInt32 = PixelIDToPixelIDValue< BasicPixelID<uint32_t> >::Result, ///< Unsigned 32 bit integer
  sitkInt32 = PixelIDToPixelIDValue< BasicPixelID<int32_t> >::Result,   ///< Signed 32 bit integer
  sitkUInt64 = PixelIDToPixelIDValue< BasicPixelID<uint64_t> >::Result, ///< Unsigned 64 bit integer
  sitkInt64 = PixelIDToPixelIDValue< BasicPixelID<int64_t> >::Result,   ///< Signed 64 bit integer
  sitkFloat32 = PixelIDToPixelIDValue< BasicPixelID<float> >::Result,   ///< 32 bit float
  sitkFloat64 = PixelIDToPixelIDValue< BasicPixelID<double> >::Result,  ///< 64 bit float
  sitkComplexFloat32 = PixelIDToPixelIDValue< BasicPixelID<std::complex<float> > >::Result,  ///< complex number of 32 bit float
  sitkComplexFloat64 = PixelIDToPixelIDValue< BasicPixelID<std::complex<double> > >::Result,  ///< complex number of 64 bit float
  sitkVectorUInt8 = PixelIDToPixelIDValue< VectorPixelID<uint8_t> >::Result, ///< Multi-component of unsigned 8 bit integer
  sitkVectorInt8 = PixelIDToPixelIDValue< VectorPixelID<int8_t> >::Result, ///< Multi-component of signed 8 bit integer
  sitkVectorUInt16 = PixelIDToPixelIDValue< VectorPixelID<uint16_t> >::Result, ///< Multi-component of unsigned 16 bit integer
  sitkVectorInt16 = PixelIDToPixelIDValue< VectorPixelID<int16_t> >::Result, ///< Multi-component of signed 16 bit integer
  sitkVectorUInt32 = PixelIDToPixelIDValue< VectorPixelID<uint32_t> >::Result, ///< Multi-component of unsigned 32 bit integer
  sitkVectorInt32 = PixelIDToPixelIDValue< VectorPixelID<int32_t> >::Result, ///< Multi-component of signed 32 bit integer
  sitkVectorUInt64 = PixelIDToPixelIDValue< VectorPixelID<uint64_t> >::Result, ///< Multi-component of unsigned 64 bit integer
  sitkVectorInt64 = PixelIDToPixelIDValue< VectorPixelID<int64_t> >::Result, ///< Multi-component of signed 64 bit integer
  sitkVectorFloat32 = PixelIDToPixelIDValue< VectorPixelID<float> >::Result, ///< Multi-component of 32 bit float
  sitkVectorFloat64 = PixelIDToPixelIDValue< VectorPixelID<double> >::Result,  ///< Multi-component of 64 bit float
  sitkLabelUInt8 = PixelIDToPixelIDValue< LabelPixelID<uint8_t> >::Result, ///< RLE label of unsigned 8 bit integers
  sitkLabelUInt16 = PixelIDToPixelIDValue< LabelPixelID<uint16_t> >::Result, ///< RLE label of unsigned 16 bit integers
  sitkLabelUInt32 = PixelIDToPixelIDValue< LabelPixelID<uint32_t> >::Result, ///< RLE label of unsigned 32 bit integers
  sitkLabelUInt64 = PixelIDToPixelIDValue< LabelPixelID<uint64_t> >::Result, ///< RLE label of unsigned 64 bit integers
};


const std::string SITKCommon_EXPORT GetPixelIDValueAsString( PixelIDValueType type );
const std::string SITKCommon_EXPORT GetPixelIDValueAsString( PixelIDValueEnum type );

/** \brief Function mapping enumeration names in std::string to values
 *
 * This function is intended for use by the R bindings. R stores the enumeration values
 * using the names : "sitkUnknown", "sitkUInt8", etc from PixelIDValueEnum above.
 * This function is used to provide the integer values using calls like:
 *
 * val = GetPixelIDValueFromString("sitkInt32")
 *
 * If the pixel type has not been instantiated then the sitkUnknown value (-1) will
 * be returned. If the pixel type string is not recognized (i.e. is not in the
 * set of tested names) then the return value is -99. The idea is to provide
 * a warning (via the R package) if this function needs to be updated to match
 * changes to PixelIDValueEnum - i.e. if a new pixel type is added.
 */
PixelIDValueType SITKCommon_EXPORT GetPixelIDValueFromString(const std::string &enumString );

#ifndef SWIG
SITKCommon_EXPORT std::ostream& operator<<(std::ostream& os, const PixelIDValueEnum id);
#endif


}
}
#endif // sitkPixelIDValues_h
