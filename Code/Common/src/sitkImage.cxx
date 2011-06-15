#include "sitkImage.h"
#include "sitkMemberFunctionFactory.h"

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"
#include "itkLabelObject.h"

#include "itkImageDuplicator.h"


namespace itk
{
  namespace simple
  {

  /** \class PimpleImageBase
   * \brief Private implementation idiom image base class
   *
   * We utilize the private implementation ( or PImple)
   * programming idiom to modify the behavior of the simple image
   * class based on the different image types.
   *
   * This class is desinged to utilize the trivial copy,
   * and assgnement operators
   */
  class PimpleImageBase
  {
  public:
    virtual ~PimpleImageBase( void ) { };

    virtual PixelIDValueType GetPixelIDValue(void) = 0;
    virtual unsigned int GetDimension( void ) = 0;

    virtual PimpleImageBase *ShallowCopy(void) const = 0;
    virtual PimpleImageBase *DeepCopy(void) const = 0;
    virtual itk::DataObject* GetDataBase( void ) = 0;
    virtual const itk::DataObject* GetDataBase( void ) const = 0;

    virtual unsigned int GetWidth( void ) const { return this->GetSize( 0 ); }
    virtual unsigned int GetHeight( void ) const { return this->GetSize( 1 ); }
    virtual unsigned int GetDepth( void ) const { return this->GetSize( 2 ); }

    virtual std::vector< unsigned int > GetSize( void ) const = 0;
    virtual unsigned int GetSize( unsigned int dimension ) const = 0;

    virtual std::vector<double> GetOrigin( void ) const = 0;
    virtual void SetOrigin( const std::vector<double> &orgn ) = 0;
    virtual std::vector<double> GetSpacing( void ) const = 0;
    virtual void SetSpacing( const std::vector<double> &spc ) = 0;

    virtual std::vector<int64_t> TransformPhysicalPointToIndex( const std::vector<double> &pt) const = 0;
    virtual std::vector<double> TransformIndexToPhysicalPoint( const std::vector<int64_t> &idx) const = 0;

    virtual std::string ToString() const = 0;


    virtual int GetReferenceCountOfImage() const = 0;

    virtual uint8_t  GetPixelAsUInt8( const std::vector<uint32_t> &idx) const = 0;
    virtual int16_t  GetPixelAsInt16( const std::vector<uint32_t> &idx ) const = 0;
    virtual uint16_t GetPixelAsUInt16( const std::vector<uint32_t> &idx ) const = 0;
    virtual int32_t  GetPixelAsInt32( const std::vector<uint32_t> &idx ) const = 0;
    virtual uint32_t GetPixelAsUInt32( const std::vector<uint32_t> &idx ) const = 0;
    virtual float    GetPixelAsFloat( const std::vector<uint32_t> &idx ) const = 0;
    virtual double   GetPixelAsDouble(  const std::vector<uint32_t> &idx ) const = 0;

    virtual void SetPixelAsUInt8( const std::vector<uint32_t> &idx, uint8_t v ) = 0;
    virtual void SetPixelAsInt16( const std::vector<uint32_t> &idx, int16_t v ) = 0;
    virtual void SetPixelAsUInt16( const std::vector<uint32_t> &idx, uint16_t v ) = 0;
    virtual void SetPixelAsInt32( const std::vector<uint32_t> &idx, int32_t v ) = 0;
    virtual void SetPixelAsUInt32( const std::vector<uint32_t> &idx, uint32_t v ) = 0;
    virtual void SetPixelAsFloat( const std::vector<uint32_t> &idx, float v ) = 0;
    virtual void SetPixelAsDouble( const std::vector<uint32_t> &idx, double v ) = 0;
  };


///
/// Private name space for a concrete implementation of pimple image
/// for a specific image types with dimensions and pixel types
///
  namespace
  {

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


    PixelIDValueType GetPixelIDValue(void) throw()
      {
        // The constructor ensures that we have a valid image
        // this maps the Image's pixel type to the array index
        return ImageTypeToPixelIDValue< ImageType>::Result;
      }

    virtual unsigned int GetDimension( void )
      {
        return ImageType::ImageDimension;
      }


