#ifndef __sitkImage_h
#define __sitkImage_h

#include "sitkMacro.h"


namespace itk
{
namespace simple
{

class Image
  : public LightObject {
public:
  typedef Image              Self;
  typedef SmartPointer<Self> Pointer;

  template <typename TImageType>
  Image( typename TImageType::Pointer image )
    : m_Image( image )
    {
      // assign to auto pointer
      m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
    }
  template <typename TImageType>
  Image( TImageType* image )
    : m_Image( image )
    {
      // assign to auto pointer
      m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
    }

  // could return -1 if in valid
  SimpleImageBase::Pointer GetITKImage( void );

  ImageDataType GetImageDataType( void );

  uint64_t GetHeight( void );
  uint64_t GetWidth( void );
  uint64_t GetDepth( void );

  std::string ToString( void );

private:

  // Copying is not supported
  Image( const Image & ); // Not implemented
  Image &operator=( const Image & ); // Not implemented

  /// We utilize the private implementation ( or PImple)
  /// programming idiom to modify the behavior of the simple image
  /// class based on the different image types.
  ///
  /// This class is desinged to be utilize to have trivial copy,
  /// and assgnement operators
  struct PimpleImageBase
  {
    virtual ~PimpleImageBase( void ) {};
    virtual ImageDataType GetImageDataType(void) = 0;
  };

  template <class TImageType>
  struct PimpleImage
    : public PimpleImageBase
  {
    PimpleImage ( TImageType* image )
      {
        // verify that simpleITK supports this image type and dimension

        // this should be a STATIC ASSERT
        assert( TImageType::ImageDimension == 3 );


        // get the id of the pixel type
        typedef typename TImageType::PixelType PixelType;
        static const int id = typelist::IndexOf< InstantiatedPixelTypeList, PixelType >::Result;

        // THIS SHOULD BE A STATIC ASSERT
        assert(  id != -1 );
      }

    ImageDataType GetImageDataType(void) throw()
      {
        typedef typename TImageType::PixelType PixelType;

        // The constructor ensures that we have a valid image
        // this maps the Image's pixel type to the array index
        return typelist::IndexOf< InstantiatedPixelTypeList, PixelType>::Result;
      }

  };

  // utilize std::auto_ptr to per form automatic deletion on deconstruction
  std::auto_ptr< PimpleImageBase > m_PimpleImage;

  SimpleImageBase::Pointer m_Image;
};

}
}

#endif
