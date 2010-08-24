#ifndef __simpleImage_h
#define __simpleImage_h

#include <SimpleITKMacro.h>



namespace itk {
  namespace simple {

    class Image
      : public LightObject {
    public:
      typedef Image              Self;
      typedef SmartPointer<Self> Pointer;

      // could return -1 if in valid
      virtual SimpleImageBase::Pointer getITKImage();

      virtual int getImageDataType() = 0;

      unsigned long getHeight();
      unsigned long getWidth();
      unsigned long getDepth();

      std::string toString();
    protected:
      Image( SimpleImageBase::Pointer image );

    private:

      SimpleImageBase::Pointer mImage;
    };

  template <class TImageType>
  class ImageImplementation
    : public Image
  {
  public:
    typedef Image Self;
    typedef SmartPointer<Self> Pointer;

    typedef TImageType  ImageType;

    ImageImplementation ( typename ImageType::Pointer image)  : Image(image.GetPointer()) 
      {
        // THIS SHOULD BE A STATIC ASSERT
        assert( typelist::IndexOf< InstantiatedPixelTypeList >::Result != -1 );
      }


    virtual int getImageDataType(void)
    {
       typedef typename TImageType::PixelType PixelType;
       // could be -1 if type is not found
       // this maps the Image's pixel type to the array index
       return typelist::IndexOf< InstantiatedPixelTypeList, PixelType>::Result;
     }
  };


  }
}

#endif