    // Get Origin
    virtual std::vector<double> GetOrigin( void ) const
      {
      typename ImageType::PointType origin = this->m_Image->GetOrigin();
      std::vector<double> orgn( ImageType::ImageDimension );

      std::copy( origin.Begin(), origin.End(), orgn.begin() );

      return orgn;
      }

    // Set Origin
    virtual void SetOrigin( const std::vector<double> & orgn )
      {
      if (orgn.size() != ImageType::ImageDimension)
        {
        sitkExceptionMacro("Image::SetOrigin -> vector dimension mismatch");
        }
      typename ImageType::PointType origin;

      std::copy( orgn.begin(), orgn.end(), origin.Begin() );

      this->m_Image->SetOrigin( origin );
      }

    // Get Spacing
    virtual std::vector<double> GetSpacing( void ) const
      {
      typename ImageType::SpacingType spacing = this->m_Image->GetSpacing();
      std::vector<double> spc( ImageType::ImageDimension );

      std::copy( spacing.Begin(), spacing.End(), spc.begin() );

      return spc;
      }

    // Set Spacing
    virtual void SetSpacing( const std::vector<double> &spc )
      {
      if (spc.size() != ImageType::ImageDimension)
        {
        sitkExceptionMacro("Image::SetSpacing -> vector dimension mismatch");
        }
      typename ImageType::SpacingType spacing;

      std::copy( spc.begin(), spc.end(), spacing.Begin() );

      this->m_Image->SetSpacing( spacing );
      }

    // Physical Point to Index
    virtual std::vector<int64_t> TransformPhysicalPointToIndex( const std::vector<double> &pt ) const
      {
        if (pt.size() != ImageType::ImageDimension)
        {
        sitkExceptionMacro("vector dimension mismatch");
        }

      typename ImageType::PointType point;
      std::copy( pt.begin(), pt.end(), point.Begin() );

      typename ImageType::IndexType index;
      this->m_Image->TransformPhysicalPointToIndex(point, index);
      std::vector<int64_t> idx( ImageType::ImageDimension );

      for( unsigned int i = 0; i < ImageType::ImageDimension; ++i )
        {
        idx[i] = index[i];
        }

      return idx;
      }

    // Index to Physical Point
    virtual std::vector<double> TransformIndexToPhysicalPoint( const std::vector<int64_t> &idx ) const
      {
        if (idx.size() != ImageType::ImageDimension)
        {
        sitkExceptionMacro("vector dimension mismatch");
        }
      typename ImageType::IndexType index;

      for( unsigned int i = 0; i < ImageType::ImageDimension; ++i )
        {
        index[i] = idx[i];
        }

      typename ImageType::PointType point;
      this->m_Image->TransformIndexToPhysicalPoint(index, point);
      std::vector<double> pt( ImageType::ImageDimension );

      std::copy( point.Begin(), point.End(), pt.begin() );

      return pt;
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

        for ( unsigned int i = 0; i < ImageType::ImageDimension; ++i )
          {
          size[i] = largestRegion.GetSize(i);
          }
        return size;
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
        return this->m_Image->GetPixel( this->ConvertSTLToIndex( idx ) );
      }

    template < typename TPixelIDType >
    typename EnableIf<std::tr1::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && IsLabel<TPixelIDType>::Value
                      && !IsVector<TPixelIDType>::Value,
                      typename ImageType::PixelType >::Type
    InternalGetPixel( const std::vector<uint32_t> &idx ) const
      {
        return this->m_Image->GetPixel( this->ConvertSTLToIndex( idx ) );
      }

    template < typename TPixelIDType >
    typename EnableIf<std::tr1::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value
                      && !IsLabel<TPixelIDType>::Value
                      && IsVector<TPixelIDType>::Value,
                      int >::Type
    InternalGetPixel( const std::vector<uint32_t> &idx ) const
      {
        sitkExceptionMacro( "This method is not supported for this vector images currently." )
      }

