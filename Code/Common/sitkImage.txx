#ifndef __sitkImage_txx
#define __sitkImage_txx

#include "sitkImage.h"
#include "sitkPixelContainer.txx"
#include "sitkPixelIDTokens.h"

#if defined(__INTEL_COMPILER)
// disable warning for Intel Compiler:
//  class "itk::simple::Image::PimpleImageBase" (declared at line 97
//  of "Code/Common/sitkImage.h") is an inaccessible type (allowed for
//  cfront compatibility)
#pragma warning( disable 525 )
#endif


namespace itk
{
  namespace simple
  {

  template <class TImageType>
  class PimpleImage : public Image::PimpleImageBase
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

    virtual Image::PimpleImageBase *Clone( void ) const { return new Self(this->m_Image.GetPointer()); }
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

    PixelContainer::Pointer GetPixelContainer()
      {
        return this->GetPixelContainer<TImageType>();
      }

    template <typename UImageType>
    typename DisableIf<IsLabel<UImageType>::Value, PixelContainer::Pointer>::Type
    GetPixelContainer()
      {
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

  template <typename TImageType>
  Image::Image( itk::SmartPointer<TImageType> image )
    {
      // assign to auto pointer
    this->m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
    }

  template <typename TImageType>
  Image::Image( TImageType* image )
    {
    // assign to auto pointer
    this->m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
    }


  }
}


#endif
