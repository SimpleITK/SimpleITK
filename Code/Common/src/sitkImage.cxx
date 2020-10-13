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
#include "sitkImage.h"

#include "itkMetaDataObject.h"
#include "itkDataObject.h"

#include "sitkExceptionObject.h"
#include "sitkPimpleImageBase.h"
#include "sitkPixelIDTypeLists.h"
#include "sitkConditional.h"

#include <utility>


namespace itk
{
  namespace simple
  {

  Image::~Image( )
  {
    delete this->m_PimpleImage;
    this->m_PimpleImage = nullptr;
  }

  Image::Image( )
    : m_PimpleImage( nullptr )
  {
    Allocate ( {0, 0}, sitkUInt8, 1 );
  }

  Image::Image( const Image &img )
  : m_PimpleImage( img.m_PimpleImage->ShallowCopy())
  {
  }

  Image::Image( Image && img ) noexcept
  : m_PimpleImage( img.m_PimpleImage )
  {
    img.m_PimpleImage = nullptr;
  }

  Image& Image::operator=( const Image &img )
  {
    return *this = Image(img);
  }

  Image &Image::operator=(Image && img) noexcept
  {
    using std::swap;
    swap(m_PimpleImage, img.m_PimpleImage);
    return *this;
  }

    Image::Image( unsigned int Width, unsigned int Height, PixelIDValueEnum ValueEnum )
      : m_PimpleImage( nullptr )
    {
      Allocate ( {Width, Height}, ValueEnum, 0 );
    }

    Image::Image( unsigned int Width, unsigned int Height, unsigned int Depth, PixelIDValueEnum ValueEnum )
      : m_PimpleImage( nullptr )
    {
      Allocate ( {Width, Height, Depth}, ValueEnum, 0 );
    }

    Image::Image( const std::vector< unsigned int > &size, PixelIDValueEnum ValueEnum, unsigned int numberOfComponents )
      : m_PimpleImage( nullptr )
    {
      Allocate( size, ValueEnum, numberOfComponents );
    }

    itk::DataObject* Image::GetITKBase( )
    {
      if ( m_PimpleImage )
        {
        this->MakeUnique();
        return m_PimpleImage->GetDataBase();
        }
      else
        {
        return nullptr;
        }
    }

    const itk::DataObject* Image::GetITKBase( ) const
    {
      if ( m_PimpleImage )
        {
        return m_PimpleImage->GetDataBase();
        }
      else
        {
        return nullptr;
        }
    }

    PixelIDValueType Image::GetPixelIDValue( ) const
    {
      return this->GetPixelID();
    }

    PixelIDValueEnum Image::GetPixelID( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelID();
    }

    unsigned int Image::GetDimension( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetDimension();
    }

    unsigned int Image::GetNumberOfComponentsPerPixel( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetNumberOfComponentsPerPixel();
    }

    uint64_t Image::GetNumberOfPixels( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetNumberOfPixels();
    }

