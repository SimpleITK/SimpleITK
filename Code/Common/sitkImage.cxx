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

    virtual std::vector<double> GetOrigin( void ) const = 0;
    virtual void SetOrigin( std::vector<double> orgn ) = 0;
    virtual std::vector<double> GetSpacing( void ) const = 0;
    virtual void SetSpacing( std::vector<double> spc ) = 0;

    virtual std::vector<unsigned int> TransformPhysicalPointToIndex( std::vector<double> pt) const = 0;
    virtual std::vector<double> TransformIndexToPhysicalPoint( std::vector<unsigned int> idx) const = 0;

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
    virtual std::vector<double> GetOrigin( void ) const
      {
      typename ImageType::PointType origin = this->m_Image->GetOrigin();
      std::vector<double> orgn;
      orgn.push_back(origin[0]);
      orgn.push_back(origin[1]);
      if (ImageType::ImageDimension == 3)
        {
        orgn.push_back(origin[2]);
        }
      return orgn;
      }

    // Set Origin
    virtual void SetOrigin( std::vector<double> orgn )
      {
      if (orgn.size() != ImageType::ImageDimension)
        {
        sitkExceptionMacro("Image::SetOrigin -> vector dimension mismatch");
        }
      typename ImageType::PointType origin;
      origin[0] = orgn[0];
      origin[1] = orgn[1];
      if (ImageType::ImageDimension == 3)
        {
        origin[2] = orgn[2];
        }
      this->m_Image->SetOrigin( origin );
      }

    // Get Spacing
    virtual std::vector<double> GetSpacing( void ) const
      {
      typename ImageType::SpacingType spacing = this->m_Image->GetSpacing();
      std::vector<double> spc;
      spc.push_back(spacing[0]);
      spc.push_back(spacing[1]);
      if (ImageType::ImageDimension == 3)
        {
        spc.push_back(spacing[2]);
        }
      return spc;
      }

    // Set Spacing
    virtual void SetSpacing( std::vector<double> spc )
      {
      if (spc.size() != ImageType::ImageDimension)
        {
        sitkExceptionMacro("Image::SetSpacing -> vector dimension mismatch");
        }
      typename ImageType::SpacingType spacing;
      spacing[0] = spc[0];
      spacing[1] = spc[1];
      if (ImageType::ImageDimension == 3)
        {
        spacing[2] = spc[2];
        }
      this->m_Image->SetSpacing( spacing );
      }

    // Physical Point to Index
    virtual std::vector<unsigned int> TransformPhysicalPointToIndex( std::vector<double> pt ) const
      {
      typename ImageType::PointType point;
      point[0] = pt[0];
      point[1] = pt[1];
      if (ImageType::ImageDimension == 3)
        {
        point[2] = pt[2];
        }
      typename ImageType::IndexType index;
      this->m_Image->TransformPhysicalPointToIndex(point, index);
      std::vector<unsigned int> idx;
      idx.push_back(index[0]);
      idx.push_back(index[1]);
      if (ImageType::ImageDimension == 3)
        {
        idx.push_back(index[2]);
        }
      return idx;
      }

    // Index to Physical Point
    virtual std::vector<double> TransformIndexToPhysicalPoint( std::vector<unsigned int> idx ) const
      {
      typename ImageType::IndexType index;
      index[0] = idx[0];
      index[1] = idx[1];
      if (ImageType::ImageDimension == 3)
        {
        index[2] = idx[2];
        }
      typename ImageType::PointType point;
      this->m_Image->TransformIndexToPhysicalPoint(index, point);
      std::vector<double> pt;
      pt.push_back(point[0]);
      pt.push_back(point[1]);
      if (ImageType::ImageDimension == 3)
        {
        pt.push_back(point[2]);
        }
      return pt;
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

    std::string ToString( void ) const
      {
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

    std::string Image::ToString( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->ToString();
    }

    uint64_t Image::GetWidth( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetWidth();
    }

    uint64_t Image::GetHeight( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetHeight();
    }

    uint64_t Image::GetDepth( void ) const
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetDepth();
    }

    PixelContainer::Pointer Image::GetPixelContainer()
    {
      assert( m_PimpleImage );
      return this->m_PimpleImage->GetPixelContainer();
    }

    // Get Origin
    std::vector< double > Image::GetOrigin( void ) const
    {
      return this->m_PimpleImage->GetOrigin();
    }

    // Set Origin
    void Image::SetOrigin( std::vector<double> orgn )
    {
      this->m_PimpleImage->SetOrigin(orgn);
    }

    // Get Spacing
    std::vector< double > Image::GetSpacing( void ) const
    {
      return this->m_PimpleImage->GetSpacing();
    }

    // Set Spacing
    void Image::SetSpacing( std::vector<double> spc )
    {
      this->m_PimpleImage->SetSpacing(spc);
    }

    // Index to Physical Point
    std::vector< double > Image::TransformIndexToPhysicalPoint( std::vector< unsigned int > idx ) const
    {
      return this->m_PimpleImage->TransformIndexToPhysicalPoint( idx );
    }

    // Physical Point to Index
    std::vector< unsigned int > Image::TransformPhysicalPointToIndex( std::vector< double > pt ) const
    {
      return this->m_PimpleImage->TransformPhysicalPointToIndex( pt );
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