    template < typename TPixelIDType >
    typename DisableIf<std::tr1::is_same<TPixelIDType, typename ImageTypeToPixelID<ImageType>::PixelIDType>::value,
                      int >::Type
    InternalGetPixel( const std::vector<uint32_t> &idx ) const
      {
        sitkExceptionMacro( "This method is not supported for this image type." )
      }


    template < typename TPixelType >
    typename EnableIf<std::tr1::is_same<BasicPixelID<TPixelType>,
                                        typename ImageTypeToPixelID<ImageType>::PixelIDType >::value >::Type
    InternalSetPixel( const std::vector<uint32_t> &idx, TPixelType v  ) const
      {
        return this->m_Image->SetPixel( this->ConvertSTLToIndex( idx ), v );
      }

    template < typename TPixelType >
    typename DisableIf<std::tr1::is_same<BasicPixelID<TPixelType>,
                                         typename ImageTypeToPixelID<ImageType>::PixelIDType>::value >::Type
    InternalSetPixel( const std::vector<uint32_t> &idx, TPixelType v ) const
      {
        sitkExceptionMacro( "This method is not supported for this image type." )
      }

    static IndexType ConvertSTLToIndex( const std::vector<uint32_t> &idx )
      {
        // convert idx to itk::Index
        if ( idx.size() < ImageType::ImageDimension )
          {
          sitkExceptionMacro( "Image index size mismatch" );
          }
        IndexType itkIDX;
        for ( unsigned int i = 0; i < ImageType::ImageDimension; ++i )
            itkIDX[i] = idx[i];
        return itkIDX;
      }

  private:
    ImagePointer m_Image;
  };

  }
//
// End private namespace for pimple implementation
//


  template <typename TImageType>
  void Image::InternalInitialization( TImageType *image )
  {
    // no need to check if null
    delete this->m_PimpleImage;
    this->m_PimpleImage = NULL;

    // assign to basic pointer
    this->m_PimpleImage = new PimpleImage<TImageType>( image );
  }

  template<class TImageType>
  typename EnableIf<IsBasic<TImageType>::Value>::Type
  Image::AllocateInternal ( unsigned int Width, unsigned int Height, unsigned int Depth )
  {
    typename TImageType::IndexType  index;
    typename TImageType::SizeType   size;
    typename TImageType::RegionType region;
    index.Fill ( 0 );
    size.Fill(1);
    size[0] = Width;
    size[1] = Height;
    if ( TImageType::ImageDimension > 2 ) {
    assert(Depth != 0 );
    size[2] = Depth;
    }
    region.SetSize ( size );
    region.SetIndex ( index );
    typename TImageType::Pointer image = TImageType::New();
    image->SetRegions ( region );
    image->Allocate();
    image->FillBuffer ( itk::NumericTraits<typename TImageType::PixelType>::Zero );

    delete this->m_PimpleImage;
    this->m_PimpleImage = NULL;
    m_PimpleImage =  new PimpleImage<TImageType>( image );
  }

  template<class TImageType>
  typename EnableIf<IsVector<TImageType>::Value>::Type
  Image::AllocateInternal ( unsigned int Width, unsigned int Height, unsigned int Depth )
  {
    typename TImageType::IndexType  index;
    typename TImageType::SizeType   size;
    typename TImageType::RegionType region;
    typename TImageType::PixelType  zero;

    index.Fill ( 0 );
    size.Fill(1);
    size[0] = Width;
    size[1] = Height;
    if ( TImageType::ImageDimension > 2 )
      {
      assert(Depth != 0 );
      size[2] = Depth;
      }
    region.SetSize ( size );
    region.SetIndex ( index );

    zero.SetSize( TImageType::ImageDimension );
    zero.Fill( 0.0 );


    typename TImageType::Pointer image = TImageType::New();
    image->SetRegions ( region );
    image->SetVectorLength( TImageType::ImageDimension );
    image->Allocate();
    image->FillBuffer ( zero );

    delete this->m_PimpleImage;
    this->m_PimpleImage = NULL;

    m_PimpleImage = new PimpleImage<TImageType>( image );
  }

