#ifndef __sitkImportImageFilter_h
#define __sitkImportImageFilter_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkImageReaderBase.h"
#include "sitkMemberFunctionFactory.h"

namespace itk {
  namespace simple {

    /** \class ImportImageFilter
     * \brief Compose a 2D or 3D image and return a smart pointer to a SimpleITK
     * image
     *
     * This filter is intended to interface SimpleITK to other image processing
     * libraries and applications that may have their own representation of an
     * image class.
     */
    class ImportImageFilter
      : public ImageReaderBase {
    public:
      typedef ImportImageFilter Self;

      ImportImageFilter();

      Self& SetSize( const std::vector< unsigned int > &size );
      Self& SetSpacing( const std::vector< double > &spacing );
      Self& SetOrigin( const std::vector< double > &origin );
      Self& SetDirection( const std::vector< double > &direction );

      Self& SetBufferAsInt8( int8_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsUInt8( uint8_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsInt16( int16_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsUInt16( uint16_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsInt32( int32_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsUInt32( uint32_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsFloat( float * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsDouble( double * buffer, unsigned int numberOfComponents = 1 );

      std::string ToString() const;

      Image Execute();

    protected:

      // Internal method called the the template dispatch system
      template <class TImageType> Image ExecuteInternal ( void );

      // If the output image type is a VectorImage then the number of
      // components per pixel needs to be set, otherwise the method
      // does not exist. This is done with the EnableIf Idiom.
      template <class TImageType>
      typename DisableIf<IsVector<TImageType>::Value>::Type
      SetNumberOfComponentsOnImage( TImageType* ) {}
      template <class TImageType>
      typename EnableIf<IsVector<TImageType>::Value>::Type
      SetNumberOfComponentsOnImage( TImageType* );

    private:

      // function pointer type
      typedef Image (Self::*MemberFunctionType)( void );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

      unsigned int     m_NumberOfComponentsPerPixel;
      PixelIDValueType m_PixelIDValue;

      std::vector< double >         m_Origin;
      std::vector< double >         m_Spacing;
      std::vector< unsigned int >   m_Size;
      std::vector< double >         m_Direction;

      void        * m_Buffer;

    };

  Image ImportAsInt8(
    int8_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image ImportAsUInt8(
    uint8_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image ImportAsInt16(
    int16_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image ImportAsUInt16(
    uint16_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image ImportAsInt32(
    int32_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image ImportAsUInt32(
    uint32_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image ImportAsFloat(
    float * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image ImportAsDouble(
    double * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  }
}

#endif
