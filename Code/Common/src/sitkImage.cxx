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
