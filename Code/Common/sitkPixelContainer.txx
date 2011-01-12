#ifndef __sitkPixelContainer_txx
#define __sitkPixelContainer_txx

#include "sitkPixelContainer.h"

namespace itk
{
  namespace simple
  {

  template <class TImageType>
  class PimplePixelContainer : public PixelContainer::PimplePixelContainerBase
  {
  public:
    typedef typename TImageType::PixelContainer  PixelContainerType;
    typedef typename PixelContainerType::Pointer PixelContainerPointer;

    PimplePixelContainer( TImageType * image )
      {
      this->m_PixelContainer = image->GetPixelContainer();
      }

    PixelContainerType * GetPixelContainer()
      {
      return this->m_PixelContainer.GetPointer();
      }

    PixelIDValueType GetPixelIDValue( void ) const
      {
      return ImageTypeToPixelIDValue< TImageType >::Result;
      }

    std::string ToString( void ) const
      {
      std::ostringstream out;
      this->m_PixelContainer->Print( out );
      return out.str();
      }

    uint64_t GetNumberOfPixels( void ) const
    {
      return static_cast< uint64_t >( this->m_PixelContainer->Size() );
    }

    int8_t * GetBufferAsInt8()
    {
      int8_t * buffer = reinterpret_cast< int8_t * >(
        this->m_PixelContainer->GetImportPointer() );
      return buffer;
    }

    uint8_t * GetBufferAsUnsignedInt8()
    {
      uint8_t * buffer = reinterpret_cast< uint8_t * >(
        this->m_PixelContainer->GetImportPointer() );
      return buffer;
    }

    int16_t * GetBufferAsInt16()
    {
      int16_t * buffer = reinterpret_cast< int16_t * >(
        this->m_PixelContainer->GetImportPointer() );
      return buffer;
    }

    uint16_t * GetBufferAsUnsignedInt16()
    {
      uint16_t * buffer = reinterpret_cast< uint16_t * >(
        this->m_PixelContainer->GetImportPointer() );
      return buffer;
    }

    int32_t * GetBufferAsInt32()
    {
      int32_t * buffer = reinterpret_cast< int32_t * >(
        this->m_PixelContainer->GetImportPointer() );
      return buffer;
    }

    uint32_t * GetBufferAsUnsignedInt32()
    {
      uint32_t * buffer = reinterpret_cast< uint32_t * >(
        this->m_PixelContainer->GetImportPointer() );
      return buffer;
    }

    float * GetBufferAsFloat()
    {
      float * buffer = reinterpret_cast< float * >(
        this->m_PixelContainer->GetImportPointer() );
      return buffer;
    }

    double * GetBufferAsDouble()
    {
      double * buffer = reinterpret_cast< double * >(
        this->m_PixelContainer->GetImportPointer() );
      return buffer;
    }



  private:
    PixelContainerPointer   m_PixelContainer;
  };



  template <typename TImageType>
  PixelContainer::PixelContainer( TImageType * image )
  {
    typedef PimplePixelContainer< TImageType >  PixelContainerType;
    PixelContainerType * container = new PixelContainerType( image );
    this->m_Internal.reset( container );
  }


  }
}


#endif
