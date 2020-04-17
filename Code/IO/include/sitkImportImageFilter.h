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
#ifndef sitkImportImageFilter_h
#define sitkImportImageFilter_h

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
     * image class. It creates a SimpleITK image which shares the bulk
     * data buffer as what is set. SimpleITK will not responsible to
     * delete the buffer afterwards, and it buffer must remain valid
     * while in use.
     *
     * \sa itk::simple::ImportAsInt8, itk::simple::ImportAsUInt8,
     * itk::simple::ImportAsInt16, itk::simple::ImportAsUInt16,
     * itk::simple::ImportAsInt32, itk::simple::ImportAsUInt32,
     * itk::simple::ImportAsInt64, itk::simple::ImportAsUInt64,
     * itk::simple::ImportAsFloat,itk::simple::ImportAsDouble for the
     * procedural interfaces.
     */
    class SITKIO_EXPORT ImportImageFilter
      : public ImageReaderBase {
    public:
      using Self = ImportImageFilter;

      ~ImportImageFilter() override;

      ImportImageFilter();

      /** Print ourselves to string */
      std::string ToString() const override;

      /** return user readable name of the filter */
      std::string GetName() const override { return std::string("ImportImageFilter"); }

      SITK_RETURN_SELF_TYPE_HEADER SetSize( const std::vector< unsigned int > &size );
      const std::vector< unsigned int > &GetSize( ) const;

      SITK_RETURN_SELF_TYPE_HEADER SetSpacing( const std::vector< double > &spacing );
      const std::vector< double > &GetSpacing( ) const;

      SITK_RETURN_SELF_TYPE_HEADER SetOrigin( const std::vector< double > &origin );
      const std::vector< double > &GetOrigin( ) const;

      SITK_RETURN_SELF_TYPE_HEADER SetDirection( const std::vector< double > &direction );
      const std::vector< double > &GetDirection( ) const;

      SITK_RETURN_SELF_TYPE_HEADER SetBufferAsInt8( int8_t * buffer, unsigned int numberOfComponents = 1 );
      SITK_RETURN_SELF_TYPE_HEADER SetBufferAsUInt8( uint8_t * buffer, unsigned int numberOfComponents = 1 );
      SITK_RETURN_SELF_TYPE_HEADER SetBufferAsInt16( int16_t * buffer, unsigned int numberOfComponents = 1 );
      SITK_RETURN_SELF_TYPE_HEADER SetBufferAsUInt16( uint16_t * buffer, unsigned int numberOfComponents = 1 );
      SITK_RETURN_SELF_TYPE_HEADER SetBufferAsInt32( int32_t * buffer, unsigned int numberOfComponents = 1 );
      SITK_RETURN_SELF_TYPE_HEADER SetBufferAsUInt32( uint32_t * buffer, unsigned int numberOfComponents = 1 );
      SITK_RETURN_SELF_TYPE_HEADER SetBufferAsInt64( int64_t * buffer, unsigned int numberOfComponents = 1 );
      SITK_RETURN_SELF_TYPE_HEADER SetBufferAsUInt64( uint64_t * buffer, unsigned int numberOfComponents = 1 );
      SITK_RETURN_SELF_TYPE_HEADER SetBufferAsFloat( float * buffer, unsigned int numberOfComponents = 1 );
      SITK_RETURN_SELF_TYPE_HEADER SetBufferAsDouble( double * buffer, unsigned int numberOfComponents = 1 );

      Image Execute() override;

    protected:

      // Internal method called by the template dispatch system
      template <class TImageType> Image ExecuteInternal ( );

      // If the output image type is a VectorImage then the number of
      // components per pixel needs to be set, otherwise the method
      // does not exist. This is done with the enable if idiom.
      template <class TImageType>
        typename std::enable_if<!IsVector<TImageType>::Value>::type
      SetNumberOfComponentsOnImage( TImageType* ) {}
      template <class TImageType>
        typename std::enable_if<IsVector<TImageType>::Value>::type
      SetNumberOfComponentsOnImage( TImageType* );

    private:

      // function pointer type
      typedef Image (Self::*MemberFunctionType)( );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::unique_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

      unsigned int     m_NumberOfComponentsPerPixel;
      PixelIDValueType m_PixelIDValue;

      std::vector< double >         m_Origin;
      std::vector< double >         m_Spacing;
      std::vector< unsigned int >   m_Size;
      std::vector< double >         m_Direction;

      void        * m_Buffer;

    };

  Image SITKIO_EXPORT ImportAsInt8(
    int8_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsUInt8(
    uint8_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsInt16(
    int16_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsUInt16(
    uint16_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsInt32(
    int32_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsUInt32(
    uint32_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsInt64(
    int64_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsUInt64(
    uint64_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsFloat(
    float * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsDouble(
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
