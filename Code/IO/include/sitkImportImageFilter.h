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

      void SetSpacing( const std::vector< double > &spacing );
      void SetOrigin( const std::vector< double > &origin );
      void SetSize( const std::vector< unsigned int > &size );

      void SetBufferAsInt8( int8_t * buffer, unsigned int numberOfComponents = 1 );
      void SetBufferAsUInt8( uint8_t *, unsigned int numberOfComponents = 1 );
      void SetBufferAsInt16( int16_t *, unsigned int numberOfComponents = 1 );
      void SetBufferAsUInt16( uint16_t *, unsigned int numberOfComponents = 1 );
      void SetBufferAsInt32( int32_t *, unsigned int numberOfComponents = 1 );
      void SetBufferAsUInt32( uint32_t *, unsigned int numberOfComponents = 1 );

      void SetBufferAsFloat( float *, unsigned int numberOfComponents = 1 );
      void SetBufferAsDouble( double *, unsigned int numberOfComponents = 1 );


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

      void        * m_Buffer;

    };
  }
}

#endif