  unsigned int Image::GetSizeOfPixelComponent( ) const
    {
    switch( this->GetPixelIDValue() )
      {
      case ConditionalValue< sitkVectorUInt8 != sitkUnknown, sitkVectorUInt8, -14 >::Value:
      case ConditionalValue< sitkUInt8 != sitkUnknown, sitkUInt8, -2 >::Value:
        return sizeof( uint8_t );
        break;
      case ConditionalValue< sitkVectorInt8 != sitkUnknown, sitkVectorInt8, -15 >::Value:
      case ConditionalValue< sitkInt8 != sitkUnknown, sitkInt8, -3 >::Value:
        return sizeof( int8_t );
        break;
      case ConditionalValue< sitkVectorUInt16 != sitkUnknown, sitkVectorUInt16, -16 >::Value:
      case ConditionalValue< sitkUInt16 != sitkUnknown, sitkUInt16, -4 >::Value:
        return sizeof( uint16_t );
        break;
      case ConditionalValue< sitkVectorInt16 != sitkUnknown, sitkVectorInt16, -17 >::Value:
      case ConditionalValue< sitkInt16 != sitkUnknown, sitkInt16, -5 >::Value:
        return sizeof( int16_t );
        break;
      case ConditionalValue< sitkVectorUInt32 != sitkUnknown, sitkVectorUInt32, -18 >::Value:
      case ConditionalValue< sitkUInt32 != sitkUnknown, sitkUInt32, -6 >::Value:
        return sizeof( uint32_t );
        break;
      case ConditionalValue< sitkVectorInt32 != sitkUnknown, sitkVectorInt32, -19 >::Value:
      case ConditionalValue< sitkInt32 != sitkUnknown, sitkInt32, -7 >::Value:
        return sizeof( int32_t );
        break;
      case ConditionalValue< sitkVectorUInt64 != sitkUnknown, sitkVectorUInt64, -20 >::Value:
      case ConditionalValue< sitkUInt64 != sitkUnknown, sitkUInt64, -8 >::Value:
        return sizeof( uint64_t );
        break;
      case ConditionalValue< sitkVectorInt64 != sitkUnknown, sitkVectorInt64, -21 >::Value:
      case ConditionalValue< sitkInt64 != sitkUnknown, sitkInt64, -9 >::Value:
        return sizeof( int64_t );
        break;
      case ConditionalValue< sitkVectorFloat32 != sitkUnknown, sitkVectorFloat32, -22 >::Value:
      case ConditionalValue< sitkFloat32 != sitkUnknown, sitkFloat32, -10 >::Value:
        return sizeof( float );
        break;
      case ConditionalValue< sitkVectorFloat64 != sitkUnknown, sitkVectorFloat64, -23 >::Value:
      case ConditionalValue< sitkFloat64 != sitkUnknown, sitkFloat64, -11 >::Value:
        return sizeof( double );
        break;
      case ConditionalValue< sitkComplexFloat32 != sitkUnknown, sitkComplexFloat32, -12 >::Value:
        return 2*sizeof( float );
        break;
      case ConditionalValue< sitkComplexFloat64 != sitkUnknown, sitkComplexFloat64, -13 >::Value:
        return 2*sizeof( double );
        break;
      case sitkUnknown:
      default:
        return 0;
      }
    }


    std::string Image::GetPixelIDTypeAsString( ) const
    {
      return std::string( GetPixelIDValueAsString( this->GetPixelIDValue() ) );
    }

    std::string Image::ToString( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->ToString();
    }

    std::vector< unsigned int > Image::GetSize( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetSize();
    }

    unsigned int Image::GetWidth( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetWidth();
    }

    unsigned int Image::GetHeight( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetHeight();
    }

    unsigned int Image::GetDepth( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetDepth();
    }

    // Get Origin
    std::vector< double > Image::GetOrigin( ) const
    {
       assert( m_PimpleImage );
      return this->m_PimpleImage->GetOrigin();
    }

    // Set Origin
    void Image::SetOrigin( const std::vector<double> &orgn )
    {
       assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetOrigin(orgn);
    }

    // Get Spacing
    std::vector< double > Image::GetSpacing( ) const
    {
       assert( m_PimpleImage );
      return this->m_PimpleImage->GetSpacing();
    }

    // Set Spacing
    void Image::SetSpacing( const std::vector<double> &spc )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetSpacing(spc);
    }

    // Get Direction
    std::vector< double > Image::GetDirection( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetDirection();
    }

