#ifndef __simpleImage_h
#define __simpleImage_h

#include <SimpleITKMacro.h>

namespace itk {
  namespace simple {
    class Image : public LightObject {
    public:
      typedef Image Self;
      typedef SmartPointer<Self> Pointer;

      Image ( SimpleImageBase::Pointer image, ImageDataType datatype );

      SimpleImageBase::Pointer getITKImage();
      ImageDataType getImageDataType();

      std::string toString();

    private:
      SimpleImageBase::Pointer mImage;
      ImageDataType mDataType;
      
    };
  }
}

#endif
