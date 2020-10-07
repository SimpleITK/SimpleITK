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
#ifndef sitkPimpleImageBase_h
#define sitkPimpleImageBase_h

#include <vector>
#include "sitkPixelIDTokens.h"
#include "sitkTemplateFunctions.h"

namespace itk
{
  namespace simple
  {

  /** \class PimpleImageBase
   * \brief Private implementation idiom image base class
   *
   * We utilize the private implementation ( or PImpl)
   * programming idiom to modify the behavior of the simple image
   * class based on the different image types.
   *
   * This class is designed to utilize the trivial copy,
   * and assignment operators
   */
  class SITKCommon_HIDDEN PimpleImageBase
  {
  public:

    virtual ~PimpleImageBase( ) = default;

    virtual PixelIDValueEnum GetPixelID() const = 0;
    virtual unsigned int GetDimension( ) const  = 0;
    virtual uint64_t GetNumberOfPixels( ) const = 0;
    virtual unsigned int GetNumberOfComponentsPerPixel( ) const = 0;

    virtual PimpleImageBase *ShallowCopy() const = 0;
    virtual PimpleImageBase *DeepCopy() const = 0;
    virtual itk::DataObject* GetDataBase( ) = 0;
    virtual const itk::DataObject* GetDataBase( ) const = 0;

    virtual unsigned int GetWidth( ) const { return this->GetSize( 0 ); }
    virtual unsigned int GetHeight( ) const { return this->GetSize( 1 ); }
    virtual unsigned int GetDepth( ) const { return this->GetSize( 2 ); }

    virtual std::vector< unsigned int > GetSize( ) const = 0;
    virtual unsigned int GetSize( unsigned int dimension ) const = 0;


    virtual std::vector<double> GetOrigin( ) const = 0;
    virtual void SetOrigin( const std::vector<double> &orgn ) = 0;
    virtual std::vector<double> GetSpacing( ) const = 0;
    virtual void SetSpacing( const std::vector<double> &spc ) = 0;

    virtual std::vector< double > GetDirection( ) const = 0;
    virtual void SetDirection( const std::vector< double > &direction ) = 0;

    virtual std::vector<int64_t> TransformPhysicalPointToIndex( const std::vector<double> &pt) const = 0;
    virtual std::vector<double> TransformIndexToPhysicalPoint( const std::vector<int64_t> &idx) const = 0;
    virtual std::vector<double> TransformPhysicalPointToContinuousIndex( const std::vector<double> &pt) const = 0;
    virtual std::vector<double> TransformContinuousIndexToPhysicalPoint( const std::vector<double> &idx) const = 0;

    virtual std::string ToString() const = 0;


    virtual int GetReferenceCountOfImage() const = 0;

    virtual int8_t   GetPixelAsInt8( const std::vector<uint32_t> &idx) const = 0;
    virtual uint8_t  GetPixelAsUInt8( const std::vector<uint32_t> &idx) const = 0;
    virtual int16_t  GetPixelAsInt16( const std::vector<uint32_t> &idx ) const = 0;
    virtual uint16_t GetPixelAsUInt16( const std::vector<uint32_t> &idx ) const = 0;
    virtual int32_t  GetPixelAsInt32( const std::vector<uint32_t> &idx ) const = 0;
    virtual uint32_t GetPixelAsUInt32( const std::vector<uint32_t> &idx ) const = 0;
    virtual int64_t  GetPixelAsInt64( const std::vector<uint32_t> &idx ) const = 0;
    virtual uint64_t GetPixelAsUInt64( const std::vector<uint32_t> &idx ) const = 0;
    virtual float    GetPixelAsFloat( const std::vector<uint32_t> &idx ) const = 0;
    virtual double   GetPixelAsDouble(  const std::vector<uint32_t> &idx ) const = 0;

    virtual std::vector<int8_t>   GetPixelAsVectorInt8( const std::vector<uint32_t> &idx) const = 0;
    virtual std::vector<uint8_t>  GetPixelAsVectorUInt8( const std::vector<uint32_t> &idx) const = 0;
    virtual std::vector<int16_t>  GetPixelAsVectorInt16( const std::vector<uint32_t> &idx ) const = 0;
    virtual std::vector<uint16_t> GetPixelAsVectorUInt16( const std::vector<uint32_t> &idx ) const = 0;
    virtual std::vector<int32_t>  GetPixelAsVectorInt32( const std::vector<uint32_t> &idx ) const = 0;
    virtual std::vector<uint32_t> GetPixelAsVectorUInt32( const std::vector<uint32_t> &idx ) const = 0;
    virtual std::vector<int64_t>  GetPixelAsVectorInt64( const std::vector<uint32_t> &idx ) const = 0;
    virtual std::vector<uint64_t> GetPixelAsVectorUInt64( const std::vector<uint32_t> &idx ) const = 0;
    virtual std::vector<float>    GetPixelAsVectorFloat32( const std::vector<uint32_t> &idx ) const = 0;
    virtual std::vector<double>   GetPixelAsVectorFloat64(  const std::vector<uint32_t> &idx ) const = 0;

