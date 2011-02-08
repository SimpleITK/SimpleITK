#include "sitkImage.h"
#include "sitkMemberFunctionFactory.h"

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"
#include "itkLabelObject.h"

// This is the only file which needs to include this implementation
#include "sitkPixelContainer.txx"

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
   * This class is desinged to be utilize to have trivial copy,
   * and assgnement operators
   */
  class PimpleImageBase
  {
  public:
    virtual ~PimpleImageBase( void ) { };

    virtual PixelIDValueType GetPixelIDValue(void) = 0;
    virtual unsigned int GetDimension( void ) = 0;

    virtual PimpleImageBase *Clone(void) const = 0;
    virtual itk::DataObject::Pointer GetDataBase( void ) = 0;
    virtual itk::DataObject::ConstPointer GetDataBase( void ) const = 0;

    virtual uint64_t GetWidth( void ) const { return this->GetSize( 0 ); }
    virtual uint64_t GetHeight( void ) const { return this->GetSize( 1 ); }
    virtual uint64_t GetDepth( void ) const { return this->GetSize( 2 ); }

    virtual uint64_t GetSize( unsigned int dimension ) const = 0;
    virtual double GetOrigin( unsigned int dimension ) const = 0;
    virtual double GetSpacing( unsigned int dimension ) const = 0;

    virtual std::string ToString() const = 0;

    virtual PixelContainer::Pointer GetPixelContainer() = 0;

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
    typedef PimpleImage                 Self;
    typedef TImageType                  ImageType;
    typedef typename ImageType::Pointer ImagePointer;

    PimpleImage ( ImageType* image )
      : m_Image( image )
      {
        sitkStaticAssert( TImageType::ImageDimension == 3 || TImageType::ImageDimension == 2,
                          "Image Dimension out of range" );
        sitkStaticAssert( ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown,
                          "invalid pixel type" );

        if ( image == NULL )
          {
          sitkExceptionMacro( << "unable to initialize an image with NULL" );
          }
      }

    virtual PimpleImageBase *Clone( void ) const { return new Self(this->m_Image.GetPointer()); }
    virtual itk::DataObject::Pointer GetDataBase( void ) { return this->m_Image.GetPointer(); }
    virtual itk::DataObject::ConstPointer GetDataBase( void ) const { return this->m_Image.GetPointer(); }

    PixelIDValueType GetPixelIDValue(void) throw()
      {
        // The constructor ensures that we have a valid image
        // this maps the Image's pixel type to the array index
        return ImageTypeToPixelIDValue< ImageType>::Result;
      }

    virtual unsigned int GetDimension( void ) { return ImageType::ImageDimension; }


    // Get Origin
    virtual double GetOrigin( unsigned int dimension ) const 
      {
      if ( dimension > ImageType::ImageDimension - 1 )
        {
        return 0;
        }

      return this->m_Image->GetOrigin()[dimension];
      }
    // Get Spacing
    virtual double GetSpacing( unsigned int dimension ) const 
      {
      if ( dimension > ImageType::ImageDimension - 1 )
        {
        return 0;
        }

      return this->m_Image->GetSpacing()[dimension];
      }

    virtual uint64_t GetSize( unsigned int dimension ) const
      {
        if ( dimension > ImageType::ImageDimension - 1 )
          {
          return 0;
          }

        typename ImageType::RegionType largestRegion = this->m_Image->GetLargestPossibleRegion();
        return largestRegion.GetSize(dimension);
      }

    std::string ToString( void ) const {
      std::ostringstream out;
      this->m_Image->Print ( out );
      return out.str();
    }

    PixelContainer::Pointer GetPixelContainer()
      {
        return this->GetPixelContainer<TImageType>();
      }

    template <typename UImageType>
    typename DisableIf<IsLabel<UImageType>::Value, PixelContainer::Pointer>::Type
    GetPixelContainer()
      {
        // note: this is the only file which includes
        // itkPixelContainer.txx, the following statement will
        // instantiate all needed implementations of the object
        PixelContainer::Pointer container =
          new PixelContainer( this->m_Image.GetPointer() );
        return container;
      }

    template <typename UImageType>
    typename EnableIf<IsLabel<UImageType>::Value, PixelContainer::Pointer>::Type
    GetPixelContainer()
      {
        return NULL;
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

    // assign to auto pointer
    this->m_PimpleImage = new PimpleImage<TImageType>( image );
  }

  template<class TImageType>
  typename EnableIf<IsBasic<TImageType>::Value>::Type
  Image::AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth )
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
    image->FillBuffer ( 0.0 );

    delete this->m_PimpleImage;
    this->m_PimpleImage = NULL;
    m_PimpleImage =  new PimpleImage<TImageType>( image );
  }

  template<class TImageType>
  typename EnableIf<IsVector<TImageType>::Value>::Type
  Image::AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth )
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
  Image::AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth )
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


  void Image::Allocate ( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum )
  {
      // Allocate an image

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

    Image::Image( uint64_t Width, uint64_t Height, PixelIDValueEnum ValueEnum )
      : m_PimpleImage( NULL )
    {
      Allocate ( Width, Height, 0, ValueEnum );
    }

    Image::Image( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum )
      : m_PimpleImage( NULL ){
      Allocate ( Width, Height, Depth, ValueEnum );
    }

    itk::DataObject::Pointer Image::GetImageBase( void )
    {
      assert( m_PimpleImage );
      return m_PimpleImage->GetDataBase();
    }

    itk::DataObject::ConstPointer Image::GetImageBase( void ) const
    {
      assert( m_PimpleImage );
      return m_PimpleImage->GetDataBase().GetPointer();
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

    std::string Image::ToString( void )
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->ToString();
    }

    uint64_t Image::GetWidth( void )
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetWidth();
    }

    uint64_t Image::GetHeight( void )
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetHeight();
    }

    uint64_t Image::GetDepth( void )
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetDepth();
    }

    PixelContainer::Pointer Image::GetPixelContainer()
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelContainer();
    }

    // Get Size
    std::vector< uint64_t > Image::GetSize( void )
    {
      std::vector< uint64_t > out;
      out.push_back( this->GetWidth() );
      out.push_back( this->GetHeight() );
      if (this->GetDimension() == 3 )
        {
        out.push_back( this->GetDepth() );
        }
      return out;
    }

    // Get Origin
    std::vector< double > Image::GetOrigin( void )
    {
      std::vector< double > out;
      out.push_back( this->m_PimpleImage->GetOrigin(0) );
      out.push_back( this->m_PimpleImage->GetOrigin(1) );
      if (this->GetDimension() == 3 )
        {
        out.push_back( this->m_PimpleImage->GetOrigin(2) );
        }
      return out;
    }

    // Get Spacing
    std::vector< double > Image::GetSpacing( void )
    {
      std::vector< double > out;
      out.push_back( this->m_PimpleImage->GetSpacing(0) );
      out.push_back( this->m_PimpleImage->GetSpacing(1) );
      if (this->GetDimension() == 3 )
        {
        out.push_back( this->m_PimpleImage->GetSpacing(2) );
        }
      return out;
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
