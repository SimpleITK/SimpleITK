#include "sitkPixelContainer.h"
#include "sitkPixelContainer.txx"

namespace itk
{
  namespace simple
  {

    PixelIDValueType PixelContainer::GetPixelIDValue( void ) const
    {
      return this->m_Internal->GetPixelIDValue();
    }

    std::string PixelContainer::GetPixelIDTypeAsString( void ) const
    {
      return std::string( GetPixelIDValueAsString( this->GetPixelIDValue() ) );
    }

    std::string PixelContainer::ToString( void )
    {
      return this->m_Internal->ToString();
    }

    uint64_t PixelContainer::GetNumberOfPixels( void ) const
    {
      return this->m_Internal->GetNumberOfPixels();
    }

    int8_t * PixelContainer::GetBufferAsInt8()
    {
      return this->m_Internal->GetBufferAsInt8();
    }

    uint8_t * PixelContainer::GetBufferAsUnsignedInt8()
    {
      return this->m_Internal->GetBufferAsUnsignedInt8();
    }

    int16_t * PixelContainer::GetBufferAsInt16()
    {
      return this->m_Internal->GetBufferAsInt16();
    }

    uint16_t * PixelContainer::GetBufferAsUnsignedInt16()
    {
      return this->m_Internal->GetBufferAsUnsignedInt16();
    }

    int32_t * PixelContainer::GetBufferAsInt32()
    {
      return this->m_Internal->GetBufferAsInt32();
    }

    uint32_t * PixelContainer::GetBufferAsUnsignedInt32()
    {
      return this->m_Internal->GetBufferAsUnsignedInt32();
    }

    float * PixelContainer::GetBufferAsFloat()
    {
      return this->m_Internal->GetBufferAsFloat();
    }

    double * PixelContainer::GetBufferAsDouble()
    {
      return this->m_Internal->GetBufferAsDouble();
    }

  }
}
