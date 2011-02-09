#include "sitkPixelContainer.h"
#include "sitkPixelContainer.txx"

namespace itk
{
  namespace simple
  {

    PixelContainer::PixelContainer()
    {
      this->m_Internal = NULL;
    }

    PixelContainer::~PixelContainer()
    {
      // no need to check if null
      delete this->m_Internal;
      this->m_Internal = NULL;
    }

    PixelIDValueType PixelContainer::GetPixelIDValue( void ) const
    {
      assert( m_Internal );
      return this->m_Internal->GetPixelIDValue();
    }

    std::string PixelContainer::GetPixelIDTypeAsString( void ) const
    {
      return std::string( GetPixelIDValueAsString( this->GetPixelIDValue() ) );
    }

    std::string PixelContainer::ToString( void )
    {
      assert( m_Internal );
      return this->m_Internal->ToString();
    }

    uint64_t PixelContainer::GetNumberOfPixels( void ) const
    {
      assert( m_Internal );
      return this->m_Internal->GetNumberOfPixels();
    }

    int8_t * PixelContainer::GetBufferAsInt8()
    {
      assert( m_Internal );
      return this->m_Internal->GetBufferAsInt8();
    }

    uint8_t * PixelContainer::GetBufferAsUnsignedInt8()
    {
      assert( m_Internal );
      return this->m_Internal->GetBufferAsUnsignedInt8();
    }

    int16_t * PixelContainer::GetBufferAsInt16()
    {
      assert( m_Internal );
      return this->m_Internal->GetBufferAsInt16();
    }

    uint16_t * PixelContainer::GetBufferAsUnsignedInt16()
    {
      assert( m_Internal );
      return this->m_Internal->GetBufferAsUnsignedInt16();
    }

    int32_t * PixelContainer::GetBufferAsInt32()
    {
      assert( m_Internal );
      return this->m_Internal->GetBufferAsInt32();
    }

    uint32_t * PixelContainer::GetBufferAsUnsignedInt32()
    {
      assert( m_Internal );
      return this->m_Internal->GetBufferAsUnsignedInt32();
    }

    float * PixelContainer::GetBufferAsFloat()
    {
      assert( m_Internal );
      return this->m_Internal->GetBufferAsFloat();
    }

    double * PixelContainer::GetBufferAsDouble()
    {
      assert( m_Internal );
      return this->m_Internal->GetBufferAsDouble();
    }

  }
}
