#ifndef __sitkImage_h
#define __sitkImage_h

#include "sitkMacro.h"

#include "itkImage.h"
#include "sitkPixelIDTypeLists.h"
#include "sitkMemberFunctionFactory.h"

namespace itk
{
  namespace simple
  {

    class Image : public LightObject {
    public:
      typedef Image              Self;
      typedef SmartPointer<Self> Pointer;

      Image( uint64_t Width, uint64_t Height, PixelIDValueEnum ValueEnum );
      Image( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum );

  template <typename TImageType>
  Image( itk::SmartPointer<TImageType> image )
    {
      // assign to auto pointer
      m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
    }
  template <typename TImageType>
  Image( TImageType* image )
    {
      // assign to auto pointer
      m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
    }

      itk::DataObject::Pointer GetImageBase( void );
      itk::DataObject::ConstPointer GetImageBase( void ) const;

      // could return -1 if in valid
      PixelIDValueType GetPixelIDValue( void ) const;

      unsigned int GetDimension( void ) const;

      uint64_t GetHeight( void );
      uint64_t GetWidth( void );
      uint64_t GetDepth( void );


      std::string GetPixelIDTypeAsString( void ) const;
      std::string ToString( void );

      typedef AllPixelIDTypeList PixelIDTypeList;
      typedef void (Self::*MemberFunctionType)( uint64_t Width, uint64_t Height, uint64_t Depth );

    protected:

      /** \brief Methods called by the constructor to allocate and initialize
       * an image.
       *
       * This method internally utlizes the member function factory to
       * dispatch to methods instantiated on the image of the pixel ID
       */
      void Allocate ( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum );

      /** \brief Dispatched methods for allocating images
       *
       * The enable if idiom is used here to enable different methods
       * for different pixe/image types.
       *
       * @{
       */
      template<class TImageType>
      typename EnableIf<IsBasic<TImageType>::Value>::Type
      AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth );

      template<class TImageType>
      typename EnableIf<IsVector<TImageType>::Value>::Type
      AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth );

      template<class TImageType>
      typename EnableIf<IsLabel<TImageType>::Value>::Type
      AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth );
      /**@}*/

      typedef detail::AllocateMemberFunctionAddressor<MemberFunctionType> AllocateAddressor;
      friend struct detail::AllocateMemberFunctionAddressor<MemberFunctionType>;

    private:

      // Copying is not supported
      Image &operator=( const Image & ); // Not implemented
      // For some reason, SWIG gets a little confused here, so don't let it see this code.
#ifndef SWIG

  /// We utilize the private implementation ( or PImple)
  /// programming idiom to modify the behavior of the simple image
  /// class based on the different image types.
  ///
  /// This class is desinged to be utilize to have trivial copy,
  /// and assgnement operators
  struct PimpleImageBase
  {
    virtual ~PimpleImageBase( void ) {};

    virtual PixelIDValueType GetPixelIDValue(void) = 0;
    virtual unsigned int GetDimension( void ) = 0;

    virtual PimpleImageBase *Clone(void) const = 0;
    virtual itk::DataObject::Pointer GetDataBase( void ) = 0;
    virtual itk::DataObject::ConstPointer GetDataBase( void ) const = 0;

    virtual uint64_t GetWidth( void ) const { return this->GetSize( 0 ); }
    virtual uint64_t GetHeight( void ) const { return this->GetSize( 1 ); }
    virtual uint64_t GetDepth( void ) const { return this->GetSize( 2 ); }

    virtual uint64_t GetSize( unsigned int dimension ) const = 0;
    virtual std::string ToString() const = 0;

  };

template <class TImageType> struct PimpleImage;

  template <class TImageType>
  struct PimpleImage
    : public PimpleImageBase
  {
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


  private:
    ImagePointer m_Image;
  };

    // utilize std::auto_ptr to perform automatic deletion on deconstruction
    std::auto_ptr< PimpleImageBase > m_PimpleImage;

#endif
  };
  }
}


#endif
