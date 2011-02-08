#ifndef __sitkPixelContainer_h
#define __sitkPixelContainer_h

#include "sitkPixelIDTypeLists.h"
#include "sitkPixelIDValues.h"
#include "sitkNonCopyable.h"

#include "itkLightObject.h"

#include <memory>

namespace itk
{
  namespace simple
  {

  // forward declaration needed for friendship
  class Image;

  // This is the forward declaration of a class used internally to the
  // PixelContainer class, but the actual interface is never exposed
  // to simple ITK. A pointer to the implmentation is used inside the
  // PixelContainter clss as per the pimple idom.
  class PimplePixelContainerBase;

    /** \class PixelContainer
     * \brief Container used to get the pixel buffer of a SimpleITK image
     */
    class PixelContainer :
      public LightObject,
      protected NonCopyable
    {
    public:
      typedef PixelContainer     Self;
      typedef SmartPointer<Self> Pointer;

      virtual ~PixelContainer( );

      uint64_t GetNumberOfPixels( void ) const;

      PixelIDValueType GetPixelIDValue( void ) const;
      std::string GetPixelIDTypeAsString( void ) const;
      std::string ToString( void );

      template <typename TImageType>
      explicit PixelContainer( TImageType * image )
        { this->InternalInitialization( image ); }

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

    private:

      /** Method called my certain constructors to convert ITK images
       * into simpleITK ones.
       */
      template <typename TImageType>
      void InternalInitialization( TImageType *image );


      friend class Image;

      // utilize std::auto_ptr to perform automatic deletion on deconstruction
      std::auto_ptr< PimplePixelContainerBase > m_Internal;
  };

  }
}


#endif