  template<class TImageType>
  typename EnableIf<IsLabel<TImageType>::Value>::Type
  Image::AllocateInternal ( unsigned int Width, unsigned int Height, unsigned int Depth )
  {
    typename TImageType::IndexType  index;
    typename TImageType::SizeType   size;
    typename TImageType::RegionType region;

    index.Fill ( 0 );
    size.Fill(1);
    size[0] = Width;
    size[1] = Height;
    if ( TImageType::ImageDimension > 2 )
      {
      assert(Depth != 0 );
      size[2] = Depth;
      }
    region.SetSize ( size );
    region.SetIndex ( index );

    typename TImageType::Pointer image = TImageType::New();
    image->SetRegions ( region );
    image->Allocate();
    image->SetBackgroundValue( 0 );

    delete this->m_PimpleImage;
    this->m_PimpleImage = NULL;

    m_PimpleImage = new PimpleImage<TImageType>( image );
  }


  void Image::Allocate ( unsigned int Width, unsigned int Height, unsigned int Depth, PixelIDValueEnum ValueEnum )
  {
      // initialize member function factory for allocating images

      // The pixel IDs supported
      typedef AllPixelIDTypeList              PixelIDTypeList;

      typedef void (Self::*MemberFunctionType)( unsigned int Width, unsigned int Height, unsigned int Depth );

      typedef AllocateMemberFunctionAddressor<MemberFunctionType> AllocateAddressor;

      detail::MemberFunctionFactory<MemberFunctionType> allocateMemberFactory(this);
      allocateMemberFactory.RegisterMemberFunctions< PixelIDTypeList, 3,  AllocateAddressor > ();
      allocateMemberFactory.RegisterMemberFunctions< PixelIDTypeList, 2,  AllocateAddressor > ();

      if ( ValueEnum == sitkUnknown )
        {
        sitkExceptionMacro( "Unable to construct image of unsupported pixel type" );
        }

      PixelIDValueType type = ValueEnum;
      if ( Depth == 0 ) {
        allocateMemberFactory.GetMemberFunction( type, 2 )( Width, Height, Depth );
      } else {
        allocateMemberFactory.GetMemberFunction( type, 3 )( Width, Height, Depth );
      }
    }

  Image::~Image( )
  {
    delete this->m_PimpleImage;
    this->m_PimpleImage = NULL;
  }

  Image::Image( const Image &img )
  {
    this->m_PimpleImage = img.m_PimpleImage->ShallowCopy();
  }

  Image& Image::operator=( const Image &img )
  {
    // note: If img and this are this same, the following statement
    // will still be safe. It is also exception safe.
    std::auto_ptr<PimpleImageBase> temp( img.m_PimpleImage->ShallowCopy() );
    delete this->m_PimpleImage;
    this->m_PimpleImage = temp.release();
    return *this;
  }

    Image::Image( unsigned int Width, unsigned int Height, PixelIDValueEnum ValueEnum )
      : m_PimpleImage( NULL )
    {
      Allocate ( Width, Height, 0, ValueEnum );
    }

    Image::Image( unsigned int Width, unsigned int Height, unsigned int Depth, PixelIDValueEnum ValueEnum )
      : m_PimpleImage( NULL )
    {
      Allocate ( Width, Height, Depth, ValueEnum );
    }

