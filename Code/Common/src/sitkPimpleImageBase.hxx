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
#ifndef sitkPimpleImageBase_hxx
#define sitkPimpleImageBase_hxx

#include "sitkPimpleImageBase.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkConditional.h"

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"
#include "itkImageDuplicator.h"
#include "itkConvertLabelMapFilter.h"


#include <type_traits>

namespace itk
{
  namespace simple
  {

///
/// Private name space for a concrete implementation of pimple image
/// for a specific image types with dimensions and pixel types
///
  namespace
  {

  template <typename T, typename U>
  struct MakeDependentOn
    : public U {};

  template <class TImageType>
  class PimpleImage
    : public PimpleImageBase
  {
  public:
    using Self = PimpleImage;
    using ImageType = TImageType;
    using ImagePointer = typename ImageType::Pointer;
    using IndexType = typename ImageType::IndexType;
    using PixelType = typename ImageType::PixelType;

    PimpleImage ( ImageType* image )
      : m_Image( image )
      {
        static_assert( ImageType::ImageDimension <= SITK_MAX_DIMENSION && ImageType::ImageDimension >= 2,
                       "Image Dimension out of range" );
        static_assert( ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown,
                       "invalid pixel type" );

        if ( image == nullptr )
          {
          sitkExceptionMacro( << "Unable to initialize an image with nullptr" );
          }

        if ( image->GetLargestPossibleRegion() != image->GetBufferedRegion() )
          {
          sitkExceptionMacro( << "The image has a LargestPossibleRegion of " << image->GetLargestPossibleRegion()
                              << " while the buffered region is " << image->GetBufferedRegion() << std::endl
                              << "SimpleITK does not support streaming or unbuffered regions!" );
          }

        InternalCheckBuffer(image);

        const IndexType & idx = image->GetBufferedRegion().GetIndex();
        for ( unsigned int i = 0; i < ImageType::ImageDimension; ++i )
          {
          if ( idx[i] != 0 )
            {
            sitkExceptionMacro( << "The image has a staring index of " << idx
                                << "SimpleITK only supports images with a zero starting index!" );
            }
          }
      }

    PimpleImageBase *ShallowCopy( ) const override { return new Self(this->m_Image.GetPointer()); }
    PimpleImageBase *DeepCopy( ) const override { return this->DeepCopy<TImageType>(); }

    template <typename UImageType>
    typename std::enable_if<!IsLabel<UImageType>::Value, PimpleImageBase*>::type
    DeepCopy( void ) const
      {
        using ImageDuplicatorType = itk::ImageDuplicator< ImageType >;
        typename ImageDuplicatorType::Pointer dup = ImageDuplicatorType::New();

        dup->SetInputImage( this->m_Image );
        dup->Update();
        ImagePointer output = dup->GetOutput();

        return new Self( output.GetPointer() );
      }
    template <typename UImageType>
    typename std::enable_if<IsLabel<UImageType>::Value, PimpleImageBase*>::type
    DeepCopy( void ) const
      {
        using FilterType = itk::ConvertLabelMapFilter<UImageType, UImageType>;
        typename FilterType::Pointer filter = FilterType::New();
        filter->SetInput ( this->m_Image );
        filter->UpdateLargestPossibleRegion();
        ImagePointer output = filter->GetOutput();

        return new Self( output.GetPointer() );
      }

    itk::DataObject* GetDataBase( ) override { return this->m_Image.GetPointer(); }
    const itk::DataObject* GetDataBase( ) const override { return this->m_Image.GetPointer(); }


    PixelIDValueEnum GetPixelID() const noexcept override
      {
        // The constructor ensures that we have a valid image
        // this maps the Image's pixel type to the array index
        return static_cast<PixelIDValueEnum>(ImageTypeToPixelIDValue<ImageType>::Result);
      }

    unsigned int GetDimension( ) const override
      {
        return ImageType::ImageDimension;
      }


    unsigned int GetNumberOfComponentsPerPixel( ) const override { return this->GetNumberOfComponentsPerPixel<TImageType>(); }

    template <typename UImageType>
    typename std::enable_if<!IsVector<UImageType>::Value, unsigned int>::type
    GetNumberOfComponentsPerPixel( void ) const
      {
        return 1;
      }
    template <typename UImageType>
    typename std::enable_if<IsVector<UImageType>::Value, unsigned int>::type
    GetNumberOfComponentsPerPixel( void ) const
    {
        // This returns 1 for itk::Image, and the number of elements
        // is the vectors of a VectorImage
        return this->m_Image->GetNumberOfComponentsPerPixel();
      }


    // Get Origin
    std::vector<double> GetOrigin( ) const override
      {
        return sitkITKVectorToSTL<double>( this->m_Image->GetOrigin() );
      }

    // Set Origin
    void SetOrigin( const std::vector<double> & orgn ) override
      {
        this->m_Image->SetOrigin( sitkSTLVectorToITK< typename ImageType::PointType> ( orgn ) );
      }

    // Get Spacing
    std::vector<double> GetSpacing( ) const override
      {
        return sitkITKVectorToSTL<double>( this->m_Image->GetSpacing() );
      }

    // Set Spacing
    void SetSpacing( const std::vector<double> &spc ) override
      {
        this->m_Image->SetSpacing( sitkSTLVectorToITK< typename ImageType::SpacingType> ( spc ) );
      }


    // Get Direction
    std::vector< double > GetDirection( ) const override
      {
      return sitkITKDirectionToSTL( this->m_Image->GetDirection() );
      }

    // Set Direction
    void SetDirection( const std::vector< double > & in ) override
      {
      this->m_Image->SetDirection( sitkSTLToITKDirection<typename ImageType::DirectionType>( in ) );
      }


    // Physical Point to Index
    std::vector<int64_t> TransformPhysicalPointToIndex( const std::vector<double> &pt ) const override
      {
        if (pt.size() != ImageType::ImageDimension)
        {
        sitkExceptionMacro("vector dimension mismatch");
        }


        typename ImageType::IndexType index;
        this->m_Image->TransformPhysicalPointToIndex( sitkSTLVectorToITK< typename ImageType::PointType> ( pt ), index);

        return sitkITKVectorToSTL<int64_t>( index );
      }

    // Index to Physical Point
    std::vector<double> TransformIndexToPhysicalPoint( const std::vector<int64_t> &idx ) const override
      {

        if (idx.size() != ImageType::ImageDimension)
          {
          sitkExceptionMacro("vector dimension mismatch");
          }

        typename ImageType::IndexType index;
        for ( unsigned int i = 0; i < ImageType::ImageDimension; ++i )
          {
          index[i] = idx[i];
          }


        typename ImageType::PointType point;
        this->m_Image->TransformIndexToPhysicalPoint( index, point );
        return sitkITKVectorToSTL<double>( point );
      }

    //  Physical Point To Continuous Index
    std::vector<double> TransformPhysicalPointToContinuousIndex( const std::vector<double> &pt ) const override
      {
        if (pt.size() != ImageType::ImageDimension)
        {
        sitkExceptionMacro("vector dimension mismatch");
        }

        typename itk::ContinuousIndex<double, ImageType::ImageDimension> index;
        this->m_Image->TransformPhysicalPointToContinuousIndex(sitkSTLVectorToITK< typename ImageType::PointType> ( pt ), index);

        return sitkITKVectorToSTL<double>( index );
      }

    // Continuous Index to Physical Point
    std::vector<double> TransformContinuousIndexToPhysicalPoint( const std::vector<double> &idx ) const override
      {
        if (idx.size() != ImageType::ImageDimension)
        {
        sitkExceptionMacro("vector dimension mismatch");
        }


        typename itk::ContinuousIndex<double, ImageType::ImageDimension> index;
        for ( unsigned int i = 0; i < ImageType::ImageDimension; ++i )
          {
          index[i] = idx[i];
          }

      typename ImageType::PointType point;
      this->m_Image->TransformContinuousIndexToPhysicalPoint(index, point);

      return sitkITKVectorToSTL<double>( point );
      }

    unsigned int GetSize( unsigned int dimension ) const override
      {
        if ( dimension > ImageType::ImageDimension - 1 )
          {
          return 0;
          }

        typename ImageType::RegionType largestRegion = this->m_Image->GetLargestPossibleRegion();
        return largestRegion.GetSize(dimension);
      }

    std::vector<unsigned int> GetSize( ) const override
      {
        typename ImageType::RegionType largestRegion = this->m_Image->GetLargestPossibleRegion();
        std::vector<unsigned int> size( ImageType::ImageDimension );

        return sitkITKVectorToSTL<unsigned int>( largestRegion.GetSize() );
      }

    uint64_t GetNumberOfPixels( ) const override
      {
        return this->m_Image->GetLargestPossibleRegion().GetNumberOfPixels();
      }

    std::string ToString( ) const override
      {
        std::ostringstream out;
        this->m_Image->Print ( out );
        return out.str();
      }

    int GetReferenceCountOfImage() const override
      {
        return this->m_Image->GetReferenceCount();
      }

    int8_t  GetPixelAsInt8( const std::vector<uint32_t> &idx) const override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalGetPixel< LabelPixelID<int8_t> >( idx );
        return this->InternalGetPixel< BasicPixelID<int8_t> >( idx );
      }
    uint8_t  GetPixelAsUInt8( const std::vector<uint32_t> &idx) const override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalGetPixel< LabelPixelID<uint8_t> >( idx );
        return this->InternalGetPixel< BasicPixelID<uint8_t> >( idx );
      }
    int16_t  GetPixelAsInt16( const std::vector<uint32_t> &idx ) const override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalGetPixel< LabelPixelID<int16_t> >( idx );
        return this->InternalGetPixel< BasicPixelID<int16_t> >( idx );
      }
    uint16_t GetPixelAsUInt16( const std::vector<uint32_t> &idx ) const override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalGetPixel< LabelPixelID<uint16_t> >( idx );
        return this->InternalGetPixel< BasicPixelID<uint16_t> >( idx );
      }
    int32_t  GetPixelAsInt32( const std::vector<uint32_t> &idx ) const override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalGetPixel< LabelPixelID<int32_t> >( idx );
        return this->InternalGetPixel< BasicPixelID<int32_t> >( idx );
      }
    uint32_t GetPixelAsUInt32( const std::vector<uint32_t> &idx ) const override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalGetPixel< LabelPixelID<uint32_t> >( idx );
        return this->InternalGetPixel< BasicPixelID<uint32_t> >( idx );
      }
    int64_t  GetPixelAsInt64( const std::vector<uint32_t> &idx ) const override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalGetPixel< LabelPixelID<int64_t> >( idx );
        return this->InternalGetPixel< BasicPixelID<int64_t> >( idx );
      }
    uint64_t GetPixelAsUInt64( const std::vector<uint32_t> &idx ) const override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalGetPixel< LabelPixelID<uint64_t> >( idx );
        return this->InternalGetPixel< BasicPixelID<uint64_t> >( idx );
      }
    float    GetPixelAsFloat( const std::vector<uint32_t> &idx ) const override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalGetPixel< LabelPixelID<float> >( idx );
        return this->InternalGetPixel< BasicPixelID<float> >( idx );
      }
    double   GetPixelAsDouble(  const std::vector<uint32_t> &idx ) const override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalGetPixel< LabelPixelID<double> >( idx );
        return this->InternalGetPixel< BasicPixelID<double> >( idx );
      }
    std::vector<int8_t>  GetPixelAsVectorInt8( const std::vector<uint32_t> &idx) const override
    {
        return this->InternalGetPixel< VectorPixelID<int8_t> >( idx );
      }
    std::vector<uint8_t>  GetPixelAsVectorUInt8( const std::vector<uint32_t> &idx) const override
      {
        return this->InternalGetPixel< VectorPixelID<uint8_t> >( idx );
      }
    std::vector<int16_t>  GetPixelAsVectorInt16( const std::vector<uint32_t> &idx ) const override
      {
        return this->InternalGetPixel< VectorPixelID<int16_t> >( idx );
      }
    std::vector<uint16_t> GetPixelAsVectorUInt16( const std::vector<uint32_t> &idx ) const override
      {
        return this->InternalGetPixel< VectorPixelID<uint16_t> >( idx );
      }
    std::vector<int32_t>  GetPixelAsVectorInt32( const std::vector<uint32_t> &idx ) const override
      {
        return this->InternalGetPixel< VectorPixelID<int32_t> >( idx );
      }
    std::vector<uint32_t> GetPixelAsVectorUInt32( const std::vector<uint32_t> &idx ) const override
      {
        return this->InternalGetPixel< VectorPixelID<uint32_t> >( idx );
      }
    std::vector<int64_t>  GetPixelAsVectorInt64( const std::vector<uint32_t> &idx ) const override
      {
        return this->InternalGetPixel< VectorPixelID<int64_t> >( idx );
      }
    std::vector<uint64_t> GetPixelAsVectorUInt64( const std::vector<uint32_t> &idx ) const override
      {
        return this->InternalGetPixel< VectorPixelID<uint64_t> >( idx );
      }
    std::vector<float>   GetPixelAsVectorFloat32( const std::vector<uint32_t> &idx ) const override
      {
        return this->InternalGetPixel< VectorPixelID<float> >( idx );
      }
    std::vector<double>   GetPixelAsVectorFloat64(  const std::vector<uint32_t> &idx ) const override
      {
        return this->InternalGetPixel< VectorPixelID<double> >( idx );
      }
    std::complex<float>   GetPixelAsComplexFloat32( const std::vector<uint32_t> &idx ) const override
      {
        return this->InternalGetPixel< BasicPixelID<std::complex<float> > >( idx );
      }
    std::complex<double>   GetPixelAsComplexFloat64(  const std::vector<uint32_t> &idx ) const override
      {
        return this->InternalGetPixel< BasicPixelID<std::complex<double> > >( idx );
      }

    int8_t  *GetBufferAsInt8() override
      {
        if ( IsVector<ImageType>::Value )
          return this->InternalGetBuffer< VectorPixelID<int8_t> >( );
        return this->InternalGetBuffer< BasicPixelID<int8_t> >( );
      }
    uint8_t  *GetBufferAsUInt8() override
      {
        if ( IsVector<ImageType>::Value )
          return this->InternalGetBuffer< VectorPixelID<uint8_t> >( );
        return this->InternalGetBuffer< BasicPixelID<uint8_t> >( );
      }
    int16_t  *GetBufferAsInt16( ) override
      {
        if ( IsVector<ImageType>::Value )
          return this->InternalGetBuffer< VectorPixelID<int16_t> >( );
        return  this->InternalGetBuffer< BasicPixelID<int16_t> >( );
      }
    uint16_t *GetBufferAsUInt16( ) override
      {
        if ( IsVector<ImageType>::Value )
          return this->InternalGetBuffer< VectorPixelID<uint16_t> >( );
        return this->InternalGetBuffer< BasicPixelID<uint16_t> >( );
      }
     int32_t  *GetBufferAsInt32( ) override
      {
        if ( IsVector<ImageType>::Value )
          return this->InternalGetBuffer< VectorPixelID<int32_t> >( );
        return this->InternalGetBuffer< BasicPixelID<int32_t> >( );
      }
    uint32_t *GetBufferAsUInt32( ) override
      {
        if ( IsVector<ImageType>::Value )
          return this->InternalGetBuffer< VectorPixelID<uint32_t> >( );
        return this->InternalGetBuffer< BasicPixelID<uint32_t> >( );
      }
     int64_t  *GetBufferAsInt64( ) override
      {
        if ( IsVector<ImageType>::Value )
          return this->InternalGetBuffer< VectorPixelID<int64_t> >( );
        return this->InternalGetBuffer< BasicPixelID<int64_t> >( );
      }
    uint64_t *GetBufferAsUInt64( ) override
      {
        if ( IsVector<ImageType>::Value )
          return this->InternalGetBuffer< VectorPixelID<uint64_t> >( );
        return this->InternalGetBuffer< BasicPixelID<uint64_t> >( );
      }
    float    *GetBufferAsFloat( ) override
      {
        if ( IsVector<ImageType>::Value )
          return this->InternalGetBuffer< VectorPixelID<float> >( );
        if (std::is_same<BasicPixelID<std::complex<float> >, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value)
          return reinterpret_cast<float*>(this->InternalGetBuffer< BasicPixelID<std::complex<float> > >());
        return this->InternalGetBuffer< BasicPixelID<float> >( );
      }
    double   *GetBufferAsDouble(  ) override
      {
        if ( IsVector<ImageType>::Value )
          return this->InternalGetBuffer< VectorPixelID<double> >( );
        if (std::is_same<BasicPixelID<std::complex<double> >, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value)
          {
          return reinterpret_cast<double *>(this->InternalGetBuffer< BasicPixelID<std::complex<double> > >());
          }
        return this->InternalGetBuffer< BasicPixelID<double> >( );
      }
    void *GetBufferAsVoid( ) override
      {
        return this->InternalGetBuffer< typename ImageTypeToPixelID<ImageType>::PixelIDType >( );
      }

    const int8_t  *GetBufferAsInt8() const override
      {
        if ( IsVector<ImageType>::Value )
          return const_cast<Self*>(this)->InternalGetBuffer< VectorPixelID<int8_t> >( );
        return const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<int8_t> >( );
      }
    const uint8_t  *GetBufferAsUInt8() const override
      {
        if ( IsVector<ImageType>::Value )
          return const_cast<Self*>(this)->InternalGetBuffer< VectorPixelID<uint8_t> >( );
        return const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<uint8_t> >( );
      }
    const int16_t  *GetBufferAsInt16( ) const override
      {
        if ( IsVector<ImageType>::Value )
          return const_cast<Self*>(this)->InternalGetBuffer< VectorPixelID<int16_t> >( );
        return const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<int16_t> >( );
      }
    const uint16_t *GetBufferAsUInt16( ) const override
      {
        if ( IsVector<ImageType>::Value )
          return const_cast<Self*>(this)->InternalGetBuffer< VectorPixelID<uint16_t> >( );
        return const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<uint16_t> >( );
      }
    const int32_t  *GetBufferAsInt32( ) const override
      {
        if ( IsVector<ImageType>::Value )
          return const_cast<Self*>(this)->InternalGetBuffer< VectorPixelID<int32_t> >( );
        return const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<int32_t> >( );
      }
    const uint32_t *GetBufferAsUInt32( ) const override
      {
        if ( IsVector<ImageType>::Value )
          return const_cast<Self*>(this)->InternalGetBuffer< VectorPixelID<uint32_t> >( );
        return const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<uint32_t> >( );
      }
    const int64_t  *GetBufferAsInt64( ) const override
      {
        if ( IsVector<ImageType>::Value )
          return const_cast<Self*>(this)->InternalGetBuffer< VectorPixelID<int64_t> >( );
        return const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<int64_t> >( );
      }
    const uint64_t *GetBufferAsUInt64( ) const override
      {
        if ( IsVector<ImageType>::Value )
          return const_cast<Self*>(this)->InternalGetBuffer< VectorPixelID<uint64_t> >( );
        return const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<uint64_t> >( );
      }
    const float    *GetBufferAsFloat( ) const override
      {
        if ( IsVector<ImageType>::Value )
          return const_cast<Self*>(this)->InternalGetBuffer< VectorPixelID<float> >( );
        if (std::is_same<BasicPixelID<std::complex<float> >, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value)
          return reinterpret_cast<float*>(const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<std::complex<float> > >());
        return const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<float> >( );
      }
    const double   *GetBufferAsDouble(  ) const override
      {
        if ( IsVector<ImageType>::Value )
          return const_cast<Self*>(this)->InternalGetBuffer< VectorPixelID<double> >( );
        if (std::is_same<BasicPixelID<std::complex<double> >, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value)
          {
          return reinterpret_cast<double *>(const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<std::complex<double> > >());
          }
        return const_cast<Self*>(this)->InternalGetBuffer< BasicPixelID<double> >( );
      }
    const void *GetBufferAsVoid( ) const override
      {
        return const_cast<Self*>(this)->InternalGetBuffer< typename ImageTypeToPixelID<ImageType>::PixelIDType >( );
      }


    void SetPixelAsInt8( const std::vector<uint32_t> &idx, int8_t v ) override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalSetPixel< LabelPixelID<int8_t> >( idx, v );
        this->InternalSetPixel<BasicPixelID<int8_t> >( idx, v );
      }
    void SetPixelAsUInt8( const std::vector<uint32_t> &idx, uint8_t v ) override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalSetPixel< LabelPixelID<uint8_t> >( idx, v );
        this->InternalSetPixel<BasicPixelID<uint8_t> >( idx, v );
      }
    void SetPixelAsInt16( const std::vector<uint32_t> &idx, int16_t v ) override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalSetPixel< LabelPixelID<int16_t> >( idx, v );
        this->InternalSetPixel<BasicPixelID<int16_t> >( idx, v );
      }
    void SetPixelAsUInt16( const std::vector<uint32_t> &idx, uint16_t v ) override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalSetPixel< LabelPixelID<uint16_t> >( idx, v );
        this->InternalSetPixel<BasicPixelID<uint16_t> >( idx, v );
      }
    void SetPixelAsInt32( const std::vector<uint32_t> &idx, int32_t v ) override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalSetPixel< LabelPixelID<int32_t> >( idx, v );
        this->InternalSetPixel<BasicPixelID<int32_t> >( idx, v );
      }
    void SetPixelAsUInt32( const std::vector<uint32_t> &idx, uint32_t v ) override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalSetPixel< LabelPixelID<uint32_t> >( idx, v );
        this->InternalSetPixel<BasicPixelID<uint32_t> >( idx, v );
      }
    void SetPixelAsInt64( const std::vector<uint32_t> &idx, int64_t v ) override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalSetPixel< LabelPixelID<int64_t> >( idx, v );
        this->InternalSetPixel<BasicPixelID<int64_t> >( idx, v );
      }
    void SetPixelAsUInt64( const std::vector<uint32_t> &idx, uint64_t v ) override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalSetPixel< LabelPixelID<uint64_t> >( idx, v );
        this->InternalSetPixel<BasicPixelID<uint64_t> >( idx, v );
      }
    void SetPixelAsFloat( const std::vector<uint32_t> &idx, float v ) override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalSetPixel< LabelPixelID<float> >( idx, v );
        this->InternalSetPixel<BasicPixelID<float> >( idx, v );
      }
    void SetPixelAsDouble( const std::vector<uint32_t> &idx, double v ) override
      {
        if ( IsLabel<ImageType>::Value )
          return this->InternalSetPixel< LabelPixelID<double> >( idx, v );
        this->InternalSetPixel<BasicPixelID<double> >( idx, v );
      }
    void SetPixelAsVectorInt8( const std::vector<uint32_t> &idx, const std::vector<int8_t> &v ) override
      {
        this->InternalSetPixel<VectorPixelID<int8_t> >( idx, v );
      }
    void SetPixelAsVectorUInt8( const std::vector<uint32_t> &idx, const std::vector<uint8_t> &v ) override
      {
        this->InternalSetPixel<VectorPixelID<uint8_t> >( idx, v );
      }
    void SetPixelAsVectorInt16( const std::vector<uint32_t> &idx, const std::vector<int16_t> &v ) override
      {
        this->InternalSetPixel<VectorPixelID<int16_t> >( idx, v );
      }
    void SetPixelAsVectorUInt16( const std::vector<uint32_t> &idx, const std::vector<uint16_t> &v ) override
      {
        this->InternalSetPixel<VectorPixelID<uint16_t> >( idx, v );
      }
    void SetPixelAsVectorInt32( const std::vector<uint32_t> &idx, const std::vector<int32_t> &v ) override
      {
        this->InternalSetPixel<VectorPixelID<int32_t> >( idx, v );
      }
    void SetPixelAsVectorUInt32( const std::vector<uint32_t> &idx, const std::vector<uint32_t> &v ) override
      {
        this->InternalSetPixel<VectorPixelID<uint32_t> >( idx, v );
      }
    void SetPixelAsVectorInt64( const std::vector<uint32_t> &idx, const std::vector<int64_t> &v ) override
      {
        this->InternalSetPixel<VectorPixelID<int64_t> >( idx, v );
      }
    void SetPixelAsVectorUInt64( const std::vector<uint32_t> &idx, const std::vector<uint64_t> &v ) override
      {
        this->InternalSetPixel<VectorPixelID<uint64_t> >( idx, v );
      }
    void SetPixelAsVectorFloat32( const std::vector<uint32_t> &idx, const std::vector<float> &v ) override
      {
        this->InternalSetPixel<VectorPixelID<float> >( idx, v );
      }
    void SetPixelAsVectorFloat64( const std::vector<uint32_t> &idx, const std::vector<double> &v ) override
      {
        this->InternalSetPixel<VectorPixelID<double> >( idx, v );
      }
    void SetPixelAsComplexFloat32( const std::vector<uint32_t> &idx, const std::complex<float> v ) override
      {
        this->InternalSetPixel<BasicPixelID<std::complex<float> > >( idx, v );
      }
    void SetPixelAsComplexFloat64( const std::vector<uint32_t> &idx, const std::complex<double> v ) override
      {
        this->InternalSetPixel<BasicPixelID<std::complex<double> > >( idx, v );
      }


  protected:

    template < typename TPixelIDType >
    typename std::enable_if<std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && !IsLabel<TPixelIDType>::Value
                      && !IsVector<TPixelIDType>::Value,
                      typename ImageType::PixelType >::type
    InternalGetPixel( const std::vector<uint32_t> &idx ) const
      {
        const IndexType itkIdx = sitkSTLVectorToITK<IndexType>( idx );
        if ( ! this->m_Image->GetLargestPossibleRegion().IsInside( itkIdx ) )
          {
          sitkExceptionMacro( "index out of bounds" );
          }
        return this->m_Image->GetPixel( itkIdx  );
      }

    template < typename TPixelIDType >
    typename std::enable_if<std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && IsLabel<TPixelIDType>::Value
                      && !IsVector<TPixelIDType>::Value,
                      typename ImageType::PixelType >::type
    InternalGetPixel( const std::vector<uint32_t> &idx ) const
      {
        const IndexType itkIdx = sitkSTLVectorToITK<IndexType>( idx );
        if ( ! this->m_Image->GetLargestPossibleRegion().IsInside( itkIdx ) )
          {
          sitkExceptionMacro( "index out of bounds" );
          }
        return this->m_Image->GetPixel( itkIdx  );
      }

    template < typename TPixelIDType >
    typename std::enable_if<std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && !IsLabel<TPixelIDType>::Value
                      && IsVector<TPixelIDType>::Value,
                      std::vector<typename MakeDependentOn<TPixelIDType, ImageType>::InternalPixelType> >::type
    InternalGetPixel( const std::vector<uint32_t> &idx ) const
      {
        const IndexType itkIdx = sitkSTLVectorToITK<IndexType>( idx );
        if ( ! this->m_Image->GetLargestPossibleRegion().IsInside( itkIdx ) )
          {
          sitkExceptionMacro( "index out of bounds" );
          }
        const typename ImageType::PixelType px = this->m_Image->GetPixel( itkIdx  );
        return std::vector<typename ImageType::InternalPixelType>(&px[0], &px[px.GetSize()]);
      }

    template < typename TPixelIDType >
    typename std::enable_if<!std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value,
                            typename std::conditional< IsVector<TPixelIDType>::Value,
                                             std::vector< typename itk::NumericTraits<typename PixelIDToImageType<TPixelIDType,ImageType::ImageDimension>::ImageType::PixelType >::ValueType >,
                                             typename PixelIDToImageType<TPixelIDType,ImageType::ImageDimension>::ImageType::PixelType >::type >::type
    InternalGetPixel( const std::vector<uint32_t> &idx ) const
      {
        Unused( idx );
        sitkExceptionMacro( << "The image is of type: " << GetPixelIDValueAsString( this->GetPixelID() )
                            << " but the GetPixel access method requires type: "
                            << GetPixelIDValueAsString(  PixelIDToPixelIDValue<TPixelIDType>::Result )
                            << "!" );
      }

    template< typename TPixelType, unsigned int NDimension >
    bool
    InternalCheckBuffer(const itk::Image<TPixelType, NDimension> *image)
      {
        auto container = image->GetPixelContainer();
        if (container->GetReferenceCount() != 1)
          {
          sitkExceptionMacro( << "The image pixel container is shared by other resources and presents aliasing issue.");
          }
        return true;
      }

    template< typename TPixelType, unsigned int NDimension >
    bool
    InternalCheckBuffer(const itk::VectorImage<TPixelType, NDimension> *image)
      {
        auto container = image->GetPixelContainer();
        if (container->GetReferenceCount() != 1)
          {
          sitkExceptionMacro( << "The vector image pixel container is shared by other resources and presents aliasing issues.");
          }
        return true;
      }


    template< typename TLabelObject >
    bool
    InternalCheckBuffer(const itk::LabelMap<TLabelObject> *)
      {
        return true;
      }

    template < typename TPixelIDType >
    typename std::enable_if<std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && !IsLabel<TPixelIDType>::Value
                      && !IsVector<TPixelIDType>::Value,
                      typename ImageType::PixelType *>::type
    InternalGetBuffer( void )
      {
        return this->m_Image->GetPixelContainer()->GetBufferPointer();
      }

    template < typename TPixelIDType >
    typename std::enable_if<std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && IsLabel<TPixelIDType>::Value
                      && !IsVector<TPixelIDType>::Value,
                      typename ImageType::PixelType *>::type
    InternalGetBuffer( void )
      {
        sitkExceptionMacro( "This method is not supported for LabelMaps." )
      }

    template < typename TPixelIDType >
    typename std::enable_if<std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && !IsLabel<TPixelIDType>::Value
                      && IsVector<TPixelIDType>::Value,
                      typename MakeDependentOn<TPixelIDType, ImageType>::InternalPixelType * >::type
    InternalGetBuffer( void )
      {
        return this->m_Image->GetPixelContainer()->GetBufferPointer();
      }

    template < typename TPixelIDType >
    typename std::enable_if<!std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value,
                       typename NumericTraits<typename PixelIDToImageType<TPixelIDType,2>::ImageType::PixelType>::ValueType *>::type
    InternalGetBuffer( void )
      {
        sitkExceptionMacro( << "The image is of type: " << GetPixelIDValueAsString( this->GetPixelID() )
                            << " but the GetBuffer access method requires type: "
                            << GetPixelIDValueAsString(  PixelIDToPixelIDValue<TPixelIDType>::Result )
                            << "!" );
      }


    template < typename TPixelIDType, typename TPixelType >
    typename std::enable_if<std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && !IsLabel<TPixelIDType>::Value
                      && !IsVector<TPixelIDType>::Value >::type
    InternalSetPixel( const std::vector<uint32_t> &idx, const TPixelType v ) const
      {
        const IndexType itkIdx = sitkSTLVectorToITK<IndexType>( idx );
        if ( ! this->m_Image->GetLargestPossibleRegion().IsInside( itkIdx ) )
          {
          sitkExceptionMacro( "index out of bounds" );
          }
        this->m_Image->SetPixel( itkIdx, v );
      }

    template < typename TPixelIDType, typename TPixelType >
    typename std::enable_if<std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && IsLabel<TPixelIDType>::Value
                      && !IsVector<TPixelIDType>::Value >::type
    InternalSetPixel( const std::vector<uint32_t> &idx, const TPixelType v ) const
      {
        const IndexType itkIdx = sitkSTLVectorToITK<IndexType>( idx );
        if ( ! this->m_Image->GetLargestPossibleRegion().IsInside( itkIdx ) )
          {
          sitkExceptionMacro( "index out of bounds" );
          }
        this->m_Image->SetPixel( itkIdx, v );
      }

    template < typename TPixelIDType, typename TPixelValueType >
    typename std::enable_if<std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && !IsLabel<TPixelIDType>::Value
                      && IsVector<TPixelIDType>::Value >::type
    InternalSetPixel( const std::vector<uint32_t> &idx, const std::vector<TPixelValueType> & v  ) const
      {
        const IndexType itkIdx = sitkSTLVectorToITK<IndexType>( idx );
        if ( ! this->m_Image->GetLargestPossibleRegion().IsInside( itkIdx ) )
          {
          sitkExceptionMacro( "index out of bounds" );
          }

        typename ImageType::PixelType px = this->m_Image->GetPixel( itkIdx );

        if ( px.GetSize() != v.size() )
          {
          sitkExceptionMacro(<<"Unable to convert vector to ITK pixel type\n"
                             << "Expected vector of length " <<  px.GetSize()
                             << " but only got " << v.size() << " elements." );
          }

        std::copy( v.begin(), v.end(), &px[0] );
      }


    template < typename TPixelIDType, typename TPixelType >
    typename std::enable_if<!std::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value >::type
    InternalSetPixel( const std::vector<uint32_t> &idx, const TPixelType &v ) const
      {
        Unused( idx );
        Unused( v );
        sitkExceptionMacro( << "The image is of type: " << GetPixelIDValueAsString( this->GetPixelID() )
                            << " but the SetPixel access method requires type: "
                            << GetPixelIDValueAsString(  PixelIDToPixelIDValue<BasicPixelID<TPixelType> >::Result )
                            << "!" );
      }

  private:
    ImagePointer m_Image;
  };

  }

  } // end namespace simple
} // end namespace itk

#endif // sitkPimpleImageBase_hxx
