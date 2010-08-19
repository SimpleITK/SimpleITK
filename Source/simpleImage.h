#ifndef __simpleImage_h
#define __simpleImage_h

#include <SimpleITKMacro.h>

namespace itk {
  namespace simple {
    
    /**
     * Non-templated base image class
     */
    class Image : public LightObject {
    
    public:
      //Image ( SimpleImageBase::Pointer image, ImageDataType datatype );
      
#define simpleImageDeclareConstructor(pixelType) \
      Image ( itk::Image<pixelType,3>::Pointer image, ImageDataType datatype );
      
      /**
       * Constructors for each supported pixel type
       */
      sitkRepeatForEachType( simpleImageDeclareConstructor );
      
      typedef Image Self;
      typedef SmartPointer<Self> Pointer;
      
      /**
       * Get a pointer to the itk::Image object
       */
      SimpleImageBase::Pointer getITKImage();
      
      /**
       * Get the image's pixel data type
       */
      ImageDataType getImageDataType();
      
      /**
       * Get the image's height
       */
      unsigned long getHeight();
      
      /**
       * Get the image's width
       */
      unsigned long getWidth();
      
      /**
       * Get the image's depth
       */
      unsigned long getDepth();
      
      /**
       * Print out a string representation of the image
       */
      std::string toString();
      
#define simpleImageDeclareGetPixel(pixelType) \
      void getPixel(int x, int y, int z, pixelType* out);
      /**
       * Pixel accessors for each pixel type
       */
      sitkRepeatForEachType(simpleImageDeclareGetPixel);
      
      
    private:
      SimpleImageBase::Pointer mImage;
      ImageDataType mDataType;
      
    };
  }
}

#endif
