#ifndef __sitkPimpleImageBase_h
#define __sitkPimpleImageBase_h

#include <vector>
#include "sitkPixelIDTokens.h"

namespace itk
{
  namespace simple
  {

  /** \class PimpleImageBase
   * \brief Private implementation idiom image base class
   *
   * We utilize the private implementation ( or PImple)
   * programming idiom to modify the behavior of the simple image
   * class based on the different image types.
   *
   * This class is desinged to utilize the trivial copy,
   * and assgnement operators
   */
  class PimpleImageBase
  {
  public:
    virtual ~PimpleImageBase( void ) { };

    virtual PixelIDValueType GetPixelIDValue(void) const = 0;
    virtual unsigned int GetDimension( void ) const  = 0;
    virtual unsigned int GetNumberOfComponentsPerPixel( void ) const = 0;

    virtual PimpleImageBase *ShallowCopy(void) const = 0;
    virtual PimpleImageBase *DeepCopy(void) const = 0;
    virtual itk::DataObject* GetDataBase( void ) = 0;
    virtual const itk::DataObject* GetDataBase( void ) const = 0;

    virtual unsigned int GetWidth( void ) const { return this->GetSize( 0 ); }
    virtual unsigned int GetHeight( void ) const { return this->GetSize( 1 ); }
    virtual unsigned int GetDepth( void ) const { return this->GetSize( 2 ); }

    virtual std::vector< unsigned int > GetSize( void ) const = 0;
    virtual unsigned int GetSize( unsigned int dimension ) const = 0;

    virtual std::vector<double> GetOrigin( void ) const = 0;
    virtual void SetOrigin( const std::vector<double> &orgn ) = 0;
    virtual std::vector<double> GetSpacing( void ) const = 0;
    virtual void SetSpacing( const std::vector<double> &spc ) = 0;

    virtual std::vector<int64_t> TransformPhysicalPointToIndex( const std::vector<double> &pt) const = 0;
    virtual std::vector<double> TransformIndexToPhysicalPoint( const std::vector<int64_t> &idx) const = 0;

    virtual std::string ToString() const = 0;


    virtual int GetReferenceCountOfImage() const = 0;

    virtual uint8_t  GetPixelAsUInt8( const std::vector<uint32_t> &idx) const = 0;
    virtual int16_t  GetPixelAsInt16( const std::vector<uint32_t> &idx ) const = 0;
    virtual uint16_t GetPixelAsUInt16( const std::vector<uint32_t> &idx ) const = 0;
    virtual int32_t  GetPixelAsInt32( const std::vector<uint32_t> &idx ) const = 0;
    virtual uint32_t GetPixelAsUInt32( const std::vector<uint32_t> &idx ) const = 0;
    virtual float    GetPixelAsFloat( const std::vector<uint32_t> &idx ) const = 0;
    virtual double   GetPixelAsDouble(  const std::vector<uint32_t> &idx ) const = 0;

    virtual void SetPixelAsUInt8( const std::vector<uint32_t> &idx, uint8_t v ) = 0;
    virtual void SetPixelAsInt16( const std::vector<uint32_t> &idx, int16_t v ) = 0;
    virtual void SetPixelAsUInt16( const std::vector<uint32_t> &idx, uint16_t v ) = 0;
    virtual void SetPixelAsInt32( const std::vector<uint32_t> &idx, int32_t v ) = 0;
    virtual void SetPixelAsUInt32( const std::vector<uint32_t> &idx, uint32_t v ) = 0;
    virtual void SetPixelAsFloat( const std::vector<uint32_t> &idx, float v ) = 0;
    virtual void SetPixelAsDouble( const std::vector<uint32_t> &idx, double v ) = 0;

    virtual uint8_t  *GetBufferAsUInt8() = 0;
    virtual int16_t  *GetBufferAsInt16( )= 0;
    virtual uint16_t *GetBufferAsUInt16( ) = 0;
    virtual int32_t  *GetBufferAsInt32( ) = 0;
    virtual uint32_t *GetBufferAsUInt32( ) = 0;
    virtual float    *GetBufferAsFloat( ) = 0;
    virtual double   *GetBufferAsDouble( ) = 0;
  };

  } // end namespace simple
} // end namespace itk


#endif // __sitkPimpleImageBase_h