    itk::DataObject* Image::GetImageBase( void )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return m_PimpleImage->GetDataBase();
    }

    const itk::DataObject* Image::GetImageBase( void ) const
    {
      assert( m_PimpleImage );
      return m_PimpleImage->GetDataBase();
    }

    PixelIDValueType Image::GetPixelIDValue( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelIDValue();
    }

    unsigned int Image::GetDimension( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetDimension();
    }

    std::string Image::GetPixelIDTypeAsString( void ) const
    {
      return std::string( GetPixelIDValueAsString( this->GetPixelIDValue() ) );
    }

    std::string Image::ToString( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->ToString();
    }

    std::vector< unsigned int > Image::GetSize( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetSize();
    }

    unsigned int Image::GetWidth( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetWidth();
    }

    unsigned int Image::GetHeight( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetHeight();
    }

    unsigned int Image::GetDepth( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetDepth();
    }

    // Get Origin
    std::vector< double > Image::GetOrigin( void ) const
    {
       assert( m_PimpleImage );
      return this->m_PimpleImage->GetOrigin();
    }

    // Set Origin
    void Image::SetOrigin( const std::vector<double> &orgn )
    {
       assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetOrigin(orgn);
    }

    // Get Spacing
    std::vector< double > Image::GetSpacing( void ) const
    {
       assert( m_PimpleImage );
      return this->m_PimpleImage->GetSpacing();
    }

    // Set Spacing
    void Image::SetSpacing( const std::vector<double> &spc )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetSpacing(spc);
    }

    // Index to Physical Point
    std::vector< double > Image::TransformIndexToPhysicalPoint( const std::vector< int64_t > &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->TransformIndexToPhysicalPoint( idx );
    }

    // Physical Point to Index
    std::vector< int64_t > Image::TransformPhysicalPointToIndex( const std::vector< double > &pt ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->TransformPhysicalPointToIndex( pt );
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

    void Image::SetPixelAsUInt8( const std::vector<uint32_t> &idx, uint8_t v )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetPixelAsUInt8( idx, v );
    }

    void Image::SetPixelAsInt16( const std::vector<uint32_t> &idx, int16_t v )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetPixelAsInt16( idx, v );
    }

    void Image::SetPixelAsUInt16( const std::vector<uint32_t> &idx, uint16_t v )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetPixelAsUInt16( idx, v );
    }

    void Image::SetPixelAsInt32( const std::vector<uint32_t> &idx, int32_t v )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetPixelAsInt32( idx, v );
    }

    void Image::SetPixelAsUInt32( const std::vector<uint32_t> &idx, uint32_t v )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetPixelAsUInt32( idx, v );
    }

    void Image::SetPixelAsFloat( const std::vector<uint32_t> &idx, float v )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetPixelAsFloat( idx, v );
    }

    void Image::SetPixelAsDouble( const std::vector<uint32_t> &idx, double v )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetPixelAsDouble( idx, v );
    }


    void Image::MakeUniqueForWrite( void )
    {
      if ( this->m_PimpleImage->GetReferenceCountOfImage() > 1 )
        {
        // note: care is take here to be exception safe with memory allocation
        std::auto_ptr<PimpleImageBase> temp( this->m_PimpleImage->DeepCopy() );
        delete this->m_PimpleImage;
        this->m_PimpleImage = temp.release();
        }

    }

///
/// Private name space for class for __ImplicitInstantiate
///
  namespace
  {
  // this class is designed to work with typelist::Vist
  //
  // The purpose of this class it to implicitly instantiate the
  // templated constructors of this class.
  struct ConstructorInstantiator
  {

    template< typename TPixelIDType >
    void operator() ( void ) const
      {
        typedef typename PixelIDToImageType<TPixelIDType, 2>::ImageType Image2Type;
        typedef typename PixelIDToImageType<TPixelIDType, 3>::ImageType Image3Type;

        void (Image::*pFunc1)(Image2Type*) = &Image::InternalInitialization<Image2Type>;
        Unused( pFunc1 );

        void (Image::*pFunc2)(Image3Type*) = &Image::InternalInitialization<Image3Type>;
        Unused( pFunc2 );

      }
  };
  }
//
// End private namespace
//
  void Image::__ImplicitInstantiate( void )
  {
    typelist::Visit<InstantiatedPixelIDTypeList> visitToImplicitlyInstantiate;
    visitToImplicitlyInstantiate( ConstructorInstantiator() );
  }


    /*
    void Image::Show(const std::string name) const
    {
      // Try to find ImageJ, write out a file and open
#if defined(__WIN32__)
      // Windows
#elseif defined(__APPLE__)
      // Mac
      char *filename = malloc ( sizeof(char) * (100 + name.size()) );
      sprintf ( filename, "/tmp/%s-XXXXX.nrrd", name.c_str() );
      mktemp ( filename );
      ImageFileWriter().SetFilename ( filename ).Execute ( this );
      std::cout << "Show Filename: " << filename << std::endl;
#else
      // Linux
#endif
    }
    */

  }
}