    virtual std::complex<float>  GetPixelAsComplexFloat32( const std::vector<uint32_t> &idx ) const = 0;
    virtual std::complex<double> GetPixelAsComplexFloat64( const std::vector<uint32_t> &idx ) const = 0;

    virtual void SetPixelAsInt8( const std::vector<uint32_t> &idx, int8_t v ) = 0;
    virtual void SetPixelAsUInt8( const std::vector<uint32_t> &idx, uint8_t v ) = 0;
    virtual void SetPixelAsInt16( const std::vector<uint32_t> &idx, int16_t v ) = 0;
    virtual void SetPixelAsUInt16( const std::vector<uint32_t> &idx, uint16_t v ) = 0;
    virtual void SetPixelAsInt32( const std::vector<uint32_t> &idx, int32_t v ) = 0;
    virtual void SetPixelAsUInt32( const std::vector<uint32_t> &idx, uint32_t v ) = 0;
    virtual void SetPixelAsInt64( const std::vector<uint32_t> &idx, int64_t v ) = 0;
    virtual void SetPixelAsUInt64( const std::vector<uint32_t> &idx, uint64_t v ) = 0;
    virtual void SetPixelAsFloat( const std::vector<uint32_t> &idx, float v ) = 0;
    virtual void SetPixelAsDouble( const std::vector<uint32_t> &idx, double v ) = 0;

    virtual void SetPixelAsVectorInt8( const std::vector<uint32_t> &idx, const std::vector<int8_t> &v ) = 0;
    virtual void SetPixelAsVectorUInt8( const std::vector<uint32_t> &idx, const std::vector<uint8_t> &v ) = 0;
    virtual void SetPixelAsVectorInt16( const std::vector<uint32_t> &idx, const std::vector<int16_t> &v ) = 0;
    virtual void SetPixelAsVectorUInt16( const std::vector<uint32_t> &idx, const std::vector<uint16_t> &v ) = 0;
    virtual void SetPixelAsVectorInt32( const std::vector<uint32_t> &idx, const std::vector<int32_t> &v ) = 0;
    virtual void SetPixelAsVectorUInt32( const std::vector<uint32_t> &idx, const std::vector<uint32_t> &v ) = 0;
    virtual void SetPixelAsVectorInt64( const std::vector<uint32_t> &idx, const std::vector<int64_t> &v ) = 0;
    virtual void SetPixelAsVectorUInt64( const std::vector<uint32_t> &idx, const std::vector<uint64_t> &v ) = 0;
    virtual void SetPixelAsVectorFloat32( const std::vector<uint32_t> &idx, const std::vector<float> &v ) = 0;
    virtual void SetPixelAsVectorFloat64( const std::vector<uint32_t> &idx, const std::vector<double> &v ) = 0;

    virtual void SetPixelAsComplexFloat32( const std::vector<uint32_t> &idx, const std::complex<float> v ) = 0;
    virtual void SetPixelAsComplexFloat64( const std::vector<uint32_t> &idx, const std::complex<double> v ) = 0;


    virtual int8_t   *GetBufferAsInt8( ) = 0;
    virtual uint8_t  *GetBufferAsUInt8( ) = 0;
    virtual int16_t  *GetBufferAsInt16( ) = 0;
    virtual uint16_t *GetBufferAsUInt16( ) = 0;
    virtual int32_t  *GetBufferAsInt32( ) = 0;
    virtual uint32_t *GetBufferAsUInt32( ) = 0;
    virtual int64_t  *GetBufferAsInt64( ) = 0;
    virtual uint64_t *GetBufferAsUInt64( ) = 0;
    virtual float    *GetBufferAsFloat( ) = 0;
    virtual double   *GetBufferAsDouble( ) = 0;
    virtual void     *GetBufferAsVoid( ) = 0;

    virtual const int8_t   *GetBufferAsInt8( ) const = 0;
    virtual const uint8_t  *GetBufferAsUInt8( ) const = 0;
    virtual const int16_t  *GetBufferAsInt16( ) const = 0;
    virtual const uint16_t *GetBufferAsUInt16( ) const = 0;
    virtual const int32_t  *GetBufferAsInt32( ) const = 0;
    virtual const uint32_t *GetBufferAsUInt32( ) const = 0;
    virtual const int64_t  *GetBufferAsInt64( ) const = 0;
    virtual const uint64_t *GetBufferAsUInt64( ) const = 0;
    virtual const float    *GetBufferAsFloat( ) const = 0;
    virtual const double   *GetBufferAsDouble( ) const = 0;
    virtual const void     *GetBufferAsVoid( ) const = 0;
  };

  } // end namespace simple
} // end namespace itk


#endif // sitkPimpleImageBase_h
