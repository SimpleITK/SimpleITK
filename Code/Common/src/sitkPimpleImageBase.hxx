#ifndef __sitkPimpleImageBase_hxx
#define __sitkPimpleImageBase_hxx

#include "sitkPimpleImageBase.h"
#include "sitkMemberFunctionFactory.h"

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"

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
    typedef PimpleImage                   Self;
    typedef TImageType                    ImageType;
    typedef typename ImageType::Pointer   ImagePointer;
    typedef typename ImageType::IndexType IndexType;
    typedef typename ImageType::PixelType PixelType;

    PimpleImage ( ImageType* image )
      : m_Image( image )
      {
        sitkStaticAssert( ImageType::ImageDimension == 3 || ImageType::ImageDimension == 2,
                          "Image Dimension out of range" );
        sitkStaticAssert( ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown,
                          "invalid pixel type" );

        if ( image == NULL )
          {
          sitkExceptionMacro( << "unable to initialize an image with NULL" );
          }
      }

    virtual PimpleImageBase *ShallowCopy( void ) const { return new Self(this->m_Image.GetPointer()); }
    virtual PimpleImageBase *DeepCopy( void ) const { return this->DeepCopy<TImageType>(); }

    template <typename UImageType>
    typename DisableIf<IsLabel<UImageType>::Value, PimpleImageBase*>::Type
    DeepCopy( void ) const
      {
        typedef itk::ImageDuplicator< ImageType > ImageDuplicatorType;
        typename ImageDuplicatorType::Pointer dup = ImageDuplicatorType::New();

        dup->SetInputImage( this->m_Image );
        dup->Update();
        ImagePointer output = dup->GetOutput();

        return new Self( output.GetPointer() );
      }
    template <typename UImageType>
    typename EnableIf<IsLabel<UImageType>::Value, PimpleImageBase*>::Type
    DeepCopy( void ) const
      {
        sitkExceptionMacro( "This method is not implemented yet" );
        return new Self( this->m_Image.GetPointer() );
      }

    virtual itk::DataObject* GetDataBase( void ) { return this->m_Image.GetPointer(); }
    virtual const itk::DataObject* GetDataBase( void ) const { return this->m_Image.GetPointer(); }


    PixelIDValueType GetPixelIDValue(void) const throw()
      {
        // The constructor ensures that we have a valid image
        // this maps the Image's pixel type to the array index
        return ImageTypeToPixelIDValue<ImageType>::Result;
      }

    virtual unsigned int GetDimension( void ) const
      {
        return ImageType::ImageDimension;
      }


    // Get Origin
    virtual std::vector<double> GetOrigin( void ) const
      {
        return sitkITKVectorToSTL<double>( this->m_Image->GetOrigin() );
      }

    // Set Origin
    virtual void SetOrigin( const std::vector<double> & orgn )
      {
      if (orgn.size() != ImageType::ImageDimension)
        {
        sitkExceptionMacro("Image::SetOrigin -> vector dimension mismatch");
        }

      this->m_Image->SetOrigin( sitkSTLVectorToITK< typename ImageType::PointType> ( orgn ) );
      }

    // Get Spacing
    virtual std::vector<double> GetSpacing( void ) const
      {
        return sitkITKVectorToSTL<double>( this->m_Image->GetSpacing() );
      }

    // Set Spacing
    virtual void SetSpacing( const std::vector<double> &spc )
      {
      if (spc.size() != ImageType::ImageDimension)
        {
        sitkExceptionMacro("Image::SetSpacing -> vector dimension mismatch");
        }

      this->m_Image->SetSpacing( sitkSTLVectorToITK< typename ImageType::SpacingType> ( spc ) );
      }

    // Physical Point to Index
    virtual std::vector<int64_t> TransformPhysicalPointToIndex( const std::vector<double> &pt ) const
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
    virtual std::vector<double> TransformIndexToPhysicalPoint( const std::vector<int64_t> &idx ) const
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
      this->m_Image->TransformIndexToPhysicalPoint( index, point);

      return sitkITKVectorToSTL<double>( point );
      }

    virtual unsigned int GetSize( unsigned int dimension ) const
      {
        if ( dimension > ImageType::ImageDimension - 1 )
          {
          return 0;
          }

        typename ImageType::RegionType largestRegion = this->m_Image->GetLargestPossibleRegion();
        return largestRegion.GetSize(dimension);
      }

    virtual std::vector<unsigned int> GetSize( void ) const
      {
        typename ImageType::RegionType largestRegion = this->m_Image->GetLargestPossibleRegion();
        std::vector<unsigned int> size( ImageType::ImageDimension );

        return sitkITKVectorToSTL<unsigned int>( largestRegion.GetSize() );
      }

    std::string ToString( void ) const
      {
        std::ostringstream out;
        this->m_Image->Print ( out );
        return out.str();
      }

    virtual int GetReferenceCountOfImage() const
      {
        return this->m_Image->GetReferenceCount();
      }


    virtual uint8_t  GetPixelAsUInt8( const std::vector<uint32_t> &idx) const
      {
        return this->InternalGetPixel< BasicPixelID<uint8_t> >( idx );
      }
    virtual int16_t  GetPixelAsInt16( const std::vector<uint32_t> &idx ) const
      {
        return this->InternalGetPixel< BasicPixelID<int16_t> >( idx );
      }
    virtual uint16_t GetPixelAsUInt16( const std::vector<uint32_t> &idx ) const
      {
        return this->InternalGetPixel< BasicPixelID<uint16_t> >( idx );
      }
    virtual int32_t  GetPixelAsInt32( const std::vector<uint32_t> &idx ) const
      {
        return this->InternalGetPixel< BasicPixelID<int32_t> >( idx );
      }
    virtual uint32_t GetPixelAsUInt32( const std::vector<uint32_t> &idx ) const
      {
        return this->InternalGetPixel< BasicPixelID<uint32_t> >( idx );
      }
    virtual float    GetPixelAsFloat( const std::vector<uint32_t> &idx ) const
      {
        return this->InternalGetPixel< BasicPixelID<float> >( idx );
      }
    virtual double   GetPixelAsDouble(  const std::vector<uint32_t> &idx ) const
      {
        return this->InternalGetPixel< BasicPixelID<double> >( idx );
      }

    virtual uint8_t  *GetBufferAsUInt8()
      {
        return static_cast<uint8_t*>(this->InternalGetBuffer< BasicPixelID<uint8_t> >( ));
      }
    virtual int16_t  *GetBufferAsInt16( )
      {
        return  static_cast<int16_t*>(this->InternalGetBuffer< BasicPixelID<int16_t> >( ));
      }
    virtual uint16_t *GetBufferAsUInt16( )
      {
        return  static_cast<uint16_t*>(this->InternalGetBuffer< BasicPixelID<uint16_t> >( ));
      }
    virtual  int32_t  *GetBufferAsInt32( )
      {
        return  static_cast<int32_t*>(this->InternalGetBuffer< BasicPixelID<int32_t> >( ));
      }
    virtual uint32_t *GetBufferAsUInt32( )
      {
        return  static_cast<uint32_t*>(this->InternalGetBuffer< BasicPixelID<uint32_t> >( ));
      }
    virtual float    *GetBufferAsFloat( )
      {
        return  static_cast<float*>(this->InternalGetBuffer< BasicPixelID<float> >( ));
      }
    virtual double   *GetBufferAsDouble(  )
      {
        return  static_cast<double*>(this->InternalGetBuffer< BasicPixelID<double> >( ));
      }

    virtual void SetPixelAsUInt8( const std::vector<uint32_t> &idx, uint8_t v )
      {
        this->InternalSetPixel( idx, v );
      }
    virtual void SetPixelAsInt16( const std::vector<uint32_t> &idx, int16_t v )
      {
        this->InternalSetPixel( idx, v );
      }
    virtual void SetPixelAsUInt16( const std::vector<uint32_t> &idx, uint16_t v )
      {
        this->InternalSetPixel( idx, v );
      }
    virtual void SetPixelAsInt32( const std::vector<uint32_t> &idx, int32_t v )
      {
        this->InternalSetPixel( idx, v );
      }
    virtual void SetPixelAsUInt32( const std::vector<uint32_t> &idx, uint32_t v )
      {
        this->InternalSetPixel( idx, v );
      }
    virtual void SetPixelAsFloat( const std::vector<uint32_t> &idx, float v )
      {
        this->InternalSetPixel( idx, v );
      }
    virtual void SetPixelAsDouble( const std::vector<uint32_t> &idx, double v )
      {
        this->InternalSetPixel( idx, v );
      }


  protected:

    template < typename TPixelIDType >
    typename EnableIf<std::tr1::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && !IsLabel<TPixelIDType>::Value
                      && !IsVector<TPixelIDType>::Value,
                      typename ImageType::PixelType >::Type
    InternalGetPixel( const std::vector<uint32_t> &idx ) const
      {
        return this->m_Image->GetPixel( sitkSTLVectorToITK<IndexType>( idx ) );
      }

    template < typename TPixelIDType >
    typename EnableIf<std::tr1::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && IsLabel<TPixelIDType>::Value
                      && !IsVector<TPixelIDType>::Value,
                      typename ImageType::PixelType >::Type
    InternalGetPixel( const std::vector<uint32_t> &idx ) const
      {
        return this->m_Image->GetPixel( sitkSTLVectorToITK<IndexType>( idx ) );
      }

    template < typename TPixelIDType >
    typename EnableIf<std::tr1::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && !IsLabel<TPixelIDType>::Value
                      && IsVector<TPixelIDType>::Value,
                      int >::Type
    InternalGetPixel( const std::vector<uint32_t> &idx ) const
      {
        Unused( idx );
        sitkExceptionMacro( "This method is not supported for this vector images currently." )
      }

    template < typename TPixelIDType >
    typename DisableIf<std::tr1::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value,
                      int >::Type
    InternalGetPixel( const std::vector<uint32_t> &idx ) const
      {
        Unused( idx );
        sitkExceptionMacro( << "The image is of type: " << GetPixelIDValueAsString( this->GetPixelIDValue() )
                            << " but the GetPixel access method requires type: "
                            << GetPixelIDValueAsString(  PixelIDToPixelIDValue<TPixelIDType>::Result )
                            << "!" );
      }


    template < typename TPixelIDType >
    typename EnableIf<std::tr1::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && !IsLabel<TPixelIDType>::Value
                      && !IsVector<TPixelIDType>::Value,
                      typename ImageType::PixelType *>::Type
    InternalGetBuffer( void )
      {
        return this->m_Image->GetPixelContainer()->GetBufferPointer();
      }

    template < typename TPixelIDType >
    typename EnableIf<std::tr1::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && IsLabel<TPixelIDType>::Value
                      && !IsVector<TPixelIDType>::Value,
                      typename ImageType::PixelType *>::Type
    InternalGetBuffer( void )
      {
        sitkExceptionMacro( "This method is not supported for LabelMaps." )
      }

    template < typename TPixelIDType >
    typename EnableIf<std::tr1::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && !IsLabel<TPixelIDType>::Value
                      && IsVector<TPixelIDType>::Value,
                      typename MakeDependentOn<TPixelIDType, ImageType>::InternalPixelType >::Type
    InternalGetBuffer( void )
      {
        return this->m_Image->GetPixelContainer()->GetBufferPointer();
      }

    template < typename TPixelIDType >
    typename DisableIf<std::tr1::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value,
                      void *>::Type
    InternalGetBuffer( void )
      {
        sitkExceptionMacro( << "The image is of type: " << GetPixelIDValueAsString( this->GetPixelIDValue() )
                            << " but the GetPixel access method requires type: "
                            << GetPixelIDValueAsString(  PixelIDToPixelIDValue<TPixelIDType>::Result )
                            << "!" );
      }


    template < typename TPixelType >
    typename EnableIf<std::tr1::is_same<BasicPixelID<TPixelType>,
                                        typename ImageTypeToPixelID<ImageType>::PixelIDType >::value >::Type
    InternalSetPixel( const std::vector<uint32_t> &idx, TPixelType v  ) const
      {
        return this->m_Image->SetPixel( sitkSTLVectorToITK<IndexType>( idx ), v );
      }

    template < typename TPixelType >
    typename DisableIf<std::tr1::is_same<BasicPixelID<TPixelType>,
                                         typename ImageTypeToPixelID<ImageType>::PixelIDType>::value >::Type
    InternalSetPixel( const std::vector<uint32_t> &idx, TPixelType v ) const
      {
        Unused( idx );
        Unused( v );
        sitkExceptionMacro( "This method is not supported for this image type." )
      }

  private:
    ImagePointer m_Image;
  };

  }

  } // end namespace simple
} // end namespace itk

#endif // __sitkPimpleImageBase_hxx
