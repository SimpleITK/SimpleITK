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
      Image ( SimpleImageBase::Pointer image, ImageDataType datatype );
      
      /**
       * Constructors for each supported pixel type (NOT DONE YET... WILL USE MACRO)
       */
      Image ( itk::Image<int,3>::Pointer image, ImageDataType datatype );
      
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
      
      /**
       * Pixel accessors for each pixel type
       */
      //template <class TPixelType>
      //TPixelType getPixel(int x, int y, int z);
      void getPixel(int x, int y, int z, float* out);
      //uint32_t getPixel(int x, int y, int z);
      
      
    private:
      SimpleImageBase::Pointer mImage;
      ImageDataType mDataType;
      
    };
  }
}

#endif
