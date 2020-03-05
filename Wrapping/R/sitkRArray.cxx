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


#include <iostream>

#include <Rdefines.h>
#include <Rversion.h>

#include "sitkImage.h"
#include "sitkConditional.h"
#include "sitkImportImageFilter.h"

SEXP ImAsArray(itk::simple::Image src)
{
  // tricky to make this efficient with memory and fast.
  // Ideally we want multithreaded casting directly to the
  // R array. We could use a Cast filter and then a memory copy,
  // obviously producing a redundant copy. If we do a direct cast,
  // then we're probably not multi-threaded.
  // Lets be slow but memory efficient.

  std::vector<unsigned int> sz = src.GetSize();
  itk::simple::PixelIDValueType  PID=src.GetPixelIDValue();
  SEXP res = 0;
  double *dans=0;
  int *ians=0;
  unsigned pixcount=src.GetNumberOfComponentsPerPixel();
  for (unsigned k = 0; k < sz.size();k++)
    {
    pixcount *= sz[k];
    }
  switch (PID)
    {
    case itk::simple::sitkUnknown:
    {
    char error_msg[1024];
    snprintf( error_msg, 1024, "Exception thrown ImAsArray : unknown pixel type");
    Rprintf(error_msg);
    return(res);
    }
    break;
    case itk::simple::ConditionalValue< itk::simple::sitkInt8 != itk::simple::sitkUnknown, itk::simple::sitkInt8, -3 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorInt8 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt8, -15 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkUInt8 != itk::simple::sitkUnknown, itk::simple::sitkUInt8, -2 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt8 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt8, -14 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkInt16 != itk::simple::sitkUnknown, itk::simple::sitkInt16, -5 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorInt16 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt16, -17 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkUInt16 != itk::simple::sitkUnknown, itk::simple::sitkUInt16, -4 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt16 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt16, -16 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkInt32 != itk::simple::sitkUnknown, itk::simple::sitkInt32, -7 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorInt32 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt32, -19 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkUInt32 != itk::simple::sitkUnknown, itk::simple::sitkUInt32, -6 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt32 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt32, -18 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkUInt64 != itk::simple::sitkUnknown, itk::simple::sitkUInt64, -8 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt64 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt64, -20 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkInt64 != itk::simple::sitkUnknown, itk::simple::sitkInt64, -9 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorInt64 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt64, -21 >::Value:
    {
    // allocate an integer array
    PROTECT(res = Rf_allocVector(INTSXP, pixcount));
    ians = INTEGER_POINTER(res);
    }
    break;
    default:
    {
    // allocate double array
    PROTECT(res = Rf_allocVector(REALSXP, pixcount));
    dans = NUMERIC_POINTER(res);
    }
    }

  switch (PID)
    {
    case itk::simple::ConditionalValue< itk::simple::sitkUInt8 != itk::simple::sitkUnknown, itk::simple::sitkUInt8, -2 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt8 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt8, -14 >::Value:
    {
    uint8_t * buff = src.GetBufferAsUInt8();
    std::copy(buff,buff + pixcount,ians);
    }
    break;
    case itk::simple::ConditionalValue< itk::simple::sitkInt8 != itk::simple::sitkUnknown, itk::simple::sitkInt8, -3 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorInt8 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt8, -15 >::Value:
    {
    int8_t * buff = src.GetBufferAsInt8();
    std::copy(buff,buff + pixcount,ians);
    }
    break;
    case itk::simple::ConditionalValue< itk::simple::sitkUInt16 != itk::simple::sitkUnknown, itk::simple::sitkUInt16, -4 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt16 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt16, -16 >::Value:
    {
    uint16_t * buff = src.GetBufferAsUInt16();
    std::copy(buff,buff + pixcount,ians);
    }
    break;
    case itk::simple::ConditionalValue< itk::simple::sitkInt16 != itk::simple::sitkUnknown, itk::simple::sitkInt16, -5 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorInt16 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt16, -17 >::Value:
    {
    int16_t * buff = src.GetBufferAsInt16();
    std::copy(buff,buff + pixcount,ians);
    }
    break;
    case itk::simple::ConditionalValue< itk::simple::sitkUInt32 != itk::simple::sitkUnknown, itk::simple::sitkUInt32, -6 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt32 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt32, -18 >::Value:
    {
    uint32_t * buff = src.GetBufferAsUInt32();
    std::copy(buff,buff + pixcount,ians);
    }
    break;
    case itk::simple::ConditionalValue< itk::simple::sitkInt32 != itk::simple::sitkUnknown, itk::simple::sitkInt32, -7 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorInt32 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt32, -19 >::Value:
    {
    int32_t * buff = src.GetBufferAsInt32();
    std::copy(buff,buff + pixcount,ians);
    }
    break;
    case itk::simple::ConditionalValue< itk::simple::sitkUInt64 != itk::simple::sitkUnknown, itk::simple::sitkUInt64, -8 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorUInt64 != itk::simple::sitkUnknown, itk::simple::sitkVectorUInt64, -20 >::Value:

    {
    uint64_t * buff = src.GetBufferAsUInt64();
    std::copy(buff,buff + pixcount,ians);
    }
    break;
    case itk::simple::ConditionalValue< itk::simple::sitkInt64 != itk::simple::sitkUnknown, itk::simple::sitkInt64, -9 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorInt64 != itk::simple::sitkUnknown, itk::simple::sitkVectorInt64, -21 >::Value:
    {
    int64_t * buff = src.GetBufferAsInt64();
    std::copy(buff,buff + pixcount,ians);
    }
    break;
    case itk::simple::ConditionalValue< itk::simple::sitkFloat32 != itk::simple::sitkUnknown, itk::simple::sitkFloat32, -10 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorFloat32 != itk::simple::sitkUnknown, itk::simple::sitkVectorFloat32, -22 >::Value:
    {
    float * buff = src.GetBufferAsFloat();
    std::copy(buff,buff + pixcount,dans);
    }
    break;
    case itk::simple::ConditionalValue< itk::simple::sitkFloat64 != itk::simple::sitkUnknown, itk::simple::sitkFloat64, -11 >::Value:
    case itk::simple::ConditionalValue< itk::simple::sitkVectorFloat64 != itk::simple::sitkUnknown, itk::simple::sitkVectorFloat64, -23 >::Value:
    {
    double * buff = src.GetBufferAsDouble();
    std::copy(buff,buff + pixcount,dans);
    }
    break;
    default:
      char error_msg[1024];
      snprintf( error_msg, 1024, "Exception thrown ImAsArray : unsupported pixel type: %d", PID );
      Rprintf(error_msg);
    }
  UNPROTECT(1);
  return(res);
}

itk::simple::Image ArrayAsIm(SEXP arr,
                             std::vector<unsigned int> size,
                             std::vector<double> spacing,
                             std::vector<double> origin,
                             unsigned int numberOfComponents)
{
  // can't work out how to get the array size in C
  itk::simple::ImportImageFilter importer;
  importer.SetSpacing( spacing );
  importer.SetOrigin( origin );
  importer.SetSize( size );
  if (Rf_isReal(arr))
    {
    importer.SetBufferAsDouble(NUMERIC_POINTER(arr), numberOfComponents);
    }
  else if (Rf_isInteger(arr) || Rf_isLogical(arr))
    {
    importer.SetBufferAsInt32(INTEGER_POINTER(arr), numberOfComponents);
    }
  else
    {
    char error_msg[1024];
    snprintf( error_msg, 1024, "Exception thrown ArrayAsIm : unsupported array type");
    Rprintf(error_msg);
    }
  itk::simple::Image res = importer.Execute();
  return(res);
}
