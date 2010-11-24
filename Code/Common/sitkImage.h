#ifndef __sitkImage_h
#define __sitkImage_h

#include "sitkMacro.h"

namespace itk
{
  namespace simple
  {

    class Image : public LightObject {
    public:
      typedef Image              Self;
      typedef SmartPointer<Self> Pointer;

  template <typename TImageType>
  Image( typename TImageType::Pointer image )
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
      ImageDataType GetDataType( void ) const;

      unsigned int GetDimension( void ) const;

      uint64_t GetHeight( void );
      uint64_t GetWidth( void );
      uint64_t GetDepth( void );

      std::string ToString( void );

    private:

      // Copying is not supported
      Image( const Image & ); // Not implemented
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

    virtual ImageDataType GetDataType(void) = 0;
    virtual unsigned int GetDimension( void ) = 0;

    virtual PimpleImageBase *Clone(void) const = 0;
    virtual itk::DataObject::Pointer GetDataBase( void ) = 0;
    virtual itk::DataObject::ConstPointer GetDataBase( void ) const = 0;

    virtual uint64_t GetWidth( void ) const { return this->GetSize( 0 ); }
    virtual uint64_t GetHeight( void ) const { return this->GetSize( 1 ); }
    virtual uint64_t GetDepth( void ) const { return this->GetSize( 2 ); }

    virtual uint64_t GetSize( unsigned int dimension ) const = 0;

  };

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
          // this should be a STATIC ASSERT
          assert( TImageType::ImageDimension == 3 );

        // get the id of the pixel type
        typedef typename TImageType::PixelType PixelType;
        // WARNING ABOUT UNUSED VARIABLE
        // static const int id = typelist::IndexOf< InstantiatedPixelTypeList, PixelType >::Result;

        // THIS SHOULD BE A STATIC ASSERT
        // WARNING ABOUT UNUSED VARIABLE
        //  assert(  id != -1 );
        }

    virtual PimpleImageBase *Clone( void ) const { return new Self(this->m_Image.GetPointer()); }
    virtual itk::DataObject::Pointer GetDataBase( void ) { return this->m_Image.GetPointer(); }
    virtual itk::DataObject::ConstPointer GetDataBase( void ) const { return this->m_Image.GetPointer(); }

    ImageDataType GetDataType(void) throw()
      {
        typedef typename TImageType::PixelType PixelType;

          // The constructor ensures that we have a valid image
          // this maps the Image's pixel type to the array index
          return typelist::IndexOf< InstantiatedPixelTypeList, PixelType>::Result;
        }

    virtual unsigned int GetDimension( void ) { return ImageType::ImageDimension; }

    virtual uint64_t GetSize( unsigned int dimension ) const
      {
        if ( dimension > ImageType::ImageDimension - 1 )
          {
          return 1;
          }

        typename ImageType::RegionType largestRegion = this->m_Image->GetLargestPossibleRegion();
        return largestRegion.GetSize(dimension);
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
