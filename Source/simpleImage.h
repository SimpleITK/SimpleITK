#ifndef __simpleImage_h
#define __simpleImage_h

#include <SimpleITKMacro.h>



namespace itk {
  namespace simple {

    class ImageBase
      : public LightObject {
    public:
      typedef ImageBase Self;
      typedef SmartPointer<Self> Pointer;

      ImageBase( SimpleImageBase::Pointer image );

      // could return -1 if in valid
      virtual SimpleImageBase::Pointer getITKImage();

      virtual int getImageDataType() = 0;

      unsigned long getHeight();
      unsigned long getWidth();
      unsigned long getDepth();

      std::string toString();

    private:

      SimpleImageBase::Pointer mImage;
    };

  template <class TImageType>
  class Image
    : public ImageBase
  {
  public:
    typedef Image Self;
    typedef SmartPointer<Self> Pointer;

    typedef TImageType  ImageType;

    Image ( typename ImageType::Pointer image)  : ImageBase(image.GetPointer()) {}


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
