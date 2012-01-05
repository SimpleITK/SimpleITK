#include "sitkImage.h"
#include "sitkMemberFunctionFactory.h"

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"
#include "itkLabelObject.h"

#include "itkImageDuplicator.h"

#include "sitkPimpleImageBase.hxx"


namespace itk
{
  namespace simple
  {

  // this is a little specialization just to get the
  // InternalInitialization method's PixelIDTpImageType lookup to get
  // a valid void type, so it'll dispatch to the a specialized
  // method. All this is just to instantiate something that will never
  // be actually used.
  template <unsigned int VImageDimension>
  struct PixelIDToImageType< typelist::NullType , VImageDimension >
  {
    typedef void ImageType;
  };

  // This method is explicitly instantiated, and in-turn implicitly
  // instantates the PipleImage for all used image types. This method
  // just dispatces to nother method, to aid in instantiating only the
  // images requested.
  template <int VPixelIDValue, unsigned int VImageDimension>

  void Image::InternalInitialization( typename PixelIDToImageType<typename typelist::TypeAt<InstantiatedPixelIDTypeList,
                                                                                            VPixelIDValue>::Result,
                                                                  VImageDimension>::ImageType *i )
  {
    this->ConditionalInternalInitialization<VPixelIDValue>( i );
  }

  template<int VPixelIDValue, typename TImageType>
  typename DisableIf<std::tr1::is_same<TImageType, void>::value>::Type
  Image::ConditionalInternalInitialization( TImageType *image )
  {
    // no need to check if null
    delete this->m_PimpleImage;
    this->m_PimpleImage = NULL;

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
    zero.Fill ( itk::NumericTraits<typename TImageType::PixelType::ValueType>::Zero );


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

    itk::DataObject* Image::GetITKBase( void )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return m_PimpleImage->GetDataBase();
    }

    const itk::DataObject* Image::GetITKBase( void ) const
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

    unsigned int Image::GetNumberOfComponentsPerPixel( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetNumberOfComponentsPerPixel();
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

    // Get Direction
    std::vector< double > Image::GetDirection( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetDirection();
    }

    // Set Direction
    void Image::SetDirection( const std::vector< double > &direction )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetDirection( direction );
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

    int32_t Image::GetPixelAsInt64( const std::vector<uint32_t> &idx ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelAsInt64( idx );
    }

    uint32_t Image::GetPixelAsUInt64( const std::vector<uint32_t> &idx ) const
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

    int8_t *Image::GetBufferAsInt8( )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return this->m_PimpleImage->GetBufferAsInt8( );
    }

    uint8_t *Image::GetBufferAsUInt8( )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return this->m_PimpleImage->GetBufferAsUInt8( );
    }

    int16_t *Image::GetBufferAsInt16( )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return this->m_PimpleImage->GetBufferAsInt16( );
    }

    uint16_t *Image::GetBufferAsUInt16( )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return this->m_PimpleImage->GetBufferAsUInt16( );
    }

    int32_t *Image::GetBufferAsInt32( )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return this->m_PimpleImage->GetBufferAsInt32( );
    }

    uint32_t *Image::GetBufferAsUInt32( )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return this->m_PimpleImage->GetBufferAsUInt32( );
    }

    int64_t *Image::GetBufferAsInt64( )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return this->m_PimpleImage->GetBufferAsInt64( );
    }

    uint64_t *Image::GetBufferAsUInt64( )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return this->m_PimpleImage->GetBufferAsUInt64( );
    }

    float *Image::GetBufferAsFloat( )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return this->m_PimpleImage->GetBufferAsFloat( );
    }

    double *Image::GetBufferAsDouble( )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      return this->m_PimpleImage->GetBufferAsDouble( );
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

    void Image::SetPixelAsInt8( const std::vector<uint32_t> &idx, int8_t v )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetPixelAsUInt8( idx, v );
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

    void Image::SetPixelAsInt64( const std::vector<uint32_t> &idx, int64_t v )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetPixelAsInt64( idx, v );
    }

    void Image::SetPixelAsUInt64( const std::vector<uint32_t> &idx, uint64_t v )
    {
      assert( m_PimpleImage );
      this->MakeUniqueForWrite();
      this->m_PimpleImage->SetPixelAsUInt64( idx, v );
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
  } // end namespace simple
} // end namespace itk


//
// There is only one templated function in the external interface
// which need to be instantiated, so that the itk::Image and the
// sitk::PimpleImage are completely encapsulated. That is the
// InternalInitialization method. The following uses a macro to
// explicitly instantiate for the expected image types.
//

#define SITK_TEMPLATE_InternalInitialization_D( _I, _D )                \
  namespace itk { namespace simple {                                    \
  template void Image::InternalInitialization<_I,_D>(  PixelIDToImageType< typelist::TypeAt<InstantiatedPixelIDTypeList, \
                                                                                            _I>::Result, \
                                                                           _D>::ImageType *i ); \
  } }


#define SITK_TEMPLATE_InternalInitialization( _I ) SITK_TEMPLATE_InternalInitialization_D( _I, 2 ) SITK_TEMPLATE_InternalInitialization_D( _I, 3 )



// Instantiate for all types in the lists
SITK_TEMPLATE_InternalInitialization( 0 );
SITK_TEMPLATE_InternalInitialization( 1 );
SITK_TEMPLATE_InternalInitialization( 2 );
SITK_TEMPLATE_InternalInitialization( 3 );
SITK_TEMPLATE_InternalInitialization( 4 );
SITK_TEMPLATE_InternalInitialization( 5 );
SITK_TEMPLATE_InternalInitialization( 6 );
SITK_TEMPLATE_InternalInitialization( 7 );
SITK_TEMPLATE_InternalInitialization( 8 );
SITK_TEMPLATE_InternalInitialization( 9 );
SITK_TEMPLATE_InternalInitialization( 10 );
SITK_TEMPLATE_InternalInitialization( 11 );
SITK_TEMPLATE_InternalInitialization( 12 );
SITK_TEMPLATE_InternalInitialization( 13 );
SITK_TEMPLATE_InternalInitialization( 14 );
SITK_TEMPLATE_InternalInitialization( 15 );
SITK_TEMPLATE_InternalInitialization( 16 );
SITK_TEMPLATE_InternalInitialization( 17 );
SITK_TEMPLATE_InternalInitialization( 18 );
SITK_TEMPLATE_InternalInitialization( 19 );
SITK_TEMPLATE_InternalInitialization( 20 );
SITK_TEMPLATE_InternalInitialization( 21 );
SITK_TEMPLATE_InternalInitialization( 22 );
SITK_TEMPLATE_InternalInitialization( 23 );
SITK_TEMPLATE_InternalInitialization( 24 );
SITK_TEMPLATE_InternalInitialization( 25 );
SITK_TEMPLATE_InternalInitialization( 26 );
SITK_TEMPLATE_InternalInitialization( 27 );
SITK_TEMPLATE_InternalInitialization( 28 );
SITK_TEMPLATE_InternalInitialization( 29 );


sitkStaticAssert( typelist::Length<itk::simple::InstantiatedPixelIDTypeList>::Result < 30, "Number of explicitly instantiated pixel types is more then expected!" );