    // Set Direction
    void Image::SetDirection( const std::vector< double > &direction )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetDirection( direction );
    }

    void Image::CopyInformation( const Image & srcImage )
    {
      // check that the dimension match
      if ( this->GetDimension() != srcImage.GetDimension() )
        {
        sitkExceptionMacro( "Source Image for information does not match this image's dimension." );
        }


      // check that the image size's match
      if ( this->GetSize() != srcImage.GetSize() )
        {
        sitkExceptionMacro( "Source image size of " << srcImage.GetSize()
                            << " does not match this image's size of " << this->GetSize() << "!" );
        }

      this->SetOrigin( srcImage.GetOrigin() );
      this->SetSpacing( srcImage.GetSpacing() );
      this->SetDirection( srcImage.GetDirection() );
    }

    std::vector<std::string> Image::GetMetaDataKeys( ) const
    {
      assert( m_PimpleImage );
      const itk::MetaDataDictionary &mdd = this->m_PimpleImage->GetDataBase()->GetMetaDataDictionary();
      return mdd.GetKeys();
    }

    bool Image::HasMetaDataKey( const std::string &key ) const
    {
      assert( m_PimpleImage );
      const itk::MetaDataDictionary &mdd = this->m_PimpleImage->GetDataBase()->GetMetaDataDictionary();
      return mdd.HasKey(key);
    }

    std::string Image::GetMetaData( const std::string &key ) const
    {
      assert( m_PimpleImage );
      const itk::MetaDataDictionary &mdd = this->m_PimpleImage->GetDataBase()->GetMetaDataDictionary();
      std::string value;
      if (ExposeMetaData(mdd, key, value))
        {
        return value;
        }

      std::ostringstream ss;
      mdd.Get(key)->Print(ss);
      return ss.str();
    }

    void Image::SetMetaData( const std::string &key, const std::string &value)
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      itk::MetaDataDictionary &mdd = this->m_PimpleImage->GetDataBase()->GetMetaDataDictionary();
      itk::EncapsulateMetaData<std::string>(mdd, key, value);
    }

    bool Image::EraseMetaData( const std::string &key )
    {
      assert( m_PimpleImage );
      itk::MetaDataDictionary &mdd = this->m_PimpleImage->GetDataBase()->GetMetaDataDictionary();
      this->MakeUnique();
      return mdd.Erase(key);
    }

    // Physical Point to Continuous Index
    std::vector< int64_t > Image::TransformPhysicalPointToIndex( const std::vector< double > &pt ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->TransformPhysicalPointToIndex( pt );
    }

    // Index to Physical Point
    std::vector< double > Image::TransformIndexToPhysicalPoint( const std::vector< int64_t > &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->TransformIndexToPhysicalPoint( idx );
    }

    // Physical Point to Continuous Index
    std::vector< double > Image::TransformPhysicalPointToContinuousIndex( const std::vector< double > &pt ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->TransformPhysicalPointToContinuousIndex( pt );
    }
    // Continuous Index to Physical Point
    std::vector< double > Image::TransformContinuousIndexToPhysicalPoint( const std::vector< double > &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->TransformContinuousIndexToPhysicalPoint( idx );
    }

    int8_t Image::GetPixelAsInt8( const std::vector<uint32_t> &idx) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsInt8( idx );
    }

    uint8_t Image::GetPixelAsUInt8( const std::vector<uint32_t> &idx) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsUInt8( idx );
    }

    int16_t Image::GetPixelAsInt16( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsInt16( idx );
    }

    uint16_t Image::GetPixelAsUInt16( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsUInt16( idx );
    }

    int32_t Image::GetPixelAsInt32( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsInt32( idx );
    }

    uint32_t Image::GetPixelAsUInt32( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsUInt32( idx );
    }

    int64_t Image::GetPixelAsInt64( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsInt64( idx );
    }

    uint64_t Image::GetPixelAsUInt64( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsUInt64( idx );
    }

    float Image::GetPixelAsFloat( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsFloat( idx );
    }

    double Image::GetPixelAsDouble(  const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsDouble( idx );
    }

    std::vector<int8_t>   Image::GetPixelAsVectorInt8( const std::vector<uint32_t> &idx) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsVectorInt8( idx );
    }

    std::vector<uint8_t>  Image::GetPixelAsVectorUInt8( const std::vector<uint32_t> &idx) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsVectorUInt8( idx );
    }

    std::vector<int16_t> Image::GetPixelAsVectorInt16( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsVectorInt16( idx );
    }

    std::vector<uint16_t> Image::GetPixelAsVectorUInt16( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsVectorUInt16( idx );
    }

    std::vector<int32_t>  Image::GetPixelAsVectorInt32( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsVectorInt32( idx );
    }

    std::vector<uint32_t> Image::GetPixelAsVectorUInt32( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsVectorUInt32( idx );
    }

    std::vector<int64_t>  Image::GetPixelAsVectorInt64( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsVectorInt64( idx );
    }

    std::vector<uint64_t> Image::GetPixelAsVectorUInt64( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsVectorUInt64( idx );
    }

    std::vector<float>    Image::GetPixelAsVectorFloat32( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsVectorFloat32( idx );
    }

    std::vector<double>   Image::GetPixelAsVectorFloat64(  const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsVectorFloat64( idx );
    }

  std::complex<float>    Image::GetPixelAsComplexFloat32( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsComplexFloat32( idx );
    }

    std::complex<double>   Image::GetPixelAsComplexFloat64(  const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsComplexFloat64( idx );
    }

    int8_t *Image::GetBufferAsInt8( )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      return this->m_PimpleImage->GetBufferAsInt8( );
    }

    uint8_t *Image::GetBufferAsUInt8( )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      return this->m_PimpleImage->GetBufferAsUInt8( );
    }

    int16_t *Image::GetBufferAsInt16( )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      return this->m_PimpleImage->GetBufferAsInt16( );
    }

    uint16_t *Image::GetBufferAsUInt16( )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      return this->m_PimpleImage->GetBufferAsUInt16( );
    }

    int32_t *Image::GetBufferAsInt32( )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      return this->m_PimpleImage->GetBufferAsInt32( );
    }

    uint32_t *Image::GetBufferAsUInt32( )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      return this->m_PimpleImage->GetBufferAsUInt32( );
    }

    int64_t *Image::GetBufferAsInt64( )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      return this->m_PimpleImage->GetBufferAsInt64( );
    }

    uint64_t *Image::GetBufferAsUInt64( )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      return this->m_PimpleImage->GetBufferAsUInt64( );
    }

    float *Image::GetBufferAsFloat( )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      return this->m_PimpleImage->GetBufferAsFloat( );
    }

    double *Image::GetBufferAsDouble( )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      return this->m_PimpleImage->GetBufferAsDouble( );
    }

    void *Image::GetBufferAsVoid( )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      return this->m_PimpleImage->GetBufferAsVoid( );
    }

    const int8_t *Image::GetBufferAsInt8( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetBufferAsInt8( );
    }

    const uint8_t *Image::GetBufferAsUInt8( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetBufferAsUInt8( );
    }

    const int16_t *Image::GetBufferAsInt16( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetBufferAsInt16( );
    }

    const uint16_t *Image::GetBufferAsUInt16( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetBufferAsUInt16( );
    }

    const int32_t *Image::GetBufferAsInt32( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetBufferAsInt32( );
    }

    const uint32_t *Image::GetBufferAsUInt32( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetBufferAsUInt32( );
    }

    const int64_t *Image::GetBufferAsInt64( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetBufferAsInt64( );
    }

    const uint64_t *Image::GetBufferAsUInt64( )  const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetBufferAsUInt64( );
    }

    const float *Image::GetBufferAsFloat( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetBufferAsFloat( );
    }

    const double *Image::GetBufferAsDouble( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetBufferAsDouble( );
    }

    const void *Image::GetBufferAsVoid ( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetBufferAsVoid( );
    }

    void Image::SetPixelAsInt8( const std::vector<uint32_t> &idx, int8_t v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsInt8( idx, v );
    }

    void Image::SetPixelAsUInt8( const std::vector<uint32_t> &idx, uint8_t v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsUInt8( idx, v );
    }

    void Image::SetPixelAsInt16( const std::vector<uint32_t> &idx, int16_t v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsInt16( idx, v );
    }

    void Image::SetPixelAsUInt16( const std::vector<uint32_t> &idx, uint16_t v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsUInt16( idx, v );
    }

    void Image::SetPixelAsInt32( const std::vector<uint32_t> &idx, int32_t v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsInt32( idx, v );
    }

    void Image::SetPixelAsUInt32( const std::vector<uint32_t> &idx, uint32_t v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsUInt32( idx, v );
    }

    void Image::SetPixelAsInt64( const std::vector<uint32_t> &idx, int64_t v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsInt64( idx, v );
    }

    void Image::SetPixelAsUInt64( const std::vector<uint32_t> &idx, uint64_t v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsUInt64( idx, v );
    }

    void Image::SetPixelAsFloat( const std::vector<uint32_t> &idx, float v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsFloat( idx, v );
    }

    void Image::SetPixelAsDouble( const std::vector<uint32_t> &idx, double v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsDouble( idx, v );
    }

    void Image::SetPixelAsVectorInt8( const std::vector<uint32_t> &idx, const std::vector<int8_t> &v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsVectorInt8( idx, v );
    }

    void Image::SetPixelAsVectorUInt8( const std::vector<uint32_t> &idx, const std::vector<uint8_t> &v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsVectorUInt8( idx, v );
    }

    void Image::SetPixelAsVectorInt16( const std::vector<uint32_t> &idx, const std::vector<int16_t> &v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsVectorInt16( idx, v );
    }

    void Image::SetPixelAsVectorUInt16( const std::vector<uint32_t> &idx, const std::vector<uint16_t> &v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsVectorUInt16( idx, v );
    }

    void Image::SetPixelAsVectorInt32( const std::vector<uint32_t> &idx, const std::vector<int32_t> &v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsVectorInt32( idx, v );
    }

    void Image::SetPixelAsVectorUInt32( const std::vector<uint32_t> &idx, const std::vector<uint32_t> &v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsVectorUInt32( idx, v );
    }

    void Image::SetPixelAsVectorInt64( const std::vector<uint32_t> &idx, const std::vector<int64_t> &v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsVectorInt64( idx, v );
    }

    void Image::SetPixelAsVectorUInt64( const std::vector<uint32_t> &idx, const std::vector<uint64_t> &v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsVectorUInt64( idx, v );
    }

    void Image::SetPixelAsVectorFloat32( const std::vector<uint32_t> &idx, const std::vector<float> &v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsVectorFloat32( idx, v );
    }

    void Image::SetPixelAsVectorFloat64( const std::vector<uint32_t> &idx, const std::vector<double> &v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsVectorFloat64( idx, v );
    }

  void Image::SetPixelAsComplexFloat32( const std::vector<uint32_t> &idx, const std::complex<float> v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsComplexFloat32( idx, v );
    }

    void Image::SetPixelAsComplexFloat64( const std::vector<uint32_t> &idx, const std::complex<double> v )
    {
      assert( m_PimpleImage );
      this->MakeUnique();
      this->m_PimpleImage->SetPixelAsComplexFloat64( idx, v );
    }


    void Image::MakeUnique( )
    {
      assert( m_PimpleImage );
      if ( this->m_PimpleImage->GetReferenceCountOfImage() > 1 )
        {
        // note: care is take here to be exception safe with memory allocation
        std::unique_ptr<PimpleImageBase> temp( this->m_PimpleImage->DeepCopy() );
        delete this->m_PimpleImage;
        this->m_PimpleImage = temp.release();
        }

    }

    bool Image::IsUnique( ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetReferenceCountOfImage() == 1;
    }
  } // end namespace simple
} // end namespace itk
