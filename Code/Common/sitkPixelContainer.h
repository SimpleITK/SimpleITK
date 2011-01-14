#ifndef __sitkPixelContainer_h
#define __sitkPixelContainer_h

#include "sitkPixelIDTypeLists.h"
#include "sitkPixelIDValues.h"
#include "sitkNonCopyable.h"

namespace itk
{
  namespace simple
  {

  // forward declaration needed for friendship
  class Image;

    class PixelContainer :
      public LightObject,
      protected NonCopyable
    {
    public:
      typedef PixelContainer     Self;
      typedef SmartPointer<Self> Pointer;

      uint64_t GetNumberOfPixels( void ) const;

      PixelIDValueType GetPixelIDValue( void ) const;
      std::string GetPixelIDTypeAsString( void ) const;
      std::string ToString( void );

      template <typename TImageType>
      PixelContainer( TImageType * image );

      /** Variety of methods for getting the buffer as a specific type. These
       * methods DO NOT perform error checking, they simply cast the basic pointer
       * to what you are requesting.  These methods should ONLY be called after
       * verifying with GetPixelIDValue() the actual type of the underlying buffer.
       */
      int8_t    * GetBufferAsInt8();
      uint8_t   * GetBufferAsUnsignedInt8();
      int16_t   * GetBufferAsInt16();
      uint16_t  * GetBufferAsUnsignedInt16();
      int32_t   * GetBufferAsInt32();
      uint32_t  * GetBufferAsUnsignedInt32();
      float     * GetBufferAsFloat();
      double    * GetBufferAsDouble();

    protected:

      // Copying is not supported
      PixelContainer &operator=( const PixelContainer & ); // Not implemented

    private:

      class PimplePixelContainerBase
      {
      public:

        PimplePixelContainerBase() {}
        virtual ~PimplePixelContainerBase() {}

        virtual uint64_t GetNumberOfPixels( void ) const = 0;

        virtual PixelIDValueType GetPixelIDValue( void ) const = 0;
        virtual std::string ToString( void ) const = 0;

        virtual int8_t    * GetBufferAsInt8() = 0;
        virtual uint8_t   * GetBufferAsUnsignedInt8() = 0;
        virtual int16_t   * GetBufferAsInt16() = 0;
        virtual uint16_t  * GetBufferAsUnsignedInt16() = 0;
        virtual int32_t   * GetBufferAsInt32() = 0;
        virtual uint32_t  * GetBufferAsUnsignedInt32() = 0;
        virtual float     * GetBufferAsFloat() = 0;
        virtual double    * GetBufferAsDouble() = 0;

      };

      friend class Image;

      void SetInternal( PimplePixelContainerBase * internal );

      // utilize std::auto_ptr to perform automatic deletion on deconstruction
      std::auto_ptr< PimplePixelContainerBase > m_Internal;
  };

  }
}


#endif
